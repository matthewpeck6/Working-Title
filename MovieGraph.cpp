#include "MovieGraph.h"
#include <queue>
#include <string>
#include <iostream>
#include <stack>
using namespace std;

//Adds edge to adjacency list.
void MovieGraph::addEdge(string src, string dest)
{
	this->adjList[src].push_back(dest);
	this->adjList[dest].push_back(src);
}

//BFS Algorithm Implementation
void MovieGraph::bfs(string src, string dest)
{
    //If the matching names are equal
    if (src == dest) {
        cout << src << endl;
        return;
    }

    string result;
    bool isFound = false;
    queue<string> q;
    unordered_map<string, bool> visited;
    q.push(src);
    visited[src] = true;

    while (!q.empty())
    {
        string u = q.front();
        result.append(u + "->");
        q.pop();

        for (string neighbor : adjList[u])
        {
            if (u == dest) {
                cout << result.substr(0, result.size() - 2) << endl;
                isFound == true;
                return;
            }

            if (!visited[neighbor])  {
                q.push(neighbor);
                visited[neighbor] = true;
            }
            
        }
    }
    if (isFound == false)
        cout << "No related movies found between " << src << " and " << dest << "!" << endl;
}

//DFS Algorithm Implementation
void MovieGraph::dfs(string src, string dest)
{
    //If the matching names are equal
    if (src == dest) {
        cout << src << endl;
        return;
    }

    string result;
    bool isFound = false;
    stack<string> s;
    unordered_map<string, bool> visited;
    s.push(src);
    visited[src] = true;

    while (!s.empty())
    {
        string u = s.top();
        result.append(u + "->");
        s.pop();

        for (string neighbor : adjList[u])
        {
            if (u == dest) {
                cout << result.substr(0, result.size() - 2) << endl;
                isFound == true;
                return;
            }

            if (!visited[neighbor]) {
                s.push(neighbor);
                visited[neighbor] = true;
            }

        }
    }
    if (isFound == false)
        cout << "No related movies found between " << src << " and " << dest << "!" << endl;
}
