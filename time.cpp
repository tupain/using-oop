#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

const int NUM_HOSTELS = 2;
const int NUM_ROOMS_PER_HOSTEL = 10;

class Student {
public:
    string name;
    string mobileNumber;
    string address;
    string gender;
    time_t reservationDate;
    string roomnumber;

    Student(const string& n, const string& mobile, const string& addr, const string& gen, time_t date, const string& room)
        : name(n), mobileNumber(mobile), address(addr), gender(gen), reservationDate(date), roomnumber(room) {}
};

class HostelReservationSystem {
private:
    bool rooms[NUM_HOSTELS][NUM_ROOMS_PER_HOSTEL];
    vector<Student> reservations;

public:
    HostelReservationSystem() {
        // Initialize all rooms as available
        for (int i = 0; i < NUM_HOSTELS; ++i) {
            for (int j = 0; j < NUM_ROOMS_PER_HOSTEL; ++j) {
                rooms[i][j] = true;
            }
        }
    }

    void displayAvailableRooms() {
        cout << "Available Rooms:\n";
        for (int i = 0; i < NUM_HOSTELS; ++i) {
            cout << "Hostel " << (i + 1) << ": ";
            for (int j = 0; j < NUM_ROOMS_PER_HOSTEL; ++j) {
                if (rooms[i][j]) {
                    cout << setw(3) << (j + 1) << " ";
                }
            }
            cout << "\n";
        }
    }

    bool reserveRoom(const string& name, const string& mobile, const string& address,
                     const string& gender, int roomNumber) {
        int hostelNumber;
        if (gender == "boys") {
            hostelNumber = 1;
        } else if (gender == "girls") {
            hostelNumber = 2;
        } else {
            cout << "Invalid gender.\n";
            return false;
        }

        if (roomNumber < 1 || roomNumber > NUM_ROOMS_PER_HOSTEL) {
            cout << "Invalid room number.\n";
            return false;
        }

        if (rooms[hostelNumber - 1][roomNumber - 1]) {
            rooms[hostelNumber - 1][roomNumber - 1] = false;
            time_t now = time(0);
            reservations.emplace_back(name, mobile, address, gender, now, to_string(roomNumber));
            if (hostelNumber == 1) {
                cout << "Room reserved successfully for boys\n";
            } else if (hostelNumber == 2) {
                cout << "Room reserved successfully for girl\n";
            }
            return true;
        } else {
            cout << "Room is already reserved.\n";
            return false;
        }
    }

    bool cancelReservation(const string& name, const string& mobile, const string& gender) {
        for (auto it = reservations.begin(); it != reservations.end(); ++it) {
            if (it->name == name && it->mobileNumber == mobile && it->gender == gender) {
                int hostelNumber = (it->gender == "boys") ? 1 : 2;
                int roomNumber = stoi(it->roomnumber);

                rooms[hostelNumber - 1][roomNumber - 1] = true;
                reservations.erase(it);

                time_t now = time(0);
                struct tm* dt = localtime(&now);
                cout << "Reservation canceled successfully on " << setw(2) << dt->tm_mday << "/"
                     << setw(2) << (dt->tm_mon + 1) << "/" << (dt->tm_year + 1900) << "\n";
                return true;
            }
        }

        cout << "Reservation not found.\n";
        return false;
    }

    void displayReservations() {
        cout << "\nCurrent Reservations:\n";
        for (const auto& student : reservations) {
            int roomNumber = stoi(student.roomnumber);
            cout << "Room Number: " << roomNumber << "\n";
            cout << "Name: " << student.name << "\n";
            cout << "Mobile: " << student.mobileNumber << "\n";
            cout << "Address: " << student.address << "\n";
            cout << "Gender: " << student.gender << "\n";
            struct tm* dt = localtime(&student.reservationDate);
            cout << "Reservation Date: " << setw(2) << dt->tm_mday << "/"
                 << setw(2) << (dt->tm_mon + 1) << "/" << (dt->tm_year + 1900) << "\n";
            cout << "\n";
        }
    }
};

int main() {
    HostelReservationSystem hostelSystem;

    while (true) {
        cout << "\n1. Display available rooms\n";
        cout << "2. Reserve a room\n";
        cout << "3. Display reservations\n";
        cout << "4. Cancel a reservation\n";
        cout << "5. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hostelSystem.displayAvailableRooms();
                break;

            case 2: {
                string name, mobile, address, gender;
                int roomNumber;

                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, name);
                do{
                cout << "Enter your mobile number: ";
                cin >> mobile;
                }while(mobile.length()!=10);

                cout << "Enter your address: ";
                cin.ignore();
                getline(cin, address);

                cout << "Enter your gender (boys/girls): ";
                cin >> gender;

                cout << "Enter room number: ";
               
               cin >> roomNumber;
              
                hostelSystem.reserveRoom(name, mobile, address, gender, roomNumber);
                break;
            }

            case 3:
                hostelSystem.displayReservations();
                break;

            case 4: {
                string name, mobile, gender;

                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, name);

                cout << "Enter your mobile number: ";
                cin >> mobile;

                cout << "Enter your gender (boys/girls): ";
                cin >> gender;

                hostelSystem.cancelReservation(name, mobile, gender);
                break;
            }

            case 5:
                cout << "Exiting program.\n";
                return 0;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}