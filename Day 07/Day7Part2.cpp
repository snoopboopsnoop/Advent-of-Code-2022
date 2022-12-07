#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

// difficulty leap from day 6 up to this one is bigger than your mother

const int totalSpace = 70000000;
const int spaceReq = 30000000;

enum fileType {
        dir, file
    };

struct Node {
    fileType type;
    string name;
    int value;
    vector<Node*>* next;
    Node* previous;
};

vector<Node*>& addNodes(ifstream& in, Node* curr) {
    vector<Node*>* subtree = new vector<Node*>;
    string line;
    while(getline(in, line)) {
        if(line == "") break;
        string first, second;
        istringstream sin(line);

        sin >> first >> second;
        if(isdigit(first[0])) {
            cout << "found file " << second << endl;
            subtree->push_back(new Node{fileType::file, second, stoi(first), nullptr, curr});
        }
        else {
            cout << "found dir " << second << endl;
            subtree->push_back(new Node{fileType::dir, second, -1, new vector<Node*>, curr});
        }
        if(in.peek() == '$' || '\0') {
            break;
        }
    }
    return *subtree;
}

ostream& operator<<(ostream& out, Node* root) {
    Node* curr = root;
    if(curr->next == nullptr) return out;

    out << "Node " << curr->name << " points to ";
    for(const auto& i : *(curr->next)) {
        out << i->name << ", ";
    }
    out << endl;
    for(const auto& i : *(curr->next)) {
        out << i;
    }
    return out;
}

int size_of(Node* root) {
    int result = 0;
    Node* curr = root;
    if(curr->next == nullptr) return curr->value;

    for(const auto& i : *(curr->next)) {
        result += size_of(i);
    }
    return result;
}

int size_of_helper(Node* root) {
    int result = size_of(root);
    //cout << "checking size of " << root->name << ": ";
    //cout << result << endl;
    return result;
}

int solve(Node* root, int spaceNeeded, int prev) {
    //cout << "checking node " << root->name << " to get at least " << spaceNeeded << ", best option is " << prev << endl;
    int result = prev;
    int temp = 0;

    if(root->next == nullptr) return 0; 

    temp = size_of_helper(root);
    if(temp >= spaceNeeded && temp < prev) {
        result = temp;
        //cout << "can delete node " << root->name << " to save " << result << " storage" << endl;
    }
    for(auto& i : *(root->next)) {
        temp = solve(i, spaceNeeded, result);
        if(temp >= spaceNeeded && temp < prev) {
            result = temp;
            //cout << "can delete node " << root->name << " to save " << result << " storage" << endl;
        }
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

    Node* root = new Node{fileType::dir, "/", -1, new vector<Node*>, nullptr};
    Node* curr = root;

    getline(in, line);

    while(getline(in, line)) {
        if(line == "") break;

        istringstream sin(line);
        string token;
        sin >> token;
        if(token == "$") {
            string command;
            sin >> command;
            if(command == "ls") {
                cout << "looking in dir " << curr->name << endl;
                curr->next = &addNodes(in, curr);
            }
            else if(command == "cd") {
                string dir;
                sin >> dir;
                if(dir == "..") {
                    cout << "going back" << endl;
                    curr = curr->previous;
                }
                else {
                    for(const auto& i : *(curr->next)) {
                        if(i->name == dir) {
                            curr = i;
                            cout << "entering " << curr->name << endl;
                        }
                    }
                }
            }
        }
    }

    //cout << size_of_helper(root) << endl;
    int usedSpace = size_of_helper(root);
    int spaceNeeded = spaceReq - (totalSpace - usedSpace);


    cout << "need to delete " << spaceNeeded << " amount of storage" << endl;

    result = solve(root, spaceNeeded, usedSpace+1);

    cout << "result: " << result << endl;

    return 0;
}

