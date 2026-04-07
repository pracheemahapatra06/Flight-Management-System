# Flight Reservation System

This is a simple flight reservation system written in C. It allows users to view flights, book tickets, cancel bookings, update passenger information, and add new flights.

## Files

- `CSD_Project.c` - Main source code for the flight reservation system.
- `Flight_details.txt` - Stores the list of flights and their seat availability.
- `Passenger_details.txt` - Created and updated by the program to store passenger booking records.
- `Flight Management System CSD101 project report '28.pdf` - Project report file.

## Features

- View all available flights
- Book tickets for one or more passengers
- Cancel flight bookings by PNR
- Update existing passenger information
- View passengers for a selected flight
- Add a new flight using the admin code
- Persist flight and passenger data using text files

## How to build

Open a terminal in the project directory and run:

```sh
cc CSD_Project.c -o flight_system
```

If your system uses `gcc`, you can also run:

```sh
gcc CSD_Project.c -o flight_system
```

## How to run

```sh
./flight_system
```

The program will read from `Flight_details.txt` and may create or update `Passenger_details.txt` during use.

## Notes

- The admin code for adding flights is `20241129`.
- The program uses a PNR number starting from `234543`.
- `Flight_details.txt` is required for initial flight data.
- `Passenger_details.txt` is created automatically if it does not exist.

## Initial flight data

The current `Flight_details.txt` includes:

- Indigo: Hyderabad -> Delhi
- Vistara: Mumbai -> Bhubaneswar
- Vistara: Mumbai -> Guwahati
- Vistara: Chennai -> Ahmedabad
- Indigo: Chennai -> Bhubaneswar

Each flight starts with 20 seats available.
