#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// difficulty leap from day 5 down to this one is bigger than your mother

int getScenicScore(const size_t row, const size_t column, const vector<string>& map) {
    int result = 1;
    
    int val = map[row][column];
    cout << "checking tree at row " << row << ", column " << column << " with value " << val << endl;

    size_t rowEnd = map.size();
    size_t columnEnd = map[0].size();
    // check top
    int temp = 0;
    for(size_t i = 0; i < row; ++i) {
        //cout << "looking at tree at row " << i << ", column " << column << " with value " << map[i][column] << endl;
        if(map[i][column] >= val) {
            temp++;
            break;
        }
        temp++;
    }
    result *= temp;
    // check bottom
    temp = 0;
    for(size_t i = rowEnd-1; i > row; --i) {
        //cout << "looking at tree at row " << i << ", column " << column << " with value " << map[i][column] << endl;
        if(map[i][column] >= val) {
            temp++;
            break;
        }
        temp++;
    }
    result *= temp;
    // check left
    temp = 0;
    for(size_t i = 0; i <= column; ++i) {
        //cout << "looking at tree at row " << row << ", column " << i << " with value " << map[row][i] << endl;
        if(map[row][i] >= val) {
            temp++;
            break;
        }
        temp++;
    }
    result *= temp;
    // check right
    temp = 0;
    for(size_t i = columnEnd-1; i >= column; --i) {
        //cout << "looking at tree at row " << row << ", column " << i << " with value " << map[row][i] << endl;
        if(map[row][i] >= val) {
            temp++;
            break;
        }
        temp++;
    }
    result *= temp;

    cout << "score: " << to_string(result) << endl;
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


    for(size_t row = 1; row < map.size()-1; ++row) {
        for(size_t column = 1; column < map[0].size()-1; ++column) {
            int temp = getScenicScore(row, column, map);
            if(temp > result) result = temp;
        }
    }

    cout << "result " << result << endl;

    return 0;
}