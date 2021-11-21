//
// Created by u on 21.11.21.
//

#include "Organism.h"
#include <utility>

Organism_Step Organism::update() {
    auto uptake = Uptake{this->uptake_rate(this->size)};
    return this->update(uptake);
}

Organism_Step Organism::update(double available_food) {
    auto uptake = Uptake{
        std::min(available_food, this->uptake_rate(this->size))
    };
    return update(uptake);
}

Organism_Step Organism::update(Uptake uptake) {
    bool ready_to_divide = false;

    if (this->alive){
        this->size += uptake.value;
        this->size -= this->metabolic_rate(this->size);
    }
    if (this->size <= 0)
        this->alive = false;

    if (this->size >= this->division_threshold){
        ready_to_divide = true;
    }

    return Organism_Step{
            ready_to_divide,
            uptake.value
    };
}

Organism::Organism(std::string species, double size, double division_threshold,
                   std::function<double(double)> metabolicRate, std::function<double(double)> uptakeRate)
        : metabolic_rate(std::move(metabolicRate)), uptake_rate(std::move(uptakeRate)) {

    this->species = std::move(species);
    this->size = size;
    this->division_threshold = division_threshold;
}

double Organism::get_size() const {
    return this->size;
}

bool Organism::is_alive() const {
    return this->alive;
}

void Organism::divide(std::vector<Organism>* vec) {

    auto new_org = Organism{
            this->species,
            this->size / 2.0,
            this->division_threshold,
            this->metabolic_rate,
            this->uptake_rate
    };

    vec->push_back(new_org);
    vec->push_back(new_org);
}
