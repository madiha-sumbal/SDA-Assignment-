#include <iostream>

using namespace std;

// Interface for Extendability
class IService {
public:
    virtual void execute() = 0;
    virtual ~IService() = default;
};

// Welcome Screen (UI Handler)
class WelcomeScreen {
public:
    static void display() {
        cout << "********** Welcome to XYZ Hospital Management System **********" << endl;
        cout << "[1] Hospital Services" << endl;
        cout << "[2] Cafe" << endl;
        cout << "[0] Exit" << endl;
    }
};

// Hospital Bed Management
class BedManager {
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
int BedManager::capacity = 500;

// Patient Management
class Patient {
private:
    string name;
    int age, id;
public:
    void registerPatient() {
        cout << "Enter Name: "; cin >> name;
        cout << "Enter Age: "; cin >> age;
        cout << "Enter Patient ID: "; cin >> id;

        if (BedManager::allocateBed()) {
            cout << "Patient Registered Successfully!" << endl;
        }
    }
};

// Hospital Services (Extensible via IService)
class HospitalService : public IService {
public:
    void execute() override {
        int subChoice;
        Patient patient;
        do {
            cout << "[1] Register Patient" << endl;
            cout << "[2] View Bed Capacity" << endl;
            cout << "[0] Back to Main Menu" << endl;
            cout << "Enter Choice: "; cin >> subChoice;

            if (subChoice == 1) patient.registerPatient();
            else if (subChoice == 2) BedManager::showCapacity();
            else if (subChoice != 0) cout << "Invalid Choice!" << endl;

        } while (subChoice != 0);
    }
};

// Cafe Menu (Using Array Instead of Vector)
class CafeMenu {
public:
    struct Item {
        string name;
        float price;
    };
    
    // Using Static Array Instead of Vector
    static const int menuSize = 4;
    static Item menu[menuSize];

    static void displayMenu() {
        for (int i = 0; i < menuSize; i++) {
            cout << "[" << i + 1 << "] " << menu[i].name << " - Rs. " << menu[i].price << endl;
        }
        cout << "[0] Checkout" << endl;
    }
};

// Initialize Cafe Menu Items
CafeMenu::Item CafeMenu::menu[CafeMenu::menuSize] = {
    {"Tea", 450},
    {"Coffee", 550},
    {"Sandwich", 600},
    {"Cookie", 400}
};

// Cafe Ordering System
class CafeOrder {
private:
    float total = 0;
public:
    void placeOrder() {
        int choice;

        do {
            CafeMenu::displayMenu();
            cout << "Select Item: "; cin >> choice;

            if (choice > 0 && choice <= CafeMenu::menuSize) {
                total += CafeMenu::menu[choice - 1].price;
            } else if (choice != 0) {
                cout << "Invalid Choice!" << endl;
            }

        } while (choice != 0);
        
        cout << "Total Bill: Rs. " << total << endl;
    }
};

// Cafe Service (Extensible)
class CafeService : public IService {
public:
    void execute() override {
        CafeOrder order;
        order.placeOrder();
    }
};

// Main System Controller (Extensible)
class HospitalManagementSystem {
private:
    IService* services[2]; // Using array instead of vector
public:
    HospitalManagementSystem() {
        services[0] = new HospitalService();
        services[1] = new CafeService();
    }

    ~HospitalManagementSystem() {
        delete services[0];
        delete services[1];
    }

    void run() {
        int choice;
        do {
            WelcomeScreen::display();
            cout << "Enter Your Choice: "; cin >> choice;
            cout << endl;

            if (choice > 0 && choice <= 2) {
                services[choice - 1]->execute();
            } else if (choice != 0) {
                cout << "Invalid Option! Try again." << endl;
            }
        } while (choice != 0);

        cout << "Exiting... Thank you!" << endl;
    }
};

// Entry Point
int main() {
    HospitalManagementSystem system;
    system.run();
    return 0;
}
