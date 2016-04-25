//===============================================================================//
// Name			: aograph.cpp
// Author(s)	: Barbara Bruno, Yeshasvi Tirupachuri V.S.
// Affiliation	: University of Genova, Italy - dept. DIBRIS
// Version		: 1.0
// Description	: AND-OR graph
//===============================================================================//

#include "aograph.h"

//! constructor of class Path
//! @param[in] cost 	initial cost of the path
//! @param[in] index 	unique index of the path
Path::Path(int cost, int index)
{
    pIndex = index;
    pCost = cost;
    pComplete = false;
}

//! copy constructor of class Path
//! @param[in] &toBeCopied  path to be copied
//! @param[in] index        unique index of the path
Path::Path(const Path &toBeCopied, int index)
{
    pIndex = index;
    pCost = toBeCopied.pCost;
    pComplete = false;
    pathNodes = toBeCopied.pathNodes;
    checkedNodes = toBeCopied.checkedNodes;
}

//! display path information
void Path::printPathInfo()
{
    cout<<"Info of path: " <<pIndex <<endl;
    //DEBUG: cout<<"Is complete? " <<boolalpha <<pComplete <<endl;
    cout<<"Total cost: " <<pCost <<endl;
    cout<<"Nodes in path:" <<endl;
    for (int i=0; i< (int)pathNodes.size(); i++)
    {
        cout<<pathNodes[i]->nName <<" ";
        //DEBUG: cout<<"checked? " <<boolalpha <<checkedNodes[i];
        if (checkedNodes[i] == true)
            cout<<"- done";
        cout<<endl;
    }
    cout<<endl;
}

//! add a node in the path
//! @param[in] node    node to add to the path
void Path::addNode(AOnode* node)
{
    pathNodes.push_back(node);
    checkedNodes.push_back(false);
    pCost = pCost + node->nCost;
}

//! update the path information (when a node is solved)
//! @param[in] nameNode    name of the node
void Path::updatePath(string nameNode)
{
    // check whether the node is in the path
    for(int i=0; i < (int)pathNodes.size(); i++)
    {
        // if a node is solved, its cost goes to 0
        if (pathNodes[i]->nName == nameNode)
        {
            checkedNodes[i] = true;
            pCost = pCost - pathNodes[i]->nCost;
        }
    }
    
    cout<<"Path: " <<pIndex <<endl;
    cout<<"Updated path cost: " <<pCost <<endl;
}

//! find the feasible node to suggest
//! @return node to suggest
AOnode* Path::suggestNode()
{
    //!\todo define a finer strategy for the selection of the node to suggest
    
    AOnode* selection = NULL;
    
    // iterate on the nodes in the path, from the last to the first one
    for (int i = (int)pathNodes.size()-1; i > -1; i--)
    {
        // rationale for the suggestion:
        // 1. move along the path from the leaves to the head
        // 2. choose the first feasible & not-solved node
        if (checkedNodes[i] == false)
        {
            if (pathNodes[i]->nFeasible == true)
            {
                selection = pathNodes[i];
                break;
            }
        }
    }
    
    // raise an error if the suggested node is NULL
    if (selection == NULL)
        cout<<"[ERROR] No suggestion possible." <<endl;
    
    return selection;
}

//! add a node in the graph
//! @param[in] nameNode    name of the node
//! @param[in] cost        generic node cost
void AOgraph::addNode(string nameNode, int cost)
{
    // create the node
    AOnode toAdd(nameNode, cost);
    
    // add it to the set of nodes in the graph
    graph.push_back(toAdd);
}

//! find a node by name
//! @param[in] nameNode    name of the node
//! @return	               pointer to the node with given name
AOnode* AOgraph::findByName(string nameNode)
{
    AOnode* temp = NULL;
    
    for (int i=0; i< (int)graph.size(); i++)
    {
        if (graph[i].nName == nameNode)
        {
            temp = &graph[i];
            break;
        }
    }
    
    // issue a warning if the node has not been found
    if (temp == NULL)
        cout<<"[Warning] Name not found."
            <<"Did you really look for " <<nameNode <<"?" <<endl;
    return temp;
}

//! update the feasibility status of the nodes in the graph
void AOgraph::updateNodeFeasibility()
{
    for (int i=0; i< (int)graph.size(); i++)
        graph[i].isFeasible();        
}

