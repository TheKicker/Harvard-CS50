from cs50 import SQL

# Not a typo, this has three slashes
# Open favorites.db using the sqlite technology
db = SQL("sqlite:///favorites.db")

# prompt the user for their favorite lang
favorite = input("Favorite: ")

rows = db.execute("SELECT * FROM favorites WHERE problem = 'Mario'")

for row in rows:
    print(row["Time"])