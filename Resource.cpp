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

std::string Resource::getResourceID() const {
    return resourceID;
}

std::string Resource::getResourceName() const {
    return resourceName;
}

std::string Resource::getResourceType() const {
    return resourceType;
}

bool Resource::getAvailability() const {
    return available;
}

void Resource::setAvailability(bool status) {
    available = status;
}