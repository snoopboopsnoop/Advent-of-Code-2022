#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// difficulty leap from day 4 to this one is bigger than your mother

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string result;
    string line;

    getline(in, line);
    int stacks = (line.size() + 1) / 4;
    
    vector<vector<char>> crates(stacks, vector<char>());
    
    // PART 1: parse top crate diagram into 2d vector
    while(in) {
        //check for end of diagram
        if(line[1] == '1') break;
        
        // add the character from the crate to its respective column vector
        for(size_t i = 1; i < line.size(); i+=4) {
            char c = line[i];
            int stack = (i-1) / 4;

            if(c == ' ') continue;
            crates[stack].insert(crates[stack].begin(), c);
        }
        getline(in, line);
    }

    // throw away blank line
    getline(in, line);

    // PART 2: move the shit 
    string trash;
    int quantity = 0;
    int start = 0;
    int dest = 0;

    while(getline(in, line)) {
        // check for eof
        if(line == "") break;

        // read directions into variables
        istringstream sin(line);
        sin >> trash >> quantity >> trash >> start >> trash >> dest;

        // index 1 crates -> index 0 vectors
        start--;
        dest--;

        for(int i = 0; i < quantity; ++i) {
            crates[dest].push_back(crates[start].back());
            crates[start].pop_back();
        }
    }

    for(auto i : crates) {
        result += i.back();
    }

    cout << "result: " << result << endl;

    return 0;
}