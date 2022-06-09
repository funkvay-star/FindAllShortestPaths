#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <queue>
#include <list>

typedef std::vector<std::list<std::pair<int, int>>> adjacency_list;

bool VertexInRnge(int vertex, int verticesCount)
{
    return vertex >= 0 && vertex < verticesCount;
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Invalid number of arguments" << std::endl;
        return 1;
    }

    std::ifstream in;

    std::string pathToFile = argv[1];

    in.open(pathToFile);

    if (!in.is_open())
    {
        std::cout << "Coudn't open the file to read the Source and Destination vertices" << std::endl;
        return 1;
    }
    else
    {
        int fromVertex, toVertex;

        in >> fromVertex >> toVertex;

        if (!VertexInRnge(fromVertex, 10000) || !VertexInRnge(toVertex, 10000))
        {
            std::cout << "Invalid values for fromVertex or toVertex " << fromVertex << " " << toVertex << std::endl;
            return 1;
        }

        in.close();

        std::ofstream out;

        //out.open("../AnswerFiles/AnswerNOSPC.txt");

        pathToFile = argv[2];

        out.open(pathToFile);

        if (!out.is_open())
        {
            std::cout << "Coudn't open the file to write the answer" << std::endl;
            return 1;
        }
        else
        {
            out << std::min(std::abs(fromVertex - toVertex), std::abs(10000 - std::abs(fromVertex - toVertex))) + 1;
        }
        out.close();
    }

    in.close();
}