#include <iostream>
#include "src/PropertyManager.h"
#include "src/UserInterface.h"

#define MAX_PROPERTIES 20

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <property_file>\n";
        return 1;
    }

    PropertyManager manager(MAX_PROPERTIES);
    manager.loadPropertiesFromFile(argv[1]);

    UserInterface ui(manager);
    ui.run();

    return 0;
}