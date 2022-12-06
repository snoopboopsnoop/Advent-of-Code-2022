#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// difficulty leap from day 5 down to this one is bigger than your mother

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;


    int result = 0;
    int kConsec = 4;
    string line;

    getline(in, line);

    // grab groups of size kConsec, check if unique
    for(size_t i = 0; i < line.size(); i++) {
        string subs = line.substr(i, kConsec);
        
        sort(subs.begin(), subs.end());

        bool isUnique = (unique(subs.begin(), subs.end()) == subs.end());
        if(isUnique) {
            result = i + kConsec;
            break;
        } 
    }

    cout << "Start-of-packet marker ends at position: " << result << endl;

    return 0;
}