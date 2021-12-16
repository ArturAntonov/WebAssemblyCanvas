#include <stdlib.h>

// Number of circles
#define NUM_CIRCLES 100

// Circle Struct
struct Circle {
  int x; // x coordinate
  int y; // y coordinate
  int r; // r radius
  int cr; // color red
  int cg; // color green
  int cb; // color blue
};

// Circle Animation Data Struct
struct CircleAnimationData {
  int x; // x coordinate
  int y; // y coordinate
  int r; // r radius
  int xv; // x - axis velocity
  int yv; // y - axis velocity
  int xd; // x - axis direction (1 = forward)
  int yd; // y - axis direction (1 = forward)
};

// Circles variable
Circle circles[NUM_CIRCLES];
CircleAnimationData animationData[NUM_CIRCLES];

// Definition on exported functions
extern "C" {
 Circle* getCircles(int canvasWidth, int canvasHeight);
}
// render function from JS
extern void render(int dataLength, int circlesStructSize);

// Random number generator
int getRand(int max) {
  return (rand() % max);
}

// Init circle data and start render - JS

int main() {

  // Seed random number generator
  srand(42);

  // Create circles
  for(int i = 0; i < NUM_CIRCLES; i++) {
    // Radius
    int radius = getRand(20);

    // Coordinates
    int x = getRand(1000) + radius;
    int y = getRand(1000) + radius;

    // Fill animation data struct - i
    animationData[i].x = x;
    animationData[i].y = y;
    animationData[i].r = radius;
    animationData[i].xv = getRand(10);
    animationData[i].yv = getRand(10);
    animationData[i].xd = 1;
    animationData[i].yd = 1;

    // Fill circle struct
    circles[i].x = x;
    circles[i].y = y;
    circles[i].r = radius;
    circles[i].cr = getRand(255);
    circles[i].cg = getRand(255);
    circles[i].cb = getRand(255);

  }

    render(NUM_CIRCLES*6, 6);
}

// Return animated circles to JS
Circle* getCircles(int canvasWidth, int canvasHeight) {
  // Update circle data
  for(int i =0; i < NUM_CIRCLES; i++) {
    // Collision RIGHT - set x direction backwards 0
    if((animationData[i].x + animationData[i].r) >= canvasWidth) {
      animationData[i].xd = 0;
      circles[i].cr = getRand(255);
      circles[i].cg = getRand(255);
      circles[i].cb = getRand(255);
    }
    // Collision LEFT - set x direction forwards 1
    if((animationData[i].x - animationData[i].r) <= 0) {
      animationData[i].xd = 1;
      circles[i].cr = getRand(255);
      circles[i].cg = getRand(255);
      circles[i].cb = getRand(255);
    }
    // Collision TOP - set y direction forwards 1
    if((animationData[i].y - animationData[i].r) <= 0) {
      animationData[i].yd = 1;
      circles[i].cr = getRand(255);
      circles[i].cg = getRand(255);
      circles[i].cb = getRand(255);
    }
    // Collision TOP - set y direction backwards 0
    if((animationData[i].y + animationData[i].r) >= canvasHeight) {
      animationData[i].yd = 0;
      circles[i].cr = getRand(255);
      circles[i].cg = getRand(255);
      circles[i].cb = getRand(255);
    }

    // Move circle in specified direction
    if (animationData[i].xd == 1) {
      animationData[i].x += animationData[i].xv;
    }
    else {
      animationData[i].x -= animationData[i].xv;
    }
    if (animationData[i].yd == 1) {
      animationData[i].y += animationData[i].yv;
    }
    else {
      animationData[i].y -= animationData[i].yv;
    }

    // Update matching circle
    circles[i].x = animationData[i].x;
    circles[i].y = animationData[i].y;
  }

  return circles;
}
