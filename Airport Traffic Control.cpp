#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;


class Person {
protected:
    string name;
public:
    Person(const string& n) : name(n) {}
    virtual void displayInfo() const {
        cout << "Name: " << name << endl;
    }
    virtual ~Person() {}
};


class Dispatcher : public Person {
private:
    string employeeID;
    string shift;
    int age;
    string contact;
    string email;
public:
    Dispatcher(const string& n, const string& id, const string& s, int a, const string& c, const string& e)
        : Person(n), employeeID(id), shift(s), age(a), contact(c), email(e) {}

    void displayInfo() const override {
        cout << "\n--- Dispatcher Details ---\n";
        cout << "Name: " << name
             << "\nEmployee ID: " << employeeID
             << "\nShift: " << shift
             << "\nAge: " << age
             << "\nContact: " << contact
             << "\nEmail: " << email << endl;
    }
};


class Flight {
protected:
    string flightNumber;
    string airline;
    string gateNumber;
public:
    Flight(const string& f, const string& a, const string& g)
        : flightNumber(f), airline(a), gateNumber(g) {}
    virtual void displayStatus() const = 0;
    string getFlightNumber() const { return flightNumber; }
    virtual string getType() const = 0;
    virtual ~Flight() {}
};


class DepartingFlight : public Flight {
    string destination;
public:
    DepartingFlight(const string& f, const string& a, const string& g, const string& d)
        : Flight(f, a, g), destination(d) {}
    void displayStatus() const override {
        cout << left << setw(10) << "Departure"
             << " | Flight: " << setw(8) << flightNumber
             << " | Airline: " << setw(10) << airline
             << " | Gate: " << setw(5) << gateNumber
             << " | Destination: " << destination << endl;
    }
    string getType() const override { return "Departure"; }
};


class ArrivingFlight : public Flight {
    string origin;
public:
    ArrivingFlight(const string& f, const string& a, const string& g, const string& o)
        : Flight(f, a, g), origin(o) {}
    void displayStatus() const override {
        cout << left << setw(10) << "Arrival"
             << " | Flight: " << setw(8) << flightNumber
             << " | Airline: " << setw(10) << airline
             << " | Gate: " << setw(5) << gateNumber
             << " | Origin: " << origin << endl;
    }
    string getType() const override { return "Arrival"; }
};


class StalledFlight : public Flight {
    string reason;
    string location;
public:
    StalledFlight(const string& f, const string& a, const string& g, const string& r, const string& loc)
        : Flight(f, a, g), reason(r), location(loc) {}
    void displayStatus() const override {
        cout << left << setw(10) << "Stalled"
             << " | Flight: " << setw(8) << flightNumber
             << " | Airline: " << setw(10) << airline
             << " | Gate: " << setw(5) << gateNumber
             << " | Reason: " << reason
             << " | Location: " << location << endl;
    }
    string getType() const override { return "Stalled"; }
};


class AirportSystem {
private:
    Dispatcher dispatcher;
    vector<Flight*> flights;
public:
    AirportSystem(const Dispatcher& d) : dispatcher(d) {}

    void addFlight(Flight* f) {
        flights.push_back(f);
        cout << "✅ Flight added successfully.\n";
    }

    void showAllFlights() const {
        if (flights.empty()) {
            cout << "⚠️ No flights available.\n";
            return;
        }
        cout << "\n--- All Flights ---\n";
        for (auto f : flights) f->displayStatus();
    }

    void searchFlight(const string& fn) const {
        for (auto f : flights) {
            if (f->getFlightNumber() == fn) {
                cout << "\nFlight Found:\n";
                f->displayStatus();
                return;
            }
        }
        cout << "❌ Flight not found.\n";
    }

    void removeFlight(const string& fn) {
        for (auto it = flights.begin(); it != flights.end(); ++it) {
            if ((*it)->getFlightNumber() == fn) {
                delete *it;
                flights.erase(it);
                cout << "🗑️ Flight removed successfully.\n";
                return;
            }
        }
        cout << "❌ Flight not found.\n";
    }

    void showSummary() const {
        int dep = 0, arr = 0, stall = 0;
        for (auto f : flights) {
            string type = f->getType();
            if (type == "Departure") dep++;
            else if (type == "Arrival") arr++;
            else if (type == "Stalled") stall++;
        }
        cout << "\n--- Flight Summary ---\n";
        cout << "Departing: " << dep
             << " | Arriving: " << arr
             << " | Stalled: " << stall
             << " | Total: " << flights.size() << endl;
    }

    void showDispatcher() const {
        dispatcher.displayInfo();
    }

    ~AirportSystem() {
        for (auto f : flights) delete f;
    }
};


int main() {
    cout << "===== Airport Traffic Control & Dispatcher System =====\n";

    string name, id, shift, contact, email;
    int age;

    cout << "Enter Dispatcher Name: "; getline(cin, name);
    cout << "Enter Dispatcher ID: "; getline(cin, id);
    cout << "Enter Shift (Morning/Evening/Night): "; getline(cin, shift);
    cout << "Enter Age: "; cin >> age; cin.ignore();
    cout << "Enter Contact: "; getline(cin, contact);
    cout << "Enter Email: "; getline(cin, email);

    Dispatcher disp(name, id, shift, age, contact, email);
    AirportSystem system(disp);

    int choice;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Add Departing Flight\n";
        cout << "2. Add Arriving Flight\n";
        cout << "3. Add Stalled Flight\n";
        cout << "4. Show All Flights\n";
        cout << "5. Search Flight\n";
        cout << "6. Remove Flight\n";
        cout << "7. Show Summary\n";
        cout << "8. Show Dispatcher Info\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice; cin.ignore();

        if (choice == 1) {
            string fn, al, g, d;
            cout << "Flight Number: "; getline(cin, fn);
            cout << "Airline: "; getline(cin, al);
            cout << "Gate: "; getline(cin, g);
            cout << "Destination: "; getline(cin, d);
            system.addFlight(new DepartingFlight(fn, al, g, d));
        }
        else if (choice == 2) {
            string fn, al, g, o;
            cout << "Flight Number: "; getline(cin, fn);
            cout << "Airline: "; getline(cin, al);
            cout << "Gate: "; getline(cin, g);
            cout << "Origin: "; getline(cin, o);
            system.addFlight(new ArrivingFlight(fn, al, g, o));
        }
        else if (choice == 3) {
            string fn, al, g, r, l;
            cout << "Flight Number: "; getline(cin, fn);
            cout << "Airline: "; getline(cin, al);
            cout << "Gate: "; getline(cin, g);
            cout << "Reason: "; getline(cin, r);
            cout << "Location: "; getline(cin, l);
            system.addFlight(new StalledFlight(fn, al, g, r, l));
        }
        else if (choice == 4) system.showAllFlights();
        else if (choice == 5) {
            string fn; cout << "Enter Flight Number: "; getline(cin, fn);
            system.searchFlight(fn);
        }
        else if (choice == 6) {
            string fn; cout << "Enter Flight Number to remove: "; getline(cin, fn);
            system.removeFlight(fn);
        }
        else if (choice == 7) system.showSummary();
        else if (choice == 8) system.showDispatcher();
        else if (choice == 9) cout << "Exiting System... Goodbye!\n";
        else cout << "Invalid choice.\n";

    } while (choice != 9);

    return 0;
}