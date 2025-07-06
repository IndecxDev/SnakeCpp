#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <algorithm> 

#include "../include/food.h"
#include "../include/settings.h"

std::mt19937 rng{std::chrono::steady_clock::now().time_since_epoch().count()};

std::uniform_int_distribution<int> randX{0, GRID_WIDTH - 1};
std::uniform_int_distribution<int> randY{0, GRID_HEIGHT - 1};

void FoodGenerator::SpawnFood() {
    Food f;
    f.position = {randX(rng), randY(rng)};
    f.value = 1;
    f.rect.setSize({GRID_TILE_SIZE - GRID_MARGIN * 2, GRID_TILE_SIZE - GRID_MARGIN * 2});
    f.rect.setFillColor(sf::Color::Red);
    f.rect.setPosition(f.position.x * GRID_TILE_SIZE + GRID_MARGIN, f.position.y * GRID_TILE_SIZE + GRID_MARGIN);
    
    foods_.push_back(f);
};

void FoodGenerator::Draw(sf::RenderWindow& window) {
    for (Food& f : foods_) {
        window.draw(f.rect);
    }
}

int FoodGenerator::GetInterval() {
    return interval_;
}