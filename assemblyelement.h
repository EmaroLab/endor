//===============================================================================//
// Name			: assemblyelement.h
// Author(s)	: Barbara Bruno
// Affiliation	: University of Genova, Italy - dept. DIBRIS
// Description	: "Assembly operations"-specific class for AO nodes
//===============================================================================//

#ifndef ASSEMBLY_ELEMENT_H
#define ASSEMBLY_ELEMENT_H

#include "element.h"

//! derivate class "AssemblyElement" for the "Assembly operations"-specific parameters inside a node
class AssemblyElement: public NodeElement
{
    public:
        vector<string> actions; //!< list of actions required by the assembly operation
        vector<bool> done;      //!< done[i]: the i-th action has been performed
        bool finished;          //!< finished: all actions have been performed
        bool sequential;        //!< sequential: the actions MUST be performed in order
        int level;              //!< stage of the whole assembly task at which this operation is performed

        //! constructor
        AssemblyElement(vector<string> some_actions, bool some_sequential, int some_level): NodeElement()
        {
            actions = some_actions;
            // initialize the "done" flags as false for all actions
            for (int i=0; i< (int)actions.size(); i++)
                done.push_back(false);
            // initialize the "finished" flag as false
            finished = false;

            sequential = some_sequential;
            level = some_level;
        }
        
        //! display element information
        void printNodeElementInfo()
        {
            cout<<"Level of the assembly operation: " <<level <<endl;
            cout<<"Is finished? " <<boolalpha <<finished <<endl;
            cout<<"Is sequential? " <<boolalpha <<sequential <<endl;

            cout<<"Actions in the assembly operation:" <<endl;
            for (int i=0; i< (int)actions.size(); i++)
                cout<<actions[i] <<" - done? " <<boolalpha <<done[i] <<endl;
        }
        
        //! destructor
		~AssemblyElement()
		{
			//DEBUG:cout<<endl <<"Destroying AssemblyElement object" <<endl;
		}
};

#endif