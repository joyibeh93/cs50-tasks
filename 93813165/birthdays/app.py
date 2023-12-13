import os
from cs50 import SQL
from flask import Flask, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # Get user input from the form
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Validate that all fields are provided
        if not name or not month or not day:
            #flash("All fields are required", "error")
            return redirect("/")

        # TODO: Insert a new row into the "birthdays" table
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
        #flash("Birthday added successfully!", "success")

        return redirect("/")
    else:
        # Retrieve all entries from the database
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)

@app.route("/delete/<int:birthday_id>", methods=["POST"])
def delete_birthday(birthday_id):
     # TODO: Implement logic to delete the birthday entry with the given ID
    db.execute("DELETE FROM birthdays WHERE id = ?", birthday_id)
    #flash("Birthday deleted successfully!", "success")
    return redirect("/")

@app.route("/edit/<int:birthday_id>")
def edit_birthday(birthday_id):
    # TODO: Implement logic to retrieve the birthday entry with the given ID and render an edit form
    birthday = db.execute("SELECT * FROM birthdays WHERE id = ?", birthday_id)
    return render_template("edit.html", birthday=birthday)



@app.route("/update/<int:birthday_id>", methods=["POST"])
def update_birthday(birthday_id):
    # TODO: Implement logic to update the birthday entry with the given ID
    name = request.form.get("name")
    month = request.form.get("month")
    day = request.form.get("day")

    # Validate that all fields are provided
    if not name or not month or not day:
        #flash("All fields are required", "error")
        return redirect(f"/edit/{birthday_id}")

    # Update the entry in the database
    db.execute("UPDATE birthdays SET name = ?, birthdate = ? WHERE id = ?", name, f"{month} {day}", birthday_id)
    #flash("Birthday updated successfully!", "success")
    return redirect("/")



if __name__ == '__main__':
    app.run(debug=True)
