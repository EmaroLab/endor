//===============================================================================//
// Name			: navigateElement.h
// Author(s)	: Marco Cicellini, Nicolò Bastianelli Naticchi
// Affiliation	: University of Genova, Italy
// Description	: Derivate class for the application-specific parameters inside a node
//===============================================================================//

#ifndef NAVIGATE_ELEMENT_H
#define NAVIGATE_ELEMENT_H

#include "element.h"

//! derivate class "NavigateElement" from "NodeElement" to obtain the specific parameters inside a node
class NavigateElement: public NodeElement
{
    public:
	double x;			//!< X coordinate of the Node
	double y;			//!< Y coordinate of the Node
	double z;			//!< Z coordinate of the Node
	double alpha;			//!< Alpha parameter of the Node
	std::string action; 		//!< action to do by the Node
	int id;				//!< unique identificator of the Node

        //! constructor
        	NavigateElement(double X=0,double Y=0,double Z=0,double alfa=0,std::string actions="",int I_D=-1): NodeElement()
        	{
        		x = X;
			y= Y;
			z = Z;
			alpha = alfa;
			action=actions;
       			id=I_D;   
        	}
	
	//! get X coordinate
        double GetX() {return x;}     			

	//! get the ID of the node
	int GetID() {return id;}
	
	//! get Y coordinate
        double GetY() {return y;}  
        
	//! get Z coordinate
	double GetZ() {return z;}
        
	//! get Alpha parameter
	double GetAlpha() {return alpha;}
	
	//! get the action to do
	std::string GetAction() {return action;}   

	//! display element information
        void printNodeElementInfo()
        {
            
            std::cout<<"Coordinate of the node x: " << x << " y: " << y << " z: "<< z << std::endl;
            std::cout<<"Identificator of the node: " << id << std::endl;
            std::cout<<"Type of action: " << action << std::endl;
        }
        
        //! destructor
		~NavigateElement()
		{
		
		}
};

#endif
