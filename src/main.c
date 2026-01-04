#include <math.h>
#include <raylib.h>
#include <stdio.h>

#include "Player.h"

int map[20][20] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

Player RotateM(Player player, float rotSpeed, int d) {
    float OldDirX = player.dir.x;
    player.dir.x =
        player.dir.x * cos(rotSpeed) - d * player.dir.y * sin(rotSpeed);
    player.dir.y = player.dir.y * cos(rotSpeed) + d * OldDirX * sin(rotSpeed);

    float OldPlaneX = player.plane.x;
    player.plane.x =
        player.plane.x * cos(rotSpeed) - d * player.plane.y * sin(rotSpeed);
    player.plane.y =
        player.plane.y * cos(rotSpeed) + d * OldPlaneX * sin(rotSpeed);
    return player;
}

int CheckTargetPos(float posX, float posY) {
    int x = floor(posX / 32), y = floor(posY / 32);
    // printf("%f %f # %d %d %d\n",posX,posY,x,y,map[y][x]);
    if (map[y][x] > 0) return 0;
    return 1;
}

int main(void) {
    const int screenWidth = 1200;
    const int screenHeight = 800;
    const int TILE_SIZE = 32;
    const int MAP_WIDTH = 20;
    const int MAP_HEIGHT = 20;
    const int MINI_TILE_SIZE = 10;
    const int padx = 950, pady = 10;
    Player player;
    player.pos.x = 1 * TILE_SIZE;
    player.pos.y = 1 * TILE_SIZE;
    player.map_pos.x = 1 * MINI_TILE_SIZE;
    player.map_pos.y = 1 * MINI_TILE_SIZE;
    player.dir.x = -1.0;
    player.dir.y = 0.0;
    player.plane.x = 0.0;
    player.plane.y = 0.66;
    InitWindow(screenWidth, screenHeight, "Raycaster");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        float moveSpeed = 100.0 * dt;
        float rotSpeed = 5.0 * dt;
        if (IsKeyDown(KEY_W)) {
            if (CheckTargetPos(player.pos.x + moveSpeed * player.dir.x,
                               player.pos.y + moveSpeed * player.dir.y)) {
                player.pos.y += moveSpeed * player.dir.y;
                player.pos.x += moveSpeed * player.dir.x;
                player.map_pos.y += moveSpeed * player.dir.y / 3.2;
                player.map_pos.x += moveSpeed * player.dir.x / 3.2;
            }
        }
        if (IsKeyDown(KEY_S)) {
            if (CheckTargetPos(player.pos.x - moveSpeed * player.dir.x,
                               player.pos.y - moveSpeed * player.dir.y)) {
                player.pos.y -= moveSpeed * player.dir.y;
                player.pos.x -= moveSpeed * player.dir.x;
                player.map_pos.y -= moveSpeed * player.dir.y / 3.2;
                player.map_pos.x -= moveSpeed * player.dir.x / 3.2;
            }
        }
        if (IsKeyDown(KEY_D)) {
            if (CheckTargetPos(player.pos.x + moveSpeed * player.dir.y,
                               player.pos.y + moveSpeed * player.dir.x)) {
                player.pos.x += moveSpeed * player.dir.y;
                player.pos.y += moveSpeed * player.dir.x;
                player.map_pos.x += moveSpeed * player.dir.y / 3.2;
                player.map_pos.y += moveSpeed * player.dir.x / 3.2;
            }
        }
        if (IsKeyDown(KEY_A)) {
            if (CheckTargetPos(player.pos.x - moveSpeed * player.dir.y,
                               player.pos.y - moveSpeed * player.dir.x)) {
                player.pos.x -= moveSpeed * player.dir.y;
                player.pos.y -= moveSpeed * player.dir.x;
                player.map_pos.x -= moveSpeed * player.dir.y / 3.2;
                player.map_pos.y -= moveSpeed * player.dir.x / 3.2;
            }
        }
        if (IsKeyDown(KEY_RIGHT)) {
            player = RotateM(player, rotSpeed, -1);
        }
        if (IsKeyDown(KEY_LEFT)) {
            player = RotateM(player, rotSpeed, 1);
        }
        BeginDrawing();
        ClearBackground(BLACK);

        for (int x = 0; x < screenWidth; x++) {
            double cameraX = 2 * (x / (double)screenWidth) - 1;
            double rayDirX = player.dir.x + player.plane.x * cameraX;
            double rayDirY = player.dir.y + player.plane.y * cameraX;

            int mapX = floor(player.pos.x / TILE_SIZE),
                mapY = floor(player.pos.y / TILE_SIZE);
            double posX = player.pos.x / TILE_SIZE,
                   posY = player.pos.y / TILE_SIZE;

            double sideDistX, sideDistY;

            double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
            double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
            double perpWallDist;

            int stepX, stepY;

            // DDA
            int hit = 0;
            int side;

            if (rayDirX < 0) {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            } else {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            if (rayDirY < 0) {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            } else {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }

            while (!hit) {
                if (sideDistX < sideDistY) {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                } else {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                if (map[mapY][mapX]) hit = 1;
            }

            if (side == 0)
                perpWallDist = (sideDistX - deltaDistX);
            else
                perpWallDist = (sideDistY - deltaDistY);

            int lineHeight = (int)(screenHeight / perpWallDist);

            int drawStart = screenHeight / 2 - lineHeight / 2;
            if (drawStart < 0) drawStart = 0;
            int drawEnd = screenHeight / 2 + lineHeight / 2;
            if (drawEnd > screenHeight) drawEnd = screenHeight - 1;
            Color color = GRAY;
            if (side == 1) color = DARKGRAY;
            DrawLine(x, 0, x, drawStart, SKYBLUE);
            DrawLine(x, drawStart, x, drawEnd, color);
            DrawLine(x, drawEnd, x, screenHeight, BLACK);
        }
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (map[y][x]) {
                    DrawRectangle(padx + x * MINI_TILE_SIZE,
                                  pady + y * MINI_TILE_SIZE, MINI_TILE_SIZE,
                                  MINI_TILE_SIZE, BLACK);
                } else {
                    DrawRectangle(padx + x * MINI_TILE_SIZE,
                                  pady + y * MINI_TILE_SIZE, MINI_TILE_SIZE,
                                  MINI_TILE_SIZE, WHITE);
                }
                DrawRectangleLines(padx + x * MINI_TILE_SIZE,
                                   pady + y * MINI_TILE_SIZE, MINI_TILE_SIZE,
                                   MINI_TILE_SIZE, DARKGRAY);
            }
        }
        // printf("%f , %f\n",player.pos.x , player.pos.y);

        DrawCircle(padx + player.map_pos.x, pady + player.map_pos.y, 4, RED);
        DrawLine(padx + player.map_pos.x, pady + player.map_pos.y,
                 padx + player.map_pos.x + 10 * player.dir.x,
                 pady + player.map_pos.y + 10 * player.dir.y, RED);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}