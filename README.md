# Hotel Management System (C++)

Console-based hotel management program with room availability, bookings, customer records, billing and file storage.

## Features
- View rooms 101–110 and their availability
- Book an available room
- View customer bookings and estimated bills
- Cancel a booking
- Save and load bookings using `bookings.txt`

## Compile and run
```bash
g++ main.cpp -o hotel
./hotel
```
Windows:
```bash
g++ main.cpp -o hotel.exe
.\hotel.exe
```

The program creates/updates `bookings.txt` in the working directory. Customer names are entered with underscores instead of spaces.

## Browser preview
Open `index.html` for a colourful interactive demonstration. The C++ source is `main.cpp`.
