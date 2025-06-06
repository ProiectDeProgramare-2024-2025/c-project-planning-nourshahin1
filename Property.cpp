#include "Property.h"
#include "PropertyValidator.h"
#include "Colors.h"
#include <iostream>
#include <vector>
#include <sstream>

// Constructor
Property::Property() : name(""), address(""), price(0), size(0), rooms(0), bathrooms(0), parking(false) {}

// Setters with validation
bool Property::setName(const std::string& newName) {
    if (PropertyValidator::validateName(newName)) {
        name = newName;
        return true;
    }
    return false;
}

bool Property::setAddress(const std::string& newAddress) {
    if (PropertyValidator::validateAddress(newAddress)) {
        address = newAddress;
        return true;
    }
    return false;
}

bool Property::setPrice(int newPrice) {
    if (PropertyValidator::validateNumberLength(newPrice, 6)) {
        price = newPrice;
        return true;
    }
    return false;
}

bool Property::setSize(int newSize) {
    if (PropertyValidator::validateNumberLength(newSize, 3)) {
        size = newSize;
        return true;
    }
    return false;
}

// Basic setters
void Property::setRooms(int count) {
    rooms = count;
}

void Property::setBathrooms(int count) {
    bathrooms = count;
}

void Property::setParking(bool hasParking) {
    parking = hasParking;
}

// Getters
std::string Property::getName() const {
    return name;
}

std::string Property::getAddress() const {
    return address;
}

int Property::getPrice() const {
    return price;
}

int Property::getSize() const {
    return size;
}

int Property::getRooms() const {
    return rooms;
}

int Property::getBathrooms() const {
    return bathrooms;
}

bool Property::hasParking() const {
    return parking;
}

// Display function
void Property::display(int index) const {
    if (name.empty()) return;
    std::cout << "\n\033[1;36mProperty " << index + 1 << ":\033[0m\n"
              << "Name: \033[1;32m" << name << "\033[0m\n"
              << "Address: " << address << "\n"
              << "Price: \033[1;32m$" << price << "\033[0m\n"
              << "Size: " << size << " sq. meters\n"
              << "Rooms: " << rooms << "\n"
              << "Bathrooms: " << bathrooms << "\n"
              << "Parking: " << (parking ? "\033[1;32mYes\033[0m" : "\033[1;31mNo\033[0m") << "\n";
}

// Save to file
void Property::saveToFile(std::ofstream& file) const {
    file << name << "|" << address << "|" << price << "|"
         << size << "|" << rooms << "|" << bathrooms << "|" << parking << "\n";
}

// Load from file
bool Property::loadFromFile(std::ifstream& file) {
    std::string line;
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (std::getline(ss, token, '|')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 7) {
            name = tokens[0];
            address = tokens[1];
            price = std::stoi(tokens[2]);
            size = std::stoi(tokens[3]);
            rooms = std::stoi(tokens[4]);
            bathrooms = std::stoi(tokens[5]);
            parking = std::stoi(tokens[6]) != 0;
            return true;
        }
    }
    return false;
}