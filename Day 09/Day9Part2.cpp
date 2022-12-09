#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

// https://www.google.com/search?q=snake but with a physics engine

const int kNumKnots = 9;

// "why didn't you just put all the knots in a vector" fuck you
struct Knot {
    Knot* next = nullptr;
    pair<int, int> data = make_pair(0, 0);
    Knot* last = nullptr;

    // lmao idk if this even works but who cares i have 32 gb of ram
    ~Knot() {
        if(next == nullptr) {
            this->last->next = nullptr;
            delete this;
        }
        delete next;
    }
};

// returns magnitude between coordinates of head and tail
// if tail is next to head, returns 1
// if tail is 1 away from head in a single direction, returns 2
// if tail is 1 away from head in multiple directions, returns sqrt(5)
double magnitude(const Knot* head, const Knot* tail) {
    return sqrt(pow(head->data.first-tail->data.first, 2)
        + pow(head->data.second-tail->data.second, 2));
}

// moves tail according to the rules given in the instructions based on magnitude
// (see magnitude function for return values)
void moveTail(const Knot* head, Knot* tail) {
    double mag = magnitude(head, tail);
    // "dont compare floating points to integers" suck my dick
    if(mag == 2) {
        if(head->data.first > tail->data.first) tail->data.first++;
        else if(head->data.first < tail->data.first) tail->data.first--;
        else if(head->data.second > tail->data.second) tail->data.second++;
        else if(head->data.second < tail->data.second) tail->data.second--;
    }
    else if(mag > 2) {
        int horizontalDir = (head->data.first > tail->data.first) ? 1 : -1;
        int verticalDir = (head->data.second > tail->data.second) ? 1 : -1;
        
        tail->data.first += horizontalDir;
        tail->data.second += verticalDir;
    }
}

// moves head 1 unit in given direction
void move(Knot* head, char direction) {
    switch(direction) {
        case 'R': 
            head->data.first++;
            break;
        case 'L':
            head->data.first--;
            break;
        case 'U':
            head->data.second++;
            break;
        case 'D':
            head->data.second--;
            break;
    }
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;
    
    // initialize rope, head and tail pointers
    Knot* head = new Knot;
    Knot* curr = head;
    Knot* temp;
    for(int i = 0; i < kNumKnots; ++i) {
        curr->next = new Knot;
        temp = curr;
        curr = curr->next;
        curr->last = temp;
    }
    Knot* tail = curr;
    vector<pair<int, int>> visited;

    char direction;
    int amt;

    while(in) {
        in >> direction >> amt;
        for(int i = 0; i < amt; i++) {
            curr = head;
            move(head, direction);
            // move the next knot according to its previous
            while(curr != tail) {
                // DEBUG
                // cout << "next knot moved from " << curr->next->data.first << ", " << curr->next->data.second << " to ";
                moveTail(curr, curr->next);
                // cout << curr->next->data.first << ", " << curr->next->data.second << endl;
                curr = curr->next;
            }
            if(find(visited.begin(), visited.end(), tail->data) == visited.end()) {
                visited.push_back(tail->data);
                // DEBUG:
                // cout << "tail visited new position at " << tail->data.first << ", " << tail->data.second << endl;
            }
        }
        //throw away \n
        in.get();
    }
    cout << "End of rope visited " << visited.size() << " unique positions" << endl;

    // pray this actually does something
    delete head;
    return 0;
}