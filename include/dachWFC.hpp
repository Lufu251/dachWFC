#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <queue>
#include <algorithm>

#include <chrono>

uint64_t nanoTime(){
    using namespace std;
    using namespace chrono;
    return duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
}

enum direction {UP, RIGHT, DOWN, LEFT};

// queueNode
struct queueNode{
    uint32_t x, y;
    queueNode(uint32_t xPos, uint32_t yPos): x(xPos), y(yPos){}
};


// defines a section of the input grid contains rules for its neihboring patterns
struct pattern
{
    uint32_t x_size = 0, y_size = 0;

    // How many times the pattern is appeared in the input
    uint32_t frequency = 1;

    // Cells that represent the pattern
    std::vector<uint32_t> data;

    // Rules that define which patterns can be placed adjacent to this pattern
    std::vector<std::set<uint32_t>> rules;

    pattern(int32_t x, uint32_t y) : data(x*y), x_size(x), y_size(y){
        rules.resize(4); // set rules vector to 4
    }

    // compare the data of the pattern
    bool operator == (pattern& p){
        if(data == p.data){
            return true;
        }
        return false;
    }

    uint32_t& operator()(uint32_t x, uint32_t y){
        return data[x_size * y + x];
    }

    const uint32_t& operator()(uint32_t x, uint32_t y) const {
        return data[x_size * y + x];
    }
};

// one cell of the wave that is used to collapse the algorithm
struct waveCell{
    bool fix = false; // tile is already set or not
    bool queued = false; // was the tile queued

    // all patterns that can be picked
    std::set<uint32_t> possiblePatterns;

    uint32_t getEntropy(){
        return possiblePatterns.size();
    }

    void pickRandomPattern(std::mt19937_64& rGen, std::vector<pattern>& rPatterns){
        // add all the pattern frequencys together
        uint32_t addedFrequencys = 0;
        std::vector<uint32_t> probabilityValue;
        for (auto pP : possiblePatterns){
            // calculate added value of all patterns frequency
            addedFrequencys += rPatterns[pP].frequency;
            // create the added value for each pattern
            probabilityValue.push_back(addedFrequencys);
        }

        // uniform int distribution between 0 and the addedFrequency
        std::uniform_int_distribution<int> patternDis(0,addedFrequencys-1);
        int random = patternDis(rGen); // random number between values

        // pick the random tile
        uint32_t index;
        for (size_t i = 0; i < probabilityValue.size(); i++){
            if(random < probabilityValue[i]){
                index = i;
                break;
            }
        }
        // clear the patterns and insert the randomly picked pattern
        uint32_t randomTile = *std::next(possiblePatterns.begin(), index);
        possiblePatterns.clear();
        possiblePatterns.insert(randomTile);
        fix = true; // set fixed to true
    }
};

// waveGrid that will be collapsed
class waveGrid
{
private:
    uint32_t x_size;
    uint32_t y_size;
    std::vector<waveCell> data;

public:
    bool collapsed = false;

    waveGrid(){
    }
    waveGrid(size_t x, size_t y):data(x*y), x_size(x), y_size(y){

    }

    void resize(uint32_t x, uint32_t y){
        data.resize(x * y);
        x_size = x;
        y_size = y;
    }

    uint32_t sizeX(){
        return x_size;
    }

    uint32_t sizeY(){
        return y_size;
    }

    waveCell& operator()(uint32_t x, uint32_t y){
        return data[x_size * y + x];
    }

    const waveCell& operator()(uint32_t x, uint32_t y) const {
        return data[x_size * y + x];
    }

    void setAllCellsToMaxEntropy(std::vector<pattern>& rPatterns){
        std::set<uint32_t> maxEntropy;
        for (uint32_t i = 0; i < rPatterns.size(); i++){
            maxEntropy.insert(i);
        }
        for (size_t i = 0; i < data.size(); i++){
            data[i].possiblePatterns = maxEntropy;
        }
    }

