#include <raylib-cpp.hpp>

#include <dachWFC.hpp>
#include <sstream>
#include <chrono>


uint64_t nanoTime(){
    using namespace std;
    using namespace chrono;
    return duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
}


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void){
    const int screenWidth = 1200;
    const int screenHeight = 1200;
    raylib::InitWindow(screenWidth, screenHeight, "wfc");
    SetTargetFPS(60);

    dachWFC wfc;

    pattern p0(3,3);
    p0.frequency = 1;
    p0.rules[UP].insert(6);
    p0.rules[RIGHT].insert(2);
    p0.rules[RIGHT].insert(3);
    p0.rules[RIGHT].insert(4);
    p0.rules[DOWN].insert(1);
    p0.rules[DOWN].insert(3);
    p0.rules[DOWN].insert(5);
    p0.rules[LEFT].insert(6);
    p0(0,0) = 1;
    p0(1,0) = 1;
    p0(2,0) = 1;

    p0(0,1) = 1;
    p0(1,1) = 0;
    p0(2,1) = 0;

    p0(0,2) = 1;
    p0(1,2) = 0;
    p0(2,2) = 1;

    pattern p1(3,3);
    p1.frequency = 1;
    p1.rules[UP].insert(0);
    p1.rules[UP].insert(5);
    p1.rules[UP].insert(4);
    p1.rules[RIGHT].insert(2);
    p1.rules[RIGHT].insert(3);
    p1.rules[RIGHT].insert(4);
    p1.rules[DOWN].insert(6);
    p1.rules[LEFT].insert(6);
    p1(0,0) = 1;
    p1(1,0) = 0;
    p1(2,0) = 1;

    p1(0,1) = 1;
    p1(1,1) = 0;
    p1(2,1) = 0;

    p1(0,2) = 1;
    p1(1,2) = 1;
    p1(2,2) = 1;

    pattern p2(3,3);
    p2.frequency = 1;
    p2.rules[UP].insert(6);
    p2.rules[RIGHT].insert(2);
    p2.rules[RIGHT].insert(3);
    p2.rules[RIGHT].insert(4);
    p2.rules[DOWN].insert(6);
    p2.rules[LEFT].insert(0);
    p2.rules[LEFT].insert(1);
    p2.rules[LEFT].insert(2);
    p2(0,0) = 1;
    p2(1,0) = 1;
    p2(2,0) = 1;

    p2(0,1) = 0;
    p2(1,1) = 0;
    p2(2,1) = 0;

    p2(0,2) = 1;
    p2(1,2) = 1;
    p2(2,2) = 1;

    pattern p3(3,3);
    p3.frequency = 1;
    p3.rules[UP].insert(0);
    p3.rules[UP].insert(4);
    p3.rules[UP].insert(5);
    p3.rules[RIGHT].insert(6);
    p3.rules[DOWN].insert(6);
    p3.rules[LEFT].insert(0);
    p3.rules[LEFT].insert(1);
    p3.rules[LEFT].insert(2);
    p3(0,0) = 1;
    p3(1,0) = 0;
    p3(2,0) = 1;

    p3(0,1) = 0;
    p3(1,1) = 0;
    p3(2,1) = 1;

    p3(0,2) = 1;
    p3(1,2) = 1;
    p3(2,2) = 1;

    pattern p4(3,3);
    p4.frequency = 1;
    p4.rules[UP].insert(6);
    p4.rules[RIGHT].insert(6);
    p4.rules[DOWN].insert(1);
    p4.rules[DOWN].insert(3);
    p4.rules[DOWN].insert(5);
    p4.rules[LEFT].insert(0);
    p4.rules[LEFT].insert(1);
    p4.rules[LEFT].insert(2);
    p4(0,0) = 1;
    p4(1,0) = 1;
    p4(2,0) = 1;

    p4(0,1) = 0;
    p4(1,1) = 0;
    p4(2,1) = 1;

    p4(0,2) = 1;
    p4(1,2) = 0;
    p4(2,2) = 1;

    pattern p5(3,3);
    p5.frequency = 1;
    p5.rules[UP].insert(0);
    p5.rules[UP].insert(4);
    p5.rules[UP].insert(5);
    p5.rules[RIGHT].insert(6);
    p5.rules[DOWN].insert(1);
    p5.rules[DOWN].insert(3);
    p5.rules[DOWN].insert(5);
    p5.rules[LEFT].insert(6);
    p5(0,0) = 1;
    p5(1,0) = 0;
    p5(2,0) = 1;

    p5(0,1) = 1;
    p5(1,1) = 0;
    p5(2,1) = 1;

    p5(0,2) = 1;
    p5(1,2) = 0;
    p5(2,2) = 1;

    pattern p6(3,3);
    p6.frequency = 1;
    p6.rules[UP].insert(1);
    p6.rules[UP].insert(2);
    p6.rules[UP].insert(3);
    p6.rules[UP].insert(6);
    p6.rules[RIGHT].insert(0);
    p6.rules[RIGHT].insert(1);
    p6.rules[RIGHT].insert(5);
    p6.rules[RIGHT].insert(6);
    p6.rules[DOWN].insert(0);
    p6.rules[DOWN].insert(2);
    p6.rules[DOWN].insert(4);
    p6.rules[DOWN].insert(6);
    p6.rules[LEFT].insert(3);
    p6.rules[LEFT].insert(4);
    p6.rules[LEFT].insert(5);
    p6.rules[LEFT].insert(6);
    p6(0,0) = 1;
    p6(1,0) = 1;
    p6(2,0) = 1;

    p6(0,1) = 1;
    p6(1,1) = 1;
    p6(2,1) = 1;

    p6(0,2) = 1;
    p6(1,2) = 1;
    p6(2,2) = 1;

    wfc.setPatternSize(3,3);
    wfc.loadPattern(p0);
    wfc.loadPattern(p1);
    wfc.loadPattern(p2);
    wfc.loadPattern(p3);
    wfc.loadPattern(p4);
    wfc.loadPattern(p5);
    wfc.loadPattern(p6);

    wfc.setSeed(13);
    // 13 does creat a failure
    // 14 does creat a failure
    wfc.setPatternSize(3,3);
    wfc.setOutputSize(90,90);


    waveGrid map;
    std::mt19937_64 gen(13);

    uint64_t t1 = nanoTime();
    map = wfc.generateOutput(gen);
    uint64_t t2 = nanoTime();

    std::cout << (t2 - t1) / 1000 / 1000.0 << " milliseconds\n";

    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            wfc.setSeed(std::rand() * 100);
        }
        
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            //wfc.collapseWave(map, gen);
            map = wfc.generateOutput(gen);
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(GRAY);
            int size = 40;
            for (size_t x = 0; x < map.sizeX(); x++){
                for (size_t y = 0; y < map.sizeY(); y++){
                    if(map(x,y).possiblePatterns.size() == 1 && map(x,y).fix == true){
                        int i = *map(x,y).possiblePatterns.begin();
                        if(i == 0){
                            DrawLine(x*size +size/2, y*size + size/2, x*size +size/2, y*size + size, GREEN);
                            DrawLine(x*size +size/2, y*size + size/2, x*size +size, y*size + size/2, GREEN);
                        }
                        else if(i == 1){
                            DrawLine(x*size +size/2, y*size + size/2, x*size +size/2, y*size, BLUE);
                            DrawLine(x*size +size/2, y*size + size/2, x*size +size, y*size + size/2, BLUE);
                        }
                        else if(i == 2){
                            DrawLine(x*size, y*size + size/2, x*size +size, y*size + size/2, BLUE);
                        }
                        else if(i == 3){
                            DrawLine(x*size +size/2, y*size + size/2, x*size +size/2, y*size, BLACK);
                            DrawLine(x*size +size/2, y*size + size/2, x*size, y*size + size/2, BLACK);
                        }
                        else if(i == 4){
                            DrawLine(x*size +size/2, y*size + size/2, x*size +size/2, y*size + size, RED);
                            DrawLine(x*size +size/2, y*size + size/2, x*size, y*size + size/2, RED);
                        }
                        else if(i == 5){
                            DrawLine(x*size +size/2, y*size, x*size +size/2, y*size + size, RED);
                        }
                        else if(i == 6){
                            DrawRectangle(x*size,y*size, size,size,WHITE);
                        }
                        DrawText(std::to_string(i).c_str(), x*size +2, y*size +2, 10, BLACK);
                    }
                    else{
                        std::stringstream ss;
                        for (size_t i = 0; i < map(x,y).possiblePatterns.size(); i++){
                            ss << map(x,y).possiblePatterns[i];
                        }
                        
                        DrawText(ss.str().c_str(), x*size +2, y*size +2, 10, BLACK);
                    }
                    raylib::Rectangle rec(x*size,y*size, size, size);
                    DrawRectangleLinesEx(rec, 1, BLACK);
                }
            }
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

