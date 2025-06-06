#ifndef __USERINTERFACE_H
#define __USERINTERFACE_H

#include <string>
#include "PropertyManager.h"  
#include "PropertyValidator.h"


class PropertyManager;

class UserInterface : public PropertyValidator {
private:
    PropertyManager& manager;

public:
    UserInterface(PropertyManager& mgr);
    void clearScreen();
    void pause();
    int readInteger(const std::string& prompt);
    std::string readString(const std::string& prompt);
    void header();
    void viewProperties();
    void manageFavorites();
    void purchaseProperty();
    void addProperty();
    void menu(int option);
    void run();
};

#endif