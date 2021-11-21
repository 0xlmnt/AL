#include <iostream>
#include <cmath>
#include "Organism/Organism.h"
#include "Environment/Environment.h"


int main() {

    auto o1 = Organism("Specimen Zero",
                         100.0,
                         200.0,
                         [](double size) { return 1.0/50.0 * size; },
                         [](double size) {return 1.0/4.0 * std::pow(size, 2.0/3.0); });

    auto o2 = Organism(
            "Specimen One",
            100.0,
            200.0,
            [](double x) { return 2; },
            [](double x) { return 5; }
            );


    auto env = Environment(
            0.0,
            1000.0,
            std::vector<Organism> {o2}
            );

    for (int i = 0; i < 5000; ++i) {
        std::cout << env.get_population_size() << " | " << env.get_food() << std::endl;

        //std::cout << env.update() << std::endl;
        env.update();
    }

    return 0;
}
