#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <math.h>

using namespace std;

// difficulty leap from day 5 down to this one is bigger than your mother

// start at S
// look at neighboring positions, if can go there make them a Node
// put the nodes on a queue sort by heuristic
// check the neighbors of the node at top of queue and repeat

struct Node {
    double heuristic;
    double combinedHeuristic;
    double steps;
    pair<int, int> location;
    Node* next;
    Node* prev;
    static Node* goal;

    double magnitude() {
        if(goal == nullptr) return -1;
        return sqrt(pow(goal->location.first - location.first, 2) +
                    pow(goal->location.second - location.second, 2));
    }

    Node(int x, int y) {
        location = make_pair(x, y);
        heuristic = magnitude();
    }
    Node(pair<int, int> coords) {
        prev = nullptr;
        next = nullptr;
        location = coords;
        heuristic = -1;
        steps = 0;
    }
    Node(const pair<int, int>& coords, Node* last) {
        prev = last;
        next = nullptr;
        location = coords;
        heuristic = magnitude();
        steps = last->steps+1;
        combinedHeuristic = steps + heuristic;
    }
    void setNext(Node* node) {
        next = node;
    }
    void print() const {
        cout << "Node at " << location.first << ", " << location.second
            << " with combined heuristic " << combinedHeuristic << ", magnitude " << heuristic << ". "
            << steps << " step(s) away from start" << endl;
    }
    void printRoute() const {
        if(prev == nullptr) {
            cout << "(" << location.first << ", " << location.second << ")";
            return;
        }
        prev->printRoute();
        cout << " -> (" << location.first << ", " << location.second << ")";
    }
};

Node* Node::goal = nullptr;

void refresh(vector<Node*>& stack) {
    sort(stack.begin(), stack.end(), [](const Node* a, const Node* b) {
        return a->combinedHeuristic < b->combinedHeuristic;
    });
}

void expand(Node* curr, const pair<int, int>& check, vector<Node*>& stack, vector<Node*>& visited, const vector<string>& map) {
    // cout << "Expanding on Node at " << curr->location.first << ", " << curr->location.second << endl;
    // cout << "Looking at neighboring Node at " << check.first << ", " << check.second << endl;
    // add adjacent to curr into read vector
    // up
    auto inVisited = find_if(visited.begin(), visited.end(), [check](Node* i) {
        return (i->location.first == check.first &&
               i->location.second == check.second);
    });
    if(inVisited != visited.end()) {
        // cout << "already expanded on" << endl;
        return;
    }
    auto found = find_if(stack.begin(), stack.end(), [check](Node* i) {
        return (i->location.first == check.first &&
               i->location.second == check.second);
    });
    if(found == stack.end()) {
        // cout << "not seen yet, adding node to stack" << endl;
        stack.push_back(new Node(check, curr));
        refresh(stack);
        // for(Node* i : stack) {
        //     i->print();
        // }
    }
    else {
        // cout << "already on stack" << endl;
        // check if distance is smaller
        if((*found)->steps > curr->steps+1) {
            // cout << "more efficient route to this Node found" << endl;
            (*found)->prev = curr;
            (*found)->steps = curr->steps+1;
        }
    }
}

int search(vector<Node*>& stack, vector<Node*>& visited, const vector<string>& map) {
    Node* curr = stack[0];
    while(curr->location.first != Node::goal->location.first
        || curr->location.second != Node::goal->location.second) {
        stack.erase(stack.begin());
        
        if(curr->location.second-1 >= 0 && 
            (map[curr->location.second-1][curr->location.first] - map[curr->location.second][curr->location.first])
            <= 1) {
                expand(curr, make_pair(curr->location.first, curr->location.second-1), stack, visited, map);
        }
        // down
        if(curr->location.second+1 < map.size() && 
            (map[curr->location.second+1][curr->location.first] - map[curr->location.second][curr->location.first])
            <= 1) {
                expand(curr, make_pair(curr->location.first, curr->location.second+1), stack, visited, map);
        }
        // left
        if(curr->location.first-1 >= 0 && 
            (map[curr->location.second][curr->location.first-1] - map[curr->location.second][curr->location.first])
            <= 1) {
                expand(curr, make_pair(curr->location.first-1, curr->location.second), stack, visited, map);
        }
        // right
        if(curr->location.first+1 < map[0].size() && 
            (map[curr->location.second][curr->location.first+1] - map[curr->location.second][curr->location.first])
            <= 1) {
                expand(curr, make_pair(curr->location.first+1, curr->location.second), stack, visited, map);
        }
        visited.push_back(curr);
        curr = stack[0];
    }
    // cout << "found end:" << endl;
    // curr->print();
    // cout << "goal:" << endl;
    // Node::goal->print();

    // curr->printRoute();
    // cout << endl;
    return curr->steps;
}

int algorithm(Node* start, const vector<string>& map) {
    int result = 0;
    vector<Node*> stack;
    vector<Node*> visited;

    stack.push_back(start);
    
    result = search(stack, visited, map);

    for(Node* i: stack) {
        // cout << "stack deleting ";
        // i->print();
        delete i;
    }
    for(Node* i : visited) {
        // cout << "visited deleting ";
        // i->print();
        delete i;
    }
    return result;
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    int result = 0;
    string line;
    // increases down and right
    vector<string> map;
    vector<Node*> start;

    while(getline(in, line)) {
        map.push_back(line);
    }

    for(size_t i = 0; i < map.size(); ++i) {
        for(size_t j = 0; j < map[0].size(); ++j) {
            if(map[i][j] == 'E') {
                Node::goal = new Node(make_pair(j, i));
                map[i][j] = 'z';
            }
        }
    }

    for(size_t i = 0; i < map.size(); ++i) {
        for(size_t j = 0; j < map[0].size(); ++j) {
            if(map[i][j] == 'S' || map[i][j] == 'a') {
                start.push_back(new Node(make_pair(j, i)));
                map[i][j] = 'a';
            }
        }
    }

    result = algorithm(start[0], map);

    cout << "result: " << result << endl;

    for(Node* i : start) {
        delete i;
    }

    delete Node::goal;
    return 0;
}