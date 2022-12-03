#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

// not a real c++ programmer if you don't use <algorithm>

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int result = 0;

    while(getline(in, line)) {
        bool found = false;

        // separate 2 compartments
        string s1 = line.substr(0, line.size()/2);
        string s2 = line.substr(line.size()/2);
        
        // search for char in s1 also inside s2
        for(size_t i = 0; i < s1.size(); ++i) {
            if(found == true) break;
            for(size_t j = 0; j < s2.size(); ++j) {
                if(s1[i] == s2[j]) {
                    char c = s1[i];
                    // calculate priority and add to result
                    if(isupper(c)) result += 26;
                    result += tolower(c) - 'a' + 1;
                    found = true;
                    break;
                }
            }
        }
    }
    
    cout << "Sum of item priorities: " << result << endl;

    return 0;
}
