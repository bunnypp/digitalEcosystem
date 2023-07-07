//
//  hex.cpp
//  SFML-test
//
//  Created by Bunny Phetmunee on 7/6/23.
//
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <math.h>
#include "hex.hpp"
#include "biome.hpp"
#include <SFML/Graphics.hpp>


/* CLASS & STRUCT DEFINITONS */
template <typename Number, int w>
_Hex<Number, w>::_Hex(Number q, Number r, Number s): v{q, r, s} {
        assert (q + r + s == 0);
    }
template <typename Number, int w>
Number _Hex<Number, w>::q() const { return v[0]; }

template <typename Number, int w>
Number _Hex<Number, w>::r() const { return v[1]; }

template <typename Number, int w>
Number _Hex<Number, w>::s() const { return v[2]; }

//template <typename Number, int w>
//bool _Hex<Number, w>::operator==(const _Hex<int, 1>& other) const {
//        return (this->q() == other.q() &&  this->r() == other.r() && this->s() == other.s());
//}

namespace std{
size_t hash<Hex>::operator()(const Hex& h) const {
        hash<int> int_hash;
        size_t hq = int_hash(h.q());
        size_t hr = int_hash(h.r());
        return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
}
}


HexTile::HexTile(float radius, int x, int y): sf::CircleShape(radius-1) {
        this->setOrigin( radius/2, radius/2);
        this->setPointCount(6);
        this->setPosition(x, y);
        this->setFillColor(sf::Color(252, 248, 240));
        this->setOutlineThickness(2);
        this->setOutlineColor(sf::Color(189, 182, 168));
        this->occupied = false;
        this->occupant = NULL;
        
}
bool HexTile::is_occupied(){
    return (this->occupied == true);
}
void HexTile::set_occupied(BioBot *bb) {
    if (this->occupied){
        this->occupied = false;
        return;
    }
    this->occupied = true;
    this->occupant = bb;
}


/* FUNCTION DEFINITONS */

Hex hex_add(Hex a, Hex b) {
    return Hex(a.q() + b.q(), a.r() + b.r(), a.s() + b.s());
}

Hex hex_subtract(Hex a, Hex b) {
    return Hex(a.q() - b.q(), a.r() - b.r(), a.s() - b.s());
}

Hex hex_multiply(Hex a, int k) {
    return Hex(a.q() * k, a.r() * k, a.s() * k);
}

int hex_length(Hex hex) {
    return int((abs(hex.q()) + abs(hex.r()) + abs(hex.s())) / 2);
}

int hex_distance(Hex a, Hex b) {
    return hex_length(hex_subtract(a, b));
}

Hex hex_direction(int direction /* 0 to 5 */) {
    assert (0 <= direction && direction < 6);
    return hex_directions[direction];
}

Hex hex_neighbor(Hex hex, int direction, int k) {
    return hex_add(hex, hex_multiply(hex_direction(direction), k));
}

Point hex_to_pixel(Layout layout, Hex h) {
    const Orientation& M = layout.orientation;
    double x = (M.f0 * h.q() + M.f1 * h.r()) * layout.size.x();
    double y = (M.f2 * h.q() + M.f3 * h.r()) * layout.size.y();
    return Point(x + layout.origin.x(), y + layout.origin.y());
}

FractionalHex pixel_to_hex(Layout layout, Point p) {
        const Orientation& M = layout.orientation;
        Point pt = Point((p.x() - layout.origin.x()) / layout.size.x(),
                         (p.y() - layout.origin.y()) / layout.size.y());
        double q = M.b0 * pt.x() + M.b1 * pt.y();
        double r = M.b2 * pt.x() + M.b3 * pt.y();
        return FractionalHex(q, r, -q - r);
}

Hex hex_round(FractionalHex h) {
    int q = int(round(h.q()));
    int r = int(round(h.r()));
    int s = int(round(h.s()));
    double q_diff = abs(q - h.q());
    double r_diff = abs(r - h.r());
    double s_diff = abs(s - h.s());
    if (q_diff > r_diff and q_diff > s_diff) {
        q = -r - s;
    } else if (r_diff > s_diff) {
        r = -q - s;
    } else {
        s = -q - r;
    }
    return Hex(q, r, s);
};

