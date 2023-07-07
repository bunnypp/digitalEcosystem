//
//  main.cpp
//  SFML-test
//
//  Created by Bunny Phetmunee on 7/3/23.
//
#define _USE_MATH_DEFINES
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <random>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "hex.hpp"
#include "biome.hpp"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Hex Biome");
    sf::View view(sf::FloatRect(0,0, WINDOW_WIDTH, WINDOW_HEIGHT));
//    std::vector<HexTile> shapes;
    sf::Clock clock;
    int hex_size = 15;
    Layout layout(layout_pointy, Point(hex_size, hex_size), Point(WINDOW_WIDTH/2, WINDOW_HEIGHT/2));
    int N = 15;
    std::unordered_map<Hex, HexTile> hexMap;
    for (int q = -N; q <= N; q++) {
        int r1 = std::max(-N, -q - N);
        int r2 = std::min( N, -q + N);
        for (int r = r1; r <= r2; r++) {
            Hex h(q, r, -q-r);
            Point hex_location = hex_to_pixel(layout, h);
            hexMap.insert({h, HexTile(hex_size, hex_location.x(), hex_location.y())});
        }
    }
    
    // randomly spawn a cell
    int random_index = rand() % hexMap.size();
    HexTile *random_tile = &std::next(hexMap.begin(), random_index)->second;
    
    if (random_tile->is_occupied() == false){
        random_tile->setFillColor(sf::Color(204, 227, 186));
        random_tile->set_occupied();
    }

    while (window.isOpen()){
        sf::Event event;
        // handle all events
        while (window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed: {
                    window.close();
                    break;
                }
//                case sf::Event::MouseButtonPressed: {
//                    
//                    
//                }
                case sf::Event::KeyPressed:{
                    if (event.key.code == sf::Keyboard::Period){
                        view.zoom(0.8f);
                    } else if (event.key.code == sf::Keyboard::Comma) {
                        view.zoom(1.2f);
                    }
                }
                default: {
                    break;
                }
            }
        }
        window.setView(view);
        window.clear(sf::Color::White);
        for (auto &pair : hexMap){
            window.draw(pair.second);
        }
        // draw objects here
        window.display();
    }
}


