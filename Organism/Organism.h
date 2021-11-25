//
// Created by u on 21.11.21.
//

#ifndef ARTIFICIALLIFE_ORGANISM_H
#define ARTIFICIALLIFE_ORGANISM_H

#include <string>
#include <functional>

struct Organism_Step{
    bool is_ready_to_divide;
    double amount_food_consumed;
};

struct Uptake{
    double value;
};

class Organism{
private:
    std::string species = "unknown";
    double size{};
    double division_threshold{};

    std::function<double(double)> f_uptake;
    std::function<double(double)> f_metabolism;

    bool alive{true};

    Organism_Step update(Uptake uptake);

public:
    Organism(std::string species, double size, double division_threshold,
             std::function<double(double)> metabolicRate, std::function<double(double)> uptakeRate);

    Organism_Step update(double available_food);
    Organism_Step update();

    void divide(std::vector<Organism>* vec);

    double get_size() const;
    std::string get_name();
    bool is_alive() const;
};

#endif //ARTIFICIALLIFE_ORGANISM_H
