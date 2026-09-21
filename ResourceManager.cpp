#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

void ResourceManager::loadResources(std::string filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening resource file." << std::endl;
        return;
    }

    std::string line;
   
    while (getline(file, line)) {
        std::string id;
        std::string name;
        std::string type;
        std::string status;

        std::stringstream ss(line);

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, status, '|');

        bool available = (status == "Available");

        Resource resource(id, name, type, available);

        resources.push_back(resource);

    } 
}

void ResourceManager::displayResources() {
    std::cout << "===== Available Resources =====" << std::endl;

    for (int i = 0; i < resources.size(); i++) {
        std::cout << resources[i].getResourceID() << " | "
                  << resources[i].getResourceName() << " | "
                  << resources[i].getResourceType() << "  | ";

        if (resources[i].getAvailability()) {
            std::cout << "Available";    
        } else {
            std::cout << "Unavailable";
        }
        
        std::cout << std::endl;
    }
}

bool ResourceManager::resourceExists(std::string id) {
    for (int i = 0; i < resources.size(); i++) {
        if (resources[i].getResourceID() == id) {
            return true;
        }
    }

    return false;
}

bool ResourceManager::isAvailable(std::string id) {
    for (int i = 0; i < resources.size(); i++) {
        if (resources[i].getResourceID() == id) {
            return resources[i].getAvailability();
        }
    }

    return false;
}

void ResourceManager::setAvailability(std::string id, bool status) {
    for (int i = 0; i < resources.size(); i++) {
        if (resources[i].getResourceID() == id) {
            resources[i].setAvailability(status);
            return;
        }
    }
}