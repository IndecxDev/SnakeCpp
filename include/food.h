#include <vector>

#ifndef FOOD_H
#define FOOD_H

struct Food {
    sf::RectangleShape rect;
    sf::Vector2i position;
    int value;
};

class FoodGenerator {
private:
    std::vector<Food> foods_;
    int interval_;
public:
    FoodGenerator(int interval) : interval_(interval) {};
    int GetInterval();
    void SpawnFood();
    void Draw(sf::RenderWindow& window);
};

#endif