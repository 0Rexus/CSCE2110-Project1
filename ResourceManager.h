#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <vector>
#include <string>
#include "Resource.h"

class ResourceManager {
private:
    std::vector<Resource> resources;

public:
    const std::vector<Resource>& getResources() const {
    return resources;
}
    void loadResources(std::string filename);
    void displayResources();
    bool resourceExists(std::string id);
    bool isAvailable(std::string id);
    void setAvailability(std::string id, bool status);
};

#endif