#include "../include/arena.h"
#include "../include/settings.h"
#include <iostream>

Arena::Arena(int width, int height, sf::RenderWindow* window)
    : window_(window),
      snake_(nullptr),
      foodGen_(nullptr),
      clock_(nullptr),
      arenaSizeX_(width),
      arenaSizeY_(height), 
      arenaPixelSizeX_(GRID_TILE_SIZE * arenaSizeX_),
      arenaPixelSizeY_(GRID_TILE_SIZE * arenaSizeY_)
{
    if (!window_) { throw std::invalid_argument("Window is invalid."); }
    
    clock_ = new sf::Clock();
    
    tiles_.resize(arenaSizeX_);
    for (int i = 0; i < arenaSizeX_; i++) { 
        tiles_[i].resize(arenaSizeY_, TileState::Empty);
    }

    Reset();
}

void Arena::Turn(Direction dir) {
    snake_->Turn(dir);
}

void Arena::Reset() {
    if (snake_) { delete snake_; snake_ = nullptr; }
    if (foodGen_) { delete foodGen_; foodGen_ = nullptr; }

    snake_ = new Snake(this, arenaSizeX_ / 2, arenaSizeY_ / 2, 3);

    std::vector<sf::Vector2i> body = snake_->GetBodyPositions();
    for (sf::Vector2i pos : body) {
        tiles_[pos.y][pos.x] = TileState::SnakeBody;
    }

    foodGen_ = new FoodGenerator(this, 3000);
}

void Arena::Tick() {
    int dt = clock_->restart().asMilliseconds();
    msSnakeTimer_ += dt;
    msSnakeSpeedUpTimer_ += dt;
    msFoodSpawnTimer_ += dt;

    if (msSnakeTimer_ >= snake_->GetInterval()) {
        msSnakeTimer_ = 0;
        sf::Vector2i backBody = snake_->GetBack();
        snake_->Step();
        sf::Vector2i frontBody = snake_->GetFront();

        tiles_[backBody.y][backBody.x] = TileState::Empty;
        tiles_[frontBody.y][frontBody.x] = TileState::SnakeBody;

        std::vector<sf::Vector2i> foodPositions = foodGen_->GetFoodPositions();
        for (sf::Vector2i foodPos : foodPositions) {
            if (foodPos == frontBody) {
                foodGen_->EatFood(foodPos);
                tiles_[backBody.y][backBody.x] = TileState::SnakeBody;
                snake_->Grow(backBody);
                break;
            }
        }
        
        // Debug purposes
        /*
        for (std::vector<TileState> tilesY : tiles_) {
            for (TileState tile : tilesY) {
                if (tile == TileState::Empty) { std::cout << "."; }
                if (tile == TileState::SnakeBody) { std::cout << "#"; }
                if (tile == TileState::Food) { std::cout << "*"; }
            }
            std::cout << "\n";
        }
        std::cout << "\n---\n";
        */
    }

    if (msSnakeSpeedUpTimer_ >= SNAKE_SPEED_UP_INTERVAL) {
        msSnakeSpeedUpTimer_ = 0;
        snake_->SpeedUp();
    }

    if (msFoodSpawnTimer_ >= foodGen_->GetInterval()) {
        msFoodSpawnTimer_ = 0;
        sf::Vector2i foodPos = foodGen_->SpawnFood();
        tiles_[foodPos.y][foodPos.x] = TileState::Food;
    }
}

void Arena::Draw() {
    snake_->Draw(*window_);
    foodGen_->Draw(*window_);
}

Arena::~Arena() {
    delete snake_;
    delete foodGen_;
    delete clock_;
}