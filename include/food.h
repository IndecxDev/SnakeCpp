#ifndef FOOD_H
#define FOOD_H

class Arena;

#include <SFML/Graphics.hpp>
#include <vector>

struct Food {
    sf::RectangleShape rect;
    sf::Vector2i position;
    int value;
};

class FoodGenerator {
private:
    Arena* arena_;
    std::vector<Food> foods_;
    int interval_;
public:
    FoodGenerator(Arena* arena, int interval);
    int GetInterval();
    void SpawnFood();
    void Draw(sf::RenderWindow& window);
};

#endif