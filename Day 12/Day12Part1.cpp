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
    Node(pair<int, int> coords, Node* last) {
        prev = last;
        next = nullptr;
        location = coords;
        heuristic = magnitude();
        steps = last->steps+1;
    }
    void setNext(Node* node) {
        next = node;
    }
    void print() const {
        cout << "Node at " << location.first << ", " << location.second
            << " with heuristic " << heuristic << ". "
            << steps << " step(s) away from start" << endl;
    }
};

Node* Node::goal = nullptr;

void refresh(vector<Node*>& stack) {
    sort(stack.begin(), stack.end(), [](const Node* a, const Node* b) {
        return a->heuristic < b->heuristic;
    });
}

void expand(Node* curr, vector<Node*>& stack, const vector<string>& map) {
    // add adjacent to curr into read vector
    // up
    if(curr.second-1 >= 0 && 
        (map[curr.second-1][curr.first] - map[curr.second][curr.first])
        <= 1) {
            auto found = find_if(stack.begin(), stack.end(), [](Node* i) {
                return i->location == make_pair(curr.first, curr.second-1);
            })
            if(found != stack.end()) {
                // check if distance is smaller
            }
    }
    // down
    if(curr.second+1 < map.size() && 
        (map[curr.second+1][curr.first] - map[curr.second][curr.first])
        <= 1) {
            stack.push_back(Node(make_pair(curr.second+1, curr.first)));
    }
    // left
    if(curr.first-1 >= 0 && 
        (map[curr.second][curr.first-1] - map[curr.second][curr.first])
        <= 1) {
            stack.push_back(Node(make_pair(curr.second, curr.first-1)));
    }
    // right
    if(curr.first+1 < map.size() && 
        (map[curr.second][curr.first+1] - map[curr.second][curr.first])
        <= 1) {
            stack.push_back(Node(make_pair(curr.second, curr.first+1)));
    }
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

    for(size_t i = 0; i < map.size(); ++i) {
        for(size_t j = 0; j < map[0].size(); ++j) {
            if(map[i][j] == 'S') start = new Node(make_pair(j, i));
            else if(map[i][j] == 'E') Node::goal = new Node(make_pair(j, i));
        }
    }

    vector<Node*> stack;
    Node* curr = start;

    if(curr->location.second-1 >= 0) {
            stack.push_back(
                new Node(make_pair(curr->location.second-1, curr->location.first), curr
            ));
    }
    // down
    if(curr->location.second+1 < map.size()) {
            stack.push_back(
                new Node(make_pair(curr->location.second+1, curr->location.first), curr
            ));
    }
    // left
    if(curr->location.first-1 >= 0) {
            stack.push_back(
                new Node(make_pair(curr->location.second, curr->location.first-1), curr
            ));
    }
    // right
    if(curr->location.first+1 < map.size()) {
            stack.push_back(
                new Node(make_pair(curr->location.second, curr->location.first+1), curr
            ));
    }
    refresh(stack);

    curr = stack[0];
    expand(curr, stack, map);

    // while(curr.first != Node::goal.first
    //     && curr.second != Node::goal.second) {
    //         expand(curr, stack, map);
    //         

    //         refresh(stack);


    //     }

    cout << "Stack size: " << stack.size() << endl;

    for(Node* i : stack) {
        i->print();
    }

    cout << "result: " << result << endl;

    delete start;
    delete Node::goal;
    for(Node* i: stack) {
        delete i;
    }
    return 0;
}