    void resetQueuedAttribute(){
        for (size_t i = 0; i < data.size(); i++){
            data[i].queued = false;
        }
    }
};


// int grid for output and input
class cellGrid2D{
private:
    uint32_t x_size;
    uint32_t y_size;
    std::vector<uint32_t> data;
    
public:
    cellGrid2D(){}
    cellGrid2D(uint32_t x, uint32_t y):data(x*y), x_size(x), y_size(y){}

    void resize(uint32_t x, uint32_t y){
        data.resize(x * y);
        x_size = x;
        y_size = y;
    }

    uint32_t sizeX(){
        return x_size;
    }

    uint32_t sizeY(){
        return y_size;
    }

    uint32_t& operator()(uint32_t x, uint32_t y){
        return data[x_size * y + x];
    }

    const uint32_t& operator()(uint32_t x, uint32_t y) const {
        return data[x_size * y + x];
    }
};

class dachWFC{
public:
    cellGrid2D inputGrid;
    waveGrid backTrackWave1;
    waveGrid backTrackWave2;

    size_t seed = 0;
    std::vector<pattern> patterns;
    uint32_t patternX = 0, patternY = 0;
    uint32_t outputSizeX = 0, outputSizeY = 0;

    dachWFC(){}

    // seed for random generation
    void setSeed(size_t newSeed){
        seed = newSeed;
    }

    // set custom pattern size for loading patterns from scratch
    void setPatternSize(uint32_t sizeX, uint32_t sizeY){
        patternX = sizeX;
        patternY = sizeY;
    }

    void setOutputSize(uint32_t x, uint32_t y){
        outputSizeX = x;
        outputSizeY = y;
    }

    // load custom pattern
    void loadPattern(pattern p){
        patterns.push_back(p);
    }

    // load a cellGrid2D for rule generation
    void loadInput(cellGrid2D newInput, uint32_t patternSizeX, uint32_t patternSizeY){
        inputGrid = std::move(newInput);
        patternX = patternSizeX;
        patternY = patternSizeY;
    }

    cellGrid2D convertWaveGrid(waveGrid input){
        cellGrid2D output(input.sizeX(), input.sizeY());
        for (size_t x = 0; x < input.sizeX(); x++){
            for (size_t y = 0; y < input.sizeY(); y++){
                if(input(x,y).fix == true){
                    output(x,y) = *input(x,y).possiblePatterns.begin();
                }
                else{
                    output(x,y) = -1;
                }
            }
        }
        

        return output;
    }

    // extract rules and patterns from the inputGrid
    void generateRulesFromInput(){
        cellGrid2D workingGrid;
        workingGrid = patternTranslate(inputGrid); // translate the inputGrid to patterns
        createRules(workingGrid); // extract the rules from the working grid
    }
    
    // generate an output from all the rules
    cellGrid2D generateOutput(){

        std::mt19937_64 gen(seed); // random generator
        
        
        // start loop

        // convert waveGrid to cellGrid2D

        
        //return cellTranslate(output);
    }

    // translate the cellGrid2D to a patterns
    cellGrid2D patternTranslate(cellGrid2D& input){
        cellGrid2D output(input.sizeX() / patternX, input.sizeY() / patternY);

        // iterate the input
        for (size_t ix = 0; ix < input.sizeX(); ix += patternX){
            for (size_t iy = 0; iy < input.sizeY(); iy += patternY){
                // create pattern
                pattern newPattern(patternX, patternY);

                // iterate the pattern
                for (size_t px = 0; px < patternX; px ++){
                    for (size_t py = 0; py < patternY; py ++){
                        newPattern(px,py) = input(ix+px, iy+py);
                    }
                }

                // newPattern is generated from input
                // check if the tile already exists
                bool exists = false;
                uint32_t patternsIndex = 0;
                for (size_t i = 0; i < patterns.size(); i++){
                    if(patterns[i] == newPattern){
                        exists = true;
                        patternsIndex = i;
                    }
                }
                // add or create a new tile
                if(exists == true){
                    // pattern already exists
                    patterns[patternsIndex].frequency ++; // add one to the frequency
                    output(ix/patternX, iy/patternY) = patternsIndex; // update the output
                }
                else{
                    // pattern is unique
                    patternsIndex = patterns.size(); // lookup size befor adding to get the true index
                    patterns.push_back(newPattern); // pushback new pattern
                    output(ix/patternX, iy/patternY) = patternsIndex; // update the output
                }
            }
        }

        return output;
    }

