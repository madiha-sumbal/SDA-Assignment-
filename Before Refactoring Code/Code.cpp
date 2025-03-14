#include <iostream>
#include <cstring>

using namespace std;

// Welcome Message
void WelcomeScreen() {
    cout << "**** Welcome to XYZ Hospital Management System ****" << endl;
    cout << "[1] Hospital Services" << endl;
    cout << "[2] Cafe" << endl;
    cout << "[0] Exit" << endl;
}

// Hospital Section
class Hospital {
protected:
    static int capacity;
public:
    Hospital() { capacity = 500; }
    static void showCapacity() { cout << "Available Beds: " << capacity << endl; }
};
int Hospital::capacity;

class Patient : public Hospital {
    char name[50];
    int age, id;
public:
    void get() {
        cout << "Enter Name: "; cin >> name;
        cout << "Enter Age: "; cin >> age;
        cout << "Enter Patient ID: "; cin >> id;
        capacity--;
        cout << "Patient Registered. Remaining Beds: " << capacity << endl;
    }
    void show() {
        cout << "Patient Name: " << name << " | Age: " << age << " | ID: " << id << endl;
    }
};

// Cafe Section
class Cafe {
    float total;
public:
    Cafe() { total = 0; }
    void showMenu() {
        cout << "[1] Tea - Rs. 450" << endl;
        cout << "[2] Coffee - Rs. 550" << endl;
        cout << "[3] Sandwich - Rs. 600" << endl;
        cout << "[4] Cookie - Rs. 400" << endl;
        cout << "[0] Checkout" << endl;
    }
    void order() {
        int choice;
        do {
            showMenu();
            cout << "Select Item: "; cin >> choice;
            switch(choice) {
                case 1: total += 450; break;
                case 2: total += 550; break;
                case 3: total += 600; break;
                case 4: total += 400; break;
                case 0: break;
                default: cout << "Invalid Choice!" << endl;
            }
        } while(choice != 0);
        cout << "Total Bill: Rs. " << total << endl;
    }
};

int main() {
    int choice;
    do {
        WelcomeScreen();
        cout << "Enter Your Choice: "; cin >> choice;
        cout << endl;
        
        switch(choice) {
            case 1: {
                int subChoice;
                Patient p;
                do {
                    cout << "[1] Register Patient" << endl;
                    cout << "[2] View Capacity" << endl;
                    cout << "[0] Back to Main Menu" << endl;
                    cout << "Enter Choice: "; cin >> subChoice;
                    
                    if(subChoice == 1) p.get();
                    else if(subChoice == 2) Hospital::showCapacity();
                    else if(subChoice != 0) cout << "Invalid Choice!" << endl;
                    
                } while(subChoice != 0);
                break;
            }
            case 2: {
                Cafe c;
                c.order();
                break;
            }
            case 0:
                cout << "Exiting... Thank you!" << endl;
                break;
            default:
                cout << "Invalid Option! Try again." << endl;
        }
    } while(choice != 0);
    return 0;
}
