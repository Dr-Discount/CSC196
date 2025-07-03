#include <iostream>  
#include "Math/Math.h"  
#include "Core/Random.h"

#define NAME "Kyler\n"



int main() {  
    //constexpr float deg = radToDeg(viper::pi);
    std::cout << viper::min(5, 3) << std::endl;
    std::cout << viper::clamp(2, 3, 5) << std::endl;

    std::cout << NAME;
    std::cout << "Hello, World!\n";
    std::cout << viper::pi << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << viper::random::getRandomInt(5, 10) << std::endl;
    }
}