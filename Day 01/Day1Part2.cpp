#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// don't worry i took a C++1 course so this time it'll go better

int main() {
    // create input stream
    ifstream in("input.txt");

    // cant read
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    string line;
    int greatest = 0;
    int second = 0;
    int third = 0;
    
    //read each elf in and check if its a new top 3
    while(in) {
        int currElf = 0;
        while(getline(in, line)) {
            if(line == "") break;
            currElf += stoi(line);
        }
        if(currElf > greatest) {
            third = second;
            second = greatest;
            greatest = currElf;
        }
        else if(currElf > second) {
            third = second;
            second = currElf;
        }
        else if(currElf > third) {
            third = currElf;
        }
    }
    
    cout << "Top 3 Elves are carrying " << greatest+second+third << " Calories of food" << endl;

    return 0;
}