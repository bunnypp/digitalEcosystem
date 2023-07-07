//
//  biome.hpp
//  SFML-test
//
//  Created by Bunny Phetmunee on 7/7/23.
//

#ifndef biome_hpp
#define biome_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>


template <typename Number, int w>
struct _Hex;
typedef _Hex<int, 1> Hex;

class HexTile;

/* CONSTANTS */
const std::vector<sf::Color> bb_colors = {
    sf::Color(204, 227, 186), sf::Color(222, 255, 242), sf::Color(195, 172, 206),
    sf::Color(69, 123, 157), sf::Color(83, 128, 131), sf::Color(222, 110, 75),
    sf::Color(252, 232, 177)
};

class BioBot {
private:
    const Hex *location;
    const sf::Color *color;
public:
    BioBot(const Hex *location);
    const sf::Color * get_color() const;
};

void random_spawn(int n, std::unordered_map<Hex, HexTile> *hexMap);


#endif /* biome_hpp */
