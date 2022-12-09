#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// difficulty leap from day 5 down to this one is bigger than your mother

int getScenicScore(const size_t row, const size_t column, const vector<string>& map) {
    int result = 1;
    
    int val = map[row][column];
    //cout << "checking tree at row " << row << ", column " << column << " with value " << val-'0' << endl;

    size_t rowEnd = map.size();
    size_t columnEnd = map[0].size();
    // check top
    int temp = 0;
    for(int i = row-1; i > -1; --i) {
        //cout << "looking at tree at row " << i << ", column " << column << " with value " << map[i][column] << endl;
        if(map[i][column] >= val) {
            temp++;
            break;
        }
        temp++;
    }
    //cout << "from top, score: " << temp << endl;
    if(temp > 0) result *= temp;
    
    // check bottom
    temp = 0;
    for(int i = row+1; i < rowEnd; ++i) {
        //cout << "looking at tree at row " << i << ", column " << column << " with value " << map[i][column] << endl;
        if(map[i][column] >= val) {
            temp++;
            break;
        }
        temp++;
    }
    //cout << "from bottom, score: " << temp << endl;
    if(temp > 0) result *= temp;
    // check left
    temp = 0;
    for(int i = column-1; i > -1; --i) {
        //cout << "looking at tree at row " << row << ", column " << i << " with value " << map[row][i] << endl;
        if(map[row][i] >= val) {
            temp++;
            break;
        }
        temp++;
    }
    //cout << "from left, score: " << temp << endl;
    if(temp > 0) result *= temp;
    // check right
    temp = 0;
    for(int i = column+1; i < columnEnd; ++i) {
        //cout << "looking at tree at row " << row << ", column " << i << " with value " << map[row][i] << endl;
        if(map[row][i] >= val) {
            temp++;
            break;
        }
        temp++;
    }
    //cout << "from right, score: " << temp << endl;
    if(temp > 0) result *= temp;

    //cout << "score: " << to_string(result) << endl;
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
            if(temp > result) {
                cout << "new best at row " << row << ", column " << column << " with score " << temp << endl;
                result = temp;
            }
        }
    }

    cout << "result " << result << endl;

    return 0;
}