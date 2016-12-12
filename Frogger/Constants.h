#ifndef CONSTANTS
#define CONSTANTS

const int TILES_X = 14;
const int TILES_Y = 13;
const int OFFSET_X = 20;
const int OFFSET_Y = 20;
const int X_TILE_SIZE = 40;
const int Y_TILE_SIZE = 40;
const int POOLS_COUNT = 5;
const float POOL_VALID_INTERSECTION = 0.75;

const int POOL_SPACE = (int) ((1.0f/(POOLS_COUNT - 1))*(((TILES_X * X_TILE_SIZE) - (2 * OFFSET_X)) - (POOLS_COUNT * X_TILE_SIZE)));

const float FROG_SPEED = 180.0f;
const int FROG_START_ROW = 1;

const int WINDOW_WIDTH = 560;
const int WINDOW_HEIGHT = 590;

const float SPEED_CAR_YELLOW = -30.0f;
const float SPEED_CAR_WHITE = 80.0f;
const float SPEED_CAR_RED = -45.0f;
const float SPEED_TRUCK = -60.0f;
const float SPEED_CAR_ORANGE = 50.0f;
const float SPEED_LARGE_TREE = 90.0f;
const float SPEED_MEDIUM_TREE = 60.0f;
const float SPEED_SMALL_TREE = 40.0f;
const float SPEED_TWO_ELEMENT_CHAIN = -50.0f;
const float SPEED_THREE_ELEMENT_CHAIN = -50.0f;
const float SPEED_SNAKE = 20.0f;

#endif CONSTANTS 