#ifndef __PROPERTY_H
#define __PROPERTY_H


#include <string>
#include <fstream>

class Property {
private:
    std::string name, address;
    int price, size, rooms, bathrooms;
    bool parking;

public:
    Property();

    
    std::string getName() const;
    std::string getAddress() const;
    int getPrice() const;
    int getSize() const;
    int getRooms() const;
    int getBathrooms() const;
    bool hasParking() const;


    bool setName(const std::string& newName);
    bool setAddress(const std::string& newAddress);
    bool setPrice(int newPrice);
    bool setSize(int newSize);
    void setRooms(int newRooms);
    void setBathrooms(int newBathrooms);
    void setParking(bool hasParking);

    
    void display(int index) const;
    void saveToFile(std::ofstream& file) const;
    bool loadFromFile(std::ifstream& file);
};

#endif 