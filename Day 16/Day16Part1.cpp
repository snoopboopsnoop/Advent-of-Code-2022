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
            cout << " points to " << next[0]->name;
            for(int i = 1; i < next.size(); ++i) {
                cout << ", " << next[i]->name;
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
    string name;
    int flowRate;
    map<string, int> paths;

    Valve(string name, int rate) : flowRate(rate), name(name) {
        this->paths = map<string, int>();
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
        system.push_back(Valve(name, rate));

        istringstream sin(line);
        // cout << "line: " << line << endl;
        string next;
        sin >> next;
        vector<Node*> vNext;
        sin >> next;
        while(sin) {
            // cout << "next: " << next << endl;
            if(next.back() == ',') next.erase(next.end()-1);
            auto found = find_if(graph.nodes.begin(), graph.nodes.end(), [next](const Node* i) {
                return i->name == next;
            });

            // add Ndoe to next vector, also add to graph if doesn't exist
            if(found == graph.nodes.end()) {
                // cout << "node " << next << " doesn't exist, adding it to grpah" << endl;
                Node* temp = new Node(next);
                vNext.push_back(temp);
                graph.nodes.push_back(temp);
            }
            else {
                // cout << "node " << name << " points to " << next << endl;
                vNext.push_back(*found);
            }
            sin >> next;
        }

        auto found = find_if(graph.nodes.begin(), graph.nodes.end(), [name](const Node* i) {
            return i->name == name;
        });
        if(found == graph.nodes.end()) {
            // cout << "adding node " << name << " to graph" << endl;
            graph.nodes.push_back(new Node(name, nullptr, vNext));
        }
        else {
            (*found)->next.insert((*found)->next.end(), vNext.begin(), vNext.end());
        }
    }

    // run djikstra on it to get the shortest path to any node from any node
    // save those paths in a map in a valve struct


    int result = 0;

    cout << endl;

    sort(graph.nodes.begin(), graph.nodes.end(), [](const Node* a, const Node* b) {
        return a->name < b->name;
    });

    graph.print();
    cout << endl;

    // run bfs on it to get the shortest path to any node from any node

    // try it for just A
    for(Valve& valve : system) {
        vector<Node*> visited;
        vector<Node*> unvisited;
        unvisited.push_back(*find_if(graph.nodes.begin(), graph.nodes.end(), [valve](const Node* a) {
            return a->name == valve.name;
        }));

        for(const Node* i : graph.nodes) {
            valve.paths.insert(make_pair(i->name, 0));
        }

        while (unvisited.size() != 0) {
            Node* curr = unvisited[0];
            unvisited.erase(unvisited.begin());
            visited.push_back(curr);

            for(Node* i : curr->next) {
                if(find(visited.begin(), visited.end(), i) != visited.end()) continue;
                if(valve.paths.at(i->name) > valve.paths.at(curr->name) + 1 || valve.paths.at(i->name) == 0) {
                    valve.paths.at(i->name) += valve.paths.at(curr->name) + 1;
                    //cout << "Node " << i->name << " now has path length " << valve.paths.at(i->name) << endl;
                }
                unvisited.push_back(i);
            }
        }

        // cout << "From Node " << valve.name << ": " << endl;
        // for(auto itr = valve.paths.begin(); itr != valve.paths.end(); ++itr) {
        //     cout << "Node " <<  itr->first << " has distance " << itr->second << endl;
        // }
        // cout << endl;   
    }

    Valve start = system[0];

    system = vector<Valve>(system.begin(), remove_if(system.begin(), system.end(), [](const Valve& i) {
        return (i.flowRate == 0);
    }));

    for(const Valve& i : system) {
        cout << "valve " << i.name << endl;
    }

    long long count = 1;
    int totalCount = system.size();

    sort(system.begin(), system.end(), [](const Valve& a, const Valve& b) {
        return a.flowRate < b.flowRate;
    });

    for(const Valve& i : system) {
        cout << "valve " << i.name << " has flow rate=" << i.flowRate << endl;
    }   

    do {
        // cout.flush();
        // cout << "perm " << count << " / " << totalCount << "!" << "\r";
        // cout << "checking path: AA";
        // for(int i = system.size()-1; i >= 0; --i) {
        //     cout << "->" << system[i].name;
        // }
        // cout << endl;
        //count++;
        int time = 0;
        int pressure = 0;
        int total = 0;
        
        //cout << "moving to valve " << system[0].name << endl;
        time += start.paths.at(system.back().name);
        //cout << "turning it on" << endl;
        time += 1;
        pressure += system.back().flowRate;

        for(int i = system.size()-1; i > 0; --i) {
            //cout << "moving to valve " << system[i+1].name << endl;
            // travel to next valve
            int length = system[i].paths.at(system[i-1].name);
            //cout << " path length of " << length << endl;
            time += length;
            if(time > 30) break;
            total += length * pressure;
            //cout << "total: " << total << endl;
    
            // turn it on
            time += 1;
            if(time > 30) break;
            total += pressure;
            //cout << "total: " << total << endl;
            pressure += system[i-1].flowRate;

            //cout << "releasing " << pressure << " pressure" << endl;
        }
        if(time < 30) total += (30 - time) * pressure;
        if(result < total) {
            result = total;
            cout << "new best path: AA";
            for(int i = system.size()-1; i >= 0; --i) {
                cout << "->" << system[i].name;
            }
            cout << endl;
            cout << "released " << total << " pressure" << endl;
        }
        cout << "checking path: AA";
        for(int i = system.size()-1; i >= 0; --i) {
            cout << "->" << system[i].name;
        }
        cout << ", released " << total << " pressure" << "\r";
        cout.flush();
    }
    while(next_permutation(system.begin(), system.end(), [](const Valve& a, const Valve& b) {
        return a.flowRate < b.flowRate;
    }));

    cout << "result: " << result << endl;

    return 0;
}