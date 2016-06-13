//
//  Lattice.cpp
//  Lattice2
//
//  Created by Oliver Spiro on 5/21/16.
//  Copyright © 2016 Oliver Spiro. All rights reserved.
//

#include "Lattice.hpp"
#include <iostream>
#include <random>
#include <vector>



#define developed 4
#define parasite 3
#define forb 2
#define grass 1
#define empty 0



#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */



int mod(int x, int m) { //gotten from http://stackoverflow.com/questions/1082917/mod-of-negative-number-is-melting-my-brain need because % doesn't behave well with negative #s
    return (x%m + m)%m;
}


Lattice::Lattice(int setWidth,
                 double setRadius,
                 double prob[4],
                 double setBirthRate[4],
                 double setDeathRate[4],
                 double setGrassDeathIncrement,
                 double setParasiteBirthIncrement,
                 int devType,
                 int setAmountDevelopment)
{
    
    //set base properties
    
    width = setWidth;
    radius = setRadius;
    std::copy(setBirthRate,setBirthRate+4,birthRate);
    std::copy(setDeathRate,setDeathRate+4,deathRate);
    grassDeathIncrement = setGrassDeathIncrement;
    parasiteBirthIncrement = setParasiteBirthIncrement;
    amountDevelopment = setAmountDevelopment;
    mt_rand.seed(static_cast<unsigned int>(time(NULL))); //TODO: better seed
    std::uniform_real_distribution<double> unif(0,1);
    dt = 0.01;
    
    vector<Site> columns(width);
    for(int i = 0;i<width;i++)
    {
        lat.push_back(columns); //create 2D lat array by pushing "column" vectors into "row" vector elements
    }

    
    //initialize each site
    for(int i = 0; i< width; i++)
    {
        for(int j = 0; j< width;j++)
        {
            double probRand = unif(mt_rand);

            if(probRand <= prob[parasite])
            {
                lat[i][j].grow(parasite);
            }
            else if(probRand <= prob[parasite]+prob[forb])
            {
                lat[i][j].grow(forb);
            }
            else if(probRand<=prob[parasite]+prob[forb]+prob[grass])
            {
                lat[i][j].grow(grass);
            }
            else
            {
                lat[i][j].die();
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
                int targI = mod(i+stepI[k],width);
                int targJ = mod(j+stepJ[k],width);
                newNeighbors.at(k) = &lat[targI][targJ];
            }
            lat[i][j].fillNeighborArray(numNeighbors,newNeighbors);
        }
    }
    
    
    if(amountDevelopment > 0)
    {
        addDevelopment(devType,amountDevelopment);
    }
    
    
}

