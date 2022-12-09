#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// https://youtu.be/DuWEEKeJLMI?t=86 he's just like me fr

// returns scenic score of given tree (see day 8 part 2 instructions)
int getScenicScore(const size_t row, const size_t column, const vector<string>& map) {
    int result = 1;
    int val = map[row][column];
    size_t rowEnd = map.size();
    size_t columnEnd = map[0].size();

    // check top
    int temp = 0;
    for(int i = row-1; i > -1; --i) {
        if(map[i][column] >= val) {
            temp++;
            break;
        }
        temp++;
    }
    if(temp > 0) result *= temp;
    
    // check bottom
    temp = 0;
    for(int i = row+1; i < rowEnd; ++i) {
        if(map[i][column] >= val) {
            temp++;
            break;
        }
        temp++;
    }
    if(temp > 0) result *= temp;

    // check left
    temp = 0;
    for(int i = column-1; i > -1; --i) {
        if(map[row][i] >= val) {
            temp++;
            break;
        }
        temp++;
    }
    if(temp > 0) result *= temp;

    // check right
    temp = 0;
    for(int i = column+1; i < columnEnd; ++i) {
        if(map[row][i] >= val) {
            temp++;
            break;
        }
        temp++;
    }
    if(temp > 0) result *= temp;
    
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

    // check each internal tree (all perimeter trees will have score 0) for score and save highest
    for(size_t row = 1; row < map.size()-1; ++row) {
        for(size_t column = 1; column < map[0].size()-1; ++column) {
            int temp = getScenicScore(row, column, map);
            if(temp > result) {
                result = temp;
            }
        }
    }
    cout << "The best tree has a scenic score of " << result << endl;

    return 0;
}