#include "Resource.h"

Resource::Resource() {
    resourceID = "";
    resourceName = "";
    resourceType = "";
    available = true;
}

Resource::Resource(std::string id, std::string name, std::string type, bool status) {

    resourceID = id;
    resourceName = name;
    resourceType = type;
    available = status;
}

std::string Resource::getResourceID() {
    return resourceID;
}

std::string Resource::getResourceName() {
    return resourceName;
}

std::string Resource::getResourceType() {
    return resourceType;
}

bool Resource::getAvailability() {
    return available;
}

void Resource::setAvailability(bool status) {
    available = status;
}