void Lattice::addDevelopment(int devType,int amountDevelopment)
{
    
    
    uniform_int_distribution<int> location(0,width-1);
    int devCompleted = 0;
    
    if(devType == 0) //completely random scattering, this devType runs completely separately from the other three; no real commonalities.
    {
        while(devCompleted<amountDevelopment)
        {
            int i = location(mt_rand); //TODO: check how mt_rand used in old code
            int j = location(mt_rand);
            if(lat[i][j].isDeveloped()==false)
            {
                lat[i][j].develop();
                devCompleted++;
            }
            
        }
        return; //TODO: check behavior. This is to replace mark's large "else" clause.
    }
    
    //All other kinds of development: begin by determining # and location of cores and lines:
    uniform_int_distribution<int> total(0,3); //TODO: check these ranges with mark
    int q = total(mt_rand) + total(mt_rand);
    uniform_int_distribution<int> randq(0,q);
    
    
    int numNodes = 0;
    int numLines = 0;
    if(devType==1) //Mixed development
    {
        numNodes = randq(mt_rand);
        numLines = q - numNodes;
    }
    else if(devType==2) //TODO: change devType to string input , remove need for comments...All core development
    {
        numNodes = q;
        numLines = 0;
    }
    else //All lines is default
    {
        numNodes = 0;
        numLines = q;
    }
    
    double nodesProportion = double(numNodes)/double(q);//TODO:look up when double() is needed
    //
    
    /*If we roll to have nodes, we now need to decide where they are. We then develop the node*/
    
    
    uniform_int_distribution<int> nodeRand(0,width-1);
    int AllNodeCoords[numNodes][2];
    if(numNodes >0)
    {
        for(int i = 0;i<numNodes;i++)//TODO: Check indexing!
        {
            int NodeICoord = nodeRand(mt_rand);
            int NodeJCoord = nodeRand(mt_rand);
            lat[NodeICoord][NodeJCoord].develop();
            AllNodeCoords[i][0] = NodeICoord;
            AllNodeCoords[i][1] = NodeJCoord; //TODO: Consider: better to integrate array back through as mark had?
        }
    }
    
        //Similary, if we roll to have lines, we roll their location randomly. We roll the two end points radomly , then develop all of the squares between them.
    std::uniform_real_distribution<double> unif(0,1);
    
    int AllLineCoords[numLines][4]; //TODO: replace with cleaner implementation
    if (numLines>0)
    {
        
        int firstEndPtI;
        int firstEndPtJ;
        int secondEndPtI;
        int secondEndPtJ;
        for(int i = 0; i<numLines;i++)
        {
            
            if(unif(mt_rand) < 0.5) //TODO: maybe get rid of this? since periodic boundaries
            {
                firstEndPtI = 0;
                firstEndPtJ = location(mt_rand);
            }
            else
            {
                firstEndPtI = location(mt_rand);
                firstEndPtJ = 0;
            }
            
            
            
            if(unif(mt_rand) < 0.5)
            {
                secondEndPtI = width-1;
                secondEndPtJ = location(mt_rand);
            }
            else
            {
                secondEndPtI = location(mt_rand);
                secondEndPtJ = width-1;
            }
            
            AllLineCoords[i][0] = firstEndPtI;
            AllLineCoords[i][1] = firstEndPtJ;
            AllLineCoords[i][2] = secondEndPtI;
            AllLineCoords[i][3] = secondEndPtJ;
            
            
            
            for(int j = 0; j<width;j++)
            {
                int curI = firstEndPtI + int( (j/double(width)) * (secondEndPtI - firstEndPtI) );
                int curJ = firstEndPtJ + int( (j/double(width)) * (secondEndPtJ - firstEndPtJ) );
                lat[curI][curJ].develop();
            }
         }
      }
    
    //We now want to count how many sites are developed by placing the initial lines and cores, to make sure we don't over-shoot the desired development amount.
    
    
    for(int i = 0; i< width; i++)
    {
        for(int j = 0; j< width; j++)
        {
            if(lat[i][j].isDeveloped())
            {
                devCompleted++;
            }
        }
    }
    
    //Now we iterate until amountDevelop sites are developed. In each iteration we develop one square, budding off of the cores or lines.
    
    uniform_int_distribution<int> whichNodeRand(0,numNodes-1);
    uniform_int_distribution<int> whichLineRand(0,numLines-1);
    if(numLines == 0 && numNodes==0)
    {
        return;
    }
    while(devCompleted < amountDevelopment)
    {
        int curI;
        int curJ;
        if( (unif(mt_rand) < nodesProportion) && (numNodes > 0) ) //If we bud off a node
        {
            int whichNode = whichNodeRand(mt_rand);
//            cout<<"Node: " << whichNode<<endl;
            curI = AllNodeCoords[whichNode][0];
            curJ = AllNodeCoords[whichNode][1];
//            cout<<curI<<endl<<curJ<<endl;
            
        }
        else if(numLines >0)
        {
            int whichLine = whichLineRand(mt_rand);
//            cout<<"Line:"<<whichLine<<endl;
            curI = AllLineCoords[whichLine][0]+ int(unif(mt_rand)*(AllLineCoords[whichLine][2] - AllLineCoords[whichLine][0]));
            curJ = AllLineCoords[whichLine][1]+ int(unif(mt_rand)*(AllLineCoords[whichLine][3] - AllLineCoords[whichLine][1]));//TODO: check math
//            cout<<curI<<endl<<curJ<<endl;
        }
        //Then do a random walk from that point to an undeveloped square
      
        int stepI[4] = {-1,0,1,0};
        int stepJ[4] = {0,1,0,-1};
        
        while(lat[curI][curJ].isDeveloped())
        {
            int s = int(unif(mt_rand)*4);//TODO: check math
            curI = mod(curI+stepI[s],width); //TODO: check mod behavior
            curJ = mod(curJ+stepJ[s],width);
        }
        
        //Finally, develop the site:
        
        lat[curI][curJ].develop();
        devCompleted++;
        
    }
    
}

