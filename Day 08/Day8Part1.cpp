#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// difficulty leap from day 5 down to this one is bigger than your mother

bool isVisible(const size_t row, const size_t column, const vector<string>& map) {
    bool result = false;
    int val = map[row][column];
    //cout << "checking tree at row " << row << ", column " << column << " with value " << val << endl;

    size_t rowEnd = map.size();
    size_t columnEnd = map[0].size();
    // check top
    for(size_t i = 0; i <= row; ++i) {
        //cout << "looking at tree at row " << i << ", column " << column << " with value " << map[i][column] << endl;
        if(i == row) {
            //cout << "reached tree" << endl;
            return true;
        }
        else if(map[i][column] >= val) {
            break;
        } 
    }
    // check bottom
    for(size_t i = rowEnd-1; i >= row; --i) {
        //cout << "looking at tree at row " << i << ", column " << column << " with value " << map[i][column] << endl;
        if(i == row) {
            //cout << "reached tree" << endl;
            return true;
        }
        else if(map[i][column] >= val) break;
    }
    // check left
    for(size_t i = 0; i <= column; ++i) {
        //cout << "looking at tree at row " << row << ", column " << i << " with value " << map[row][i] << endl;
        if(i == column) {
            //cout << "reached tree" << endl;
            return true;
        }
        else if(map[row][i] >= val) break;
    }
    // check right
    for(size_t i = columnEnd-1; i >= column; --i) {
        //cout << "looking at tree at row " << row << ", column " << i << " with value " << map[row][i] << endl;
        if(i == column) {
            //cout << "reached tree" << endl;
            return true;
        }
        else if(map[row][i] >= val) break;
    }

    //cout << "Visible: " << boolalpha << result << endl;
    return result;
}

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;


    int result = 0;
    string line;
    vector<string> map;

    // initialize map
    while(getline(in, line)) {
        if(line == "") break;
        map.push_back(line);
    }

    // perimeter is visible
    result += (2*map[0].size() + 2*(map.size()-2));

    for(size_t row = 1; row < map.size()-1; ++row) {
        for(size_t column = 1; column < map[0].size()-1; ++column) {
            result += isVisible(row, column, map);
        }
    }

    cout << "result " << result << endl;

    return 0;
}