/*
for (size_t x = 0; x < map.sizeX(); x++){
    for (size_t y = 0; y < map.sizeY(); y++){
        if(map(x,y).possiblePatterns.size() == 1 && map(x,y).fix == true){
            int i = *map(x,y).possiblePatterns.begin();
            if(i == 0){
                DrawLine(x*size +size/2, y*size + size/2, x*size +size/2, y*size + size, GREEN);
                DrawLine(x*size +size/2, y*size + size/2, x*size +size, y*size + size/2, GREEN);
            }
            else if(i == 1){
                DrawLine(x*size +size/2, y*size + size/2, x*size +size/2, y*size, BLUE);
                DrawLine(x*size +size/2, y*size + size/2, x*size +size, y*size + size/2, BLUE);
            }
            else if(i == 2){
                DrawLine(x*size, y*size + size/2, x*size +size, y*size + size/2, BLUE);
            }
            else if(i == 3){
                DrawLine(x*size +size/2, y*size + size/2, x*size +size/2, y*size, BLACK);
                DrawLine(x*size +size/2, y*size + size/2, x*size, y*size + size/2, BLACK);
            }
            else if(i == 4){
                DrawLine(x*size +size/2, y*size + size/2, x*size +size/2, y*size + size, RED);
                DrawLine(x*size +size/2, y*size + size/2, x*size, y*size + size/2, RED);
            }
            else if(i == 5){
                DrawLine(x*size +size/2, y*size, x*size +size/2, y*size + size, RED);
            }
            else if(i == 6){
                DrawRectangle(x*size,y*size, size,size,WHITE);
            }
            DrawText(std::to_string(i).c_str(), x*size +2, y*size +2, 10, BLACK);
        }
        else{
            std::stringstream ss;
            for (size_t i = 0; i < map(x,y).possiblePatterns.size(); i++){
                ss << map(x,y).possiblePatterns[i];
            }
            
            DrawText(ss.str().c_str(), x*size +2, y*size +2, 10, BLACK);
        }

        DrawRectangleLines(x*size,y*size, size,size,BLACK);
    }
}
*/

/*
for (size_t x = 0; x < map.sizeX(); x++){
                for (size_t y = 0; y < map.sizeY(); y++){
                    int i = map(x,y);
                    if(i == 0){
                        DrawRectangle(x*size,y*size, size,size,WHITE);
                    }
                    else if(i == 1){
                        DrawRectangle(x*size,y*size, size,size,BLACK);
                    }
                }
            }
*/