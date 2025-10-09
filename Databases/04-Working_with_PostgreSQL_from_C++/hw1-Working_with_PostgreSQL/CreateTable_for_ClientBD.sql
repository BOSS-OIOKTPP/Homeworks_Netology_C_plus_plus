CREATE TABLE IF NOT EXISTS client (
    client_id SERIAL PRIMARY KEY,
    first_name VARCHAR(50) NOT NULL,
    last_Name VARCHAR(50) NOT NULL,
    email VARCHAR(100) NOT NULL
);

CREATE TABLE IF NOT EXISTS phone_number (
    phone_number_id SERIAL PRIMARY KEY,
    client_id INTEGER REFERENCES client(client_id) ON DELETE CASCADE,
    number VARCHAR(20) NOT NULL
);