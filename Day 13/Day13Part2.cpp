#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

// difficulty leap from day 5 down to this one is bigger than your mother

struct is_space : ctype<char> {
    is_space() : ctype<char> (get_table()) {}
    static mask const* get_table() {
        static mask rc[table_size];
        rc[','] = ctype_base::space;
        rc['\n'] = ctype_base::space;
        return &rc[0];
    }
};

vector<string> to_stack(const string& s) {
    // ignore beg and end brackets

    auto beg = s.begin()+1;
    auto end = s.end()-1;

    vector<string> result;

    while(beg != end) {
        //cout << "looking at char " << *beg << endl;
        if(*beg == ',') {
            ++beg;
            continue;
        }
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

int compare(const vector<string>& s1, const vector<string>& s2) {
    cout << "- Compare ";
    print(cout, s1);
    cout << " vs ";
    print(cout, s2) << endl;

    // if 1 is empty and the other isn't
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
        
        if(s1[i][0] == '[') {
            vector<string> temp1 = to_stack(s1[i]);
            vector<string> temp2;
            if(s2[i][0] == '[') {
                temp2 = to_stack(s2[i]);
            }
            else {
                ostringstream out;
                out << '[' << s2[i] << ']';
                temp2 = to_stack(out.str());
            }
            int result = compare(temp1, temp2);
            if(result == 1) return 1;
            else if(result == 0) return 0;
        }
        else if(s2[i][0] == '[') {
            vector<string> temp2 = to_stack(s2[i]);
            ostringstream out;
            out << '[' << s1[i] << ']';
            vector<string> temp1 = to_stack(out.str());
            int result = compare(temp1, temp2);
            if(result == 1) return 1;
            else if(result == 0) return 0;
        }
        else {
            cout << "- Compare " << s1[i] << " vs " << s2[i] << endl;
            if(stoi(s1[i]) < stoi(s2[i])) {
                return 1;
            }
            else if(stoi(s1[i]) > stoi(s2[i])) {
                return 0;
            }
            else {
                //cout << "same, continuing" << endl;
                if(i == s1.size()-1 && i == s2.size()-1) return -1;
            }
        }
        if(i == s2.size()-1 && i != s1.size()-1) {
            return 0;
        }
    }
    if(s1.size() < s2.size()) return 1;
    else if(s1.size() > s2.size()) return 0;
    else if(s1.size() == s2.size()) {
        return -1;
    }
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    int result = 1;
    string line;
    vector<vector<string>> packets;
    const vector<string> kdividerPackets = {"[[2]]", "[[6]]"};
    vector<vector<string>> dividerStacks;

    for(const string& i : kdividerPackets) {
        vector<string> stack = to_stack(i);
        packets.push_back(stack);
        dividerStacks.push_back(stack);
    }

    //while(in) {
    // while() {
    while(getline(in, line)) {
        if(line == "") continue;
        vector<string> stack = to_stack(line);
        packets.push_back(stack);
    }

    for(const vector<string>& i : packets) {
        print(cout, i);
        cout << endl;
    }
    cout << endl;

    sort(packets.begin(), packets.end(), [] (const vector<string>& a, const vector<string>& b) {
        return (compare(a, b) == 0) ? 0 : 1;
    });

    for(const vector<string>& i : packets) {
        print(cout, i);
        cout << endl;
    }
    cout << endl;

    for(const vector<string>& i : dividerStacks) {
        auto found = find(packets.begin(), packets.end(), i);
        int temp = found - packets.begin() + 1;
        cout << "divider found at index " << temp << endl;
        result *= temp;
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