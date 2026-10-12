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

    for (std::size_t i = 0; i < resources.size(); i++) {
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
    for (std::size_t i = 0; i < resources.size(); i++) {
        if (resources[i].getResourceID() == id) {
            return true;
        }
    }

    return false;
}

bool ResourceManager::isAvailable(std::string id) {
    for (std::size_t i = 0; i < resources.size(); i++) {
        if (resources[i].getResourceID() == id) {
            return resources[i].getAvailability();
        }
    }

    return false;
}

void ResourceManager::setAvailability(std::string id, bool status) {
    for (std::size_t i = 0; i < resources.size(); i++) {
        if (resources[i].getResourceID() == id) {
            resources[i].setAvailability(status);
            return;
        }
    }
}

void ResourceManager::sortResourcesByName() {
    if (resources.size() <= 1) {
        return;
    }

    mergeSort(0, resources.size() -1);
}

void ResourceManager::mergeSort(int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right -left) / 2;

    mergeSort(left, mid);

    mergeSort(mid +1, right);

    merge(left, mid, right);
}

void ResourceManager::merge(int left, int mid, int right) {
    std::vector<Resource> leftPart;
    std::vector<Resource> rightPart;

    for (int i = left; i <= mid; i++) {
        leftPart.push_back(resources[i]);
    }

    for (int i = mid +1; i <= right; i++) {
        rightPart.push_back(resources[i]);
    }

    std::size_t i = 0;
    std::size_t j = 0;
    int k = left;

    while (i < leftPart.size() && j < rightPart.size()) {
        if (leftPart[i].getResourceName() <= rightPart[j].getResourceName()) {
            resources[k] = leftPart[i];
            i++;
        } else {
            resources[k] = rightPart[j];
            j++;
        }
        k++;
    }

    while (i < leftPart.size()) {
        resources[k] = leftPart[i];
        i++;
        k++;
    }

    while (j < rightPart.size()) {
        resources[k] = rightPart[j];
        j++;
        k++;
    }
}

int ResourceManager::binarySearchByID(const std::string& targetID) const {
    int left = 0;
    int right = static_cast<int>(resources.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (resources[mid].getResourceID() == targetID) {
            return mid;
        } else if (resources[mid].getResourceID() < targetID) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int ResourceManager::binarySearchByName(const std::string& targetName) const {
    int left = 0;
    int right = static_cast<int>(resources.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (resources[mid].getResourceName() == targetName) {
            return mid;
        } else if (resources[mid].getResourceName() < targetName) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

void ResourceManager::sortResourcesByID() {
    for (std::size_t i = 1; i < resources.size(); i++) {
        Resource key = resources[i];
        int j = static_cast<int>(i) - 1;

        while (j >= 0 && resources[j].getResourceID() > key.getResourceID()) {
            resources[j + 1] = resources[j];
            j--;
        }
        resources[j + 1] = key;
    }
}

Resource ResourceManager::getResourceAt(int index) const {
    if (index >= 0 && index < static_cast<int>(resources.size())) {
        return resources[index];
    }
    return Resource();
}