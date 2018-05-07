//
//  EfficientAStar.hpp
//  Assignment5
//
//  Created by Kai Velagapudi on 5/6/18.
//  Copyright © 2018 Kai Velagapudi. All rights reserved.
//
#pragma once

#include "STP.h"
#include "heuristic.h"
#include <deque>
#include <iostream>
#include <unordered_map>

#include "PDB.h"
#include "heuristic.h"


#include <stdio.h>

struct HashStructure{
    
    
    // Same stuff from inefficient implementation
    STPState s;
    int f, g; // f , g cost
    
    STPSlideDir parent;
    bool OPEN;
    
    // Struct Declaration
    HashStructure()
    {
        // Initialising to Max value
        f = INT_MAX;
        g = INT_MAX;
        parent = kNone;
        OPEN = true;
    }
    
    HashStructure(STPState &s, int f, int g, STPSlideDir parent) // this is only ever used to initialize the root
    {
        this->s = s;
        this->f = f;
        this->g = g;
        this->parent = parent;
        OPEN = true;
    }
    
    void set(HashStructure &source, STP &puzzle, STPSlideDir o)
    {
        for (int w = 0; w < 3; ++w)
        {
            for (int h = 0; h < 5; ++h)
            {
                this->s.tiles[w][h] = source.s.tiles[w][h];
            }
        }
        this->s.blankx = source.s.blankx;
        this->s.blanky = source.s.blanky;
        
        puzzle.ApplyOperator(this->s, o);
        this->parent = o;
    }
    
    void open()
    {
        OPEN = true;
    }
    
    void close()
    {
        OPEN = false;
    }
    
    
};

class AStar
{
public:
    
    AStar();
    
    std::vector<STPSlideDir> GetPath(STPState &start, STPState &goal, Heuristic &h);
    
    
private:
    
   // Using an int as index
    std::unordered_map<int , HashStructure> LIST;
    
    bool DUPLICATE_CHECK_O(STPState &s);
    bool DUPLICATE_CHECK_C(STPState &s);
    bool OPEN_EMPTY();
    
    HashStructure& GET_BEST();
    
    void UPDATE_NODE(HashStructure &n, STPSlideDir parent, int g, int f);
    
    STPSlideDir GET_PARENT(STPState &s);
    
    std::vector<STPSlideDir> RECONSTRUCT_PATH(STP &puzzle, HashStructure curr);
    
};
