#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

class Resource {
private:
    std::string resourceID;
    std::string resourceName;
    std::string resourceType;
    bool available;

public:
    Resource();

    Resource(std::string id, std::string name,
             std::string type, bool status);

    std::string getResourceID() const;
    std::string getResourceName() const;
    std::string getResourceType() const;
    bool getAvailability() const;

    void setAvailability(bool status);

};

#endif