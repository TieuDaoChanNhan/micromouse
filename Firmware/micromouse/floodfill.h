#ifndef __MICROMOUSE_FLOODFILL_H__
#define __MICROMOUSE_FLOODFILL_H__

#include <queue>

#define DIR_UP 0
#define DIR_LEFT 1
#define DIR_DOWN 2
#define DIR_RIGHT 3

#define COMMAND_STOP 5

#define DEST_CENTER 0 
#define DEST_SOURCE 1

/**
 * floodfill.h
 * 
 * class Floodfill():
 * 
 * Floodfill::initFloodfill(): initialize maze and position

 * 
 * Floodfill::getNextCommand(u8 forward_blocked, u8 left_blocked, u8 right_blocked, u8 destination):
 *      returns an unsigned 8-bit integer from 0-4 corresponding with COMMAND_XXXX
 * 
 *  Params: XXXX_blocked: 0 if there is no wall, 1 if there is wall
 *          destination: either DEST_CENTER or DEST_SOURCE
 * 
 * Floodfill::changeDir(u8 dir):
 *  changes internal direction by relative direction --- new_dir = (current_dir + relative_dir)%4
 *  dir is either DIR_UP, DIR_LEFT, DIR_DOWN, DIR_RIGHT - corresponding with forward, left, behind and right
 *
 * Floodfill::goForward():
 *  go one square forward with current direction on the maze
 * 
 */

/* Begin parameters to change */

#define MAZESIDE_SIZE 12

#define START_DIR DIR_DOWN

/* End parameters to change */

#define INF 1000000007

typedef unsigned char u8;
typedef unsigned int u32;

#define dir_change(x, y) (x+y)%4

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

struct MazeSquare {
  bool blocked[4];
  u32 distance_to_dest;
  bool visited; 
};

class Floodfill {
private:
  MazeSquare maze[MAZESIDE_SIZE][MAZESIDE_SIZE];
  std::queue<std::pair<u32, u32>> q;
  u8 m_dir;
  u8 m_x, m_y;
  void floodfillToCenter();
  void floodfillToSource();
  bool checkFinish(u8 destination);
  void updateWalls(u8 m_view[4], u8 destination);
public:
  void initFloodfill();
  u8 getNextCommand(u8 forward_blocked, u8 left_blocked, u8 right_blocked, u8 destination);
  void changeDir(u8 dir);
  void goForward();
  void doCommand(u8 dir);
};

#endif /* __MICROMOUSE_FLOODFILL_H__ */