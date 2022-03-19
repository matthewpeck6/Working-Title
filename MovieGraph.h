#pragma once
#include <vector>
#include <unordered_map>
using namespace std;

class MovieGraph
{
private:
    unordered_map<string, vector<string>> adjList; //Utilizes adjacency list to store and find connections between vertices of actor names.
public:
    void addEdge(string src, string dest);
    void bfs(string src, string dest);
    void dfs(string src, string dest);
};

