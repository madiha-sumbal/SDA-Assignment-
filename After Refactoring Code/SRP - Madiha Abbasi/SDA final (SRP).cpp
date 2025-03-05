#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// Welcome Screen (Separate Responsibility)
void WelcomeScreen() {
    cout << "********** Welcome to XYZ Hospital Management System **********" << endl;
    cout << "[1] Hospital Services" << endl;
    cout << "[2] Cafe" << endl;
    cout << "[0] Exit" << endl;
}

// Hospital Capacity Management (SRP: Only Manages Bed Availability)
class Hospital {
private:
    static int capacity;
public:
    static void showCapacity() { 
        cout << "Available Beds: " << capacity << endl; 
    }
    static bool allocateBed() {
        if (capacity > 0) {
            capacity--;
            return true;
        } else {
            cout << "No beds available!" << endl;
            return false;
        }
    }
};
int Hospital::capacity = 500;

// Patient Management (SRP: Only Manages Patient Data)
class Patient {
private:
    char name[50];
    int age, id;
public:
    void registerPatient() {
        cout << "Enter Name: "; cin >> name;
        cout << "Enter Age: "; cin >> age;
        cout << "Enter Patient ID: "; cin >> id;

        if (Hospital::allocateBed()) {
            cout << "Patient Registered Successfully!" << endl;
        }
    }
    void showDetails() const {
        cout << "Patient Name: " << name << " | Age: " << age << " | ID: " << id << endl;
    }
};

// Hospital Services Handler (SRP: Manages Interaction with Patients)
class HospitalService {
public:
    void manageHospital() {
        int subChoice;
        Patient patient;
        do {
            cout << "[1] Register Patient" << endl;
            cout << "[2] View Capacity" << endl;
            cout << "[0] Back to Main Menu" << endl;
            cout << "Enter Choice: "; cin >> subChoice;

            if (subChoice == 1) patient.registerPatient();
            else if (subChoice == 2) Hospital::showCapacity();
            else if (subChoice != 0) cout << "Invalid Choice!" << endl;

        } while (subChoice != 0);
    }
};

// Cafe Menu Management (SRP: Only Holds Menu Data)
class CafeMenu {
public:
    struct Item {
        string name;
        float price;
    };
    static vector<Item> getMenu() {
        return {
            {"Tea", 450},
            {"Coffee", 550},
            {"Sandwich", 600},
            {"Cookie", 400}
        };
    }
    static void displayMenu() {
        vector<Item> menu = getMenu();
        for (size_t i = 0; i < menu.size(); ++i) {
            cout << "[" << i + 1 << "] " << menu[i].name << " - Rs. " << menu[i].price << endl;
        }
        cout << "[0] Checkout" << endl;
    }
};

// Cafe Ordering System (SRP: Manages Orders Only)
class CafeOrder {
private:
    float total = 0;
public:
    void placeOrder() {
        int choice;
        vector<CafeMenu::Item> menu = CafeMenu::getMenu();

        do {
            CafeMenu::displayMenu();
            cout << "Select Item: "; cin >> choice;

            if (choice > 0 && choice <= menu.size()) {
                total += menu[choice - 1].price;
            } else if (choice != 0) {
                cout << "Invalid Choice!" << endl;
            }

        } while (choice != 0);
        
        cout << "Total Bill: Rs. " << total << endl;
    }
};

// Cafe Service Manager (SRP: Handles Cafe Interaction)
class CafeService {
public:
    void manageCafe() {
        CafeOrder order;
        order.placeOrder();
    }
};

// Main System Controller (SRP: Controls the Program Flow)
class HospitalManagementSystem {
public:
    void run() {
        int choice;
        HospitalService hospitalService;
        CafeService cafeService;

        do {
            WelcomeScreen();
            cout << "Enter Your Choice: "; cin >> choice;
            cout << endl;

            switch (choice) {
                case 1: hospitalService.manageHospital(); break;
                case 2: cafeService.manageCafe(); break;
                case 0: cout << "Exiting... Thank you!" << endl; break;
                default: cout << "Invalid Option! Try again." << endl;
            }
        } while (choice != 0);
    }
};

// Entry Point
int main() {
    HospitalManagementSystem system;
    system.run();
    return 0;
}

