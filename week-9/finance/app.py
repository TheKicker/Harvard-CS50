import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Query the database to get the user's stocks and cash balance
    user_id = session["user_id"]
    rows = db.execute("""
        SELECT symbol, SUM(shares) as total_shares
        FROM transactions
        WHERE user_id = :user_id
        GROUP BY symbol
        HAVING total_shares > 0
    """, user_id=user_id)

    total_cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=user_id)[0]["cash"]

    # Iterate through the rows to get the information for each stock
    stocks = []
    total_portfolio_value = 0

    for row in rows:
        stock_info = lookup(row["symbol"])
        if stock_info:
            stock_price = stock_info["price"]
            total_value = stock_price * row["total_shares"]
            stocks.append({
                "symbol": row["symbol"],
                "shares": row["total_shares"],
                "price": usd(stock_price),
                "total_value": usd(total_value)
            })
            total_portfolio_value += total_value

    # Calculate the grand total (total portfolio value + cash balance)
    grand_total = total_portfolio_value + total_cash

    return render_template("index.html", stocks=stocks, cash=usd(total_cash), total_portfolio_value=usd(total_portfolio_value), grand_total=usd(grand_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    elif request.method == "POST":
        # Get user input from the form
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Validate user input
        if not symbol or not shares:
            return apology("Please provide both symbol and shares")

        # Ensure shares is a positive integer
        try:
            shares = int(shares)
            if shares <= 0:
                raise ValueError
        except ValueError:
            return apology("Shares must be a positive integer")

        # Lookup stock symbol to get the current price
        stock_info = lookup(symbol)
        if not stock_info:
            return apology("Symbol not found")

        stock_price = stock_info['price']
        total_price = stock_price * shares

        # Check if the user can afford the purchase
        user_cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"]
        if user_cash < total_price:
            return apology("You don't have enough cash to buy these shares homie")

        # Perform the purchase
        db.execute("UPDATE users SET cash = cash - :total_price WHERE id = :user_id",
                   total_price=total_price, user_id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
                   user_id=session["user_id"], symbol=symbol, shares=shares, price=stock_price)

        flash("Purchase successful for $" + str(total_price))
        return render_template("index.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute("SELECT * FROM transactions WHERE user_id = :user_id ORDER BY timestamp DESC", user_id=user_id)

    # Create a list to store transaction details
    transaction_list = []
    for transaction in transactions:
        if transaction["shares"] > 0:
            action = "Buy"
        else:
            action = "Sell"

        transaction_details = {
            "action": action,
            "symbol": transaction["symbol"],
            "price": usd(transaction["price"]),
            "shares": abs(transaction["shares"]),  # Take absolute value for number of shares
            "timestamp": transaction["timestamp"]
        }
        transaction_list.append(transaction_details)

    return render_template("history.html", transactions=transaction_list)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":
        symbol = request.form.get("symbol")
        price = lookup(symbol)

        if price is None:
            return apology("Err... Symbol not found... ")
        else:
            return render_template("quoted.html", symbol=symbol, price=price)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide password and confirmation", 400)

        # Ensure passwords match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Check if username already exists
        if len(rows) != 0:
            return apology("username already exists", 400)

        # Insert new user into database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                   request.form.get("username"), generate_password_hash(request.form.get("password")))

        # Redirect user to login page
        flash("Registered successfully. Please log in.")
        return redirect("/login")

    # If GET request, render registration form
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        # Fetch the user's owned stocks
        user_id = session["user_id"]
        stocks = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING SUM(shares) > 0", user_id=user_id)
        return render_template("sell.html", stocks=stocks)
    elif request.method == "POST":
        # Get user input from the form
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Validate user input
        if not symbol or not shares:
            return apology("Please select a stock and provide the number of shares")

        try:
            shares = int(shares)
            if shares <= 0:
                raise ValueError
        except ValueError:
            return apology("Shares must be a positive integer")

        # Check if the user owns the selected stock and has enough shares to sell
        user_id = session["user_id"]
        user_stock_shares = db.execute(
            "SELECT SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id AND symbol = :symbol GROUP BY symbol", user_id=user_id, symbol=symbol)
        if not user_stock_shares or user_stock_shares[0]["total_shares"] < shares:
            return apology("You don't own enough shares of this stock")

        # Lookup current stock price
        stock_info = lookup(symbol)
        if not stock_info:
            return apology("Symbol not found")

        stock_price = stock_info["price"]
        total_price = stock_price * shares

        # Update user's cash balance
        db.execute("UPDATE users SET cash = cash + :total_price WHERE id = :user_id",
                   total_price=total_price, user_id=user_id)

        # Record the transaction
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
                   user_id=user_id, symbol=symbol, shares=(-1 * shares), price=stock_price)

        flash("Shares sold successfully")
        return render_template("index.html")
