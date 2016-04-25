//===============================================================================//
// Name			: aonode.cpp
// Author(s)	: Barbara Bruno, Yeshasvi Tirupachuri V.S.
// Affiliation	: University of Genova, Italy - dept. DIBRIS
// Version		: 1.0
// Description	: Generic node element of an AND-OR graph
//===============================================================================//

#include "aonode.h"

//! constructor of class HyperArc
//! @param[in] nodes    set of child nodes connected via the hyperarc
HyperArc::HyperArc(vector<AOnode*> nodes)
{
    children = nodes;
    
    //DEBUG:printArcInfo();
}

//! display hyperarc information
//! @param[in] index    index of the arc in the vector of HyperArcs
void HyperArc::printArcInfo(int index)
{
    cout<<"Info of hyperarc: " <<index <<endl;
    cout<<"Child nodes: ";
    for (int i=0; i< (int)children.size(); i++)
        cout<<children[i]->nName <<" ";
    cout<<endl;
}

//! constructor of class AOnode
//! @param[in] name	   name of the node
//! @param[in] cost    generic node cost
AOnode::AOnode(string name, int cost)
{
    nName = name;
	nCost = cost;
    nFeasible = false;
    nSolved = false;
    
    //DEBUG:printNodeInfo();
}

//! add an hyperarc to child nodes
//! @param[in] nodes   set of child nodes connected via the hyperarc
void AOnode::addArc(vector<AOnode*> nodes)
{
    // create the hyperarc
    HyperArc toAdd(nodes);
    
    // add it to the set of hyperarcs
    arcs.push_back(toAdd);
}

//! display node information
void AOnode::printNodeInfo()
{
    cout<<"Info of node: " <<nName <<endl;
    cout<<"Cost: " <<nCost <<endl;
    cout<<"Is feasible? " <<boolalpha <<nFeasible <<endl;
    cout<<"Is solved? " <<boolalpha <<nSolved <<endl;
    cout<<"Number of hyperarcs: " <<arcs.size() <<endl;
    for (int i=0; i< (int)arcs.size(); i++)
        arcs[i].printArcInfo(i);        
}

//! determine whether the node is feasible
void AOnode::isFeasible()
{
    bool temp_isFeasible = false;
    
    // 1. the node is feasible if it is already feasible
    if (nFeasible == true)
        temp_isFeasible = true;
        
    // 2. the node is feasible if it is a terminal node (no hyperarcs)
    if (arcs.size() == 0)
        temp_isFeasible = true;
    
    // 3. the node is feasible if it has >=1 hyperarcs with all child nodes solved
    // iterate on the hyperarcs of the node
    for (int i=0; i<(int)arcs.size(); i++)
    {
        bool allSolved = true;
            
        // iterate on the child nodes
        for (int j=0; j<(int)arcs[i].children.size(); j++)
        {
            // if the node is not solved --> break
            if (arcs[i].children[j]->nSolved == false)
            {
                allSolved = false;
                break;
            }
        }
        // if all the child nodes are solved, this node is feasible
        if (allSolved == true)
        {
            temp_isFeasible = true;
            break;
        }
    }
    
    // set the feasibility property
    nFeasible = temp_isFeasible;
}

//! set the node as solved
//! @return result of the operation (true = done, false = not done)
bool AOnode::setSolved()
{
    // a node can be solved only if it's feasible
    if (nFeasible == true)
    {
        nSolved = true;
        return true;
    }
    else
    {
        cout<<"[ERROR] The node is not feasible. Are you sure it is solved?" <<endl;
        return false;
    }
}
