#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
#include <math.h>

using namespace std;

// https://www.youtube.com/watch?v=ySN5Wnu88nE my favorite youtube video

struct Node {
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
    // for start
    Node(pair<int, int> coords) {
        prev = nullptr;
        next = nullptr;
        location = coords;
        combinedHeuristic = -1;
        steps = 0;
    }
    // use this for everything else
    Node(const pair<int, int>& coords, Node* last) {
        prev = last;
        next = nullptr;
        location = coords;
        steps = last->steps+1;
        combinedHeuristic = steps + magnitude();
    }
    void setNext(Node* node) {
        next = node;
    }
    void print() const {
        cout << "Node at " << location.first << ", " << location.second
            << " with combined heuristic " << combinedHeuristic << ". "
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

// sorts stack by combinedHeuristic
// @param stack - stack to be sorted
void refresh(vector<Node*>& stack) {
    sort(stack.begin(), stack.end(), [](const Node* a, const Node* b) {
        return a->combinedHeuristic < b->combinedHeuristic;
    });
}

// expands to coords check
// @param curr - Node that is being expanded on
// @param check - Coords that are being expanded to
// @param stack - unvisited Nodes to expand
// @param visited - Nodes that have been expanded on
// @param map - vector of map
void expand(Node* curr, const pair<int, int>& check, vector<Node*>& stack, const vector<Node*>& visited, const vector<string>& map) {
    // check if there already exists a visited Node at check coords
    auto inVisited = find_if(visited.begin(), visited.end(), [check](Node* i) {
        return (i->location.first == check.first &&
               i->location.second == check.second);
    });
    // if so no use to expand
    if(inVisited != visited.end()) {
        return;
    }
    // check if there already exists an unvisited Node at check coords
    auto found = find_if(stack.begin(), stack.end(), [check](Node* i) {
        return (i->location.first == check.first &&
               i->location.second == check.second);
    });
    // doesn't exist yet, create new node and put it on stack
    if(found == stack.end()) {
        stack.push_back(new Node(check, curr));
        refresh(stack);
    }
    else {
        // check if route is more efficient, if so, change path
        if((*found)->steps > curr->steps+1) {
            (*found)->prev = curr;
            (*found)->steps = curr->steps+1;
        }
    }
}

// a* algorithm
// @param stack - stack of Nodes to be expanded
// @param vistied - stack of Nodes that have been expanded
// @param map - 2d array vector of elevation map
// @return least number of steps to goal
int search(vector<Node*>& stack, vector<Node*>& visited, const vector<string>& map) {
    Node* curr = stack[0];

    // until goal has been reached
    while(curr->location.first != Node::goal->location.first
        || curr->location.second != Node::goal->location.second) {
        stack.erase(stack.begin());

        // up
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
        // no more to expand - no path possible
        if(stack.size() == 0) {
            return -1;
        }
        visited.push_back(curr);
        curr = stack[0];
    }

    // DEBUG:
    // curr->printRoute();
    // cout << endl;
    return curr->steps;
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

    Node* start = nullptr;

    while(getline(in, line)) {
        map.push_back(line);
    }

    // initialize start and goal nodes
    for(size_t i = 0; i < map.size(); ++i) {
        for(size_t j = 0; j < map[0].size(); ++j) {
            if(map[i][j] == 'S') {
                start = new Node(make_pair(j, i));
                map[i][j] = 'a';
            }
            else if(map[i][j] == 'E') {
                Node::goal = new Node(make_pair(j, i));
                map[i][j] = 'z';
            }
        }
    }

    vector<Node*> stack;
    vector<Node*> visited;

    stack.push_back(start);

    result = search(stack, visited, map);
    
    delete Node::goal;
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

    cout << "Best path to goal is " << result << " steps long" << endl;
    return 0;
}