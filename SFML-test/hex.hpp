//
//  hex.hpp
//  SFML-test
//
//  Created by Bunny Phetmunee on 7/6/23.
//

#ifndef hex_hpp
#define hex_hpp

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <math.h>
#include <SFML/Graphics.hpp>



/* CLASS & STRUCT DEFINITONS */
template <typename Number, int w>
struct _Hex { // Vector storage, cube constructor
    const Number v[3];
    _Hex(Number q, Number r, Number s): v{q, r, s} {
        assert (q + r + s == 0);
    }
    inline Number q() const { return v[0]; }
    inline Number r() const { return v[1]; }
    inline Number s() const { return v[2]; }
    
    bool operator==(const _Hex<int, 1>& other) const {
        return (this->q() == other.q() &&  this->r() == other.r() && this->s() == other.s());
    }
    
};


typedef _Hex<int, 1> Hex;
typedef _Hex<double, 1> FractionalHex;

struct Orientation {
    const double f0, f1, f2, f3;
    const double b0, b1, b2, b3;
    const double start_angle; // in multiples of 60°
    Orientation(double f0_, double f1_, double f2_, double f3_,
                double b0_, double b1_, double b2_, double b3_,
                double start_angle_)
    : f0(f0_), f1(f1_), f2(f2_), f3(f3_),
      b0(b0_), b1(b1_), b2(b2_), b3(b3_),
      start_angle(start_angle_) {}
};
struct Point {
    const double v[2];
    Point(double x, double y): v{x, y} {}
    inline double x() const { return v[0]; }
    inline double y() const { return v[1]; }
};
struct Layout {
    const Orientation orientation;
    const Point size;
    const Point origin;
    Layout(Orientation orientation_, Point size_, Point origin_)
    : orientation(orientation_), size(size_), origin(origin_) {}
};
namespace std {
template <> struct hash<Hex> {
    size_t operator()(const Hex& h) const {
        hash<int> int_hash;
        size_t hq = int_hash(h.q());
        size_t hr = int_hash(h.r());
        return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
    }
};
}

class HexTile: public sf::CircleShape {
private:
    bool occupied;
    BioBot *occupant;
public:
    HexTile(float radius, int x, int y): sf::CircleShape(radius-1) {
        this->setOrigin( radius/2, radius/2);
        this->setPointCount(6);
        this->setPosition(x, y);
        this->setFillColor(sf::Color(252, 232, 177));
        this->setOutlineThickness(2);
        this->setOutlineColor(sf::Color(254, 240, 196));
        this->occupied = false;
        this->occupant = NULL;
        
    }
    inline bool is_occupied(){ return (this->occupied == true);};
    void set_occupied() {
        if (this->occupied){
            this->occupied = false;
            return;
        }
        this->occupied = true;
    };
};



/* CONSTANTS */
const std::vector<Hex> hex_directions = {
    Hex(1, 0, -1), Hex(1, -1, 0), Hex(0, -1, 1),
    Hex(-1, 0, 1), Hex(-1, 1, 0), Hex(0, 1, -1)
};

const Orientation layout_pointy
  = Orientation(sqrt(3.0), sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0,
                sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0,
                0.5);

/* FUNCTION DECLARATIONS */
Hex hex_add(Hex a, Hex b);
Hex hex_subtract(Hex a, Hex b);
Hex hex_multiply(Hex a, int k);
Hex hex_direction(int direction /* 0 to 5 */);
Hex hex_neighbor(Hex hex, int direction, int k);
Point hex_to_pixel(Layout layout, Hex h);
FractionalHex pixel_to_hex(Layout layout, Point p);
Hex hex_round(FractionalHex h);

#endif /* hex_hpp */
