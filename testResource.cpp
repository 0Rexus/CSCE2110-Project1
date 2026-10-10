#include "ResourceManager.h"
#include <iostream>

int main() {

    ResourceManager emptyManager;


    std::cout << "\n===== EMPTY LIST TEST =====\n";
    emptyManager.sortResourcesByName();
    emptyManager.displayResources();

    ResourceManager singleManager;

    std::cout << "\n===== SINGLE RESOURCE TEST =====\n";
    singleManager.loadResources("singleResource.txt");
    singleManager.sortResourcesByName();
    singleManager.displayResources();

    ResourceManager manager;

    manager.loadResources("resources.txt");

    std::cout << "\n===== BEFORE SORTING =====\n";

    manager.displayResources();

    manager.sortResourcesByName();
    manager.sortResourcesByName();

    std::cout << "\n===== AFTER SORTING (A-Z) =====\n";
    manager.displayResources();

    return 0;
}