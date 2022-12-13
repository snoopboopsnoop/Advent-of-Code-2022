#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <math.h>

using namespace std;

// difficulty leap from day 5 down to this one is bigger than your mother

// start at S
// look at neighboring positions, if can go there make them a Node
// put the nodes on a queue sort by heuristic
// check the neighbors of the node at top of queue and repeat

double magnitude(const pair<int, int>& location, const pair<int, int>& goal) {
    return sqrt(pow(goal.first-location.first, 2) + pow(goal.second-location.second, 2));
}

struct Node {
    double heuristic;
    pair<int, int> location;
    pair<int, int> next;
    pair<int, int> last;
    static pair<int, int> goal;

    Node(int x, int y) {
        location = make_pair(x, y);
        heuristic = magnitude(location, goal);
    }
    Node(pair<int, int> coords) {
        location = coords;
        heuristic = magnitude(location, goal);
    }
    const pair<int, int>& getPos() {
        return location;
    }
};

pair<int, int> Node::goal;

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    int result = 0;
    string line;
    // increases down and right
    vector<string> map;

    pair<int, int> startCoords;

    while(getline(in, line)) {
        map.push_back(line);
    }

    for(size_t i = 0; i < map.size(); ++i) {
        for(size_t j = 0; j < map[i].size(); ++j) {
            if(map[i][j] == 'S') startCoords = make_pair(j, i);
            else if(map[i][j] == 'E') Node::goal = make_pair(i, j);
        }
    }

    Node start(startCoords);
    vector<Node> stack;

    pair<int, int> curr = start.getPos();
    while(curr.first != Node::goal.first
        && curr.second != Node::goal.second) {
            // add adjacent to curr into read vector
            // up
            if(curr.second-1 >= 0 && 
                (map[curr.second-1][curr.first] - map[curr.second][curr.first])
                <= 1) {
                    stack.push_back(Node(make_pair(curr.second-1, curr.first)));
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
        }

    cout << "result: " << result << endl;

    return 0;
}