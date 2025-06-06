#define MAX_PROPERTIES 20

#include "PropertyManager.h"
#include "Colors.h"
#include <fstream>
#include <iostream>

#define PROPERTY_FILE "./properties.txt"

PropertyManager::PropertyManager(int max) : maxProperties(max) {}

void PropertyManager::loadPropertiesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << RED << "No property file found." << RESET << std::endl;
        return;
    }

    Property prop;
    while (properties.size() < maxProperties && prop.loadFromFile(file)) {
        properties.push_back(prop);
    }
    file.close();
}

void PropertyManager::savePropertiesToFile() {
    std::ofstream file(PROPERTY_FILE);
    if (!file.is_open()) {
        std::cout << RED << "Error saving properties to file." << RESET << std::endl;
        return;
    }

    for (const auto& prop : properties) {
        if (!prop.getName().empty()) {
            prop.saveToFile(file);
        }
    }
    file.close();
}

bool PropertyManager::addProperty(const Property& prop) {
    if (properties.size() >= maxProperties) {
        std::cout << RED << "Property list is full!" << RESET << std::endl;
        return false;
    }
    properties.push_back(prop);
    return true;
}

bool PropertyManager::addToFavorites(int index) {
    if (index < 0 || index >= static_cast<int>(properties.size()) || properties[index].getName().empty()) {
        return false;
    }
    if (favorites.size() >= maxProperties) {
        std::cout << RED << "Favorites list is full." << RESET << std::endl;
        return false;
    }
    favorites.push_back(properties[index]);
    return true;
}

bool PropertyManager::purchaseProperty(int index) {
    if (index < 0 || index >= static_cast<int>(properties.size()) || properties[index].getName().empty()) {
        return false;
    }
    properties.erase(properties.begin() + index);
    return true;
}

const std::vector<Property>& PropertyManager::getProperties() const {
    return properties;
}

const std::vector<Property>& PropertyManager::getFavorites() const {
    return favorites;
}