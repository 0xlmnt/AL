//
// Created by u on 21.11.21.
//

#include "Environment.h"
#include "Mutation.h"

Environment::Environment(double food, double refill_rate, std::vector<Organism> population) {
    this->food = food;
    this->refill_rate = refill_rate;
    this->population = std::move(population);

    auto rd = std::random_device{};
    this->rng = std::default_random_engine { rd() };
}

size_t Environment::update() {
    size_t divisions = 0;
    std::vector<Organism> new_organisms{};
    std::vector<size_t> idx_to_delete{};
    this->shuffle();

    for (int i = 0; i < this->population.size(); ++i) {
        auto organism = &this->population[i];

        auto org_step = organism->update(this->food);
        this->food -= org_step.amount_food_consumed;

        if (!organism->is_alive()) {
            idx_to_delete.push_back(i);
            continue;
        }

        if (org_step.is_ready_to_divide) {
            ++divisions;
            organism->divide(&new_organisms);

            // mark for deletion
            idx_to_delete.push_back(i);
        }
    }

    //remove
    std::sort(idx_to_delete.begin(), idx_to_delete.end(), std::greater<>());
    for (auto idx : idx_to_delete) {
        this->del_organism(idx);
    }

    // add new organisms
    for (const auto& organism : new_organisms) {
        this->population.push_back(organism);
    }

    this->food += this->refill_rate;

    return divisions;
}

std::map<std::string, size_t> Environment::get_population_size_by_name() {
    auto map = std::map<std::string, size_t>{};

    for (auto organism : this->population) {
        map[organism.get_name()] += 1;
    }

    return map;
}

void Environment::del_organism(size_t idx) {
    this->population[idx] = this->population.back();
    this->population.pop_back();
}

double Environment::get_food() const {
    return this->food;
}

void Environment::shuffle() {
    std::shuffle(std::begin(this->population), std::end(this->population), rng);
}

size_t Environment::get_population_size_total() {
    return this->population.size();
}

std::vector<Mutation> Environment::get_best_mutation_chain() {
    std::vector<Mutation> vec{};
    double best_score = 0.0;

    for (auto org : this->population) {
        auto score = org.get_size() * static_cast<double>(org.get_number_of_divisions());
        if (score > best_score) {
            vec = org.get_mutations();
            best_score = score;
        }
    }

    return vec;
}

std::map<std::string, size_t> Environment::get_population_size_by_mutations() {
    auto map = std::map<std::string, size_t>{};

    for (auto organism : this->population) {
        map[mutation_chain_to_string(organism.get_mutations())] += 1;
    }

    return map;
}

