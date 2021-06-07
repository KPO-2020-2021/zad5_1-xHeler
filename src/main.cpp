#include "Scene.h"

void displayMenu();

int main() {
    Scene scene;
    char option = ' ';
    int number = 0;

    displayMenu();

    do {
        std::cout << "Enter option: \n";
        std::cin >> option;

        switch (option) {
            case 'D':
            case 'd':
                scene.activateDrone();
                break;
            case 'F':
            case 'f':
                scene.startDrone();
                scene.rotateDrone();
                scene.flyForwardDrone();
                scene.landDrone();
                scene.draw();
                break;
            case 'M':
            case 'm':
                displayMenu();
                break;
            default:
                break;
        }

    } while (option != 'k' || option != 'K');

    return 0;
}

void displayMenu() {
    std::cout << "D - Chose drone \n";
    std::cout << "F - Setup flight \n";
    std::cout << "M - display menu \n";
    std::cout << "\n";
    std::cout << "C - close \n";
}