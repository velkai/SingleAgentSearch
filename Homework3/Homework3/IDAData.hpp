//
//  IDAData.hpp
//  Homework3
//
//  Created by Kai Velagapudi on 4/10/18.
//  Last edited by Jimmy Holmes on 4/13/2018
//  Copyright © 2018 Kai Velagapudi. All rights reserved.
//


#ifndef IDAData_hpp
#define IDAData_hpp

#include <stdio.h>
#include "STP.h"
#pragma once

class IDAData{
    
public:
    
    IDAData(STPState s,STPState p,int d);
    
    STPState getState();
    void setState(STPState s);
    
    STPState getParent();
    void setParent(STPState p);
    
    int getDepth();
    void setDepth(int d);
    

private:
    
    STPState state;
    STPState parent;
    int depth;
   
};


// Definitions

IDAData::IDAData(STPState s,STPState p,int d){
    
    state = s;
    parent = p;
    depth = d;
    
}

STPState IDAData::getState(){
    return state;
}

void IDAData::setState(STPState s){
    
    state = s;
}

STPState IDAData::getParent(){
    return parent;
}

void IDAData::setParent(STPState p){
    parent = p;
}

int IDAData::getDepth(){
    
    return depth;
}

void IDAData::setDepth(int d){
   
    depth = d;
}

#endif /* IDAData_hpp */
