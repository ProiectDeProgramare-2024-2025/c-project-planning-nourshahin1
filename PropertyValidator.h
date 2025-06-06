#ifndef __PROPERTYVALIDATOR_H
#define __PROPERTYVALIDATOR_H

#include <string>

class PropertyValidator {
public:
    static bool validateName(const std::string& name);
    static bool validateAddress(const std::string& address);
    static bool validateNumberLength(int num, int maxDigits);
};

#endif