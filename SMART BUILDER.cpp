#include <iostream>
#include <string>

using namespace std;

// Base class for rooms
class Room {
protected:
    string type;
    double area;
    int windows;
    int doors;

public:
    Room(const string& type, double area, int windows, int doors)
        : type(type), area(area), windows(windows), doors(doors) {}

    virtual double calculateCost() const = 0; // Pure virtual function

    void displayInfo() const {
        cout << "Type: " << type << "\nArea: " << area << " sq. m\nWindows: " << windows << "\nDoors: " << doors << endl;
    }

    double getArea() const {
        return area;
    }

    int getWindows() const {
        return windows;
    }

    int getDoors() const {
        return doors;
    }
};

// Derived classes for different types of rooms
class LivingRoom : public Room {
public:
    LivingRoom(double area, int windows, int doors)
        : Room("Living Room", area, windows, doors) {}

    double calculateCost() const override {
        return getArea() * 50 + getWindows() * 200 + getDoors() * 150; // Sample cost calculation
    }
};

class Kitchen : public Room {
public:
    Kitchen(double area, int windows, int doors)
        : Room("Kitchen", area, windows, doors) {}

    double calculateCost() const override {
        return getArea() * 70 + getWindows() * 200 + getDoors() * 150; // Sample cost calculation
    }
};

class GuestRoom : public Room {
public:
    GuestRoom(double area, int windows, int doors)
        : Room("Guest Room", area, windows, doors) {}

    double calculateCost() const override {
        return getArea() * 60 + getWindows() * 200 + getDoors() * 150; // Sample cost calculation
    }
};

// Warehouse class to manage available materials and their costs
class Warehouse {
private:
    const double cementCost = 10;   // Cost per bag of cement
    const double bricksCost = 0.5;  // Cost per piece of brick
    const double paintCost = 5;     // Cost per liter of paint

public:
    // Estimate materials required for construction based on area
    void estimateMaterials(double area) const {
        double cementRequired = area * 0.1; // 10% of area requires cement
        double bricksRequired = area * 2;    // 2 bricks per square meter
        double paintRequired = area * 0.05;  // 5% of area requires paint

        cout << "Estimated materials required:\n"
             << "Cement: " << cementRequired << " bags ($" << cementRequired * cementCost << ")\n"
             << "Bricks: " << bricksRequired << " pieces ($" << bricksRequired * bricksCost << ")\n"
             << "Paint: " << paintRequired << " liters ($" << paintRequired * paintCost << ")" << endl;
    }
};

// Base class for constructions
class Construction {
protected:
    string type;
    double area;
    Room* rooms[100]; // Fixed-size array for simplicity
    int roomCount;

public:
    Construction(const string& type, double area)
        : type(type), area(area), roomCount(0) {}

    virtual double calculateLabor() const = 0;
    virtual double calculateTime() const = 0;

    void addRoom(Room* room) {
        if (roomCount < 100) {
            rooms[roomCount++] = room;
        }
    }

    virtual void displayInfo() const {
        cout << "Construction Type: " << type << "\nArea: " << area << " sq. m\nNumber of Rooms: " << roomCount << endl;
        for (int i = 0; i < roomCount; ++i) {
            rooms[i]->displayInfo();
        }
        cout << "Total Room Cost: $" << getTotalRoomCost() << endl;
    }

    double getTotalRoomCost() const {
        double total = 0;
        for (int i = 0; i < roomCount; ++i) {
            total += rooms[i]->calculateCost();
        }
        return total;
    }

    virtual ~Construction() {
        for (int i = 0; i < roomCount; ++i) {
            delete rooms[i];
        }
    }
};

// Derived classes for different types of constructions
class House : public Construction {
private:
    string colorScheme;
    int numFloors;
    int garageSize;
    bool hasBalcony;

public:
    House(const string& type, double area)
        : Construction(type, area), colorScheme(""), numFloors(1), garageSize(0), hasBalcony(false) {
        while (true) {
            cout << "Enter house color scheme (alphabetic characters only): ";
            cin >> colorScheme;
            bool valid = true;

            // Check if each character is alphabetic
            for (int i = 0; i < colorScheme.length(); ++i) {
                char c = colorScheme[i];
                if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
                    valid = false;
                    break;
                }
            }

            if (valid) break; // Exit the loop if all characters are alphabetic
            else cout << "Invalid input. Please enter alphabetic characters only." << endl;
        }

        cout << "Enter number of floors: ";
        cin >> numFloors;

        cout << "Enter garage size (in cars): ";
        cin >> garageSize;

