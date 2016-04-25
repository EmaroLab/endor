//===============================================================================//
// Name			: aograph.h
// Author(s)	: Barbara Bruno, Yeshasvi Tirupachuri V.S.
// Affiliation	: University of Genova, Italy - dept. DIBRIS
// Version		: 1.0
// Description	: AND-OR graph
//===============================================================================//

#include <fstream>

#include "aonode.h"

using namespace std;

#ifndef AOGRAPH_H
#define AOGRAPH_H

//! class "Path" for each unique path traversing the graph from the head to the leaves
class Path
{        
    public:
        int pIndex;                 //!< index of the path
        int pCost;                  //!< overall cost of all the nodes in the path
        bool pComplete;             //!< complete: the path fully traverses the graph
        vector<AOnode*> pathNodes;  //!< set of the nodes in the path
        vector<bool> checkedNodes;  //!< checked: the analysed nodes
        
        //! constructor
		Path(int cost, int index);
        
        //! copy constructor
        Path(const Path &toBeCopied, int index);
        
        //! display path information
        void printPathInfo();
        
        //! add a node in the path
        void addNode(AOnode* node);
        
        //! update the path information (when a node is solved)
        void updatePath(string nameNode);
        
        //! find the feasible node to suggest
        AOnode* suggestNode();
        
        //! destructor
		~Path()
		{
			//DEBUG:cout<<endl <<"Destroying Path object" <<endl;
		}
};

//! class "AOgraph" for the AND-OR graph
class AOgraph
{    
    protected:
        //! add a node in the graph
        void addNode(string nameNode, int cost);
        
        //! find a node by name
        AOnode* findByName(string nameNode);
        
        //! update the feasibility status of the nodes in the graph
        void updateNodeFeasibility();
        
        //! generate all possible paths navigating the graph
        void generatePaths();
        
        //! find the optimal path
        int findOptimalPath();
        
        //! set up a graph
        void setupGraph();
    
    public:
        string gName;           //!< name of the graph
        vector<AOnode> graph;   //!< set of nodes in the AND-OR graph
        AOnode* head;           //!< pointer to the node = final assembly
        vector<Path> paths;     //!< set of paths in the AND-OR graph
        
        //! constructor
		AOgraph(string name);
        
        //! load the graph description from a file
        void loadFromFile(string fileName);
        
        //! display graph information
        void printGraphInfo();
        
        //! solve a node, finding it by name
        void solveByName(string nameNode);
        
        //! suggest the node to solve
        void suggestNext();
        
        //! destructor
		~AOgraph()
		{
			//DEBUG:cout<<endl <<"Destroying AOgraph object" <<endl;
		}
};

#endif
