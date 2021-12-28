""" This project is collaboration of:
ALi Ganjizadeh (magnooj), Helia Ashourizadeh(Heliaaz), Mohammadreza Akhavan(Alien1808), Sahand Samiei()"""
import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
import requests
from functools import wraps
from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///inventory.db")


def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


@app.route("/")
def index():
    """Show inventory of drugs"""
    drugs = db.execute(
        "SELECT type, drugname, dose, SUM(quantity) as total, expiration FROM drugs GROUP BY drugname, dose, expiration ORDER BY drugname, dose, type DESC")

    return render_template("index.html", drugs=drugs)


@app.route("/buy", methods=["GET", "POST"])
def buy():
    """Buy some medicines"""
    if request.method == "POST":
        drugname = request.form.get("drugname").upper()
        type = request.form.get("type").upper()
        dose = request.form.get("dose")
        expiration = request.form.get("expiration")
        quantity = int(request.form.get("quantity"))
        company = request.form.get("company")

        if not drugname:
            return apology("Please enter a medicine!")
        elif not type:
            return apology("Please enter a type!")
        elif not dose:
            return apology("Please enter a dose!")
        elif not expiration:
            return apology("Please enter a expiration!")
        elif not quantity:
            return apology("Please enter a quantity!")


        if quantity <= 0:
            return apology("Amount must be positive number!")
        else:
            db.execute("INSERT INTO drugs (type, drugname, dose, expiration, quantity, inout) VALUES (?, ?, ?, ?, ?, ?)",
                       type, drugname, dose, expiration, quantity, "buy")

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT type, drugname, dose, expiration, quantity, service, man, problem, typeinjury, inout, time FROM drugs ORDER BY time DESC")

    return render_template("history.html", transactions=transactions)


@app.route("/sell", methods=["GET", "POST"])
def sell():
    """Sell medicines"""
    if request.method == "POST":
        drug = (request.form.get("drugname")).split(" / ")
        type = drug[0]
        drugname = drug[1]
        dose = drug[2]
        expiration = drug[3]
        quantity = int(request.form.get("quantity"))
        service = request.form.get("service")
        man = request.form.get("man")
        problem = request.form.get("problem")
        typeinjury = request.form.get("typeinjury")

        if quantity < 0:
            return apology("Medicines must be a positive number!")

        db.execute("INSERT INTO drugs (type, drugname, dose, expiration, quantity, service, man, problem, typeinjury, inout) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
                   type, drugname, dose, expiration, -quantity, service, man, problem, typeinjury, "sell")

        return redirect("/")
    else:
        drugs = db.execute("SELECT type, drugname, dose, SUM(quantity) as total, expiration FROM drugs GROUP BY drugname, dose, expiration ORDER BY drugname, dose, type, expiration")
        return render_template("sell.html", drugs=drugs)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