//! generate all possible paths navigating the graph
void AOgraph::generatePaths()
{
    // if the head node is NULL, there are no paths to generate
    if (head == NULL)
    {
        cout<<"[WARNING] There is no graph to navigate (head == NULL)." <<endl;
        return;
    }
    
    // otherwise, create one empty path
    AOnode* currentNode = head;
    Path* newPath = new Path(0,0);
    newPath->addNode(currentNode);
    paths.push_back(*newPath);
    
    // iterate through the paths until they're all complete
    while(1)
    {
        // find the first not-complete path
        bool allComplete = true;
        int currentPathIndex;
        for (int i=0; i< (int)paths.size(); i++)
        {
            if (paths[i].pComplete == false)
            {
                allComplete = false;
                currentPathIndex = i;
                break;
            }
        }
        // if all paths are complete, the generation is done
        if (allComplete == true)
            return;
            
        // find the first not-checked node in the open path
        bool allChecked = true;
        int currentNodeIndex;
        for (int i=0; i< (int)paths[currentPathIndex].checkedNodes.size(); i++)
        {
            if (paths[currentPathIndex].checkedNodes[i] == false)
            {
                allChecked = false;
                currentNode = paths[currentPathIndex].pathNodes[i];
                currentNodeIndex = i;
                break;
            }
        }
        // if all nodes are checked, the path is complete
        if (allChecked == true)
            paths[currentPathIndex].pComplete = true;
        else
        {
            // if the current node is terminal:
            // 1. check it
            if (currentNode->arcs.size() == 0)
                paths[currentPathIndex].checkedNodes[currentNodeIndex] = true;
            
            // if the current node has only one hyperarc:
            // 1. check it
            // 2. add its child nodes to the path
            if (currentNode->arcs.size() == 1)
            {
                paths[currentPathIndex].checkedNodes[currentNodeIndex] = true;
                for (int i=0; i< (int)currentNode->arcs[0].children.size(); i++)
                    paths[currentPathIndex].addNode(currentNode->arcs[0].children[i]);
            }
            
            // if the current node has more than one hyperarc:
            // 1. create (numArcs-1) copies of the current path
            // 2. check the current node in the copies
            // 3. add the child nodes of the last (numArcs-1) arcs to the copies
            // 4. check the current node in the current path
            // 5. add the child nodes of the first arcs to the current path
            if (currentNode->arcs.size() > 1)
            {
                int numCopies = currentNode->arcs.size()-1;
                for (int i=0; i<numCopies; i++)
                {
                    newPath = new Path(paths[currentPathIndex], paths.size());
                    newPath->checkedNodes[currentNodeIndex] = true;
                    for (int j=0; j< (int)currentNode->arcs[i+1].children.size(); j++)
                        newPath->addNode(currentNode->arcs[i+1].children[j]);
                    paths.push_back(*newPath);
                }
                paths[currentPathIndex].checkedNodes[currentNodeIndex] = true;
                for (int i=0; i< (int)currentNode->arcs[0].children.size(); i++)
                    paths[currentPathIndex].addNode(currentNode->arcs[0].children[i]);
            }
        }
    }
}

//! find the optimal path
//! @return index of the optimal path (minimum cost)
int AOgraph::findOptimalPath()
{
    // raise an error if there are no paths
    if (paths.size() == 0)
    {
        cout<<"[ERROR] There are no paths navigating the graph. "
            <<"Did you run generatePaths()?" <<endl;
        return -1;
    }
    
    int index = 0;
    int cost = paths[0].pCost;
    for (int i=0; i< (int)paths.size(); i++)
    {
        // raise an error if there are not-complete paths
        if (paths[i].pComplete == false)
        {
            cout<<"[ERROR] The paths navigating the graph are not complete. "
                <<"Did you run generatePaths()?" <<endl;
            return -1;
        }
        
        if (paths[i].pCost < cost)
        {
            cost = paths[i].pCost;
            index = i;
        }
    }
    cout<<"The optimal path is: " <<index <<endl;
    paths[index].printPathInfo();
    
    return index;
}

