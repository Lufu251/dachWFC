#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <random>
#include <queue>
#include <algorithm>

enum direction {UP, RIGHT, DOWN, LEFT};

// queueNode
struct queueNode{
    uint64_t x, y;
    queueNode(uint64_t xPos, uint64_t yPos): x(xPos), y(yPos){}
};

struct backTrackNode{
    uint64_t x, y;
    std::vector<uint64_t> pP;
    backTrackNode(uint64_t xPos, uint64_t yPos, std::vector<uint64_t> possiblePatterns): x(xPos), y(yPos), pP(possiblePatterns){}
};


// defines a section of the input grid contains rules for its neihboring patterns
struct pattern
{
    uint64_t x_size = 0, y_size = 0;

    // How many times the pattern is appeared in the input
    uint64_t frequency = 1;

    // Cells that represent the pattern
    std::vector<uint64_t> data;

    // Rules that define which patterns can be placed adjacent to this pattern
    std::vector<std::set<uint64_t>> rules;

    pattern(int32_t x, uint64_t y) : data(x*y), x_size(x), y_size(y){
        rules.resize(4); // set rules vector to 4
    }

    // compare the data of the pattern
    bool operator == (pattern& p){
        if(data == p.data){
            return true;
        }
        return false;
    }

    uint64_t& operator()(uint64_t x, uint64_t y){
        return data[x_size * y + x];
    }

    const uint64_t& operator()(uint64_t x, uint64_t y) const {
        return data[x_size * y + x];
    }
};

// one cell of the wave that is used to collapse the algorithm
struct waveCell{
    bool fix = false; // tile is already set or not
    bool queued = false; // was the tile queued

    // all patterns that can be picked
    std::vector<uint64_t> possiblePatterns;

    uint64_t getEntropy(){
        return possiblePatterns.size();
    }

    void pickRandomPattern(std::mt19937_64& rGen, std::vector<pattern>& rPatterns){
        // add all the pattern frequencys together
        uint64_t addedFrequencys = 0;
        std::vector<uint64_t> probabilityValue;
        probabilityValue.reserve(possiblePatterns.size());

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
        uint64_t index;
        for (size_t i = 0; i < probabilityValue.size(); i++){
            if(random < probabilityValue[i]){
                index = i;
                break;
            }
        }
        // clear the patterns and insert the randomly picked pattern
        uint64_t randomTile = *std::next(possiblePatterns.begin(), index);
        possiblePatterns.clear();
        possiblePatterns.push_back(randomTile);
        fix = true; // set fixed to true
    }
};

// waveGrid that will be collapsed
class waveGrid
{
private:
    uint64_t x_size;
    uint64_t y_size;
    std::vector<waveCell> data;

public:
    bool collapsed = false;

    waveGrid(){
    }
    waveGrid(size_t x, size_t y):data(x*y), x_size(x), y_size(y){

    }

    void resize(uint64_t x, uint64_t y){
        data.resize(x * y);
        x_size = x;
        y_size = y;
    }

    uint64_t sizeX(){
        return x_size;
    }

    uint64_t sizeY(){
        return y_size;
    }

    waveCell& operator()(uint64_t x, uint64_t y){
        return data[x_size * y + x];
    }

    const waveCell& operator()(uint64_t x, uint64_t y) const {
        return data[x_size * y + x];
    }