double Lattice::meanConnectivity()
{
    double m = 0; //Initially, keeps track of number of links from undeveloped squares to undeveloped squares. Later we divide by undevelopedSites to get average number of links per undeveloped site
    int undevelopedSites = 0;
    
    for(int i = 0; i< width; i++)
    {
        for(int j = 0; j<width; j++)
        {
            
            if(lat[i][j].isDeveloped()==false)
            {
                undevelopedSites++;
                for(int k = 0; k < numNeighbors;k++)
                {
                    if( lat[i][j].getNeighbor(k)->getSpecies()!=4)
                    {
                        m++;
                    }
                }
            }
        }
    }
    
    
    return m/double(undevelopedSites*undevelopedSites);
}

double Lattice::getDeathRate(Site S) //TODO: move into site
{
    double rate = 0;
    if( !(S.isEmpty() || S.isDeveloped()) )
       {
           rate = deathRate[S.getSpecies()];
           if(S.getSpecies()==parasite)
           {
               for ( int i  = 0; i< numNeighbors; i++)
               {
                   if(S.getNeighbor(i)->getSpecies()==grass)
                   {
                       rate = rate + grassDeathIncrement;
                   }
               }
           }
       }
    return rate;
}

void Lattice::checkEvent(int ii,int jj)
{
    uniform_real_distribution<double> unif(0,1);
    double r = unif(mt_rand);
    Site* S = &lat[ii][jj];
    if(S->isEmpty() || S->isDeveloped())
    {
        return;
    }
    double trueDeathRate = getDeathRate(*S);
    if( r < trueDeathRate*dt)
    {
        S->die();
    }
    else if(r < (trueDeathRate + birthRate[S->getSpecies()])*dt ) //if roll birth
    {
        int r2 = int(unif(mt_rand)*numNeighbors);
        S->growIntoNeighbor(r2);
    }
    else if( S->getSpecies() == parasite && r <  ( trueDeathRate + birthRate[S->getSpecies()] + parasiteBirthIncrement )*dt ) //if roll colonization into grass site
    {
        int r2 = int(unif(mt_rand)*numNeighbors);
        if(S->getSpecies()==grass)
        {
            S->growIntoNeighbor(r2);
        }
    }
    
}


void Lattice::advanceTimeStep()
{
    uniform_int_distribution<int> coordRand(0,width-1);
    for(int i = 0; i<width;i++)
    {
        for(int j = 0; j<width;j++)
        {
            int I = coordRand(mt_rand);
            int J = coordRand(mt_rand);
            checkEvent(I,J);
        }
    }
}

vector<int> Lattice::countPopulation()
{
    vector<int> populations = {0,0,0,0,0};
    
    for(int i = 0; i<width;i++)
    {
        for(int j = 0; j<width; j++)
        {
            populations[lat[i][j].getSpecies()] += 100;
        }
        
    }
    return populations;
}


bool Lattice::checkExtinction()
{
    vector<int> pops = countPopulation();
    
    if( pops[parasite] == 0 ||  pops[forb] == 0 || pops[grass] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}


void Lattice::printLattice()
{
    for(int i =0;i<width;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(lat[i][j].getSpecies()==empty)
            {
                cout<<WHITE<<"o "<<RESET;
            }
            else if(lat[i][j].getSpecies()==parasite)
            {
                cout<< RED << "o " << RESET;
            }
            else if(lat[i][j].getSpecies()==forb)
            {
                cout<< BLUE << "o " << RESET;
            }
            else if(lat[i][j].getSpecies()==grass)
            {
                cout<< GREEN << "o "<< RESET;
            }
            else if(lat[i][j].isDeveloped())
            {
                cout<< BLACK << "o " <<RESET;
            }
        }
        cout<<endl;
    }
    cout<<endl<<endl<<endl;
}


//==============TEST SUITE==============





void Lattice::testNeighbors()
{
    for(int i= 0;i<width;i++)
    {
        for(int j = 0;j<width;j++)
        {
            lat[i][j].die();
        }
    }
    printLattice();
    lat[1][0].grow(parasite);
    for(int i = 0;i<numNeighbors;i++)
    {
        cout<<lat[0][0].getNeighbor(i)->getSpecies()<<endl;
    }
    printLattice();
}



































