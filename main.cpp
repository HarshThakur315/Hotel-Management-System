#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

struct Booking {
    int roomNo;
    string customer;
    int days;
    double rate;
};

const int MAX_BOOKINGS = 100;
Booking bookings[MAX_BOOKINGS];
int bookingCount = 0;

bool roomBooked(int roomNo) {
    for (int i = 0; i < bookingCount; i++)
        if (bookings[i].roomNo == roomNo) return true;
    return false;
}

void loadBookings() {
    ifstream in("bookings.txt");
    Booking b;
    while (bookingCount < MAX_BOOKINGS &&
           in >> b.roomNo >> quoted(b.customer) >> b.days >> b.rate) {
        bookings[bookingCount++] = b;
    }
}

void saveBookings() {
    ofstream out("bookings.txt");
    for (int i = 0; i < bookingCount; i++)
        out << bookings[i].roomNo << ' ' << quoted(bookings[i].customer)
            << ' ' << bookings[i].days << ' ' << bookings[i].rate << '\n';
}

void showRooms() {
    cout << "\n----------- AVAILABLE ROOMS -----------\n";
    for (int room = 101; room <= 110; room++)
        cout << "Room " << room << " : "
             << (roomBooked(room) ? "BOOKED" : "AVAILABLE") << '\n';
}

void bookRoom() {
    if (bookingCount >= MAX_BOOKINGS) {
        cout << "Booking limit reached.\n";
        return;
    }
    int room, days;
    string name;
    cout << "Enter room number (101-110): ";
    if (!(cin >> room)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
    if (room < 101 || room > 110) { cout << "Invalid room number.\n"; return; }
    if (roomBooked(room)) { cout << "Sorry, this room is already booked.\n"; return; }
    cout << "Enter customer name (use underscores instead of spaces): ";
    cin >> name;
    cout << "Enter number of days: ";
    if (!(cin >> days) || days <= 0) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Days must be positive.\n"; return; }

    double rate = 1500.0;
    bookings[bookingCount++] = {room, name, days, rate};
    saveBookings();
    cout << "Room booked successfully!\n";
    cout << "Estimated bill: Rs. " << fixed << setprecision(2) << days * rate << '\n';
}

void viewBookings() {
    cout << "\n------------- CUSTOMER BOOKINGS -------------\n";
    if (bookingCount == 0) { cout << "No bookings found.\n"; return; }
    cout << left << setw(12) << "Room" << setw(22) << "Customer"
         << setw(10) << "Days" << "Total Bill\n";
    for (int i = 0; i < bookingCount; i++)
        cout << left << setw(12) << bookings[i].roomNo
             << setw(22) << bookings[i].customer
             << setw(10) << bookings[i].days
             << "Rs. " << fixed << setprecision(2)
             << bookings[i].days * bookings[i].rate << '\n';
}

void cancelBooking() {
    int room;
    cout << "Enter room number to cancel: ";
    if (!(cin >> room)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].roomNo == room) {
            for (int j = i; j < bookingCount - 1; j++) bookings[j] = bookings[j + 1];
            bookingCount--;
            saveBookings();
            cout << "Booking cancelled successfully.\n";
            return;
        }
    }
    cout << "No booking found for that room.\n";
}

int main() {
    loadBookings();
    int choice;
    do {
        cout << "\n====================================\n";
        cout << "       HOTEL MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. View available rooms\n2. Book a room\n3. View customer bookings and bills\n4. Cancel a booking\n5. Exit\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Please enter a number.\n"; continue; }
        switch (choice) {
            case 1: showRooms(); break;
            case 2: bookRoom(); break;
            case 3: viewBookings(); break;
            case 4: cancelBooking(); break;
            case 5: saveBookings(); cout << "Thank you for choosing our hotel!\n"; break;
            default: cout << "Invalid choice. Select 1-5.\n";
        }
    } while (choice != 5);
    return 0;
}
