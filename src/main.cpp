#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Window");

    int x = 0;
    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    circle.setPosition(x, 0);
                    x += 50;
                    
                }
            }
        }

        window.clear(sf::Color::Black);

        window.draw(circle);

        window.display();
    }
}