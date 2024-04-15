//
//  main.cpp
//  FlowerSFML
//
//  Created by Dario Caric on 05.03.2024..
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <stdlib.h>
#include <chrono>

#include "Flower.hpp"
#include "game_of_life.hpp"

using namespace std;

void showFlower(){
    
    RenderWindow window(VideoMode(800, 600), "Hello, SFML world!");
    window.setFramerateLimit(60);
    Flower flower(&window);

    // Draw our shapes to the window
    int sunXLocal = 40;
    Vector2u size = window.getSize();
    

    int direction = 1;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        sunXLocal = sunXLocal + direction;
        
        //cout << "sunXLocal: " << sunXLocal << endl;
        if (sunXLocal == size.x - 40) direction = (-1) * direction;
        else if (sunXLocal == 40) direction = (-1) * direction;
        
        window.clear();
        flower.draw(sunXLocal);
        window.display();
    }

    
}

void runNonGraphicsGameOfLife() {
    cout << "Welcome to the Game of Life!" << endl;
    cout << "Press Ctrl+C to stop the game." << endl;
    cout << "Enter percentage of live cells (0-100):";
    int percentage;
    cin >> percentage;
    if (percentage < 0 || percentage > 100) {
        cerr << "Percentage must be between 0 and 100." << endl;
        exit(1);
    }
    
    // initializes the game
    game_of_life gameOfLife(percentage);
    
    int cycle = 0;
    //for (int i = 0; i < 500; i++) {
    while (true) {
        cycle++;
        // draws the game
        gameOfLife.draw(cycle); // ONLY FOR NON SMFL
        
        // runs next generation
        gameOfLife.next_generation();
        
        // waits for 2 second
        this_thread::sleep_for(std::chrono::milliseconds(100));
        
        // Clears the console for windos and macos/linux
        #ifdef _WIN32
            system("cls");
        #else
            // Set the TERM environment variable
            setenv("TERM", "xterm", 1);
            //system("clear");
            char* term_type = getenv("TERM");
            if (term_type == nullptr) {
                cerr << "Terminal type is not set. Some operations may not work." << endl;
                // Handle accordingly, perhaps by avoiding clear screen or other terminal-specific functions
            } else {
                system("clear");
            }
        #endif
    }
    
}

void showGameOfLifeGraphics() {
    RenderWindow window(VideoMode(500, 500), "Game Of Life");
    window.setFramerateLimit(60);
    
    game_of_life gameOfLife(&window);
    
    
    cout << "Welcome to the Game of Life!" << endl;
    cout << "Press Ctrl+C to stop the game." << endl;
    cout << "Enter percentage of live cells (0-100):";
    int percentage;
    cin >> percentage;
    if (percentage < 0 || percentage > 100) {
        cerr << "Percentage must be between 0 and 100." << endl;
        exit(1);
    }
    
    

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        
        long lifeCycles = 0;
        // here comes main part of the game
        while (true) {
            // draws the gamež
            lifeCycles++;
            window.clear();
            gameOfLife.drawGraphics(lifeCycles);

            stringstream sstr;
            sstr << "Game Of Life cycle: " << lifeCycles;
            window.setTitle(sstr.str());
            window.display();
            
            // calculates next generation
            gameOfLife.next_generation();
            
            // waits for 2 second
            this_thread::sleep_for(std::chrono::milliseconds(100));
            
            // Clears the console for windos and macos/linux
            #ifdef _WIN32
                system("cls");
            #else
                // Set the TERM environment variable
                setenv("TERM", "xterm", 1);
                //system("clear");
                char* term_type = getenv("TERM");
                if (term_type == nullptr) {
                    cerr << "Terminal type is not set. Some operations may not work." << endl;
                    // Handle accordingly, perhaps by avoiding clear screen or other terminal-specific functions
                } else {
                    system("clear");
                }
            #endif
        }
        
    }
}
int main() {
    
    // 1 task - Flower
    //showFlower();
    
    // 2 task Game Of Life
    showGameOfLifeGraphics();
    
    return 0;
}
