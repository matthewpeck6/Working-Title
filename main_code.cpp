/*
Project 3: "WORKING TITLE" 
by MVP Productions
Team Members: Moinak Dey, Vishwa Krishnan, Matthew Peck
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <istream>
#include <ostream>
#include <unordered_map>
#include <queue>
#include <string>
#include <stack>
#include <chrono>
#include <iomanip>
#include "MovieGraph.h"

using namespace std;
using namespace std::chrono; //Chrono implemented to test how long BFS and DFS takes to run.

typedef high_resolution_clock Clock;

//Reads the data file.
string readFileIntoString(const string& path) {
    auto ss = ostringstream{};
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
            << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}

int main()
{
 
//====================================================//
    //Reading and parsing data into unordered map.
    string filename("data.csv");
    string file_contents;
    std::unordered_map<string, vector<string>> nameid;
    char delimiter = ',';

    file_contents = readFileIntoString(filename);

    istringstream sstream(file_contents);
    std::vector<string> items;
    string record;

    //ID's to people
    std::unordered_map<string, vector<string>> reverseMap;

    int counter = 0;
    getline(sstream, record);
    while (std::getline(sstream, record)) {
        istringstream line(record);
        getline(line, record, delimiter);
        items.push_back(record);
        getline(line, record);

        if (record.find('\"') == 0) {
            string temp = record.substr(1, record.find("\"", 1) - 1);
            items.push_back(temp);

        }
        else {
            items.push_back(record.substr(1));
        }
        line = istringstream(items[1]);
        vector<string> movieids;
        while (std::getline(line, record, delimiter)) {
            movieids.push_back(record);
            if (reverseMap.count(record) == 0) {
                reverseMap[record] = vector<string>();
            }
            reverseMap[record].push_back(items[0]);
        }

        nameid[items[0]] = movieids;
        items.clear();
        counter += 1;
    }
 //====================================================//

   //GRAPH CREATION: Adds edges to graph based on similar movie titles.
    
    MovieGraph graph;

    string currTitle = "";
    for (auto name1 : nameid)
    {
        for (int i = 0; i < name1.second.size(); i++)
        {
            vector<string> movieActors = reverseMap[name1.second[i]];
            for (int j = 0; j < movieActors.size(); j++) {
                if (movieActors[j] == name1.first) {
                    continue;
                }
                graph.addEdge(name1.first, movieActors[j]);
            }
        }
    }

    /*========================================================USER INTERFACE================================================================*/
    cout << "________________________________________________________________________________________________________________________" << '\n';
    cout << setw(64) << "'WORKING TITLE'" << '\n';
    cout << setw(90) << "Find the relationship between two actors based on common movies!" << '\n';
    cout << "________________________________________________________________________________________________________________________" << '\n';
    cout  <<  "Data collected from IMDB(C)" << setw(91) << "By MVP Productions" << '\n' << '\n' << '\n';
    cout << setw(66) << "General Description" << '\n';
    cout << setw(68) << "-~~~~~~~~~~~~~~~~~~~~~-" << '\n';
    cout << '\t' << "This program intends to find a path between two movie actors based on similar movies they starred in." << '\n';
    cout << '\t' << "Each path will find a connection between multiple actors until it reaches the intended actor searched for." << '\n' << '\n';

    int userInput = 0;
    bool confirmExit = false;
    auto start = Clock::now(), end = Clock::now(), startBFS3 = Clock::now(), endBFS3 = Clock::now(), startDFS3 = Clock::now(), endDFS3 = Clock::now();
    string actor1, actor2;
    while (confirmExit != true)
    {
        cout << "Please type the first actor, for example \"Fred Astaire\": " << '\n';
        getline(cin, actor1);
        cout << "Please type the second actor, for example \"Ava Gardner\": " << '\n';
        getline(cin, actor2);

        cout << setw(83) << "__________________________________________________________" << '\n';
        cout << setw(62) << "DROPDOWN MENU" << '\n';
        cout << '\t' << '\t' << '\t' << "1. Run Breadth-First Search (BFS) between " << actor1 << " & " << actor2 << "." << '\n';
        cout << '\t' << '\t' << '\t' << "2. Run Depth-First Search (DFS) between " << actor1 << " & " << actor2 << "." << '\n';
        cout << '\t' << '\t' << '\t' << "3. Compare BFS performance and DFS performance of two actors." << '\n';
        cout << '\t' << '\t' << '\t' << "4. Exit Program." << '\n';
        cout << setw(83) << "__________________________________________________________" << '\n' << '\n';
        cout << '\t' << '\t' << '\t' << "Please enter a menu option: ";
        cin >> userInput;
        cout << '\n';


        switch (userInput)
        {
        case 1:
            cout << "Performing \"BFS\" on " << actor1 << " & " << actor2 << "." << '\n';
            cout << "========================================================================================================================" << '\n';

            start = Clock::now();
            graph.bfs(actor1, actor2);
            end = Clock::now();
            cout << '\n';
            cout << "BFS traversal between " << actor1 << " and " << actor2 << " took "
                << duration_cast<microseconds>(end - start).count()
                << " microseconds." << '\n';

            cout << "========================================================================================================================" << '\n';
            break;
        case 2:
            cout << "Performing \"DFS\" on " << actor1 << " & " << actor2 << "." << endl;
            cout << "========================================================================================================================" << '\n';
            start = Clock::now();
            graph.dfs(actor1, actor2);
            end = Clock::now();
            cout << '\n';
            cout << "DFS traversal between " << actor1 << " and " << actor2 << " took "
                << duration_cast<microseconds>(end - start).count()
                << " microseconds." << '\n';

            cout << "========================================================================================================================" << '\n';
            break;
        case 3:
            cout << "Analyzing performance difference between  \"BFS\" and  \"DFS\" on " << actor1 << " & " << actor2 << "." << endl;
            cout << "========================================================================================================================" << '\n';
            startBFS3 = Clock::now();
            cout << "BFS: " << '\n';
            graph.bfs(actor1, actor2);
            endBFS3 = Clock::now();
            cout << '\n';
      
            startDFS3 = Clock::now();
            cout << "DFS: " << '\n';
            graph.dfs(actor1, actor2);
            endDFS3 = Clock::now();
            cout << '\n';
            cout << "BFS traversal between " << actor1 << " and " << actor2 << " took "
                << duration_cast<microseconds>(endBFS3 - startBFS3).count()
                << " microseconds." << '\n';
            cout << "DFS traversal between " << actor1 << " and " << actor2 << " took "
                << duration_cast<microseconds>(endDFS3 - startDFS3).count()
                << " microseconds." << '\n';

            cout << "========================================================================================================================" << '\n';
            break;
        case 4:
            cout << "Exiting Program..." << endl;
            confirmExit = true;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    exit(EXIT_SUCCESS);
}



