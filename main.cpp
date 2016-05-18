//===============================================================================//
// Name			: main.cpp
// Author(s)	: Yeshasvi Tirupachuri V.S., Barbara Bruno
// Affiliation	: University of Genova, Italy - dept. DIBRIS
// Version		: 1.0
// Description	: Main program using the AND-OR graph library
//===============================================================================//

#include <iostream>

#include "aograph.h"

using namespace std;

// display basic information about the usage of ENDOR
void displayHelp()
{
    cout<<"To use ENDOR, follow these steps:" <<endl;
    cout<<"1. create a graph description (e.g., myGraph.txt)" <<endl;
    cout<<"   according to the template in assemblies/TEMPLATE.txt" <<endl;
    cout<<"2. load the graph in ENDOR (L + myGraph.txt)" <<endl;
    cout<<"3. set the nodes as solved one by one (S + [nodeName])" <<endl;
    cout<<"4. exit ENDOR (E)" <<endl;
}

int main(int argc, char **argv)
{
    char c;
    char c_strategy;
    string fileName;
    string nodeName;
    
    // create an empty graph
    string name = "DEFAULT";
    AOgraph oneGraph(name);
    
    cout<<endl <<"ENDOR tool for AND-OR graphs creation and navigation. Enjoy!" <<endl;
    
    do
    {
        cout<<endl;
        cout<<"Available commands:" <<endl;
        cout<<"H - display the ENDOR help" <<endl;
        cout<<"L - load a graph description from file" <<endl;
        cout<<"N - ask for a suggestion on the node to solve" <<endl;
        cout<<"S - set a node as solved" <<endl;
        cout<<"E - exit the program" <<endl;
        cout<<"Selected command: ";
        cin>>c;
        cout<<endl;
        
        switch(c)
        {
            case 'H':
                displayHelp();
                break;
            case 'L':
                cout<<"Graph configuration: ";
                cin>>fileName;
                oneGraph.loadFromFile(fileName);
                break;
            case 'N':
                cout<<"[Y/N] Use long-sighted (optimal path) strategy? ";
                cin>>c_strategy;
                oneGraph.suggestNext(c_strategy == 'Y');
                break;
            case 'S':
                cout<<"Solved node name: ";
                cin>>nodeName;
                oneGraph.solveByName(nodeName);
                break;
            case 'E':
                return 1;
        }
        
    }while (c != 'E');
    
    return 1;
}   
