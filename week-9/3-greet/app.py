from flask import Flask, render_template, request

# little trick that says turn this file into a Flask application
app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/greet')
def greet():
    return render_template('greet.html', name=request.args.get("name", "Jager"))