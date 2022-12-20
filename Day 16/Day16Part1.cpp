#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

// difficulty leap from day 5 down to this one is bigger than your mother

struct Node {
    string name;
    Node* prev;
    vector<Node*> next;

    Node(const string& name) : name(name) {
        this->prev = nullptr;
        this->next = vector<Node*>();
    }
    Node(const string& name, Node* prev, const vector<Node*>& next) {
        this->name = name;
        this->prev = prev;
        this->next = next;
    }

    void print() {
        cout << "Node " << name;
        if(next.size() != 0) {
            cout << " points to " << next[0];
            for(int i = 1; i < next.size(); ++i) {
                cout << ", " << next[i];
            }
        }
        cout << endl;
    }
};

struct Graph{
    vector<Node*> nodes;

    void print() {
        for(Node* i : nodes) {
            i->print();
        }
    }

    ~Graph() {
        for(Node* i : nodes) {
            delete i;
        }
    }
};

struct Valve {
    int flowRate;
    map<string, int> distances;

    Valve(int rate) : flowRate(rate) {
        this->distances = map<string, int>();
    }
};

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    vector<Valve> system;
    Graph graph;

    // construct a graph based on valves
    while(getline(in, line)) {
        string name = line.substr(line.find(" ")+1, line.find("has") - line.find(" ") - 2);
        int rate = stoi(line.substr(line.find("=") + 1, line.find(";")));
        line.erase(0, line.find("to") + 3);
        cout << "Valve " << name << " with rate " << rate << ", line: " << line << endl;
        system.push_back(Valve(rate));

        istringstream sin(line);
        string next;
        sin >> next;
        vector<Node*> vNext;
        while(sin) {
            sin >> next;
            auto found = find_if(graph.nodes.begin(), graph.nodes.end(), [next](const Node* i) {
                return i->name == next;
            });

            // add Ndoe to next vector, also add to graph if doesn't exist
            if(found == graph.nodes.end()) {
                Node* temp = new Node(next);
                vNext.push_back(temp);
                graph.nodes.push_back(temp);
            }
            else {
                vNext.push_back(*found);
            }
        }


        if(find_if(graph.nodes.begin(), graph.nodes.end(), [name](const Node* i) {
            return i->name == name;
        }) == graph.nodes.end()) {
            graph.nodes.push_back(name, nullptr, vNext);
        }
    }

    // run djikstra on it to get the shortest path to any node from any node
    // save those paths in a map in a valve struct


    int result = 0;

    graph.print();

    cout << "result: " << result << endl;

    return 0;
}