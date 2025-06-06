#define MAX_PROPERTIES 20

#ifndef __PROPERTYMANAGER_H
#define __PROPERTYMANAGER_H

#include <vector>
#include "Property.h"  

class PropertyManager {
private:
    std::vector<Property> properties;
    std::vector<Property> favorites;
    int maxProperties;

public:
    PropertyManager(int max);
    void loadPropertiesFromFile(const std::string& filename);
    void savePropertiesToFile();
    bool addProperty(const Property& prop);
    bool addToFavorites(int index);
    bool purchaseProperty(int index);
    const std::vector<Property>& getProperties() const;
    const std::vector<Property>& getFavorites() const;
};

#endif