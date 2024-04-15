//
//  game_of_life.hpp
//  game_of_life
//
//  Created by Dario Caric on 14.04.2024..
//

#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

using namespace std;
using namespace sf;

class game_of_life {
private:
    RenderWindow *window_local;
    static const unsigned int PIXELS_RECTANGLE = 2;

    static const unsigned int COLS = 120;
    static const unsigned int ROWS = 120;
    static const unsigned int PERCENTAGE = 35;
    bool _generation[ROWS][COLS];
    bool _next_generation[ROWS][COLS];
    bool random_value();
    bool cell_taken(int i, int j);

public:
    game_of_life(RenderWindow*);

    game_of_life(int percentage);
    void next_generation();
    void draw(int cycle);
    void drawGraphics(int);
};

#endif