    void setAllCellsToMaxEntropy(std::vector<pattern>& rPatterns){
        std::vector<uint64_t> maxEntropy;
        maxEntropy.reserve(rPatterns.size());

        for (uint64_t i = 0; i < rPatterns.size(); i++){
            maxEntropy.push_back(i);
        }
        for (auto& d : data){
            d.possiblePatterns = maxEntropy;
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
    uint64_t x_size;
    uint64_t y_size;
    std::vector<uint64_t> data;
    
public:
    cellGrid2D(){}
    cellGrid2D(uint64_t x, uint64_t y):data(x*y), x_size(x), y_size(y){}

    void resize(uint64_t x, uint64_t y){
        data.resize(x * y);
        x_size = x;
        y_size = y;
    }

    uint64_t sizeX(){
        return x_size;
    }

    uint64_t sizeY(){
        return y_size;
    }

    uint64_t& operator()(uint64_t x, uint64_t y){
        return data[x_size * y + x];
    }

    const uint64_t& operator()(uint64_t x, uint64_t y) const {
        return data[x_size * y + x];
    }
};

class dachWFC{
private:
    cellGrid2D inputGrid;
    const std::array<std::pair<int,int>, 4> directions = {{{0, -1}, {1, 0}, {0, 1}, {-1, 0}}};
    std::vector<backTrackNode> backTrackNodes; // used to revert the changes if it failes to collapse

    size_t seed = 0;
    std::vector<pattern> patterns;
    uint64_t patternX = 0, patternY = 0;
    uint64_t outputSizeX = 0, outputSizeY = 0;

public:
    dachWFC(){}

    // seed for random generation
    void setSeed(size_t newSeed){
        seed = newSeed;
    }

    // set custom pattern size for loading patterns from scratch
    void setPatternSize(uint64_t sizeX, uint64_t sizeY){
        patternX = sizeX;
        patternY = sizeY;
    }

    void setOutputSize(uint64_t x, uint64_t y){
        outputSizeX = x;
        outputSizeY = y;
    }

    // load custom pattern
    void loadPattern(pattern p){
        patterns.push_back(p);
    }

    // load a cellGrid2D for rule generation
    void loadInput(cellGrid2D newInput, uint64_t patternSizeX, uint64_t patternSizeY){
        inputGrid = std::move(newInput);
        patternX = patternSizeX;
        patternY = patternSizeY;
    }

    cellGrid2D convertWaveGridToCellGrid(waveGrid& input){
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

    // generate an output from all the rules
    waveGrid generateOutput(waveGrid& wave, std::mt19937_64& gen){
        
        //std::mt19937_64 gen(seed); // random generator
        // startWave(wave, gen);
        
        // start loop
            collapseWave(wave, gen);
         
        
        return wave; // cellTranslate the cellGrid2D
    }

public:
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
                uint64_t patternsIndex = 0;
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
            for (uint64_t ix = 0; ix < input.sizeX(); ix ++){
                for (uint64_t iy = 0; iy < input.sizeY(); iy ++){

                    // iterate the pattern
                    for (uint64_t px = 0; px < patternX; px++){
                        for (uint64_t py = 0; py < patternY; py++){
                            output(ix*patternX + px, iy*patternY + py) = patterns[input(ix,iy)](px,py);
                        }
                    }
                     
                }
            }
            

        return output;
    }

    // extract rules from the input
    void createRules(cellGrid2D& input){
        for (uint64_t ix = 0; ix < input.sizeX(); ix++){
            for (uint64_t iy = 0; iy < input.sizeY(); iy++){
                // iterate all the directions
                for (uint64_t d = 0; d < directions.size(); d++){
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

    std::vector<uint64_t> intersect(const std::vector<uint64_t>& a, const std::vector<uint64_t>& b) {
        std::vector<uint64_t> intersections;
        intersections.reserve(patterns.size());
        std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(intersections));
        return intersections;
    }

    // update the grids cells with all the neighbors
    void updateNeighbors(uint64_t collapseX, uint64_t collapseY, waveGrid& rWave){
        std::queue<queueNode> queue; // queue for pending waveCells
        
        // first queueNode to start the loop
        queue.push(queueNode(collapseX, collapseY));

        // loop untile the queue is empty
        while (queue.size()){
            queueNode cn = queue.front(); // read node
            queue.pop(); // delete node after reading it

            // loop all the directions
            for (uint64_t d = 0; d < directions.size(); d++){
                int dx = cn.x + directions[d].first; // directional x
                int dy = cn.y + directions[d].second; // directional y
                
                //check for out of bounds
                if(dx > rWave.sizeX()-1 || dy > rWave.sizeY() -1){
                    // out of bound
                }
                else{
                    // in bound
                    if(rWave(dx,dy).fix == false){
                        backTrackNodes.push_back(backTrackNode(dx, dy, rWave(dx, dy).possiblePatterns)); // save the current state to revert changes later

                        std::set<uint64_t> allPatternsInDirection; // will contain all possible patterns in the current direction
                        // iterate all the possible patterns in the current tile
                        for (auto p : rWave(cn.x, cn.y).possiblePatterns){
                            for (auto r : patterns[p].rules[d]){
                                allPatternsInDirection.insert(r);
                            }
                        }

                        std::vector<uint64_t> allPatterns(allPatternsInDirection.begin(), allPatternsInDirection.end()); // convert set to vector

                        // update the neighboring waveCell with allPatternsInDirection
                        rWave(dx, dy).possiblePatterns = std::move(intersect(rWave(dx, dy).possiblePatterns, allPatterns));

                        // check if there are no possible patterns
                        if(rWave(dx, dy).possiblePatterns.size() == 0){
                            std::cout << "seed does not collapse" << std::endl;
                            // revert changes done in this loop
                            for (auto bt : backTrackNodes){
                                rWave(bt.x, bt.y).fix = false;
                                rWave(bt.x, bt.y).possiblePatterns = bt.pP;
                            }
                            backTrackNodes.clear(); // clear the backTrackNodes
                            break; // break the while loop
                        }
                    }
                    // add the neighboring waveCell to the queue if it was not queued before
                    if(rWave(dx, dy).queued == false && rWave(dx,dy).getEntropy() != patterns.size()){
                        queue.push(queueNode(dx, dy));
                        rWave(dx, dy).queued = true;
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
        uint64_t startPosX = startDisX(rGen);
        uint64_t startPosY = startDisY(rGen);

        rWave(startPosX, startPosY).pickRandomPattern(rGen, patterns); // pick a random pattern for the first cell

        updateNeighbors(startPosX, startPosY, rWave); // collapse once before the loop starts
    }

    // collapse the wave once
    void collapseWave(waveGrid& rWave, std::mt19937_64& rGen){
        rWave.collapsed = true; // set to true every loop
        uint64_t lowest = -1; // Set to max Value
        uint64_t lowestX = -1, lowestY = -1; // Set to max Value

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

        bool skipcollapse = false;
        // check if the wave is collapsed
        if(rWave.collapsed == false){
            // check if the entropy is larger than 1 and pick a random pattern
            if(lowest > 1){
                // pick a random tile
                backTrackNodes.push_back(backTrackNode(lowestX, lowestY, rWave(lowestX, lowestY).possiblePatterns));
                rWave(lowestX, lowestY).pickRandomPattern(rGen, patterns);
            }
            // check if the tiles entropy is 1 then set the tile to fix and skip the collapseGrid
            else if(lowest == 1){
                rWave(lowestX, lowestY).fix = true; // set tile to fix
                skipcollapse = true;
            }
            
            if(skipcollapse == false){
                // collapse the grid from the newest generated tile
                updateNeighbors(lowestX, lowestY, rWave);
            }
        }
    }
};