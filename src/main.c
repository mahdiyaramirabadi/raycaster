#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "Player.h"


int map[10][10] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,1,1,0,0,1},
    {1,0,0,0,0,0,1,0,0,1},
    {1,0,0,0,0,0,1,0,0,1},
    {1,0,0,0,0,0,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};


int main(void){
    const int screenWidth = 640;
    const int screenHeight = 640;
    const int TILE_SIZE = 64;
    const int MAP_WIDTH = 10;
    const int MAP_HEIGHT = 10;
    Player player;
    player.pos.x = 1 * TILE_SIZE;
    player.pos.y = 1 * TILE_SIZE;
    player.dir.x = 1;
    player.dir.y = 0;
    InitWindow(screenWidth,screenHeight,"Raycaster");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        float dt = GetFrameTime();
        float moveSpeed = 100.0 * dt;
        float rotSpeed = 5.0 * dt;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for(int x=0;x<MAP_WIDTH;x++){
            for(int y=0;y<MAP_HEIGHT;y++){
                int screenX = x * TILE_SIZE;
                int screenY = y * TILE_SIZE;
                if(map[x][y] > 0){
                    DrawRectangle(screenX,screenY,TILE_SIZE,TILE_SIZE,WHITE);
                }else{
                    DrawRectangle(screenX,screenY,TILE_SIZE,TILE_SIZE,BLACK);
                }
                DrawRectangleLines(screenX,screenY,TILE_SIZE,TILE_SIZE,DARKGRAY);
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}