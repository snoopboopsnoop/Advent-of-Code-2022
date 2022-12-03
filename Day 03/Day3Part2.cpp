#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

// not a real c++ programmer if you don't use <algorithm>

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;
    
    int result = 0;

    while(in) {
        ostringstream str;
        string line;

        //get each of the three elves
        for(int i = 0; i < 3; i++) {
            getline(in, line);

            // remove sorted adjacent duplicates
            sort(line.begin(), line.end());
            auto it = line.begin();
            while(it != line.end()) {
                while(*(it+1) == *it && it != line.end()) line.erase(it);
                ++it;
            }

            // add to final sstream
            str << line;
        }

        // all 3 elves in one str
        line = str.str();
        sort(line.begin(), line.end());

        // find 3 adjacent duplicates
        char c = '\0';
        auto it = adjacent_find(line.begin(), line.end());
        while(it != line.end()) {
            if(*(it+2) == *it) {
                c = *it;
                break;
            }
            else it = adjacent_find(it+2, line.end());
        }

        // add priority value to result
        if(isupper(c)) result += 26;
        result += tolower(c) - 'a' + 1;

        // throw away \n if eof
        if(in.peek() == -1) {
            in.get();
        }
    }

    cout << "Sum of item priorities: " << result << endl;

    return 0;
}
