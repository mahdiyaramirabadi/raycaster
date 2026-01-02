#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "Player.h"


int map[20][20] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

Player RotateM(Player player ,float rotSpeed, int d){
    float OldDirX = player.dir.x;
    player.dir.x = player.dir.x * cos(rotSpeed)  - d * player.dir.y * sin(rotSpeed);
    player.dir.y = player.dir.y * cos(rotSpeed) + d * OldDirX * sin(rotSpeed);

    float OldPlaneX = player.plane.x;
    player.plane.x = player.plane.x * cos(rotSpeed)  - d * player.plane.y * sin(rotSpeed);
    player.plane.y = player.plane.y * cos(rotSpeed) + d * OldPlaneX * sin(rotSpeed);
    return player;
}

int CheckTargetPos(float posX , float posY){
    int x = floor(posX/32) , y = floor(posY/32);
    printf("%f %f # %d %d %d\n",posX,posY,x,y,map[y][x]);
    if(map[y][x] > 0)return 0;
    return 1;
}

int main(void){
    const int screenWidth = 640;
    const int screenHeight = 640;
    const int TILE_SIZE = 32;
    const int MAP_WIDTH = 20;
    const int MAP_HEIGHT = 20;
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
        for(int y=0;y<MAP_HEIGHT;y++){
            for(int x=0;x<MAP_WIDTH;x++){
                int screenX = x * TILE_SIZE;
                int screenY = y * TILE_SIZE;
                if(map[y][x] > 0){
                    DrawRectangle(screenX,screenY,TILE_SIZE,TILE_SIZE,WHITE);
                }else{
                    DrawRectangle(screenX,screenY,TILE_SIZE,TILE_SIZE,BLACK);
                }
                DrawRectangleLines(screenX,screenY,TILE_SIZE,TILE_SIZE,DARKGRAY);
            }
        }
        if(IsKeyDown(KEY_W)){
            if(CheckTargetPos(player.pos.x + moveSpeed * player.dir.x, player.pos.y + moveSpeed * player.dir.y))
               { player.pos.y += moveSpeed * player.dir.y;
                player.pos.x += moveSpeed * player.dir.x;}
        }
        if(IsKeyDown(KEY_S)){
            if(CheckTargetPos(player.pos.x - moveSpeed * player.dir.x, player.pos.y - moveSpeed * player.dir.y))
                {player.pos.y -= moveSpeed * player.dir.y;
                player.pos.x -= moveSpeed * player.dir.x;}
        }
        if(IsKeyDown(KEY_D)){
            if(CheckTargetPos(player.pos.x + moveSpeed * player.dir.y, player.pos.y + moveSpeed * player.dir.x))
                {player.pos.x += moveSpeed * player.dir.y;
                player.pos.y += moveSpeed * player.dir.x;}
        }
        if(IsKeyDown(KEY_A)){
            if(CheckTargetPos(player.pos.x - moveSpeed * player.dir.y, player.pos.y - moveSpeed * player.dir.x))
                {player.pos.x -= moveSpeed * player.dir.y;
                player.pos.y -= moveSpeed * player.dir.x;}
        }
        if(IsKeyDown(KEY_RIGHT)){
            player = RotateM(player , rotSpeed , 1);
        }
        if(IsKeyDown(KEY_LEFT)){
            player = RotateM(player , rotSpeed,  -1);
        }
        DrawCircle(player.pos.x,player.pos.y , 10 , RED);
        DrawLine(player.pos.x , player.pos.y , player.pos.x + 20*player.dir.x , player.pos.y + 20*player.dir.y, BLUE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}