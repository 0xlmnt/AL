#include <iostream>
#include <cmath>
#include <sstream>
#include "Organism/Organism.h"
#include "Environment/Environment.h"


int main() {
    auto organism_active = Organism(
            "one",
            100.0,
            200.0,
            2.0,
            5.0,
            1.0,
            [](double upt_coeff, double size) { return upt_coeff; },
            [](double met_coeff, double size) { return met_coeff; }
            );

    auto organism_passive = Organism(
            "two",
            100.0,
            200.0,
            1.5,
            4.95,
            1.0,
            [](double upt_coeff, double size) { return upt_coeff; },
            [](double met_coeff, double size) { return met_coeff; }
    );


    auto env = Environment(
            0.0,
            1000.0,
            std::vector<Organism> {organism_active, organism_passive}
            );

    for (int i = 0; i < 4000; ++i) {
        std::stringstream stream;
        for (const auto& x : env.get_population_size()) {
            stream << "{" << x.first << ": " << x.second << "} ";
        }

        std::cout << stream.str() << std::endl;
        env.update();
    }


    return 0;
}
