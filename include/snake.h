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
    int speed_;

    void UpdateSegmentPositions();
public:
    Snake(int startX, int startY, int startLength);
    void Step();
    void Turn(Direction dir);
    int GetInterval();
    void SetInterval(int interval);
    void SpeedUp();
    void Draw(sf::RenderWindow& window);
};

#endif