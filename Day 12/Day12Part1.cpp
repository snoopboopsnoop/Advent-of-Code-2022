#include <iostream>
#include <fstream>

using namespace std;

// difficulty leap from day 5 down to this one is bigger than your mother

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    int result = 0;

    cout << "result: " << result << endl;

    return 0;
}