#ifndef CONSTANTS
#define CONSTANTS

const int TILES_X = 14;
const int TILES_Y = 13;
const int OFFSET_X = 20;
const int OFFSET_Y = 20;
const int X_TILE_SIZE = 40;
const int Y_TILE_SIZE = 40;
const int POOLS_COUNT = 5;

const int POOL_SPACE = (1.0f/(POOLS_COUNT - 1))*(((TILES_X * X_TILE_SIZE) - (2 * OFFSET_X)) - (POOLS_COUNT * X_TILE_SIZE));

const float FROG_SPEED = 180.0f;


#endif CONSTANTS 