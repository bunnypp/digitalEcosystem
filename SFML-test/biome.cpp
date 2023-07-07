//
//  biome.cpp
//  SFML-test
//
//  Created by Bunny Phetmunee on 7/7/23.
//

#include "biome.hpp"
#include "hex.hpp"


/* CLASS & STRUCT DEFINITONS */
BioBot::BioBot(Hex *location) {
    this->location = location;
    this->color = &bb_colors[rand() % bb_colors.size()];
}

void BioBot::random_spawn(int n, std::unordered_map<Hex, HexTile> *hexMap) {
    // randomly spawn a cell
    int random_index = rand() % hexMap->size();
    HexTile *random_tile = &std::next(hexMap->begin(), random_index)->second;
    if (random_tile->is_occupied() == false){
        random_tile->setFillColor(sf::Color(204, 227, 186));
        random_tile->set_occupied();
    }
}
