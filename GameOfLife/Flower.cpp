//
//  Flower.cpp
//  FlowerSFML
//
//  Created by Dario Caric on 05.03.2024..
//

#include "Flower.hpp"

using namespace std;
// MARK: PRIVATE:
/**
 Draw sun, yellow circle in th etop left corner
 */
CircleShape Flower::drawSun(int radius, int x, int y){
    CircleShape smallCircle(radius);
    smallCircle.setFillColor(Color::Yellow);
    smallCircle.setOrigin(radius, radius);
    smallCircle.setPosition(x, y);
    return smallCircle;
}

/**
 Draw big red circle, part of the flower
 */
CircleShape Flower::redCircle(int radius, int x, int y){
    CircleShape redCircle(radius);
    redCircle.setFillColor(Color::Red);
    redCircle.setOrigin(radius, radius);
    redCircle.setPosition(x, y);
    return redCircle;
}

/**
 Draw smaller yellow circle, pert of the flower
 */
CircleShape Flower::yellowCircle(int radius, int x, int y){
    CircleShape yellowCircle(radius);
    yellowCircle.setFillColor(Color::Yellow);
    yellowCircle.setOrigin(radius, radius);
    yellowCircle.setPosition(x, y);
    return yellowCircle;
}

/**
 Draw stem, part of the flower
 */
RectangleShape Flower::stem(int width, int height, int x, int y){
    RectangleShape stem(sf::Vector2f(width, height));
    stem.setFillColor(sf::Color::Green);
    stem.setPosition(x, y);
    return stem;
}



// MARK: PUBLIC:
Flower::Flower(RenderWindow *win) {
    window_local = win;
}

/**
 Calls all functions to draw parts for the whole image
 */
void Flower::draw(int sunXLocal) {
    // Draw our shapes to the window
    window_local->draw(drawSun(sunRadius, sunXLocal, sunY));
    window_local->draw(redCircle(flowerRedRadius, flowerX, flowerY));
    window_local->draw(yellowCircle(flowerYellowRadius, flowerX, flowerY));
    window_local->draw(stem(10, 200, 200, 300));
}
