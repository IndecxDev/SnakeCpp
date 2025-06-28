#include <SFML/Graphics.hpp>
#include <iostream>

#include "../include/settings.h"
#include "../include/snake.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Window", sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Clock clock;

    int msSnakeTimer = 0;
    Snake snake{SNAKE_START_X, SNAKE_START_Y, SNAKE_START_LENGTH, SNAKE_START_INTERVAL};

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
                        snake.Turn(Direction::Right);
                        break;
                    case sf::Keyboard::Left:
                        snake.Turn(Direction::Left);
                        break;
                    case sf::Keyboard::Up:
                        snake.Turn(Direction::Up);
                        break;
                    case sf::Keyboard::Down:
                        snake.Turn(Direction::Down);
                        break;
                    default:
                    break;
                }
                
            }
        }

        window.clear(sf::Color::Black);
        
        int dt = clock.restart().asMilliseconds();
        msSnakeTimer += dt;

        if (msSnakeTimer >= snake.getInterval()) {
            msSnakeTimer = 0;
            snake.Step();
        }

        snake.Draw(window);
        window.display();
    }
}