#include <iostream>
#include <cstdlib>
#include <ctime>

#include <iomanip>

#include "Manager.h"



void main() {
    Manager new_manager;
    new_manager.startNewGame();
    new_manager.GameLoop();
    
}