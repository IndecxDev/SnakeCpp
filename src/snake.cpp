#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "../include/snake.h"
#include "../include/settings.h"
#include "../include/food.h"
#include "../include/arena.h"

Snake::Snake(Arena* arena, int startX, int startY, int startLength)
    : arena_(arena), 
      direction_(Direction::Up), 
      length_(startLength), 
      speed_(-1), 
      dead_(false)
{
    for (int i = 0; i < length_; i++) {
        sf::RectangleShape shape;
        int gridPosX = startX;
        int gridPosY = startY + i;

        shape.setFillColor(sf::Color::Green);
        shape.setSize(sf::Vector2f(GRID_TILE_SIZE - GRID_MARGIN, GRID_TILE_SIZE - GRID_MARGIN));

        SnakeSegment seg;
        seg.shape_ = shape;
        seg.position_.x = gridPosX;
        seg.position_.y = gridPosY;
        body_.push_back(seg);
    }
    Snake::SpeedUp();
    UpdateSegmentPositions();
}

void Snake::Reset(int startX, int startY, int startLength) {
    direction_ = Direction::Up;
    length_ = startLength;
    dead_ = false;
    speed_ = -1;
    body_.clear();

    for (int i = 0; i < length_; i++) {
        sf::RectangleShape shape;
        int gridPosX = startX;
        int gridPosY = startY + i;

        shape.setFillColor(sf::Color::Green);
        shape.setSize(sf::Vector2f(GRID_TILE_SIZE - GRID_MARGIN, GRID_TILE_SIZE - GRID_MARGIN));

        SnakeSegment seg;
        seg.shape_ = shape;
        seg.position_.x = gridPosX;
        seg.position_.y = gridPosY;
        body_.push_back(seg);
    }
    Snake::SpeedUp();
    UpdateSegmentPositions();
}

void Snake::UpdateSegmentPositions() {
    for (SnakeSegment& seg : body_) {
        if (seg.position_.x < 0) { seg.position_.x += GRID_WIDTH; }
        if (seg.position_.y < 0) { seg.position_.y += GRID_HEIGHT; }
        if (seg.position_.x >= GRID_WIDTH) { seg.position_.x = 0; }
        if (seg.position_.y >= GRID_HEIGHT) { seg.position_.y = 0; }
        seg.shape_.setPosition(seg.position_.x * GRID_TILE_SIZE + GRID_MARGIN / 2, seg.position_.y * GRID_TILE_SIZE + GRID_MARGIN / 2);
    }
}

void Snake::Step() {
    sf::Vector2i dir;
    if (inputBuffer.empty()) {
        switch (direction_) {
            case Direction::Up:
                dir = {0, -1};
                break;
            case Direction::Down:
                dir = {0, 1};
                break;
            case Direction::Left:
                dir = {-1, 0};
                break;
            case Direction::Right:
                dir = {1, 0};
                break;
        }
    }
    else {
        dir = inputBuffer.front();
        inputBuffer.pop();

        if      (dir.y == -1) { direction_ = Direction::Up; }
        else if (dir.y ==  1) { direction_ = Direction::Down; }
        else if (dir.x == -1) { direction_ = Direction::Left; }
        else if (dir.x ==  1) { direction_ = Direction::Right; }
    }

    sf::Vector2i prevPos = body_[0].position_;
    body_[0].position_ += dir;
    for (int i = 1; i < length_; i++) {
        sf::Vector2i currPos = body_[i].position_;
        body_[i].position_ = prevPos;
        prevPos = currPos;
    }

    for (size_t i = 1; i < body_.size(); i++) {
        if (body_[i].position_ == body_[0].position_) {
            dead_ = true;
            break;
        }
    }

    UpdateSegmentPositions();
}

void Snake::Turn(Direction dir) {
    if (inputBuffer.size() > 3) { return; }

    switch (dir) {
        case Direction::Up:
            inputBuffer.push({0, -1});
            break;
        case Direction::Down:
            inputBuffer.push({0, 1});
            break;
        case Direction::Left:
            inputBuffer.push({-1, 0});
            break;
        case Direction::Right:
            inputBuffer.push({1, 0});
            break;
    }
}

int Snake::GetInterval() {
    return interval_;
}

void Snake::SetInterval(int interval) {
    if (interval > 0) {
        interval_ = interval;
    }
}

void Snake::SpeedUp() {
    interval_ = std::max((int)std::ceil(std::pow(0.96, speed_ - 150)), 50) / 2;
    speed_++;
}

void Snake::Draw(sf::RenderWindow& window) {
    for (SnakeSegment& seg : body_) {
        window.draw(seg.shape_);
    }
}