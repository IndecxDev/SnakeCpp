#ifndef SETTINGS_H
#define SETTINGS_H

inline constexpr int WINDOW_WIDTH            = 1000;
inline constexpr int WINDOW_HEIGHT           = 1000;

inline constexpr int GRID_TILE_SIZE          = 40;
inline constexpr int GRID_WIDTH              = WINDOW_WIDTH / GRID_TILE_SIZE;
inline constexpr int GRID_HEIGHT             = WINDOW_HEIGHT / GRID_TILE_SIZE;
inline constexpr int GRID_MARGIN             = 4;

inline constexpr int SNAKE_START_LENGTH      = 8;
inline constexpr int SNAKE_SPEED_UP_INTERVAL = 3000;
inline constexpr int SNAKE_START_X           = GRID_WIDTH / 2;
inline constexpr int SNAKE_START_Y           = GRID_HEIGHT / 2;

#endif