#include "PropertyValidator.h"
#include <cctype>

bool PropertyValidator::validateName(const std::string& name) {
    int wordCount = 0;
    bool inWord = false;
    for (char c : name) {
        if (!isalpha(c) && c != ' ') return false;
        if (isalpha(c)) {
            if (!inWord) {
                wordCount++;
                inWord = true;
            }
        } else if (c == ' ') {
            inWord = false;
        }
    }
    return (wordCount > 0 && wordCount <= 3);
}

bool PropertyValidator::validateAddress(const std::string& address) {
    size_t i = 0;
    while (i < address.length() && isdigit(address[i])) i++;
    if (i == 0 || address[i] != ' ') return false;
    i++;
    int wordCount = 0;
    bool inWord = false;
    for (; i < address.length(); i++) {
        if (!isalpha(address[i]) && address[i] != ' ') return false;
        if (isalpha(address[i])) {
            if (!inWord) {
                wordCount++;
                inWord = true;
            }
        } else if (address[i] == ' ') {
            inWord = false;
        }
    }
    return (wordCount == 2);
}

bool PropertyValidator::validateNumberLength(int num, int maxDigits) {
    if (num == 0) return true;
    int digits = 0;
    while (num != 0) {
        num /= 10;
        digits++;
    }
    return digits <= maxDigits;
}