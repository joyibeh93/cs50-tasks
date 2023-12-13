-- Keep a log of any SQL queries you execute as you solve the mystery.

--Viewing the tables columns.
.schema crime_scene_reports

--understanding the content
SELECT * FROM crime_scene_reports
LIMIT 10

--
SELECT *
FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

--looking into the interview table to identify the witness
SELECT name, transcript
FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;

--.schema to view all related table inorder to get the column connecting licence_plate numbet 11J91FW

.schema

---looking through the people table where license plate is = 11J91FW to identify the owner
SELECT * FROM people
WHERE license_plate ='11J91FW';

---looking through the passenders table where passport number = 1095374669 to know his route
SELECT * FROM passengers
WHERE passport_number = 1095374669;

--Joining flights and Passengers table together to view all results
SELECT *
FROM flights
JOIN passengers ON flights.id = passengers.flight_id;

--Retrieving the origin airport id amd destination_airport_id
SELECT passengers.*, flights.origin_airport_id, flights.destination_airport_id
FROM flights
JOIN passengers ON flights.id = passengers.flight_id
WHERE passengers.passport_number = 1095374669;


SELECT *
FROM flights
WHERE year = 2021 AND month = 7 AND day = 28 AND destination_airport_id = 8;

SELECT * FROM airports
WHERE id = 5;

SELECT * FROM bank_accounts
WHERE person_id = 459;
