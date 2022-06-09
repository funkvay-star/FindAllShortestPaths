#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <stack>
#include <list>

typedef std::vector<std::list<std::pair<int, int>>> adjacency_list;

void DeleteNotShortestPaths(std::vector<std::vector<std::pair<int, int>>>& paths, int vertex, int shortestDistance)
{
    if (!paths[vertex].empty() && paths[vertex].begin()->second > shortestDistance)
    {
        paths[vertex].clear();
    }
}

std::vector<std::vector<std::pair<int, int>>> ModifiedDijkstra(adjacency_list graph, int start)
{
    std::vector<int> distance(graph.size(), std::numeric_limits<int>::max());
    std::vector<bool> used(graph.size(), false);

    std::vector<std::vector<std::pair<int, int>>> parents(graph.size());

    distance[start] = 0;

    for (int i = 0; i < graph.size(); ++i)
    {
        int vertex = -1;

        for (int j = 0; j < graph.size(); ++j)
        {
            if (used[j] == false && (vertex == -1 || distance[j] < distance[vertex]))
            {
                vertex = j;
            }
        }

        if (distance[vertex] == std::numeric_limits<int>::max())
        {
            break;
        }

        used[vertex] = true;

        for (auto neighbor : graph[vertex])
        {
            int to = neighbor.first;
            int length = neighbor.second;

            if (distance[to] >= distance[vertex] + length)
            {
                distance[to] = distance[vertex] + length;

                DeleteNotShortestPaths(parents, to, distance[to]);

                parents[to].push_back(std::make_pair(vertex, distance[to]));
            }
        }
    }

    return parents;
}

std::vector<std::vector<int>> RecoverPaths(const std::vector<std::vector<std::pair<int, int>>>& parents, int toVertex, int fromVertex)
{
    std::vector<std::vector<int>> answer;
    std::vector<int> onePath;

    std::stack<std::pair<int, int>> stack;

    stack.push(std::make_pair(fromVertex, 0));

    while (!stack.empty())
    {
        std::pair<int, int> s = stack.top();

        onePath.push_back(s.first);

        if (s.first == toVertex)
        {
            std::vector<int> reversedOnePath(onePath.rbegin(), onePath.rend());
            answer.push_back(reversedOnePath);
        }

        bool sHasNeighbors = false;

        if (s.second < parents[s.first].size())
        {
            sHasNeighbors = true;
            std::pair<int, int> helper = parents[s.first][s.second];
            helper.second = 0;
            stack.push(helper);
        }

        if (!sHasNeighbors)
        {
            stack.pop();
            if (stack.empty())
            {
                break;
            }
            s = stack.top();
            ++s.second;
            stack.pop();
            stack.push(s);
            onePath.resize(onePath.size() - 2);
        }
    }

    return answer;
}

bool VertexInRnge(int vertex, int verticesCount)
{
    return vertex >= 0 && vertex < verticesCount;
}

adjacency_list ReadGraph(std::ifstream& in)
{
    int vertices, edges;

    in >> vertices >> edges;

    if (vertices <= 0 || edges < 0)
    {
        throw std::logic_error("Invalid value for vertices or edges");
    }

    adjacency_list graph(vertices);

    for (int i = 0; i < edges; ++i)
    {
        int vertex1, vertex2, weight;

        in >> vertex1 >> vertex2 >> weight;

        if (VertexInRnge(vertex1, vertices) && VertexInRnge(vertex2, vertices) && weight >= 0)
        {
            graph[vertex1].push_back(std::make_pair(vertex2, weight));
            graph[vertex2].push_back(std::make_pair(vertex1, weight));
        }
        else
        {
            throw std::logic_error("Invalid edge or wrong weight");
        }
    }

    return graph;
}

void PrintGraph(const adjacency_list& Graph)
{
    int index = 0;
    for (auto listOfNeighbors : Graph)
    {
        std::cout << index << ": ";
        for (auto neighbor : listOfNeighbors)
        {
            std::cout << neighbor.first << "(" << neighbor.second << ")  ";
        }
        std::cout << std::endl;
        ++index;
    }
}

int main(int argc, char** argv)
{
    if(argc != 4)
    {
        std::cout << "Invalid number of arguments" << std::endl;
        return 1;
    }

    std::string pathToFile = argv[1];

    std::ifstream in;

    in.open(pathToFile);

    if (!in.is_open())
    {
        std::cout << "Coudn't open the file to read the graph" << std::endl;
        return 1;
    }
    else
    {
        adjacency_list graph;
        try 
        {
            graph = ReadGraph(in);
        }
        catch(const std::logic_error& e)
        {
            std::cout << e.what() << std::endl;
            std::cout << "Coudn't read the graph";
            return 1;
        }

        in.close();

        pathToFile = argv[2];

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

            if (!VertexInRnge(fromVertex, graph.size()) || !VertexInRnge(toVertex, graph.size()))
            {
                std::cout << "Invalid values for fromVertex or toVertex " << fromVertex << " " << toVertex << std::endl;
                return 1;
            }

            in.close();

            std::vector<std::vector<std::pair<int, int>>> notParsedPaths = ModifiedDijkstra(graph, fromVertex);

            std::vector<std::vector<int>> paths = RecoverPaths(notParsedPaths, fromVertex, toVertex);

            std::ofstream out;

            //out.open("../AnswerFiles/AnswerFASP.txt");

            pathToFile = argv[3];

            out.open(pathToFile);

            if (!out.is_open())
            {
                std::cout << "Coudn't open the file to write the answer" << std::endl;
                return 1;
            }
            else
            {
                for (auto onePath : paths)
                {
                    for (auto vertex : onePath)
                    {
                        out << vertex << " ";
                    }
                    out << std::endl;
                }
            }

            out.close();
        }
    }
}