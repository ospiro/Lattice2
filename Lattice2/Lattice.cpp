//
//  Lattice.cpp
//  Lattice2
//
//  Created by Oliver Spiro on 5/21/16.
//  Copyright © 2016 Oliver Spiro. All rights reserved.
//
#define empty 0
#define parasite 1
#define forb 2
#define grass 3

#include "Lattice.hpp"
#include <iostream>
#include <random>
#include <vector>

int mod(int x, int m) { //gotten from http://stackoverflow.com/questions/1082917/mod-of-negative-number-is-melting-my-brain need because % doesn't behave well with negative #s
    return (x%m + m)%m;
}


Lattice::Lattice(int setWidth,
                 int setRadius,
                 double prob[4],
                 double setBirthRate,
                 double setDeathRate,
                 double setGrassDeathIncrement,
                 double setParasiteBirthIncrement,
                 int devType,
                 int setAmountDevelopment)
{
    vector<Site> columns(width);
    for(int i = 0;i<width;i++)
    {
        lat.push_back(columns); //create 2D lat array by pushing "column" vectors into "row" vector elements
    }
    
    //set base properties
    
    width = setWidth;
    radius = setRadius;
    birthRate = setBirthRate;
    deathRate = setDeathRate;
    grassDeathIncrement = setGrassDeathIncrement;
    parasiteBirthIncrement = setParasiteBirthIncrement;
    amountDevelopment = setAmountDevelopment;
    mt_rand.seed(static_cast<unsigned int>(time(NULL))); //TODO: better seed
    std::uniform_real_distribution<int> unif(0,1);
    
    
    //initialize each site
    for(int i = 0; i< width; i++)
    {
        for(int j = 0; i< width;j++)
        {
            if(lat[i][j].isEmpty())
            {
                
                if( unif(mt_rand) <= prob[parasite])
                {
                    lat[i][j].grow(parasite);
                }
                else if(unif(mt_rand) <= prob[forb])
                {
                    lat[i][j].grow(forb);
                }
                else if(unif(mt_rand)<=prob[grass]);
                {
                    lat[i][j].grow(grass);
                }
                
            }
        }
    }
    
    //prepare for neighbor generation
    int count = 0;
    vector<int> stepI;
    vector<int> stepJ;
    for(int i = -radius; i <= radius; i++)
    {
        for(int j = -radius; j <=radius; j++)
        {
            if((i*i + j*j <= radius*radius) && (i*i + j*j > 0))
            {
                count++;
                stepI.push_back(i);
                stepJ.push_back(j);
            }
        }
    }
    numNeighbors = stepI.size();
    
    //fill neighbor vector for each site
    
    vector<Site*> newNeighbors(numNeighbors);
    for(int i  = 0; i< width; i++)
    {
        for(int j =0; j<width; j++)
        {
            for(int k = 0; k< numNeighbors;k++)
            {
                int targI = mod(i+stepI[i],width);
                int targJ = mod(j+stepJ[j],width);
                newNeighbors[k] = &lat[targI][targJ];
            }
            lat[i][j].fillNeighborArray(numNeighbors,newNeighbors);
        }
    }
    
    
    if(setAmountDevelopment > 0)
    {
        lat.addDevelopment(devType,setAmountDevelopment);
    }
    
    
}