#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>

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

        // separate 2 compartments
        string s1 = line.substr(0, line.size()/2);
        string s2 = line.substr(line.size()/2);
        
        // search for char in s1 also inside s2
        for(size_t i = 0; i < s1.size(); ++i) {
            auto itr = find(s2.begin(), s2.end(), s1[i]);
                if(itr == s2.end()) continue;
                char c = *itr;
                
                // calculate priority and add to result
                if(isupper(c)) result += 26;
                result += tolower(c) - 'a' + 1;
                break;
        }
    }
    
    cout << "Sum of item priorities: " << result << endl;

    return 0;
}
