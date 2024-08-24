#include "floodfill.h"

void Floodfill::initFloodfill(){
    m_dir = START_DIR;
    m_x = 0;
    m_y = 0;
    for (int i = 0; i < MAZESIDE_SIZE; i++){
        for (int j = 0; j < MAZESIDE_SIZE; j++){
            for (int k = 0; k < 4; k++){
                maze[i][j].blocked[k] = 0;
            }
            maze[i][j].distance_to_dest = 0;
            maze[i][j].visited = 0;
        }
    }

    for (int i = 0; i < MAZESIDE_SIZE; i++){
        maze[i][0].blocked[DIR_LEFT] = 1;
        maze[i][MAZESIDE_SIZE - 1].blocked[DIR_RIGHT] = 1;
        maze[0][i].blocked[DIR_UP] = 1;
        maze[MAZESIDE_SIZE - 1][i].blocked[DIR_DOWN] = 1;
    }
}

void Floodfill::floodfillToCenter(){
    for (u8 i = 0; i < MAZESIDE_SIZE; i++){
        for (u8 j = 0; j < MAZESIDE_SIZE; j++){
        maze[i][j].distance_to_dest = INF;
        }
    }
    for (u8 i = MAZESIDE_SIZE/2; i < MAZESIDE_SIZE/2 + 1; i++){
        for (u8 j = MAZESIDE_SIZE/2; j < MAZESIDE_SIZE/2 + 1; j++){
            maze[i][j].distance_to_dest = 0;
            q.push(std::make_pair(i, j));
        }
    }
    while(!q.empty()){
        auto u = q.front();
        q.pop();
        for (u8 i = 0; i < 4; i++){
            if (!maze[u.first][u.second].blocked[i] && maze[u.first + dx[i]][u.second + dy[i]].distance_to_dest == INF){
                maze[u.first + dx[i]][u.second + dy[i]].distance_to_dest = maze[u.first][u.second].distance_to_dest + 1;
                q.push(std::make_pair(u.first + dx[i], u.second + dy[i]));
            }
        }
    }
}

bool Floodfill::checkFinish(u8 destination){
    return (destination == DEST_CENTER 
        && MAZESIDE_SIZE/2 <= m_x && m_x <= MAZESIDE_SIZE/2 + 1 
        && MAZESIDE_SIZE/2 <= m_y && m_y <= MAZESIDE_SIZE/2 + 1)
    || (destination == DEST_SOURCE
        && m_x == 0
        && m_y == 0);
}

void Floodfill::updateWalls(u8 m_view[4], u8 destination){
    for (int i = 0; i < 4; i++){
        if (i == DIR_DOWN) continue;
        u8 new_dir = dir_change(m_dir, i);
        if (!maze[m_x][m_y].blocked[new_dir] && m_view[i]){
            maze[m_x][m_y].blocked[new_dir] = 0;
            maze[m_x + dx[new_dir]][m_y + dy[new_dir]].blocked[dir_change(m_dir, i + 2)] = 0;
        }
    }
    maze[m_x][m_y].visited = 1;
}

u8 Floodfill::getNextCommand(u8 forward_blocked, u8 left_blocked, u8 right_blocked, u8 destination){
    u8 view_blocked[4] = { forward_blocked, left_blocked, 0, right_blocked };
    if (checkFinish(destination)){
        return COMMAND_STOP;
    }
    if (!maze[m_x][m_y].visited){
        updateWalls(view_blocked, destination);
    }

    u8 best_dir = DIR_UP;
    u8 best_dist = INF;
    for (int i = 0; i < 4; i++){
        u8 new_dir = dir_change(m_dir, i);
        if (!maze[m_x][m_y].blocked[new_dir] && maze[m_x + dx[new_dir]][m_y + dy[new_dir]].distance_to_dest < best_dist){
            best_dist = maze[m_x + dx[new_dir]][m_y + dy[new_dir]].distance_to_dest;
            best_dir = i;
        }
    }

    if (best_dist >= maze[m_x][m_y].distance_to_dest){
        if (destination == DEST_CENTER){
            floodfillToCenter();
        }else{
            floodfillToSource();
        }
        return getNextCommand(forward_blocked, left_blocked, right_blocked, destination);
    }

    return best_dir;
}

void Floodfill::changeDir(u8 dir){
  m_dir = dir_change(m_dir, dir);
}

void Floodfill::goForward(){
  m_x += dx[m_dir];
  m_y += dy[m_dir];
}

void Floodfill::doCommand(u8 dir){
    changeDir(dir);
    goForward();
}