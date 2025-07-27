#include "../include/arena.h"
#include "../include/settings.h"

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
    if (!window_) { 
        throw std::invalid_argument("Window is invalid."); 
    }
    
    clock_ = new sf::Clock();
    
    tileOccupied_.resize(arenaSizeX_);
    for (int i = 0; i < arenaSizeX_; i++) { 
        tileOccupied_[i].resize(arenaSizeY_, false);
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
    foodGen_ = new FoodGenerator(this, 3000);
}

void Arena::Tick() {
    int dt = clock_->restart().asMilliseconds();
    msSnakeTimer_ += dt;
    msSnakeSpeedUpTimer_ += dt;
    msFoodSpawnTimer_ += dt;

    if (msSnakeTimer_ >= snake_->GetInterval()) {
        msSnakeTimer_ = 0;
        snake_->Step();
    }

    if (msSnakeSpeedUpTimer_ >= SNAKE_SPEED_UP_INTERVAL) {
        msSnakeSpeedUpTimer_ = 0;
        snake_->SpeedUp();
    }

    if (msFoodSpawnTimer_ >= foodGen_->GetInterval()) {
        msFoodSpawnTimer_ = 0;
        foodGen_->SpawnFood();
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