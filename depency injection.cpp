#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Interface for Extendability (High-Level)
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

// Interface Segregation for Bed Management (Abstractions)
class IBedCapacity {
public:
    virtual void showCapacity() const = 0;
    virtual ~IBedCapacity() = default;
};

class IBedAllocator {
public:
    virtual bool allocateBed() = 0;
    virtual ~IBedAllocator() = default;
};

// Aggregated Interface
class IBedManager : public IBedCapacity, public IBedAllocator {};

// Concrete General Bed Manager
class GeneralBedManager : public IBedManager {
protected:
    int capacity;
public:
    GeneralBedManager(int cap) : capacity(cap) {}

    void showCapacity() const override {
        cout << "Available General Beds: " << capacity << endl;
    }

    bool allocateBed() override {
        if (capacity > 0) {
            capacity--;
            return true;
        } else {
            cout << "No general beds available!" << endl;
            return false;
        }
    }
};

// Specialized ICU Bed Manager
class ICUBedManager : public IBedManager {
protected:
    int icuBeds;
public:
    ICUBedManager(int icuCap) : icuBeds(icuCap) {}

    void showCapacity() const override {
        cout << "Available ICU Beds: " << icuBeds << endl;
    }

    bool allocateBed() override {
        if (icuBeds > 0) {
            icuBeds--;
            return true;
        } else {
            cout << "No ICU beds available!" << endl;
            return false;
        }
    }
};

// Dependency Injection in Patient Class
class Patient {
private:
    IBedAllocator& bedAllocator; // Dependency injected
public:
    Patient(IBedAllocator& allocator) : bedAllocator(allocator) {}

    void registerPatient() {
        cout << "Enter Name: "; cin >> name;
        cout << "Enter Age: "; cin >> age;
        cout << "Enter Patient ID: "; cin >> id;

        if (bedAllocator.allocateBed()) {
            cout << "Patient Registered Successfully!" << endl;
        }
    }
};


// Hospital Services Implementing DIP
class HospitalService : public IService {
private:
    IBedManager& bedManager; // Dependency injected
public:
    HospitalService(IBedManager& manager) : bedManager(manager) {}

    void execute() override {
        int subChoice;
        Patient patient(bedManager); // Injecting dependency again
        do {
            cout << "[1] Register Patient" << endl;
            cout << "[2] View Bed Capacity" << endl;
            cout << "[0] Back to Main Menu" << endl;
            cout << "Enter Choice: "; cin >> subChoice;

            if (subChoice == 1) patient.registerPatient();
            else if (subChoice == 2) bedManager.showCapacity();
            else if (subChoice != 0) cout << "Invalid Choice!" << endl;

        } while (subChoice != 0);
    }
};


// Cafe Menu
class CafeMenu {
public:
    struct Item {
        string name;
        float price;
    };

    static vector<Item> menu;

    static void displayMenu() {
        for (size_t i = 0; i < menu.size(); i++) {
            cout << "[" << i + 1 << "] " << menu[i].name << " - Rs. " << menu[i].price << endl;
        }
        cout << "[0] Checkout" << endl;
    }
};

// Initialize Cafe Menu
vector<CafeMenu::Item> CafeMenu::menu = {
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

            if (choice > 0 && choice <= CafeMenu::menu.size()) {
                total += CafeMenu::menu[choice - 1].price;
            } else if (choice != 0) {
                cout << "Invalid Choice!" << endl;
            }

        } while (choice != 0);
        
        cout << "Total Bill: Rs. " << total << endl;
    }
};

// Cafe Service Implementing IService
class CafeService : public IService {
public:
    void execute() override {
        CafeOrder order;
        order.placeOrder();
    }
};

// Hospital Management System with Dependency Injection
class HospitalManagementSystem {
private:
    vector<unique_ptr<IService>> services; // Stores a list of service objects
public:
    HospitalManagementSystem(vector<unique_ptr<IService>> serviceList) 
        : services(move(serviceList)) {} // Moves the ownership of serviceList
};

    void run() {
        int choice;
        do {
            WelcomeScreen::display();
            cout << "Enter Your Choice: "; cin >> choice;
            cout << endl;

            if (choice > 0 && choice <= services.size()) {
                services[choice - 1]->execute();
            } else if (choice != 0) {
                cout << "Invalid Option! Try again." << endl;
            }
        } while (choice != 0);

        cout << "Exiting... Thank you!" << endl;
    }
};

// Main Entry with Dependency Injection
int main() {
    unique_ptr<IBedManager> bedManager = make_unique<GeneralBedManager>(500); // Create dependency

    vector<unique_ptr<IService>> services;
    services.push_back(make_unique<HospitalService>(*bedManager)); // Inject dependency
    services.push_back(make_unique<CafeService>());

    HospitalManagementSystem system(move(services)); // Inject services
    system.run();
    return 0;
}
