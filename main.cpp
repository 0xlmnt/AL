#include <iostream>
#include <cmath>
#include "Organism/Organism.h"
#include "Environment/Environment.h"


int main() {

    auto o1 = Organism("Specimen Zero",
                         100.0,
                         200.0,
                         [](double size) {return (1.0/50.0) * size;},
                         [](double size) {return (1.0/4.0) * std::pow(size, 2.0/3.0); });


    auto env = Environment(
            1000.0,
            100.0,
            std::vector<Organism> {o1}
            );

    for (int i = 0; i < 5000; ++i) {
        std::cout << env.get_population_size() << " | " << env.get_food() << std::endl;
        env.update();
    }

    return 0;
}
