#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

// recursion but cringe

// turns string into vector of things to compare
// @param s - string to convert
// @return stack of things to compare
vector<string> to_stack(const string& s) {
    // ignore beg and end brackets
    auto beg = s.begin()+1;
    auto end = s.end()-1;
    vector<string> result;

    while(beg != end) {
        if(*beg == ',') {
            ++beg;
            continue;
        }
        // parse list
        if(*beg == '[') {
            auto temp = beg+1;
            int order = 0;
            while(*temp != ']' || order != 0) {
                if(*temp == '[') order++;
                else if(*temp == ']') order--;
                ++temp;
            }
            result.push_back(string(beg, temp+1));
            beg = temp+1;
            continue;
        }
        // add number to stack
        else {
            auto temp = find(beg, s.end(), ',');
            if(temp == s.end()) {
                result.push_back(string(beg, s.end()-1));
            }
            else result.push_back(string(beg,temp));
        }
        ++beg;
    }
    return result;
}

// prints vector
// @param s - vector to print
// @return ostream idk why but i think you're supposed to so it can just cout
ostream& print(ostream& out, const vector<string>& s) {
    if(s.size() == 0) { 
        out << "[]";
        return out;
    }
    out << "[" << s[0];
    for(size_t i = 1; i < s.size(); i++) {
        out << "," << s[i];
    }
    out << "]";
    return out;
}

// compares each item in 2 stacks recursively
// @param s1 - stack 1
// @param s2 - stack 2
// @return 1 if correct, 0 if wrong, -1 if same
int compare(const vector<string>& s1, const vector<string>& s2) {
    // DEBUG:
    // cout << "- Compare ";
    // print(cout, s1);
    // cout << " vs ";
    // print(cout, s2) << endl;

    // if any are empty
    if(s1.size() == 0 && s2.size() != 0) {
        return 1;
    }
    else if(s2.size() == 0 && s1.size() != 0) {
        return 0;
    }
    else if(s1.size() == 0 && s2.size() == 0) {
        return -1;
    }

    for(size_t i = 0; i < s1.size(); ++i) { 
        // list - recursion time
        if(s1[i][0] == '[') {
            vector<string> temp1 = to_stack(s1[i]);
            vector<string> temp2;
            // 2 lists
            if(s2[i][0] == '[') {
                temp2 = to_stack(s2[i]);
            }
            // s2 not a list - turn it into a list
            else {
                ostringstream out;
                out << '[' << s2[i] << ']';
                temp2 = to_stack(out.str());
            }
            // recurse
            int result = compare(temp1, temp2);
            if(result == 1) return 1;
            else if(result == 0) return 0;
        }
        // list 1 is not a list, list 2 is 
        else if(s2[i][0] == '[') {
            vector<string> temp2 = to_stack(s2[i]);
            ostringstream out;
            out << '[' << s1[i] << ']';
            vector<string> temp1 = to_stack(out.str());
            int result = compare(temp1, temp2);
            if(result == 1) return 1;
            else if(result == 0) return 0;
        }
        // 2 numbers, check if in right order or not
        else {
            // DEBUG:
            // cout << "- Compare " << s1[i] << " vs " << s2[i] << endl;
            if(stoi(s1[i]) < stoi(s2[i])) {
                return 1;
            }
            else if(stoi(s1[i]) > stoi(s2[i])) {
                return 0;
            }
            else {
                if(i == s1.size()-1 && i == s2.size()-1) return -1;
            }
        }
        // if s2 is empty but s1 isn't
        if(i == s2.size()-1 && i != s1.size()-1) {
            return 0;
        }
    }
    // everything has been compared but neither are empty, compare sizes
    if(s1.size() < s2.size()) return 1;
    else if(s1.size() > s2.size()) return 0;
    else if(s1.size() == s2.size()) return -1;
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    int result = 0;
    string line;
    vector<string> s1;
    vector<string> s2;

    int index = 1;
    while(getline(in, line)) {
        s1 = to_stack(line);
        getline(in, line);
        s2 = to_stack(line);

        int temp = compare(s1, s2);
        if(temp == 1 || temp == -1) {
            // In right order, add index
            result += index;
        }
        getline(in, line);
        index++;
    }
    cout << "Sum of the indices of correct-order pairs: " << result << endl;

    return 0;
}