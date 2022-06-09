#Graph:


# This project processes a graph and prints all shortest paths from one vertex to another that are given as arguments.

## 1. How to build this project:
1.1) **First you need to be in the 'graphFiles' directory. After that you need to run**
> ./build.sh

**Or**

> bash build.sh

1.2) **After that in 'graphFiles' will be created a 'build' directory, and you need to switch to the 'build' directory. In that directory you need to run**
> ./allShortestPaths
* Notice that you also should pass 3 arguments
1) The txt file that will contain graph (the example of the graph in the end)
2) The txt file that will conatin two vertices where you want to get all the shortest paths from the first to the second vertex
3) The txt file where you want the result to be written
* Example:
> /allShortestPaths graph.txt vertices.txt result.txt


## 2. How to build and run tests:
2.1) **You should change the directory to 'tests/graphTest'**

2.2) **Now you need to run**
> make

2.3) **Now go back to 'tests' directory and run**
> ./test.sh
* Now this will test if the algorithm works fine for a _cycled_ graph and a _matrix_ graph.

## 3. Project's structure
```
graphFiles
├── build.sh
├── CMakeLists.txt
├── src
│   └── findAllShortestPaths.cpp
└── tests
    ├── graphs
    │   ├── circleGraph.txt
    │   └── matrixGraph.txt
    ├── graphTest
    │   ├── lengthOfShortestPathCircle.cpp
    │   ├── Makefile
    │   ├── numberOfShortestPathsMatrix.cpp
    │   └── randomVertices.cpp
    └── test.sh
```





# How to describe graph
1) **First you need to write the number of vertices and then the number of edges.**
* Here we create a graph with 5 vertices and 3 edges.
>5 3
2) **After, we need to create an edge. To create an edge you need the first vertex number and then second vertex number. The third parameter is weigth between that two vertices.**
* Warning: pay attention that vertices are numbered starting from 0.
* Here we created an edge between 0 5 vertices with weigth 7.
>0 5 7
3) **Now, you probably want to see a list of all the short paths between vertex A and vertex B. For that you only need to write the number of that vertices.**
* Here we will get all short paths from vertex 3 to  vertex 9.
>3 9

## Here is a small example of one graph where we want to get all the short paths from vertex 0 to vertex 6

* graphDescription.txt
```
7 10

0 1 3
0 5 1000
1 4 4
1 5 5
4 5 9
4 3 3
5 6 4
3 2 1
3 6 2
2 6 1
```

* vertices.txt
```
0 6
```

![GRAPH](https://user-images.githubusercontent.com/91688611/141691722-06aa8488-51bc-4bae-b399-85ff7108ced9.PNG)
