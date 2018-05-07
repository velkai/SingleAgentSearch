//
//  EfficientAStar.cpp
//  Assignment5
//
//  Created by Kai Velagapudi on 5/6/18.
//  Copyright © 2018 Kai Velagapudi. All rights reserved.
//

#include "AStar.hpp"
#include <unordered_map>

void print(STPState &s);

AStar::AStar()
{
    // Constructor does nothing
}

// Called in GetPath
std::vector<STPSlideDir> AStar::RECONSTRUCT_PATH(STP &puzzle, HashStructure curr)
{
    std::vector<STPSlideDir> path;
    path.push_back(curr.parent);
    
    while (curr.parent != kNone)
    {
        puzzle.UndoOperator(curr.s, curr.parent);
        curr.parent = GET_PARENT(curr.s);
        path.push_back(curr.parent);
    }
    
    return path;
   
}

std::vector<STPSlideDir> AStar::GetPath(STPState &start, STPState &goal, Heuristic &h)
{
    int counter = 0;
    
    LIST.clear();
    
    print(start);
    
    STP puzzle;
    HashStructure root(start, h.h(start), 0 , kNone);
  
    LIST.insert(std::make_pair(counter,root));
    
    if (!root.OPEN) std::cout << "Whoa there.\n";
    
    // while we still have nodes on the OPEN list (or until we find a solution)
    
    while (!OPEN_EMPTY())
    {
        HashStructure curr = GET_BEST();
        
        if (curr.s == goal)
        {
            print(goal);
            std::cout << "Path found\n";
            return RECONSTRUCT_PATH(puzzle, curr);
        }
        
        std::vector<STPSlideDir> operators;
        
        if (!operators.empty()) std::cout << "ERROR 1\n";
       puzzle.GetOperators(curr.s, operators);
        
        for (auto o : operators)
        {
            HashStructure neighbor;
            neighbor.set(curr, puzzle, o);
            neighbor.open();
            
            if (DUPLICATE_CHECK_C(neighbor.s))
            {
                //print(neighbor.s); std::cout << "IS CLOSED\n";
                continue;
            }
            
            if (!DUPLICATE_CHECK_O(neighbor.s))
            {
                counter++;
                LIST.insert(std::make_pair(counter,neighbor));
            }
            
            int temp = curr.g + 1;
            
            if (temp >= neighbor.g) continue;
            
            //std::cout << temp << " " << neighbor.g << "\n";
            
            UPDATE_NODE(neighbor, o, temp, temp + h.h(neighbor.s));
        }
    }
    
    std::cout << "Path not found\n";
    return std::vector<STPSlideDir>();
    
    
}

HashStructure& AStar::GET_BEST()
{
    int lowest = INT_MAX;
    HashStructure cursor;
    
    for (auto i = LIST.begin(); i != LIST.end(); ++i)
    {
        if (i->second.OPEN)
        {
            if (i->second.f < lowest)
            {
            
                i->second.close();
                lowest = i->second.f;
                cursor = i->second;
            }
            //else std::cout << "LOWEST NOT UPDATED\n:" << i->f << ":\n";
        }
    }
    
    return cursor;
}

void AStar::UPDATE_NODE(HashStructure &n, STPSlideDir parent, int g, int f) // n must be in LIST for this to be called
{
    // i is a pointer
    for( auto i = LIST.begin(); i != LIST.end(); ++i)
    {
        if (i->second.s == n.s)
        {
           
            i->second.parent = parent;
            i->second.g = g;
            i->second.f = f;
            
            return;
        }
    }
    
    std::cout << "ERROR 2\n";
    
}

STPSlideDir AStar::GET_PARENT(STPState &s) // n must be in LIST for this to be called
{
    for (auto i = LIST.begin(); i != LIST.end(); ++i)
    {
        if (i->second.s == s)
        {
            return i->second.parent;
        }
    }
    
    std::cout << "ERROR 4\n";
    return kNone;
   
}

// Kept these the same

bool AStar::DUPLICATE_CHECK_C(STPState &s)
{
    for (auto i = LIST.begin(); i!= LIST.end(); ++i)
    {
        if (i->second.s == s)
        {
            if(i->second.OPEN == false) {
                
                return true;
            }
            
            else return false;
        }
    }
    return false;
}

bool AStar::OPEN_EMPTY()
{
for (auto i = LIST.begin(); i!= LIST.end(); ++i)    {
    
    if (i->second.OPEN){
        
        return false;
    }
    
}
    return true;
}

bool AStar::DUPLICATE_CHECK_O(STPState &s)
{
    for (auto i = LIST.begin(); i!= LIST.end(); ++i)
    {
        if (i->second.s == s)
        {
            if(i->second.OPEN == true)
            {
                return true;
            }
           
            else return false;
        }
    }
    return false;
}

void print(STPState &s){
    std::cout << " ___________ \n|           |\n";
    for (int h = 0; h < 5; ++h)
    {
        std::cout << "| ";
        for (int w = 0; w < 3; ++w)
        {
            std::cout << " ";
            if (s.tiles[w][h] > 9)
            {
                std::cout << s.tiles[w][h];
            }
            else std::cout << s.tiles[w][h] << " ";
        }
        std::cout << " |\n";
    }
    std::cout << "|___________|\n";
}




