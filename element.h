//===============================================================================//
// Name			: element.h
// Author(s)	: Barbara Bruno
// Affiliation	: University of Genova, Italy - dept. DIBRIS
// Description	: Base class for the application-specific parameters inside a node
//===============================================================================//

#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>



//! base class "NodeElement" for the application-specific parameters inside a node
class NodeElement
{  
public:      
      //! constructor
		NodeElement()
        {
			//DEBUG:cout<<endl <<"Destroying NodeElement object" <<endl;
		}
        
        //! display element information
        virtual void printNodeElementInfo() = 0;

	//! get X coordinate
	virtual double GetX() = 0;  

	//! get Y coordinate
	virtual double GetY() = 0;  

	//! get Z coordinate
	virtual double GetZ() = 0;  

	//! get Alpha parameter
	virtual double GetAlpha() = 0;  

	//! get the action to do
	virtual std::string GetAction() = 0;        

	//! get the ID of the node
	virtual int GetID() = 0;

        //! destructor
		~NodeElement()
		{
			//DEBUG:cout<<endl <<"Destroying NodeElement object" <<endl;
		}
};

#endif
