#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// https://youtu.be/DuWEEKeJLMI?t=86 he's just like me fr

// returns if tree is visible from any side
bool isVisible(const size_t row, const size_t column, const vector<string>& map) {
    int val = map[row][column];
    size_t rowEnd = map.size();
    size_t columnEnd = map[0].size();

    // check top
    for(int i = row-1; i >= -1; --i) {
        if(i == -1) {
            return true;
        }
        else if(map[i][column] >= val) {
            break;
        } 
    }

    // check bottom
    for(int i = row+1; i <= rowEnd; ++i) {
        if(i == rowEnd) {
            return true;
        }
        else if(map[i][column] >= val) break;
    }

    // check left
    for(int i = column-1; i >= -1; --i) {
        if(i == -1) {
            return true;
        }
        else if(map[row][i] >= val) break;
    }

    // check right
    for(int i = column+1; i <= columnEnd; ++i) {
        if(i == columnEnd) {
            return true;
        }
        else if(map[row][i] >= val) break;
    }

    return false;
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

    // check if each internal tree is visible
    for(size_t row = 1; row < map.size()-1; ++row) {
        for(size_t column = 1; column < map[0].size()-1; ++column) {
            result += isVisible(row, column, map);
        }
    }
    cout << result << " visible trees" << endl;

    return 0;
}