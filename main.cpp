#include <iostream>
#include <sstream>
#include "Organism/Organism.h"
#include "Environment/Environment.h"


int main() {
    auto organism_active = Organism(
            "one",
            100.0,
            200.0,
            5.0,
            2.0,
            1.0,
            [](double upt_coeff, double size) { return upt_coeff; },
            [](double met_coeff, double size) { return met_coeff; }
            );

    auto organism_passive = Organism(
            "two",
            100.0,
            200.0,
            4.0,
            1.0,
            1.0,
            [](double upt_coeff, double size) { return upt_coeff; },
            [](double met_coeff, double size) { return met_coeff; }
    );


    auto env = Environment(
            100.0,
            100.0,
            std::vector<Organism> {organism_active}
            );

    for (int i = 0; i < 5000; ++i) {
        std::stringstream stream;
        std::stringstream stream2;
        for (const auto& x : env.get_population_size()) {
            stream << "{" << x.first << ": " << x.second << "} ";
        }

        std::cout << stream.str() << std::endl;
        env.update();

        for (const auto& y : env.get_best_mutation_chain()) {
            stream2 << "{" << static_cast<int>(y.type) << ":" << y.value << "}-" << std::endl;
        }

        std::cout << stream2.str() << std::endl;
        std::cout << "" << std::endl;
    }


    return 0;
}
