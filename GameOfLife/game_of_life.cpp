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


game_of_life::game_of_life(RenderWindow *win) {
    window_local = win;
}

void game_of_life::drawGraphics() {
    // draw rectangles at the position of _generation[i][j] with this formula x = 10 + (i-1) * 20 y = 10 + (j-1) * 20 with 10 width and height
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (_generation[i][j]) {
                RectangleShape rectangle(Vector2f(10, 10));
                rectangle.setPosition(10 + i * 20, 10 + j * 20);
                // generate random color
                Color color(rand() % 255, rand() % 255, rand() % 255);
                if (rand() % 2 == 0) {
                    color = Color::White;
                }
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
        int random = rand() % (ROWS * COLS);
        int row = random / COLS;
        int col = random % COLS;
        // if the cell is already true, generate another random number
        while (_generation[row][col]) {
            random = rand() % (ROWS * COLS);
            row = random / COLS;
            col = random % COLS;
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
