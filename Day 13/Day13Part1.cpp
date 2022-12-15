#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <locale>

using namespace std;

// difficulty leap from day 5 down to this one is bigger than your mother

string strip(const string& s) {
    string result = s;
    if(s[0] == '[' && s[s.size()-1] == ']') {
        result.erase(result.begin());
        result.erase(result.end()-1);
    }
    return result;
}

bool compare(const string& s1, const string& s2) {
    cout << "- Compare " << s1 << " vs " << s2 << endl;
    if(s1 == "") {
        cout << "s1 is empty, correct order" << endl;
        return true;
    }
    else if(s2 == "") {
        cout << "s2 is empty, wrong order" << endl;
        return false;
    }

    // if list
    if(s1[0] == '[') {
        if(s2[0] == '[') {
            cout << "2 lists" << endl;
            string sub1, sub2;
            int end1 = s1.find("],");
            int end2 = s2.find("],");
            if(end1 == string::npos) {
                cout << "only 1 item in s1" << endl;
                sub1 = strip(s1);
            }
            else {
                sub1 = s1.substr(0, s1.find("],")+1);
            }
            if(end2 == string::npos) {
                cout << "only 1 item in s2" << endl;
                sub2 = strip(s1);
            }
            else {
                sub2 = s2.substr(0, s2.find("],")+1);
            }
            while(sub1 != "") {
                compare(sub1, sub2);
                sub1 = 
            }
            
            //cout << "sub1: " << sub1 << ", sub2: " << sub2 << endl;
            return compare(sub1, sub2);
            
        }
        else {
           cout << "s1 is a list, s2 is a list" << endl;
        }
    }
    else if(s2[0] == '[') {
        cout << "s2 is a list, s1 is not" << endl;
    }
    else {
        cout << "Compare " << s1[0] << " vs " << s2[0] << endl;
        if(s1[0] > s2[0]) {
            cout << "right side is smaller, so inputs are not in the right order" << endl;
            return false;
        }
        else if(s1[0] < s2[0]) {
            cout << "left side smaller, so inputs are in the right order" << endl;
            return true;
        }
        else {
            cout << "both sides are equal, continuing" << endl;
            string sub1, sub2;
            sub1 = s1.substr(s1.find(',')+1);
            sub2 = s2.substr(s2.find(',')+1);
            return compare(sub1, sub2);
        }
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
    
    //while(in) {
    for(int i = 0; i < 2; ++i) {
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