        cout << "Does the house have a balcony? (1 for Yes, 0 for No): ";
        cin >> hasBalcony;
    }

    double calculateLabor() const override {
        return area * 10; // Sample labor cost calculation
    }

    double calculateTime() const override {
        return area * 0.5; // Sample time calculation
    }

    void displayInfo() const override {
        Construction::displayInfo();
        cout << "House Color Scheme: " << colorScheme << "\nNumber of Floors: " << numFloors
             << "\nGarage Size: " << garageSize << " cars" << "\nHas Balcony: " << (hasBalcony ? "Yes" : "No") << endl;
        cout << "Estimated Labor Cost: $" << calculateLabor()
             << "\nEstimated Time Required: " << calculateTime() << " days"
             << "\nEstimated Cost: $" << (getTotalRoomCost() + area * 100) << endl;
    }
};

class Building : public Construction {
private:
    int numFloors;
    string colorScheme;

public:
    Building(const string& type, double area)
        : Construction(type, area), numFloors(1) {
        cout<< "Enter number of floors: ";
        cin >> numFloors;

        while (true) {
            cout << "Enter building color scheme (alphabetic characters only): ";
            cin >> colorScheme;
            bool valid = true;

            for (int i = 0; i < colorScheme.length(); ++i) {
                char c = colorScheme[i];
                if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
                    valid = false;
                    break;
                }
            }

            if (valid) break;
            else cout << "Invalid input. Please enter alphabetic characters only." << endl;
        }
    }

    double calculateLabor() const override {
        return area * 15; // Sample labor cost calculation
    }

    double calculateTime() const override {
        return area * 0.8; // Sample time calculation
    }

    void displayInfo() const override {
    Construction::displayInfo();
    cout << "Building Color Scheme: " << colorScheme << "\nNumber of Floors: " << numFloors << endl;
    cout << "Estimated Labor Cost: $" << calculateLabor()
         << "\nTotal Cost: $" << (getTotalRoomCost() + area * 200 + calculateLabor())
         << "\nEstimated Time Required: " << calculateTime() << " days" << endl;
}

};

// Main function
int main() {
    string constructionType;
    double area;
    char response;

    do {
        cout << "Enter the type of construction (House, Building): ";
        cin >> constructionType;

        if (constructionType != "House" && constructionType != "Building") {
            cout << "Invalid construction type entered." << endl;
            return 1;
        }

        do {
            if (constructionType == "House") {
                cout << "Enter the area to construct (in square meters, range: 50 - 500): ";
                cin >> area;

                if (area < 50 || area > 500) {
                    cout << "House area should be between 50 and 500 square meters." << endl;
                }
            } else if (constructionType == "Building") {
                cout << "Enter the area to construct (in square meters, range: 100 - 1000): ";
                cin >> area;

                if (area < 100 || area > 1000) {
                    cout << "Building area should be between 100 and 1000 square meters." << endl;
                }
            }
        } while ((constructionType == "House" && (area < 50 || area > 500)) ||
                 (constructionType == "Building" && (area < 100 || area > 1000)));

        // Create construction object based on user input
        Construction* construction;
        if (constructionType == "House") {
            construction = new House(constructionType, area);
        } else {
            construction = new Building(constructionType, area);
        }

        // Add rooms
        char addMoreRooms;
do {
    string roomType;
    int roomCount; // Variable to store the count of rooms of a particular type
    double roomArea;
    int windows, doors;

    cout << "Enter room type (LivingRoom, Kitchen, GuestRoom): ";
    cin >> roomType;

    cout << "Enter the number of " << roomType << "s: "; // Prompt for the number of rooms of this type
    cin >> roomCount;

    for (int i = 0; i < roomCount; ++i) {
        cout << "Enter details for " << roomType << " " << (i + 1) << ":" << endl;

        cout << "Enter room area (in square meters): ";
        cin >> roomArea;

        cout << "Enter number of windows: ";
        cin >> windows;

        cout << "Enter number of doors: ";
        cin >> doors;

        Room* room;
        if (roomType == "LivingRoom") {
            room = new LivingRoom(roomArea, windows, doors);
        } else if (roomType == "Kitchen") {
            room = new Kitchen(roomArea, windows, doors);
        } else if (roomType == "GuestRoom") {
            room = new GuestRoom(roomArea, windows, doors);
        } else {
            cout << "Invalid room type entered." << endl;
            delete construction;
            return 1;
        }

        construction->addRoom(room);
    }

    cout << "Do you want to add another type of room? (Y/N): ";
    cin >> addMoreRooms;
} while (addMoreRooms == 'Y' || addMoreRooms == 'y');

        // Create Warehouse object to estimate required materials
        Warehouse warehouse;
        warehouse.estimateMaterials(area);

        // Display construction info
        construction->displayInfo();

        // Ask user if they are satisfied with the plan
        cout << "Is this plan within your desired cost range? (Y/N): ";
        cin >> response;

        if (response == 'Y' || response == 'y') {
            cout << "Contract signed. Construction begins!" << endl;
            break; // Exit the loop after signing the contract
        } else {
            cout << "Would you like to try another plan? (Y/N): ";
            cin >> response;
        }

        delete construction;
    } while (response == 'Y' || response == 'y');

    cout << "Thank you for considering our services. Goodbye!" << endl;

    return 0;
}