    // translate the cellGrid2D to a cells
    cellGrid2D cellTranslate(cellGrid2D& input){
        cellGrid2D output(input.sizeX() * patternX, input.sizeY() * patternY);

            // iterate input
            for (uint32_t ix = 0; ix < input.sizeX(); ix ++){
                for (uint32_t iy = 0; iy < input.sizeY(); iy ++){

                    // iterate the pattern
                    for (uint32_t px = 0; px < patternX; px++){
                        for (uint32_t py = 0; py < patternY; py++){
                            output(ix*patternX + px, iy*patternY + py) = patterns[input(ix,iy)](px,py);
                        }
                    }
                     
                }
            }
            

        return output;
    }

    // extract rules from the input
    void createRules(cellGrid2D& input){
        // all the directions that should be checked
        std::vector<std::pair<int, int>> directions;
        directions.push_back({0, -1}); // UP
        directions.push_back({1, 0}); // RIGHT
        directions.push_back({0, 1}); // DOWN
        directions.push_back({-1, 0}); // LEFT

        for (uint32_t ix = 0; ix < input.sizeX(); ix++){
            for (uint32_t iy = 0; iy < input.sizeY(); iy++){
                // iterate all the directions
                for (uint32_t d = 0; d < directions.size(); d++){
                    int dx = ix + directions[d].first; // directional x
                    int dy = iy + directions[d].second; // directional y

                    //check for out of bounds
                    if(dx > input.sizeX()-1 || dy > input.sizeY() -1){
                        // out of bound
                    }
                    else{
                        // in bound
                        patterns[input(ix,iy)].rules[d].insert(input(dx, dy)); // add the rule to the set of the current pattern
                    }
                }
            }
        }
    }

