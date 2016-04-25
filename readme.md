# README

The **ENDOR library** is a C++ library for the creation and navigation of AND-OR graphs. By describing a procedure (e.g., an assembly) as an AND-OR graph, the library can identify the optimal sequence of operations (a-priori and at run-time) and suggest the next operation to perform. As the user signals the successful execution of operations, the library automatically updates the optimal sequence and the suggested operations.

## 1. Installation & Usage

The **ENDOR library** uses the following tools:
1. `CMake` for building the executable
2. `doxygen` for generating the documentation

To build the **ENDOR library**, open a Terminal window and:
1. browse into the `<endor>` folder
2. `cmake .`
3. `make`

### Sample program

To run the sample program for the  **ENDOR library**, open a terminal window and:
1. browse into the `<endor>` folder
2. `./endor`

To test the functionalities of the library, you can load `./assemblies/pencil_assembly.txt`.

### Info for developers

To include the library in your program, include `"aograph.h"`.

During initialization, the first thing to do is to create a graph:

`AOgraph oneGraph("DEFAULT");`

and load a description from a file:

`string description = "./assemblies/pencil_assembly.txt";`

`oneGraph.loadFromFile(description);`

The loading function automatically sets up the graph, by calling `setupGraph()`, which:
1. defines whether a node is feasible
2. generates all paths navigating the graph
3. identifies the optimal path
4. suggests the first node to solve

At run-time, set a node as solved with:

`oneGraph.solveByName("[name_of_node]");`

`solveByName()` automatically calls `suggestNext()` which returns the name of the node suggested by the system to solve.

## 2. Documentation

Up-to-date documentation for this release is accessible from `./docs/html/index.xhtml`.

The rules for the generation of the documentation are specified in `./doxygen_config.txt`.

To re-generate the documentation, open a Terminal window and:
1. browse into the `<endor>` folder
2. `doxygen doxygen_config`

## 3. Licensing

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY, including the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. The authors allow the users of the **ENDOR library** to use and modify it for their own research. Any commercial application, redistribution, etc... has to be arranged between users and authors individually.

For further license information, please contact the authors.

## 4. Authors contacts

If you want to be informed about library updates and new releases, obtain further information about the provided code, or contribute to its development please write to:

Barbara Bruno - barbara.bruno@unige.it

Fulvio Mastrogiovanni - fulvio.mastrogiovanni@unige.it

Barbara Bruno and Fulvio Mastrogiovanni are with the dept. DIBRIS at the University of Genoa, Italy.
