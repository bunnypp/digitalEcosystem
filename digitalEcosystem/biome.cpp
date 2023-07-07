//
//  biome.cpp
//  SFML-test
//
//  Created by Bunny Phetmunee on 7/7/23.
//

#include <ctime>
#include "hex.hpp"
#include "biome.hpp"


/* CLASS & STRUCT DEFINITONS */
BioBot::BioBot(const Hex *location) {
    this->location = location;
    this->color = &bb_colors[rand() % bb_colors.size()];
}
const sf::Color *BioBot::get_color() const {
    return this->color;
}

void random_spawn(int n, std::unordered_map<Hex, HexTile> *hexMap) {
    // randomly spawn a cell
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        int random_index = rand() % hexMap->size();
        HexTile *tile = &std::next(hexMap->begin(), random_index)->second;
        if (tile->is_occupied() == false){
            BioBot bb(&std::next(hexMap->begin(), random_index)->first);
            tile->setFillColor(*bb.get_color());
            tile->set_occupied(&bb);
        }
    }
}
