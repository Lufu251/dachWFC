#include <raylib-cpp.hpp>

#include <dachWFC.hpp>
#include <sstream>
#include <chrono>

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

    wfc.setSeed(5);
    wfc.setPatternSize(1,1);
    wfc.setOutputSize(200,200);

    waveGrid wave;
    std::mt19937_64 gen(5);

    uint64_t t1 = nanoTime();
    wfc.startWave(wave, gen);
    while (wave.collapsed == false)
    {
        wfc.collapseWave(wave, gen);
    }
    uint64_t t2 = nanoTime();
    std::cout << (t2 - t1) / 1000 / 1000.0 << " milliseconds\n";

    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            wfc.collapseWave(wave, gen);
            
        }

        cellGrid2D  map = wfc.convertWaveGrid(wave);
        //map = wfc.cellTranslate(map);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(GRAY);
            int size = 10;
            for (size_t x = 0; x < wave.sizeX(); x++){
                for (size_t y = 0; y < wave.sizeY(); y++){
                    if(wave(x,y).fix == true){
                        int i = *wave(x,y).possiblePatterns.begin();
                        if(i == 0){
                            DrawLineEx(raylib::Vector2(x*size +size/2, y*size + size/2), raylib::Vector2(x*size +size/2, y*size + size), 3, GREEN);
                            DrawLineEx(raylib::Vector2(x*size +size/2, y*size + size/2), raylib::Vector2(x*size +size, y*size + size/2), 3, GREEN);
                            DrawText(std::to_string(i).c_str(), x*size+2, y*size + 2, 2, BLACK);
                        }
                        else if(i == 1){
                            DrawLineEx(raylib::Vector2(x*size +size/2, y*size + size/2), raylib::Vector2(x*size +size/2, y*size), 3, BLUE);
                            DrawLineEx(raylib::Vector2(x*size +size/2, y*size + size/2), raylib::Vector2(x*size +size, y*size + size/2), 3, BLUE);
                            DrawText(std::to_string(i).c_str(), x*size+2, y*size + 2, 2, BLACK);
                        }
                        else if(i == 2){
                            DrawLineEx(raylib::Vector2(x*size, y*size + size/2), raylib::Vector2(x*size +size, y*size + size/2), 3, BLUE);
                            DrawText(std::to_string(i).c_str(), x*size+2, y*size + 2, 2, BLACK);
                        }
                        else if(i == 3){
                            DrawLineEx(raylib::Vector2(x*size +size/2, y*size + size/2), raylib::Vector2(x*size +size/2, y*size), 3, BLACK);
                            DrawLineEx(raylib::Vector2(x*size +size/2, y*size + size/2), raylib::Vector2(x*size, y*size + size/2), 3, BLACK);
                            DrawText(std::to_string(i).c_str(), x*size+2, y*size + 2, 2, BLACK);
                        }
                        else if(i == 4){
                            DrawLineEx(raylib::Vector2(x*size +size/2, y*size + size/2), raylib::Vector2(x*size +size/2, y*size + size), 3, RED);
                            DrawLineEx(raylib::Vector2(x*size +size/2, y*size + size/2), raylib::Vector2(x*size, y*size + size/2), 3, RED);
                            DrawText(std::to_string(i).c_str(), x*size+2, y*size + 2, 2, BLACK);
                        }
                        else if(i == 5){
                            DrawLineEx(raylib::Vector2(x*size +size/2, y*size), raylib::Vector2(x*size +size/2, y*size + size), 3, RED);
                            DrawText(std::to_string(i).c_str(), x*size+2, y*size + 2, 2, BLACK);
                        }
                        else if(i == 6){
                            DrawRectangle(x*size,y*size, size,size,WHITE);
                            DrawText(std::to_string(i).c_str(), x*size+2, y*size + 2, 2, BLACK);
                        }
                        else{
                            DrawRectangle(x*size,y*size, size,size,RED);
                        }
                    }
                    else{
                        std::stringstream ss;
                        for (auto p : wave(x,y).possiblePatterns){
                            ss << p;

                        }
                        
                        DrawText(ss.str().c_str(), x*size+2, y*size + 2, 2, BLACK);
                    }

                    //DrawRectangleLines(x*size, y*size, size, size, BLACK);
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

/*pattern p0(3,3);
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
    wfc.loadPattern(p6);*/