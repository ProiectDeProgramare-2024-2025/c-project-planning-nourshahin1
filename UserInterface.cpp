#include "UserInterface.h"
#include <iostream>
#include <limits>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"

UserInterface::UserInterface(PropertyManager& mgr) : manager(mgr) {}

void UserInterface::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void UserInterface::pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int UserInterface::readInteger(const std::string& prompt) {
    int num;
    std::cout << GREEN << prompt << RESET;
    while (!(std::cin >> num)) {
        std::cout << RED << "Invalid input! Please enter a number: " << RESET;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return num;
}

std::string UserInterface::readString(const std::string& prompt) {
    std::string input;
    std::cout << GREEN << prompt << RESET;
    std::getline(std::cin, input);
    return input;
}

void UserInterface::header() {
    std::cout << CYAN << "-------------------------" << RESET << std::endl;
    std::cout << GREEN << "1. View Properties" << RESET << std::endl;
    std::cout << GREEN << "2. Favorites" << RESET << std::endl;
    std::cout << GREEN << "3. Purchase Property" << RESET << std::endl;
    std::cout << GREEN << "4. Add Property" << RESET << std::endl;
    std::cout << GREEN << "5. Exit" << RESET << std::endl;
    std::cout << CYAN << "-------------------------" << RESET << std::endl;
}

void UserInterface::viewProperties() {
    clearScreen();
    std::cout << CYAN << "===== Available Properties =====" << RESET << std::endl;
    const auto& props = manager.getProperties();

    if (props.empty()) {
        std::cout << RED << "No properties available." << RESET << std::endl;
    } else {
        for (size_t i = 0; i < props.size(); i++) {
            props[i].display(i);
        }
    }
    pause();
}

void UserInterface::manageFavorites() {
    clearScreen();
    std::cout << CYAN << "===== Favorite Properties =====" << RESET << std::endl;
    const auto& favs = manager.getFavorites();

    if (favs.empty()) {
        std::cout << RED << "No favorites added yet." << RESET << std::endl;
    } else {
        for (size_t i = 0; i < favs.size(); i++) {
            favs[i].display(i);
        }
    }

    const auto& props = manager.getProperties();
    if (props.empty()) {
        std::cout << RED << "No properties to add to favorites." << RESET << std::endl;
        pause();
        return;
    }

    int choice = readInteger("\nEnter property number to add to favorites (1-" + 
                             std::to_string(props.size()) + "): ") - 1;

    if (choice >= 0 && static_cast<size_t>(choice) < props.size() && manager.addToFavorites(choice)) {
        std::cout << GREEN << "Property added to favorites." << RESET << std::endl;
    } else {
        std::cout << RED << "Invalid selection." << RESET << std::endl;
    }
    pause();
}

void UserInterface::purchaseProperty() {
    clearScreen();
    const auto& props = manager.getProperties();

    if (props.empty()) {
        std::cout << RED << "No properties available for purchase." << RESET << std::endl;
        pause();
        return;
    }

    int choice = readInteger("Enter property number to purchase (1-" + 
                             std::to_string(props.size()) + "): ") - 1;

    if (choice >= 0 && static_cast<size_t>(choice) < props.size() && manager.purchaseProperty(choice)) {
        std::cout << GREEN << "You have successfully purchased the property." << RESET << std::endl;
        manager.savePropertiesToFile();
    } else {
        std::cout << RED << "Invalid selection." << RESET << std::endl;
    }
    pause();
}

void UserInterface::addProperty() {
    clearScreen();
    std::cout << CYAN << "===== Add New Property =====" << RESET << std::endl;

    Property newProp;
    std::string input;
    int num;
    bool valid;

    do {
        input = readString("Enter property name: ");
        valid = newProp.setName(input);
        if (!valid) std::cout << RED << "Invalid name. Use only letters and max 3 words." << RESET << std::endl;
    } while (!valid);

    do {
        input = readString("Enter address: ");
        valid = newProp.setAddress(input);
        if (!valid) std::cout << RED << "Invalid address. Start with a number followed by 2 words." << RESET << std::endl;
    } while (!valid);

    do {
        num = readInteger("Enter price: ");
        valid = newProp.setPrice(num);
        if (!valid) std::cout << RED << "Price must have at most 6 digits." << RESET << std::endl;
    } while (!valid);

    do {
        num = readInteger("Enter size in sqm: ");
        valid = newProp.setSize(num);
        if (!valid) std::cout << RED << "Size must have at most 3 digits." << RESET << std::endl;
    } while (!valid);

    num = readInteger("Enter number of rooms: ");
    newProp.setRooms(num);

    num = readInteger("Enter number of bathrooms: ");
    newProp.setBathrooms(num);

    do {
        num = readInteger("Enter parking (1 for yes, 0 for no): ");
        valid = (num == 0 || num == 1);
        if (!valid) std::cout << RED << "Parking must be 1 or 0." << RESET << std::endl;
    } while (!valid);
    newProp.setParking(num != 0);

    if (manager.addProperty(newProp)) {
        std::cout << GREEN << "Property added successfully!" << RESET << std::endl;
        manager.savePropertiesToFile();
    }
    pause();
}

void UserInterface::menu(int option) {
    switch (option) {
        case 1: viewProperties(); break;
        case 2: manageFavorites(); break;
        case 3: purchaseProperty(); break;
        case 4: addProperty(); break;
        default: std::cout << GREEN << "Goodbye!" << RESET << std::endl; break;
    }
}

void UserInterface::run() {
    int option;
    do {
        clearScreen();
        header();
        option = readInteger("Enter option: ");
        menu(option);
    } while (option >= 1 && option <= 4);
}