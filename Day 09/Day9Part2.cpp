#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

const int kNumKnots = 9;

struct Knot {
    Knot* next = nullptr;
    pair<int, int> data = make_pair(0, 0);
    Knot* last = nullptr;

    ~Knot() {
        if(next == nullptr) {
            this->last->next = nullptr;
            delete this;
        }
        delete next;
    }
};



// difficulty leap from day 5 down to this one is bigger than your mother

double magnitude(const Knot* head, const Knot* tail) {
    return sqrt(pow(head->data.first-tail->data.first, 2)
        + pow(head->data.second-tail->data.second, 2));
}

void moveTail(const Knot* head, Knot* tail) {
    double mag = magnitude(head, tail);
    //cout << "head and tail have magnitude " << mag << endl;
    // 1 apart
    if(mag == 2) {
        if(head->data.first > tail->data.first) tail->data.first++;
        else if(head->data.first < tail->data.first) tail->data.first--;
        else if(head->data.second > tail->data.second) tail->data.second++;
        else if(head->data.second < tail->data.second) tail->data.second--;
    }
    // not in same row or column
    else if(mag > 2) {
        int horizontalDir = (head->data.first > tail->data.first) ? 1 : -1;
        int verticalDir = (head->data.second > tail->data.second) ? 1 : -1;
        
        tail->data.first += horizontalDir;
        tail->data.second += verticalDir;
    }
    // else they're touching and no need to move
}

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
    //cout << endl <<  "moved head one to the " << direction << endl;
    //cout << "head is at " << head->data.first << ", " << head->data.second << endl;
    //cout << "tail is at " << tail.first << ", " << tail.second << endl << endl;
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    int result = 0;
    
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
    //for(int i = 0; i < 3; ++i) {
    while(in) {
        in >> direction >> amt;
        //cout << "moving head " << amt << " to the " << direction << endl;
        for(int i = 0; i < amt; i++) {
            curr = head;
            move(head, direction);
            while(curr != tail) {
                //cout << "next knot moved from " << curr->next->data.first << ", " << curr->next->data.second << " to ";
                moveTail(curr, curr->next);
                //cout << curr->next->data.first << ", " << curr->next->data.second << endl;
                curr = curr->next;
            }
            if(find(visited.begin(), visited.end(), tail->data) == visited.end()) {
                visited.push_back(tail->data);
                //cout << "tail visited new position at " << tail->data.first << ", " << tail->data.second << endl;
            }
            //cout << "head moved to " << head->data.first << ", " << head->data.second << endl;
            //cout << "tail moved to " << tail->data.first << ", " << tail->data.second << endl << endl;
        }
        //cout << endl;
        
        //throw away \n
        in.get();
    }



    cout << "result: " << visited.size() << endl;

    delete head;
    return 0;
}