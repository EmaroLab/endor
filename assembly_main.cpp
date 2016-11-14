//===============================================================================//
// Name			: assembly_main.cpp
// Author(s)	: Barbara Bruno
// Affiliation	: University of Genova, Italy - dept. DIBRIS
// Version		: 1.0
// Description	: Main program using the AND-OR graph library for assembly tasks
//===============================================================================//

#include <vector>
#include <iostream>

#include "aograph.h"
#include "assemblyelement.h"

using namespace std;

int main(int argc, char **argv)
{
    // load the pencil_assembly graph
    AOgraph oneGraph("DEFAULT");
    string fileName = "assemblies/pencil_assembly.txt";
    oneGraph.loadFromFile(fileName);

    // [dumb] create the assembly-specific operations to associate to the nodes
    const char *actions[] = {"action_1", "action_2"};
    vector<string> randomActions(actions, actions + sizeof(actions)/sizeof(actions[0]));
    bool randomSequential = true;
    int randomLevel = 0;
    for(int i=0; i<(int)oneGraph.graph.size(); i++)
    {
        AssemblyElement* someAE = new AssemblyElement(randomActions, randomSequential, randomLevel);
        // [dumb] associate the assembly-specific operations with the nodes
        oneGraph.graph[i].addElement(someAE);
    }

    // print the graph info
    oneGraph.printGraphInfo();

    pause();    
    return 1;
}   
