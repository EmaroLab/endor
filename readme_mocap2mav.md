### Info for developers

To start the program open gazebo and then open a new terminal and, in the "mocap2mav" folder, write './app_start.sh'.
After a while push 'sim'.

Then two new terminals will be opened: "exec" and "autom". Only the first must be used.

The AndOr graph is simulated via a UAV.

To include the library in your program, include `"aograph.h"`.

To trace the UAV position the derivate class "NavigateElement" has been created. It contains:

1. x coordinate of the node
2. y coordinate of the node
3. z coordinate of the node
4. alpha parameter of the node
5. identificator of the node

During initialization, the first thing to do is to create a graph:

`AOgraph::AOgraph("DEFAULT");`

and load a description from a file using:

`string description = "./Modules/Executioner/assemblies/Scenario1.txt";`

`AOgraph::loadFromFile(description);`

The loading function automatically sets up the graph, by calling `setupGraph()`, which:

1. defines whether a node is feasible
2. generates all paths navigating the graph
3. identifies the optimal path
4. suggests the first node to solve

The loaded graph can be traveled off-line by pushing 'y' by keyboard in the interface of "exec". It will appear:
"Do you want to proceed? Y/N" (this question will be repeated at each iteration)
And the user must push 'y'.

Than, it is possible to change the path online by keyboard by answering to the question as following:

1. At the beginning, it is important to do the 'takeoff' action and the first 'move' action to let UAV go on the start node (that is the final node of the graph). Otherwise the system crashes and the the user must restart the program. So user must answer 'y' for the first two times. 

1. By pushing the button 'r', user will have the possibilty to augment the cost of the next hyperarc in way to make it unfeasible. 
Than, each path is adjourned and the optimal path is recomputed.

2. By pushing the button 'a', user will have the possibilty to add an hyperarc from the current node to another one, taking care to avoid cyclic natura. 
The name of the second node, the index of hyperarc and the cost of the hyperarc have to be given by keyboard. Then, each path is adjourned and the optimal path is recomputed.
After pushing 'a', the user will see the following interface in "exec" and he will insert the respective information as in the example:
"Insert Name of Node:" 
e.g. Node4
"Insert Index of Arc:"
e.g. 1
"Insert Cost of Arc:"
e.g. 1

3. By pushing the button 's', user will have the possibilty to consider a random node as solved. This simulates the cooperative behaviour among more than one robot. 
The name of the solved node is inserted by keyboard. Then, the paths including this node are deleted.
After pushing 's', the user will see the following interface in "exec" and he will insert the respective information as in the example:
"Insert Name of Node:"
e.g. Node4
It is very important in the following iterations to not answer 'a' after having answered 's'. In this case new paths will be generated and so the changes done by 's' will be lost.

At run-time, set a node as solved with:

`AOgraph::solveByName("[name_of_node]");`


The library implements two alternative strategies for suggesting the next node to solve:

1. the long-sighted strategy suggests a node along the path which minimizes the overall cost to reach the head node of the graph;
2. the short-sighted strategy suggests a node along the path which most benefitted from the solving of the last node;

The long-sighted strategy is associated with code 0 and the long-sighted strategy with code 1. Ask for a suggestion with:

`AOgraph::suggestNext([1/0]);`

which displays the name of the node suggested by the system to solve.
