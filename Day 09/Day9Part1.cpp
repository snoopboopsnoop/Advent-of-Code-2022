#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

// https://www.google.com/search?q=snake but with a physics engine

// returns magnitude between coordinates of head and tail
// if tail is next to head, returns 1
// if tail is 1 away from head in a single direction, returns 2
// if tail is 1 away from head in multiple directions, returns sqrt(5)
double magnitude(const pair<int, int>& head, const pair<int, int>& tail) {
    return sqrt(pow(head.first-tail.first, 2) + pow(head.second-tail.second, 2));
}

// moves tail according to the rules given in the instructions based on magnitude
// (see magnitude function for return values)
void moveTail(const pair<int, int>& head, pair<int, int>& tail) {
    double mag = magnitude(head, tail);
    // "dont compare floating points to integers" suck my dick
    if(mag == 2) {
        if(head.first > tail.first) tail.first++;
        else if(head.first < tail.first) tail.first--;
        else if(head.second > tail.second) tail.second++;
        else if(head.second < tail.second) tail.second--;
    }
    else if(mag > 2) {
        int horizontalDir = (head.first > tail.first) ? 1 : -1;
        int verticalDir = (head.second > tail.second) ? 1 : -1;
        
        tail.first += horizontalDir;
        tail.second += verticalDir;
    }
}

// moves head 1 unit in given direction, then move tail accordingly
void move(pair<int, int>& head, pair<int, int>& tail, char direction) {
    switch(direction) {
        case 'R': 
            head.first++;
            break;
        case 'L':
            head.first--;
            break;
        case 'U':
            head.second++;
            break;
        case 'D':
            head.second--;
            break;
    }
    // DEBUG:
    // cout << endl <<  "moved head one to the " << direction << endl;
    // cout << "head is at " << head.first << ", " << head.second << endl;
    // cout << "tail moved from " << tail.first << ", " << tail.second << " to ";
    moveTail(head, tail);
    // cout << tail.first << ", " << tail.second << endl << endl;
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;
    
    pair<int, int> head(0, 0);
    pair<int, int> tail(0, 0);
    vector<pair<int, int>> visited;

    char direction;
    int amt;
    while(in) {
        in >> direction >> amt;
        for(int i = 0; i < amt; i++) {
            move(head, tail, direction);
            // check if tail is in a new location; if so, add location to visited
            if(find(visited.begin(), visited.end(), tail) == visited.end()) {
                visited.push_back(tail);
                // DEBUG:
                // cout << "tail visited new position at " << tail.first << ", " << tail.second << endl;
            }
        }
        // throw away \n
        in.get();
    }
    cout << "Tail has visited " << visited.size() << " unique positions" << endl;

    return 0;
}