    std::set<uint32_t> intersect(const std::set<uint32_t>& a, const std::set<uint32_t>& b) {
        std::set<uint32_t> result;
        std::vector<uint32_t> intersections;
        std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(intersections));
        for(auto i : intersections){
            result.insert(i);
        }
        return result;
    }

    // update the grids cells with all the neighbors
    void updateNeighbors(uint32_t collapsX, uint32_t collapsY, waveGrid& rWave){
        std::queue<queueNode> queue; // queue for pending waveCells

        // first queueNode to start the loop
        queue.push(queueNode(collapsX, collapsY));

        // all the directions that should be checked
        std::vector<std::pair<int, int>> directions;
        directions.push_back({0, -1}); // UP
        directions.push_back({1, 0}); // RIGHT
        directions.push_back({0, 1}); // DOWN
        directions.push_back({-1, 0}); // LEFT

        // loop untile the queue is empty
        while (queue.size()){
            queueNode cn = queue.front(); // read node
            queue.pop(); // delete node after reading it

            // loop all the directions
            for (uint32_t d = 0; d < directions.size(); d++){
                int dx = cn.x + directions[d].first; // directional x
                int dy = cn.y + directions[d].second; // directional y

                //check for out of bounds
                if(dx > rWave.sizeX()-1 || dy > rWave.sizeY() -1){
                    // out of bound
                }
                else{
                    // in bound
                    if(rWave(dx,dy).fix == false){
                        std::set<uint32_t> allPatternsInDirection; // will contain all possible patterns in the current direction
                        // iterate all the possible patterns in the current tile
                        for (auto p : rWave(cn.x, cn.y).possiblePatterns){
                            for (auto r : patterns[p].rules[d]){
                                allPatternsInDirection.insert(r);
                            }
                        }

                        // update the neighboring waveCell with allPatternsInDirection
                        rWave(dx, dy).possiblePatterns = std::move(intersect(rWave(dx, dy).possiblePatterns, allPatternsInDirection));
                    }
                    // add the neighboring waveCell to the queue if it was not queued before
                    if(rWave(dx, dy).queued == false && rWave(dx,dy).getEntropy() != patterns.size()){
                        if(rWave(cn.x, cn.y).fix == true && rWave(dx,dy).fix == true){

                        }
                        else{
                            queue.push(queueNode(dx, dy));
                            rWave(dx, dy).queued = true;
                        }
                    }
                }
            }
        }
        rWave.resetQueuedAttribute();
    }

    // start the wave
    void startWave(waveGrid& rWave, std::mt19937_64& rGen){
        rWave.resize(outputSizeX / patternX, outputSizeY / patternY);
        rWave.setAllCellsToMaxEntropy(patterns); // set all cells to max entropy

        std::uniform_int_distribution<int> startDisX(0,rWave.sizeX()-1); // distributor
        std::uniform_int_distribution<int> startDisY(0,rWave.sizeY()-1); // distributor

        // random starting coordinates
        uint32_t startPosX = startDisX(rGen);
        uint32_t startPosY = startDisY(rGen);

        rWave(startPosX, startPosY).pickRandomPattern(rGen, patterns); // pick a random pattern for the first cell

        updateNeighbors(startPosX, startPosY, rWave); // collapse once before the loop starts
    }

    // collaps the wave once
    void collapsWave(waveGrid& rWave, std::mt19937_64& rGen){
        rWave.collapsed = true; // set to true every loop
        uint32_t lowest = -1; // Set to max Value
        uint32_t lowestX = -1, lowestY = -1; // Set to max Value

        uint64_t l1 = nanoTime();
        // search waveCell with the lowest entropy
        for (size_t x = 0; x < rWave.sizeX(); x++){
            for (size_t y = 0; y < rWave.sizeY(); y++){
                
                // check if the waveCell has lower entropy than the current lowest and is not already fixed
                if(rWave(x,y).fix == false && rWave(x,y).getEntropy() < lowest){
                    // Set the current lowest value to the new value
                    lowest = rWave(x,y).getEntropy();
                    lowestX = x;
                    lowestY = y;
                    rWave.collapsed = false; // set false if a valide waveCell was found
                }
            }
        }

        bool skipCollaps = false;
        uint64_t u1 = 0;
        uint64_t u2 = 0;
        uint64_t pr1 = 0;
        uint64_t pr2 = 0;
        // check if the wave is collapsed
        if(rWave.collapsed == false){
            // check if the entropy is larger than 1 and pick a random pattern
            if(lowest > 1){
                // pick a random tile
                rWave(lowestX, lowestY).pickRandomPattern(rGen, patterns);
            }
            // check if the entropy is 0 go back one step and reset gridFullCollapsed to false
            else if(lowest == 0){
                //std::cout << "seed does not collapse at: " << "X: " << lowestX << " Y: " << lowestY << std::endl;
                rWave = backTrackWave2;
                skipCollaps = true;
            }
            // check if the tiles entropy is 1 then set the tile to fix and skip the collapsGrid
            else if(lowest == 1){
                rWave(lowestX, lowestY).fix = true; // set tile to fix
                skipCollaps = true;
            }
            
            if(skipCollaps == false){
                // collapse the grid from the newest generated tile
                updateNeighbors(lowestX, lowestY, rWave);
            }
        }
        backTrackWave2 = backTrackWave1;
        backTrackWave1 = rWave;
    }
};