//
// Created by u on 26.11.21.
//

#include <sstream>
#include "Mutation.h"

std::string mutation_chain_to_string(const std::vector<Mutation>& vec){
    std::stringstream stream;
    for (auto mut : vec) {
        stream << "[" << static_cast<int>(mut.type) << ":" << mut.value << "]-";
    }

    return stream.str();
}

