SELECT AVG(r.rating) AS average_rating
FROM movies AS m
JOIN ratings AS r ON m.id = r.movie_id
WHERE m.year = 2012;

-- SELECT  * FROM movies
-- WHERE year = 2012 AND movie_id=
-- (SELECT movie_id FROM ovies WHERE year = 2012);
