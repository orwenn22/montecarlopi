#include <raylib.h>

#include <math.h>
#include <random>
#include <stdio.h>

unsigned long point_count = 0;      // number of points placed
unsigned long point_in_circle = 0;  // number of points inside the circle
double proportion_in_circle = 0.0f; // point_in_circle / point_count
RenderTexture rt;   //This is where the point are being drawn


//Generate a random value between -1 and 1
float GetRandomCoord() {
    float val = (float)((rand()%200001)-100000);    //value between -100000 and 100000
    return val/100000;
}

//Place a point and verify if it is inside the circle
void PlaceRandomPoint() {
    point_count += 1;
    float x = GetRandomCoord();
    float y = GetRandomCoord();

    if(x*x + y*y <= 1.0f) {     //inside the circle
        point_in_circle += 1;
        DrawPixel(round(256.0f + x*200.0f), round(256.0f + y*200.0f), GREEN);
    }
    else {  //outside
        DrawPixel(round(256.0f + x*200.0f), round(256.0f + y*200.0f), RED);
    }
    proportion_in_circle = (double)point_in_circle / (double)point_count;
}

int main() {
    srand(time(0));     //random seed
    InitWindow(512, 512, "Monte Carlo");

    rt = LoadRenderTexture(512, 512);
    BeginTextureMode(rt);
        //Axes
        DrawLine(256, 0, 256, 512, GRAY);
        DrawLine(0, 256, 512, 256, GRAY);

        DrawText("1", 259, 46, 10, GRAY);
        DrawText("-1", 259, 458, 10, GRAY);
        DrawText("-1", 42, 259, 10, GRAY);
        DrawText("1", 460, 259, 10, GRAY);


        //Circle
        DrawCircleLines(256, 256, 200, YELLOW);
    EndTextureMode();

    while(!WindowShouldClose()) {
        if(IsKeyDown(KEY_SPACE)) {
            BeginTextureMode(rt);
                for(int i = 0; i < 100; i++) {
                    PlaceRandomPoint();
                }
            EndTextureMode();
        }

        if(IsKeyPressed(KEY_ENTER)) {
            BeginTextureMode(rt);
                PlaceRandomPoint();
            EndTextureMode();
        }

        if(IsKeyDown(KEY_F)) {
            BeginTextureMode(rt);
                for(int i = 0; i < 100000; i++) {
                    PlaceRandomPoint();
                }
            EndTextureMode();
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexturePro(
                rt.texture,
                {0, 0, 512, -512},  //flip vertically so the origin is at the top left
                {0, 0, 512, 512},
                {0, 0},
                0.0f,
                WHITE
            );
            DrawText(TextFormat("Point count : %lu", point_count)        , 2, 2, 20, WHITE);
            DrawText(TextFormat("Point in circle : %lu", point_in_circle), 2, 24, 20, WHITE);

            DrawText(TextFormat("Proportion : %lf", proportion_in_circle), 266, 2, 20, WHITE);
            DrawText(TextFormat("PI : %lf", proportion_in_circle*4)      , 266, 24, 20, WHITE);

            DrawText(TextFormat("Press enter/hold space : place points"), 10, 466, 20, WHITE);
            DrawText(TextFormat("Hold F : place 100 000 points"), 10, 488, 20, WHITE);
        EndDrawing();
    }

    UnloadRenderTexture(rt);
    CloseWindow();
    return 0;
}