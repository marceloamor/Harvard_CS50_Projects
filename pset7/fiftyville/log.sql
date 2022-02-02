-- Keep a log of any SQL queries you execute as you solve the mystery.
.schema
--See what the crime scene reports were like on the day
SELECT day, month, street, description FROM crime_scene_reports where month > 6 and day > 27;
--See what the transcripts of each interview were like on the day
SELECT name, transcript FROM interviews WHERE month > 6 and day > 27;
--Get list of license plates that fit the description from interview
SELECT license_plate, activity, hour, minute FROM courthouse_security_logs WHERE month = 7 and day = 28 and hour = 10 and year = "2020";
--Get list of accounts that made an atm transaction that fit the description from interview
SELECT account_number, transaction_type, atm_location FROM atm_transactions WHERE month = 7 AND day = 28 and year = "2020" and transaction_type = "withdraw" and atm_location = "Fifer Street";
--Get list of person IDs that fit the description of the atm transaction
SELECT person_id FROM bank_accounts WHERE account_number IN (
    SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 and year = "2020" and transaction_type = "withdraw" and atm_location = "Fifer Street");
--Find earliest flight out of fiftyville, its ID and destination
SELECT id, destination_airport_id, hour, minute FROM flights WHERE month = 7 AND day = 29 AND origin_airport_id IN (
    SELECT id FROM airports WHERE city = "Fiftyville");
--Find destination city of the flight the thief was on
SELECT airports.city FROM airports JOIN flights ON flights.destination_airport_id = airports.id WHERE flights.destination_airport_id = 4;
--List of phone numbers that made a eligible call
SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60;
--Get a list of passengers on the suspect flight
SELECT passport_number FROM passengers WHERE flight_id = 36;
--Find out the thief
SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60)
    AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 and day = 28 and hour = 10 AND minute > 15 AND minute < 25 AND year = "2020")
    AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (
        SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 and year = "2020" and transaction_type = "withdraw" and atm_location = "Fifer Street"))
    AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);
--Find the accomplice
SELECT name FROM people WHERE phone_number IN (
    SELECT receiver FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60 AND caller IN (
        SELECT phone_number FROM people WHERE name = "Ernest"));