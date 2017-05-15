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

    int setWidth;
    double setRadius;
    double setParasiteOnGrass;
    double setForbOnGrass;
    int devType;
    int setAmountDevelopment;
    string outfile;
    
//    string flags[8] = {"--help","--width","--radius","--P","--F","--devType","--amtDev","--outfile"};
    string helpMessage = "Parameters:\n"
   "--help                Produce help message. \n"
   "--width arg           Set lattice width.\n"
   "--radius arg          Set interaction radius.\n"
   "--P arg               Effect of parasite on grass death rate.\n"
   "--F arg               Effect of forb on grass death rate.\n"
   "--devType arg         Set development type (random/line/node/mixed).\n"
   "--amtDev arg          Set total number of sites to develop.\n"
   "--outfile arg         Filename of output csv. Saves record as file.csv if given string 'file'\n";
    for(int i =0;i <argc;i++)
    {
        string flag = string(argv[i]);
        const char* arg = argv[i+1];
        if(flag=="--help")
        {
            cout<<helpMessage;
            return 0;
        }
        else if(flag=="--width")
        {
            setWidth = stoi(arg);
        }
        else if(flag=="--radius")
        {
            setRadius = atof(arg);
        }
        else if(flag=="--P")
        {
            setParasiteOnGrass = atof(arg);
        }
        else if(flag=="--F")
        {
            setForbOnGrass = atof(arg);
        }
        else if(flag=="--devType")
        {
            devType = atoi(arg);
        }
        else if(flag=="--amtDev")
        {
            setAmountDevelopment = atoi(arg);
        }
        else if(flag=="--outfile")
        {
            outfile = arg;
        }
    }
    
    
    int numSteps = 10000;
//
//    
//    
//    int setWidth = atoi(argv[1]);
//    double setRadius = atof(argv[2]);
    double prob[4] = {0.3,0.1,0.3,0.3};//first index not used
    double setBirthRate[4] = {0,4,3.2,3};
    double setDeathRate[4] = {0,1,1,1};
//    double setParasiteOnGrass = 0.5;
//    double setForbOnGrass = 0.1;
    double setParasiteBirthIncrement = 0;
//    int devType = atoi(argv[3]);
//    int setAmountDevelopment = atoi(argv[4]);
//    
//    
    Lattice myLattice(setWidth,
            setRadius,
            prob,
            setBirthRate,
            setDeathRate,
            setParasiteOnGrass,
            setForbOnGrass,
            setParasiteBirthIncrement,
            devType,
            setAmountDevelopment);

////    vector<int> pops = myLattice.countPopulation(); //this records empties and developed squares as well, in indices 0 and 4.
//    for(int i = 0;i<5;i++)
//    {
//        cout<<pops[i]<<endl;
//    }
    
    int stepOfDeath = 0;
    for( int i = 1; i<=numSteps;i++)
    {
        if(i%10==0)
        {
            myLattice.printLattice();
        }
        if(myLattice.checkExtinction()==true)
        {
            stepOfDeath = i;
            break;
        }

        myLattice.advanceTimeStep();
        
    }
    string filename = outfile+".csv";
    
    ofstream record;
    record.open(filename);
    record<<setWidth<<","<<setRadius<<","<<devType<<","<<setAmountDevelopment<<","<<setParasiteOnGrass<<","<<setForbOnGrass<<","<<myLattice.wellMix()<<","<<stepOfDeath<<endl;
    
//    std::vector<std::vector<int>> pathLengths = myLattice.shortestPath(floor(setWidth/2), floor(setWidth/2));
//    
//    for(auto col: pathLengths)
//    {
//        for(auto entry: col)
//        {
//            cout<<entry<<",";
//        }
//        cout<<endl;
//    }
    
}
