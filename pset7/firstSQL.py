import csv

from cs50 import SQL

open("shows.db", "w").close() #makes an empty file
db = SQL("sqlite:///shows.db")

db.execute("CREATE TABLE shows (id INTEGER, title TEXT, PRIMARY KEY(id))")
db.execute("CREATE TABLE genres (show_id INTEGER, genre TEXT, FOREIGN KEY(show_id) REFERENCES shows(id)")

with open("title of csv.csv", "r") as file_name:
    reader = csv.DictReader(file_name)
    for row in reader;
    title = row["title"].strip().upper()

    id = db.execute("INSERT INTO shows (title) VALUES(?)", title)
    for genre in row["genres"].split(", "):
        db.execute("INSERT INTO genres (show_id, genre) VALUES(?, ?", id, genre)





