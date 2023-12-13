import sqlite3
import csv

# Connect to the new database
conn = sqlite3.connect('roster.db')
cursor = conn.cursor()

# Read data from the CSV file
with open('students.csv', 'r') as csv_file:
    csv_reader = csv.reader(csv_file)
    next(csv_reader)  # Skip the header row if present

    for row in csv_reader:
        student_id, student_name, house, head = row

        # Check if the student with the same ID already exists in the database
        cursor.execute("SELECT id FROM students WHERE id = ?", (int(student_id),))
        existing_student = cursor.fetchone()

        if existing_student:
            print(f"Skipping duplicate student with ID {student_id}")
            continue  # Skip the insert for duplicate students

        # Insert data into the students table
        cursor.execute(
            "INSERT INTO students (id, student_name, house, head) VALUES (?, ?, ?, ?)",
            (int(student_id), student_name, house, head)
        )

        # Insert data into the houses table (if not already present)
        cursor.execute(
            "INSERT OR IGNORE INTO house (house, head) VALUES (?, ?)",
            (house, head)
        )

        # Retrieve the house_id from the houses table
        cursor.execute("SELECT id FROM houses WHERE house_name = ?", (house,))
        house_id = cursor.fetchone()[0]

        # Insert data into the house_assignment table
        cursor.execute(
            "INSERT INTO house_assignment (student_id, house_id) VALUES (?, ?)",
            (int(student_id), house_id)
        )

# Commit the changes and close the database connection
conn.commit()
conn.close()

