from flask import Flask, render_template, request

# little trick that says turn this file into a Flask application
app = Flask(__name__)

@app.route('/')
def index():
    if "name" in request.args:
        name = request.args["name"]
    else:
        name = "World"
    return render_template('index.html', name=name)

@app.route('/about.html')
def about():
    # the better way to handle parameters, 4 lines into 1
    # request looks for get parameter "name", returns world if none exist
    name = request.args.get("name", "World")
    return render_template('about.html', name=name)