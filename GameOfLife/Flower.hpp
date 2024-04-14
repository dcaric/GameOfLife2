//
//  Flower.hpp
//  FlowerSFML
//
//  Created by Dario Caric on 05.03.2024..
//

#ifndef Flower_hpp
#define Flower_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

using namespace sf;

class Flower {
    
private:
    RenderWindow *window_local;
    CircleShape drawSun(int, int, int);
    CircleShape redCircle(int, int, int);
    CircleShape yellowCircle(int, int, int);
    RectangleShape stem(int, int, int, int);
    
    // sun values
    const int sunRadius = 20;
    const int sunX= 40;
    const int sunY = 40;
    
    // flower values
    const int flowerX = 200;
    const int flowerY = 200;
    const int flowerRedRadius = 100;
    const int flowerYellowRadius = 50;
    
    
public:
    Flower(RenderWindow*);
    void draw(int);
};


#endif /* Flower_hpp */
