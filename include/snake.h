#ifndef SNAKE_H
#define SNAKE_H

enum class Direction { Up, Down, Left, Right };

struct SnakeSegment {
    sf::RectangleShape shape_;
    sf::Vector2i position_;
};

class Snake {
private:
    std::vector<SnakeSegment> body_;
    Direction direction_;
    int interval_;
    int length_;

    void UpdateSegmentPositions();
public:
    Snake(const int startX, const int startY, const int startLength, const int startInterval);
    void Step();
    void Turn(Direction dir);
    int getInterval();
    void setInterval(int interval);
    void Draw(sf::RenderWindow& window);
};

#endif