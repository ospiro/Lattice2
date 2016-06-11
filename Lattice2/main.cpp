//
//  main.cpp
//  Lattice2
//
//  Created by Oliver Spiro on 5/21/16.
//  Copyright © 2016 Oliver Spiro. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include "Lattice.hpp"

using namespace std;
int main(int argc, const char * argv[]) {
  

    int numSteps = 10000;
    
    
    
    int setWidth = atoi(argv[1]);
    int setRadius = atoi(argv[2]);
    double prob[4] = {0.3,0.1,0.3,0.3};//first index not used
    double setBirthRate[4] = {0,4,3.2,3};
    double setDeathRate[4] = {0,1,1,1};
    double setGrassDeathIncrement = 0.5;
    double setParasiteBirthIncrement = 0.2;
    int devType = 1;
    int setAmountDevelopment = 0;
    
    
    Lattice myLattice(setWidth,
            setRadius,
            prob,
            setBirthRate,
            setDeathRate,
            setGrassDeathIncrement,
            setParasiteBirthIncrement,
            devType,
            setAmountDevelopment);
    
    
//    vector<double> pops = myLattice.countPopulation(); //this records empties and developed squares as well, in indices 0 and 4.
//    for(int i = 0;i<5;i++)
//    {
//        cout<<pops[i]<<endl;
//    }
    
    int stepOfDeath = 0;
    for( int i = 1; i<=numSteps;i++)
    {
//        if(i%10==0)
//        {
//            myLattice.printLattice();
//        }
        if(myLattice.checkExtinction()==true)
        {
            stepOfDeath = i;
            break;
        }

        myLattice.advanceTimeStep();
        
    }
    
    string filename = string(argv[3])+".csv";
    
    ofstream record;
    record.open(filename);
    record<<setWidth<<","<<setRadius<<","<<stepOfDeath<<endl;
}
