SELECT DISTINCT p.name
FROM people AS p
JOIN stars AS s ON p.id = s.person_id
JOIN movies AS m ON s.movie_id = m.id
JOIN people AS kevin_bacon ON kevin_bacon.name = 'Kevin Bacon' AND kevin_bacon.birth = 1958
WHERE m.id IN (
    SELECT movie_id
    FROM stars
    WHERE person_id = kevin_bacon.id
) AND p.name <> 'Kevin Bacon';
