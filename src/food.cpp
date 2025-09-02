#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <algorithm>

#include "../include/food.h"
#include "../include/settings.h"

std::mt19937 rng{static_cast<unsigned long>(std::chrono::steady_clock::now().time_since_epoch().count())};

std::uniform_int_distribution<int> randX{0, GRID_WIDTH - 1};
std::uniform_int_distribution<int> randY{0, GRID_HEIGHT - 1};

FoodGenerator::FoodGenerator(Arena* arena, int interval)
    : arena_(arena), interval_(interval){}

sf::Vector2i FoodGenerator::SpawnFood() {
    Food f;
    f.position = {randX(rng), randY(rng)};
    f.value = 1;
    f.rect.setSize({GRID_TILE_SIZE - GRID_MARGIN * 2, GRID_TILE_SIZE - GRID_MARGIN * 2});
    f.rect.setFillColor(sf::Color::Red);
    f.rect.setPosition(f.position.x * GRID_TILE_SIZE + GRID_MARGIN, f.position.y * GRID_TILE_SIZE + GRID_MARGIN);
    
    foods_.push_back(f);
    return f.position;
};

void FoodGenerator::Draw(sf::RenderWindow& window) {
    for (auto f = foods_.begin(); f != foods_.end(); ++f) {
        window.draw(f->rect);
    }
}

int FoodGenerator::GetInterval() {
    return interval_;
}

std::vector<sf::Vector2i> FoodGenerator::GetFoodPositions() {
    std::vector<sf::Vector2i> foodPositions;
    for (Food food : foods_) {
        foodPositions.push_back(food.position);
    }
    return foodPositions;
}

void FoodGenerator::EatFood(sf::Vector2i pos) {
    for (auto it = foods_.begin(); it != foods_.end(); ++it) {
        if (pos == it->position) {
            foods_.erase(it);
            break;
        }
    }
}