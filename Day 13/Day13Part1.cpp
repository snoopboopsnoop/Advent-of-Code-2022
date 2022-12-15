#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <locale>

using namespace std;

// difficulty leap from day 5 down to this one is bigger than your mother

void strip(string& s) {
    if(s[0] == '[' && s[s.size()-1] == ']') {
        s.erase(s.begin());
        s.erase(s.end()-1);
    }
}

bool compare(string& s1, string& s2) {
    // if(s1 == "") {

    // }

    strip(s1);
    strip(s2);

    // if list
    if(s1[0] == '[') {
        if(s2[0] == '[') {
            cout << "2 lists" << endl;
            string sub1, sub2;
            int end1 = s1.find("],");
            int end2 = s2.find("],");
            if(end1 == string::npos) {
                cout << "only 1 item" << endl;
                sub1 = strip(s1);
            }
            else {
                cout << "only 1 item" << endl;
                sub1 = s1.substr(0, s1.find("],")+1);
            }
            if(end2 == string::npos) {
                sub2 = strip(s1);
            }
            else {
                sub2 = s2.substr(0, s2.find("],")+1);
            }
            
            cout << "sub1: " << sub1 << ", sub2: " << sub2 << endl;
            
        }
        else {
           cout << "s1 is a list, s2 is a list" << endl;
        }
    }
    else if(s2[0] == '[') {
        cout << "s2 is a list, s1 is not" << endl;
    }
    else {
        cout << "both integers" << endl;
    }

    return false;
}

bool compare_wrapper(istream& in) {
    string s1, s2, trash;
    getline(in, s1);
    getline(in, s2);

    compare(s1, s2);

    getline(in, trash);

    return false;
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    int result = 0;
    string line;
    
    while(in) {
        compare_wrapper(in);
    }

    // while(getline(in, line)) {
    //     istringstream sin(line);
    //     sin.imbue(locale(sin.getloc(), new is_space));
    //     string token;

    //     while(sin >> token) {
    //         cout << token << endl;
    //     }
    // }   

    cout << "result: " << result << endl;

    return 0;
}