//! set up a graph
void AOgraph::setupGraph()
{
    // update the feasibility status of the nodes in the graph
    updateNodeFeasibility();
    printGraphInfo();
    
    // generate all paths navigating the graph
    generatePaths();
    // set the "checked" property of the nodes in the paths to false
    // NOTE: during execution, checked is used to mark the solved nodes
    for (int i=0; i < (int)paths.size(); i++)
        for (int j=0; j < (int)paths[i].checkedNodes.size(); j++)
            paths[i].checkedNodes[j] = false;
            
    // identify the first suggestion to make
    suggestNext();
}

//! constructor of class AOgraph
//! @param[in] name 	name of the graph
AOgraph::AOgraph(string name)
{
    gName = name;
    head = NULL;
    
    //DEBUG:printGraphInfo();
}

//! load the graph description from a file
//! @param[in] fileName    name of the file with the graph description
void AOgraph::loadFromFile(string fileName)
{
    // raise an error if the graph is not empty
    if (graph.size() != 0)
    {
        cout<<"[ERROR] The graph is not empty."
            <<"Do you really want to overwrite the current graph?" <<endl;
        return;
    }            
    
    ifstream graphFile(fileName.c_str());
	cout <<"Loading graph description from file: " <<fileName <<endl;
    
	while (!graphFile.eof())
	{
        // the first line contains:
        // 1. the name of the graph
        // 2. the number N=numNodes of nodes
        // 3. the name of the head node (corresponding to the final assembly)
        string name;
        int numNodes;
        string headName;
        
        graphFile >>name >>numNodes >>headName;
        if (!graphFile)
			break;
        gName = name;
        
        // the next N lines contain the name and cost of all the nodes in the graph
        string nameNode;
        int cost;
        for (int i=0; i < numNodes; i++)
        {            
            graphFile >>nameNode >> cost;
            if (!graphFile)
                break;
            addNode(nameNode, cost);
        }
        
        // the next ?? lines contain the descriptions of the hyperarcs in the graph
        while (!graphFile.eof())
        {
            AOnode* father;
            string nameFather;
            int numChildren;
            vector<AOnode*> childNodes;
            
            graphFile >>numChildren >>nameFather;
            if (!graphFile)
                break;
            father = findByName(nameFather);
            //DEBUG:cout<<"nameFather = " <<nameFather <<endl;
            
            // the next numChildren lines contain the names of the child nodes
            for (int i=0; i < numChildren; i++)
            {
                AOnode* temp;
                string nameChild;
                graphFile >>nameChild;
                if (!graphFile)
                    break;
                temp = findByName(nameChild);
                childNodes.push_back(temp);
            }
            father->addArc(childNodes);
        }
        // identify the head node in the graph
        head = findByName(headName);
    }
    graphFile.close();
    
    // set up the graph (nodes feasibility, paths costs)
    setupGraph();
}

//! display graph information
void AOgraph::printGraphInfo()
{
    cout<<endl;
    cout<<"Info of graph: " <<gName <<endl;
    cout<<"Number of nodes: " <<graph.size() <<endl;
    cout<<"Head node: " <<head->nName <<endl;
    for (int i=0; i< (int)graph.size(); i++)
        graph[i].printNodeInfo();
    cout<<endl;
}

//! solve a node, finding it by name
//! @param[in] nameNode    name of the node
void AOgraph::solveByName(string nameNode)
{
    AOnode* solved = findByName(nameNode);
    bool result = solved->setSolved();
    updateNodeFeasibility();
    printGraphInfo();
    
    // report that the graph has been solved if the solved node is the head node
    if (head->nSolved == true)
        cout<<"[REPORT] The graph is solved (head node solved)." <<endl;
    
    // update the path information (cost)
    if (result == true)
        for (int i=0; i < (int)paths.size(); i++)
            paths[i].updatePath(nameNode);
    
    // identify the next suggestion to make
    suggestNext();               
}

//! suggest the node to solve
void AOgraph::suggestNext()
{
    // issue a warning if the graph has been solved already
    if (head->nSolved == true)
        cout<<"[WARNING] The graph is solved. No suggestion possible." <<endl;
    else
    {
        int optimalPathIndex = findOptimalPath();
        AOnode* suggestion = paths[optimalPathIndex].suggestNode();
    
        cout<<"ENDOR suggestion: " <<suggestion->nName <<endl;
    }
}
