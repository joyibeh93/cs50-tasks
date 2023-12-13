import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for

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
    # Get the user's ID from the session
    user_id = session["user_id"]

    # Retrieve the user's current cash balance
    user = db.execute("SELECT * FROM users WHERE id = ?", user_id)[0]
    cash_balance = user["cash"]

    # Retrieve the user's stock holdings and their current values
    holdings = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0",
        user_id,
    )

    # Calculate the total value of each stock holding and the grand total
    total_value = 0
    for holding in holdings:
        quote = lookup(holding["symbol"])
        holding["name"] = quote["name"]
        holding["price"] = quote["price"]
        holding["total_value"] = holding["total_shares"] * quote["price"]
        total_value += holding["total_value"]

    grand_total = cash_balance + total_value

    # Render the index template with the user's portfolio information
    return render_template(
        "index.html",
        holdings=holdings,
        cash_balance=cash_balance,
        grand_total=grand_total,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy stocks"""
    if request.method == "POST":
        # Ensure symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide stock symbol", 400)

        # Get the stock quote using the lookup function
        quote = lookup(symbol)

        # Render an apology if the symbol does not exist
        if not quote:
            return apology("invalid stock symbol", 400)

        # Ensure shares were submitted and are a positive integer
        try:
            shares = int(request.form.get("shares"))
            if shares <= 0:
                raise ValueError("shares must be a positive integer")
        except ValueError:
            return apology("shares must be a positive integer", 400)

        # Get the user's cash balance
        user_id = session["user_id"]
        user = db.execute("SELECT * FROM users WHERE id = ?", user_id)[0]
        cash_balance = user["cash"]

        # Calculate the total cost of the purchase
        total_cost = quote["price"] * shares

        # Render an apology if the user cannot afford the purchase
        if cash_balance < total_cost:
            return apology("insufficient funds", 400)

        # Record the purchase in the transactions table
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, transaction_type, timestamp) VALUES (?, ?, ?, ?, 'BUY', CURRENT_TIMESTAMP)",
            user_id,
            symbol,
            shares,
            quote["price"],
        )

        # Update the user's cash balance
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", cash_balance - total_cost, user_id
        )

        # Redirect the user to the home page
        return redirect(url_for("index"))
    else:
        # Render the buy form template for GET requests
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Get the user's ID from the session
    user_id = session["user_id"]

    # Retrieve the user's transaction history
    transactions = db.execute(
        "SELECT symbol, shares, price, transaction_type, timestamp FROM transactions WHERE user_id = ? ORDER BY timestamp DESC",
        user_id,
    )

    # Render the history template with the user's transaction history
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 400)

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
    """Get stock quote"""
    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol", 400)

        # Get the stock quote using the lookup function
        quote = lookup(request.form.get("symbol"))

        # Check if the stock symbol is valid
        if not quote:
            return apology("invalid stock symbol", 400)

        # Render the quoted template with the stock quote
        return render_template("quote.html", quote=quote)
    else:
        # Render the quote form template for GET requests with a default quote value
        default_quote = {"symbol": "", "name": "", "price": 0.0}
        return render_template("quote.html", quote=default_quote)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    if request.method == "POST":
        # Ensure username was submitted
        username = request.form.get("username")
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        password = request.form.get("password")
        if not password:
            return apology("must provide password", 400)

        # Ensure password confirmation was submitted
        confirmation = request.form.get("confirmation")
        if not confirmation:
            return apology("must confirm password", 400)

        # Ensure password and confirmation match
        if password != confirmation:
            return apology("passwords do not match", 400)

        # Check if the username already exists
        existing_user = db.execute("SELECT * FROM users WHERE username = ?", username)
        if existing_user:
            return apology("username already exists", 400)

        # Hash the password
        hashed_password = generate_password_hash(password)

        # Insert the new user into the "users" table
        result = db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            username,
            hashed_password,
        )

        # Log the user in after successful registration
        session["user_id"] = result

        # Redirect user to home page
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    if request.method == "POST":
        # Ensure stock symbol and shares were submitted
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("must select a stock", 400)
        if not shares or not shares.isdigit():
            return apology("must provide a valid number of shares", 400)

        shares = int(shares)

        # Get the user's current stock holdings
        holdings = db.execute(
            "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol",
            user_id,
            symbol,
        )

        if not holdings or holdings[0]["total_shares"] < shares:
            return apology("not enough shares to sell", 400)

        # Get the current price of the stock
        quote = lookup(symbol)

        if not quote:
            return apology("invalid stock symbol", 400)

        stock_price = quote["price"]
        sale_value = stock_price * shares

        # Record the sale in the transactions table
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, transaction_type, timestamp) VALUES (?, ?, ?, ?, 'SELL', CURRENT_TIMESTAMP)",
            user_id,
            symbol,
            shares,
            stock_price,
        )

        # Update the user's cash balance
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", sale_value, user_id)

        flash(f"Sale successful! Sale value: {usd(sale_value)}", "success")
        return redirect(url_for("index"))
    else:
        # Retrieve the user's stocks for the dropdown menu
        stocks = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0",
            user_id,
        )

        return render_template("sell.html", stocks=stocks)


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """Allow users to change their passwords"""
    if request.method == "POST":
        # Ensure old password, new password, and confirmation were submitted
        old_password = request.form.get("old_password")
        new_password = request.form.get("new_password")
        confirmation = request.form.get("confirmation")

        if not old_password or not new_password or not confirmation:
            return apology("all fields are required", 400)

        # Check if the old password is correct
        user_id = session["user_id"]
        user = db.execute("SELECT * FROM users WHERE id = ?", user_id)[0]

        if not check_password_hash(user["hash"], old_password):
            return apology("incorrect old password", 403)

        # Ensure new password and confirmation match
        if new_password != confirmation:
            return apology("new passwords do not match", 400)

        # Hash the new password
        hashed_password = generate_password_hash(new_password)

        # Update the user's password in the database
        db.execute("UPDATE users SET hash = ? WHERE id = ?", hashed_password, user_id)

        flash("Password changed successfully!", "success")
        return redirect("/")
    else:
        return render_template("change_password.html")
