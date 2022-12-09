#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

// difficulty leap from day 5 down to this one is bigger than your mother

double magnitude(const pair<int, int>& head, const pair<int, int>& tail) {
    return sqrt(pow(head.first-tail.first, 2) + pow(head.second-tail.second, 2));
}

void moveTail(const pair<int, int>& head, pair<int, int>& tail) {
    double mag = magnitude(head, tail);
    //cout << "head and tail have magnitude " << mag << endl;
    // 1 apart
    if(mag == 2) {
        if(head.first > tail.first) tail.first++;
        else if(head.first < tail.first) tail.first--;
        else if(head.second > tail.second) tail.second++;
        else if(head.second < tail.second) tail.second--;
    }
    // not in same row or column
    else if(mag > 2) {
        int horizontalDir = (head.first > tail.first) ? 1 : -1;
        int verticalDir = (head.second > tail.second) ? 1 : -1;
        
        tail.first += horizontalDir;
        tail.second += verticalDir;
    }
    // else they're touching and no need to move
}

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
    //cout << endl <<  "moved head one to the " << direction << endl;
    //cout << "head is at " << head.first << ", " << head.second << endl;
    //cout << "tail is at " << tail.first << ", " << tail.second << endl << endl;
    moveTail(head, tail);
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;


    int result = 0;
    
    pair<int, int> head(0, 0);
    pair<int, int> tail(0, 0);
    vector<pair<int, int>> visited;

    char direction;
    int amt;
    while(in) {
        in >> direction >> amt;
        //cout << "moving head " << amt << " to the " << direction << endl;
        for(int i = 0; i < amt; i++) {
            move(head, tail, direction);
            if(find(visited.begin(), visited.end(), tail) == visited.end()) {
                visited.push_back(tail);
                cout << "tail visited new position at " << tail.first << ", " << tail.second << endl;
            }
            //cout << "head moved to " << head.first << ", " << head.second << endl;
            //cout << "tail moved to " << tail.first << ", " << tail.second << endl << endl;
        }
        //cout << endl;
        
        //throw away \n
        in.get();
    }



    cout << "result: " << visited.size() << endl;

    return 0;
}