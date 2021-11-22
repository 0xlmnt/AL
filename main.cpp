#include <iostream>
#include <cmath>
#include <sstream>
#include "Organism/Organism.h"
#include "Environment/Environment.h"


int main() {

    auto o1 = Organism("Specimen Zero",
                         100.0,
                         200.0,
                         [](double size) { return 1.0/50.0 * size; },
                         [](double size) {return 1.0/4.0 * std::pow(size, 2.0/3.0); });


    auto organism_active = Organism(
            "one",
            100.0,
            200.0,
            [](double x) { return 2; },
            [](double x) { return 5; }
            );

    auto organism_passive = Organism(
            "two",
            100.0,
            200.0,
            [](double x) { return 1; },
            [](double x) { return 4; }
    );


    auto env = Environment(
            0.0,
            1000.0,
            std::vector<Organism> {organism_active, organism_passive}
            );

    for (int i = 0; i < 2000; ++i) {
        std::stringstream stream;
        for (const auto& x : env.get_population_size()) {
            stream << "{" << x.first << ": " << x.second << "} ";
        }

        std::cout << stream.str() << std::endl;
        env.update();
    }


    return 0;
}
