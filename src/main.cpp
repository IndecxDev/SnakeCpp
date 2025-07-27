#include <iostream>
#include <SFML/Graphics.hpp>

#include "../include/settings.h"
#include "../include/arena.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Window", sf::Style::Close);
    window.setFramerateLimit(60);

    Arena arena = Arena(GRID_WIDTH, GRID_HEIGHT, &window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Right:
                    arena.Turn(Direction::Right);
                    break;
                case sf::Keyboard::Left:
                    arena.Turn(Direction::Left);
                    break;
                case sf::Keyboard::Up:
                    arena.Turn(Direction::Up);
                    break;
                case sf::Keyboard::Down:
                    arena.Turn(Direction::Down);
                    break;
                default:
                break;
                }
            }
        }

        arena.Tick();
        
        window.clear(sf::Color::Black);

        arena.Draw();

        window.display();
    }
}

void Reset() {

}