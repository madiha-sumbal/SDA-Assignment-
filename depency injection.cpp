#include <iostream>
#include <vector>
#include <memory>
#include <juice/juice.h> // Google Juice for Dependency Injection

using namespace std;
using namespace juice;

// Interface for Extendability (High-Level)
class IService {
public:
    virtual void execute() = 0;
    virtual ~IService() = default;
};

// Bed Management Interfaces
class IBedAllocator {
public:
    virtual bool allocateBed() = 0;
    virtual ~IBedAllocator() = default;
};

class IBedCapacity {
public:
    virtual void showCapacity() const = 0;
    virtual ~IBedCapacity() = default;
};

class IBedManager : public IBedAllocator, public IBedCapacity {};

// Concrete General Bed Manager
class GeneralBedManager : public IBedManager {
private:
    int capacity;
public:
    GeneralBedManager(int cap) : capacity(cap) {}
    void showCapacity() const override { cout << "Available General Beds: " << capacity << endl; }
    bool allocateBed() override {
        if (capacity > 0) { capacity--; return true; }
        cout << "No general beds available!" << endl;
        return false;
    }
};

// Dependency Injection for BedManager
class BedModule : public juice::AbstractModule {
public:
    void configure() override {
        bind<IBedManager>().to<GeneralBedManager>().in<Singleton>();
    }
};

// Patient Class
class Patient {
private:
    IBedAllocator& bedAllocator;
public:
    Patient(IBedAllocator& allocator) : bedAllocator(allocator) {}
    void registerPatient() {
        string name;
        cout << "Enter Name: "; cin >> name;
        if (bedAllocator.allocateBed()) {
            cout << "Patient Registered Successfully!" << endl;
        }
    }
};

// Hospital Service
class HospitalService : public IService {
private:
    IBedManager& bedManager;
public:
    HospitalService(IBedManager& manager) : bedManager(manager) {}
    void execute() override {
        Patient patient(bedManager);
        patient.registerPatient();
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

// Cafe Service
class CafeService : public IService {
public:
    void execute() override {
        CafeOrder order;
        order.placeOrder();
    }
};

// Service Injection Module
class ServiceModule : public juice::AbstractModule {
public:
    void configure() override {
        bind<IService>().to<HospitalService>();
        bind<IService>().to<CafeService>();
    }
};

// Main System
class HospitalManagementSystem {
private:
    vector<unique_ptr<IService>> services;
public:
    HospitalManagementSystem(vector<unique_ptr<IService>> svcList) : services(move(svcList)) {}
    void run() {
        for (auto& service : services) {
            service->execute();
        }
    }
};

int main() {
    Injector injector(make_unique<BedModule>(), make_unique<ServiceModule>());
    auto hospitalService = injector.getInstance<IService>();
    auto cafeService = injector.getInstance<IService>();
    vector<unique_ptr<IService>> services;
    services.push_back(move(hospitalService));
    services.push_back(move(cafeService));
    HospitalManagementSystem system(move(services));
    system.run();
    return 0;
}
