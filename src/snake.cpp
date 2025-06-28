#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>

#include "../include/snake.h"
#include "../include/settings.h"

void Snake::UpdateSegmentPositions() {
    for (SnakeSegment& seg : body_) {
        if (seg.position_.x < 0) { seg.position_.x += GRID_WIDTH; }
        if (seg.position_.y < 0) { seg.position_.y += GRID_HEIGHT; }
        if (seg.position_.x >= GRID_WIDTH) { seg.position_.x = 0; }
        if (seg.position_.y >= GRID_HEIGHT) { seg.position_.y = 0; }
        seg.shape_.setPosition(seg.position_.x * GRID_TILE_SIZE, seg.position_.y * GRID_TILE_SIZE);
    }
}

Snake::Snake(int startX, int startY, int startLength)
    : direction_(Direction::Up), length_(startLength), speed_(-1) {
    for (int i = 0; i < length_; i++) {
        sf::RectangleShape shape;
        int gridPosX = startX;
        int gridPosY = startY + i;

        shape.setFillColor(sf::Color::Green);
        shape.setSize(sf::Vector2f(GRID_TILE_SIZE, GRID_TILE_SIZE));

        SnakeSegment seg;
        seg.shape_ = shape;
        seg.position_.x = gridPosX;
        seg.position_.y = gridPosY;
        body_.push_back(seg);
    }
    Snake::SpeedUp();
    UpdateSegmentPositions();
}

void Snake::Step() {
    sf::Vector2i dir;
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

    sf::Vector2i prevPos = body_[0].position_;
    body_[0].position_ += dir;
    for (int i = 1; i < length_; i++) {
        sf::Vector2i currPos = body_[i].position_;
        body_[i].position_ = prevPos;
        prevPos = currPos;
    }

    UpdateSegmentPositions();
}

void Snake::Turn(Direction dir) {
    direction_ = dir;
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
    int newInterval = std::max((int)std::ceil(std::pow(0.96, speed_ - 150)), 50);
    std::cout << interval_ << " -> " << newInterval << std::endl;
    speed_++;
    interval_ = newInterval;
}

void Snake::Draw(sf::RenderWindow& window) {
    for (SnakeSegment& seg : body_) {
        window.draw(seg.shape_);
    }
}