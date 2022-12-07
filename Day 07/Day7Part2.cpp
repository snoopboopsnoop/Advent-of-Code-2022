#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

// difficulty leap from day 6 up to this one is bigger than your mother

const int kTotalSpace = 70000000;
const int kMinSpace = 30000000;

enum fileType {
    dir, file
};

struct Node {
    fileType type;
    string name;
    int value;
    vector<Node*>* next;
    Node* previous;

    // i have no clue if this works, if not I'm definitely leaking memory but ¯\_(ツ)_/¯
    ~Node() {
        for(auto& i : *next) {
            if(i->type == 1) delete i;
            delete[] i;
        }
    }
};

// attaches vector of Nodes to curr through file input
vector<Node*>* addNodes(ifstream& in, Node* curr) {
    vector<Node*>* subtree = new vector<Node*>;
    string line;

    while(getline(in, line)) {
        // file display in form "[size] [name]"
        // dir display in form "dir [name]"
        string first, second;
        istringstream sin(line);
        sin >> first >> second;

        if(isdigit(first[0])) {
            //cout << "found file " << second << endl;
            subtree->push_back(new Node{fileType::file, second, stoi(first), nullptr, curr});
        }
        else {
            //cout << "found dir " << second << endl;
            subtree->push_back(new Node{fileType::dir, second, -1, new vector<Node*>, curr});
        }
        // check for new command
        if(in.peek() == '$') {
            break;
        }
    }
    return subtree;
}

// DEBUG function, prints the tree starting from given root
ostream& operator<<(ostream& out, Node* root) {
    Node* curr = root;
    if(curr->type == 1) return out;

    out << "Node " << curr->name << " points to ";
    for(const auto& i : *(curr->next)) {
        // extra comma at the end of everything but who gives a shit
        out << i->name << ", ";
    }
    out << endl;
    for(const auto& i : *(curr->next)) {
        out << i;
    }

    return out;
}

// returns size of a directory node (the sum of all its files/subfiles)
// recursion !
int size_of(Node* node) {
    int result = 0;
    Node* curr = node;
    if(curr->type == 1) return curr->value;

    for(const auto& i : *(curr->next)) {
        result += size_of(i);
    }

    return result;
}

// returns the smallest of all directory nodes with size of at least spaceNeeded
// moar recursion !
int solve(Node* root, int spaceNeeded, int prev) {
    int result = prev;
    int temp = 0;

    // skip file nodes
    if(root->next == nullptr) return 0; 

    // check root
    temp = size_of(root);
    if(temp >= spaceNeeded && temp < prev) {
        result = temp;
    }
    // check everything under root
    for(auto& i : *(root->next)) {
        temp = solve(i, spaceNeeded, result);
        if(temp >= spaceNeeded && temp < prev) {
            result = temp;
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

    // establish root directory, set to looking at it
    Node* root = new Node{fileType::dir, "/", -1, new vector<Node*>, nullptr};
    Node* curr = root;

    // throw away root line (assuming there is always a root directory)
    getline(in, line);

    while(getline(in, line)) {
        istringstream sin(line);
        // by structure of filesystem, token will always be $
        string token;
        string command;
        sin >> token >> command;
        if(command == "ls") {
            //cout << "looking in dir " << curr->name << endl;
            curr->next = addNodes(in, curr);
        }
        else if(command == "cd") {
            string dir;
            sin >> dir;
            if(dir == "..") {
                //cout << "going back" << endl;
                curr = curr->previous;
            }
            else {
                for(const auto& i : *(curr->next)) {
                    if(i->name == dir) {
                        curr = i;
                        //cout << "entering " << curr->name << endl;
                    }
                }
            }
        }
    }
    //cout << root << endl;

    // calculate the minimum size of directory to delete (spaceNeeded)
    int usedSpace = size_of(root);
    int spaceNeeded = kMinSpace - (kTotalSpace - usedSpace);
    //cout << "need to delete " << spaceNeeded << " amount of storage" << endl;

    result = solve(root, spaceNeeded, usedSpace);
    cout << "Directory to delete increases space by: " << result << endl;

    delete root;
    return 0;
}
