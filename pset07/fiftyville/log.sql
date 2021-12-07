-- I solved this solution with my teammates: Helia Ashourizadeh, Mohammadreza Akhavan, Sahand Samiei

-- Finding the report of crime scene
SELECT description
FROM crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";
-- it happened in courthouse

-- checking the interviews about the courthouse
SELECT name, transcript
FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28 AND transcript LIKE "%courthouse%";
-- the thief did these actions: 1. withdrwed money from ATM, 2. Called someone less than a minute, 3. Drove away from parking lot, 4. flew with the earliest flight in next day


-- finding the thief trogh the data we have
SELECT DISTINCT(people.name)
FROM people
-- joning all databases together
JOIN phone_calls
    ON people.phone_number = phone_calls.caller
JOIN courthouse_security_logs
    ON people.license_plate = courthouse_security_logs.license_plate
JOIN passengers
    ON people.passport_number = passengers.passport_number
JOIN bank_accounts
    ON people.id = bank_accounts.person_id
JOIN atm_transactions
    ON bank_accounts.account_number = atm_transactions.account_number
-- Defining the conditions
WHERE
people.license_plate IN (
    -- checking security footages of the courthouse parking lot in 28 July 2020 from 10:15 to 10:26
    SELECT license_plate
    FROM courthouse_security_logs
    WHERE activity = "exit" and year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND (minute BETWEEN 15 AND 26)
    )
AND
people.phone_number IN (
    -- finding the calls less than a minute
    SELECT caller
    FROM phone_calls
    WHERE duration <60 and year = 2020 AND month = 7 AND day = 28
    )
AND
people.id IN (
    -- checking ATM footage on Fifer Street where the thief was withdrawing some money
    SELECT id
    from people
    WHERE transaction_type = "withdraw" and atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_location = "Fifer Street"
    )
AND
people.name IN (
    -- cross check names with people flew next day
    SELECT name
    FROM people
    WHERE flight_id = (
        -- fining earliest flight id
        SELECT id
        FROM flights
        WHERE day = 29 AND month = 7 AND year = 2020
        ORDER BY hour, minute
        LIMIT 1
        )
    )
;
-- Ernest is the thief.


-- finding the city Ernest escaped
SELECT city
FROM airports
WHERE id = (
    -- fining earliest flight id
    SELECT destination_airport_id
    FROM flights
    WHERE day = 29 AND month = 7 AND year = 2020
    ORDER BY hour, minute
    LIMIT 1
    );
-- Ernest flew to the London.

-- finding the accomplice
SELECT name
FROM people
-- joning all databases together
JOIN phone_calls
    ON people.phone_number = phone_calls.receiver
WHERE duration <60 and year = 2020 AND month = 7 AND day = 28 AND caller = (
    -- finding Ernest phone number
    SELECT phone_number
    FROM people
    WHERE name = "Ernest"
    )
;
-- Berthold is the accoumplice