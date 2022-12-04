#include <iostream>
#include <fstream>
#include <utility>

using namespace std;

// honestly embarrassing if you can't solve this one

pair <int, int> getElf(ifstream& in);

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    int result = 0;

    while(in) {
        // initialize 2 elves
        pair<int, int> elf1 = getElf(in);
        pair<int, int> elf2 = getElf(in);

        // check if bigger first is smaller than the other's second
        if((elf1.first >= elf2.first && elf1.first <= elf2.second)
            || (elf1.first <= elf2.first && elf1.second >= elf2.first)) result++;
    }
    
    cout << result << " overlapping pairs" << endl;

    return 0;
}

pair <int, int> getElf(ifstream& in) {
    int u, v;
    in >> u;
    in.get();
    in >> v;
    in.get();
    return pair<int, int> (u, v);
}