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
#include <boost/program_options.hpp>
namespace po = boost::program_options;

using namespace std;
int main(int argc, const char * argv[]) {
  
    po::options_description desc("Parameters");
    desc.add_options()
    ("help", "Produce help message.")
    ("width", po::value<int>(), "Set lattice width.")
    ("radius",po::value<double>(),"Set interaction radius.")
    ("P",po::value<double>(),"Effect of parasite on grass death rate.")
    ("F",po::value<double>(),"Effect of forb on grass death rate.")
    ("devType",po::value<std::string>(),"Set development type (random/line/node/mixed).")
    ("amtDev",po::value<int>(),"Set total number of sites to develop.")
    ("outfile",po::value<std::string>(),"Filename of output csv. Saves record as file.csv if given string 'file' ")
;
    po::variables_map vm;
    po::store(po::parse_command_line(argc,argv,desc),vm);
    po::notify(vm);
    
    if(vm.count("help"))
    {
        cout<<desc<<endl;
        return 0;
    }
    
    int setWidth;
    if(vm.count("width"))
    {
        setWidth = vm["width"].as<int>();
    }
    double setRadius;
    if(vm.count("radius"))
    {
        setRadius = vm["radius"].as<double>();
    }
    double setParasiteOnGrass;
    if(vm.count("P"))
    {
        setParasiteOnGrass = vm["P"].as<double>();
    }
    double setForbOnGrass;
    if(vm.count("F"))
    {
        setForbOnGrass = vm["F"].as<double>();
    }
    int devType;
    if(vm.count("devType"))
    {
        if(vm["devType"].as<std::string>()=="random")
        {
            devType = 0;
        }
        if(vm["devType"].as<std::string>()=="line")
        {
            devType = 3;
        }
        else if(vm["devType"].as<std::string>()=="node")
        {
            devType = 2;
        }
        else if(vm["devType"].as<std::string>()=="mixed")
        {
            devType = 1;
        }
        //TODO: add else clause
    }
    int setAmountDevelopment;
    if(vm.count("amtDev"))
    {
        setAmountDevelopment = vm["amtDev"].as<int>();
    }
    std::string outfile;
    if(vm.count("outfile"))
    {
        outfile = vm["outfile"].as<std::string>();
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
    string filename = outfile+".csv";
    
    ofstream record;
    record.open(filename);
    record<<setWidth<<","<<setRadius<<","<<devType<<","<<setAmountDevelopment<<","<<myLattice.wellMix()<<","<<stepOfDeath<<endl;
    
    
    
    
    
    
}
