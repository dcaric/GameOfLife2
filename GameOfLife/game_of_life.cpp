//
//  game_of_life.cpp
//  game_of_life
//
//  Created by Dario Caric on 14.04.2024..
//

#include "game_of_life.hpp"
#include <time.h>
#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <sstream>

game_of_life::game_of_life(RenderWindow *win) {
    window_local = win;
}

void game_of_life::drawGraphics(int lifeCycles) {
    
    //stringstream sstr;
    //sstr << "Game Of Life cycle: " << lifeCycles;
    //window_local->setTitle(sstr.str());

    // draw rectangles at the position of _generation[i][j] with this formula x = 10 + (i-1) * 20 y = 10 + (j-1) * 20 with 10 width and height
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (_generation[i][j]) {
                RectangleShape rectangle(Vector2f(PIXELS_RECTANGLE, PIXELS_RECTANGLE));
                rectangle.setPosition(PIXELS_RECTANGLE / 2 + (i-1) * PIXELS_RECTANGLE * 2, PIXELS_RECTANGLE / 2 + (j-1) * PIXELS_RECTANGLE * 2);
                // generate random light color for live cells
                int r = 180 - rand() % (255-120 +1);
                int g = 180 - rand() % (255-120 +1);
                int b = 180 - rand() % (255-120 +1);

                Color color(r,g,b);
                rectangle.setFillColor(color);
                window_local->draw(rectangle);
            }
        }
    }
}

/**
 Sets initial game with 25% cells live
 */
game_of_life::game_of_life(int percentage) {
    srand(time(NULL));
    
    // set all to false
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            _generation[i][j] = false;
            _next_generation[i][j] = false;
        }
    }
    
    // generate array of ROWS * COLS where some percentage elements will be true and the rest false
    int totalTrueCells = ROWS * COLS * percentage / 100;
    cout << "Total true cells: " << totalTrueCells << endl;
    
    // generate ROWS * COLS * percentage/100 numbers between 1 and ROWS * COLS but without duplicates
    for (int i = 0; i < totalTrueCells; i++) {
        int row = 1- rand() % (ROWS - 1 + 1); // 1-ROWS
        int col = 1- rand() % (COLS - 1 + 1); // 1-COLS
        // if the cell is already true, generate another random number
        while (_generation[row][col]) {
            int row = 1- rand() % (ROWS - 1 + 1);
            int col = 1- rand() % (COLS - 1 + 1);
        }
        _generation[row][col] = true;
    }
    
    // print the array
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << _generation[i][j] << " ";
        }
        cout << endl;
    }
    
}

/**
 Runs next game iterraion
 */
void game_of_life::next_generation() {
    // for each cell
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            
            
            /**
             for cell (i, j) the neighbours are:
             
            (i-i, j-1)          (i-i, j)           (i-i, j+1)
            (i, j-1)            (i, j)              (i, j+1)
            (i + 1, j-1)      (i + 1, j)        ( i + 1, j+1)
             */
            
            // count the number of live neighbours
            int liveNeighbours = 0;
            for (int k = i - 1; k <= i + 1; k++) { // rows
                for (int l = j - 1; l <= j + 1; l++) { // columns
                    if (k >= 0 && k < ROWS && l >= 0 && l < COLS) {
                        if (_generation[k][l] && (k != i || l != j)) {
                            liveNeighbours++;
                        }
                    }
                }
            }
            
            // apply the rules and set the next generation
            if (_generation[i][j]) {
                if (liveNeighbours < 2 || liveNeighbours > 3) {
                    _next_generation[i][j] = false;
                } else {
                    _next_generation[i][j] = true;
                }
            } else {
                if (liveNeighbours == 3) {
                    _next_generation[i][j] = true;
                } else {
                    _next_generation[i][j] = false;
                }
            }
        }
    }
    
    // check if the current generation is the same as the next generation
    bool same = true;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (_generation[i][j] != _next_generation[i][j]) {
                same = false;
                break;
            }
        }
    }
    if (same) {
        cout << "The game is over. No changes in the next generation." << endl;
        exit(0);
    }
    
    
    // copy the next generation to the current generation
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            _generation[i][j] = _next_generation[i][j];
        }
    }
}


/**
 Draws the current generation
 */
void game_of_life::draw(int cycle) {
    cout << "Generation number: " << cycle << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (_generation[i][j]) {
                cout << "o";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}
