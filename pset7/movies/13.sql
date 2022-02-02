SELECT people.name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE movies.id IN (
SELECT movies.id FROM movies
JOIN people ON people.id = stars.person_id
JOIN stars ON stars.movie_id = movies.id
WHERE people.name = "Kevin Bacon"
)
AND people.name != "Kevin Bacon";