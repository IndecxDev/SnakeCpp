#ifndef ARENA_H
#define ARENA_H

#include "snake.h"
#include "food.h"
#include "settings.h"

#include <SFML/Graphics.hpp>
#include <vector>

class Arena {
private:
    sf::RenderWindow* window_;
    std::vector<std::vector<bool>> tileOccupied_;
    Snake* snake_;
    FoodGenerator* foodGen_;

    sf::Clock* clock_;

    int msSnakeTimer_ = 0;
    int msSnakeSpeedUpTimer_ = 0;
    int msFoodSpawnTimer_ = 0;
    
public:
    const int arenaSizeX_;
    const int arenaSizeY_;
    const int arenaPixelSizeX_;
    const int arenaPixelSizeY_;
    
    Arena(int width, int height, sf::RenderWindow* window);
    ~Arena();

    void Turn(Direction dir);
    void Reset();
    void Tick();
    void Draw();
};


#endif