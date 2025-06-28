#ifndef SETTINGS_H
#define SETTINGS_H

inline constexpr int WINDOW_WIDTH         = 1000;
inline constexpr int WINDOW_HEIGHT        = 800;

inline constexpr int GRID_TILE_SIZE       = 25;   // How big a grid tile is
inline constexpr int GRID_WIDTH           = WINDOW_WIDTH / GRID_TILE_SIZE;
inline constexpr int GRID_HEIGHT          = WINDOW_HEIGHT / GRID_TILE_SIZE;

inline constexpr int SNAKE_START_X        = GRID_WIDTH / 2;
inline constexpr int SNAKE_START_Y        = GRID_HEIGHT / 2;
inline constexpr int SNAKE_START_LENGTH   = 8;
inline constexpr int SNAKE_START_INTERVAL = 100; // Starting time interval in ms between snake steps

#endif