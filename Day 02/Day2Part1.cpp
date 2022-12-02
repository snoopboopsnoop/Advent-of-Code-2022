#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// if statements? i prefer abstract algebra

int main() {
    // input stream
    ifstream in("input.txt");

    // broke
    if(!in) cerr << "oops tehre was a fucky wucky" << endl;

    int result = 0;
    const int kLose = 0;
    const int kDraw = 3;
    const int kWin = 6;

    while(in) {
        char c;

        // moves 1 = rock, 2 = paper, 3 = scissors
        in >> c;
        int elfMove = c - 'A' + 1;
        in >> c;
        int move = c - 'X' + 1;

        // Z mod 3
        switch ((move - elfMove + 3) % 3) {
            //win
            case 1:
                result += kWin;
                break;
            //draw
            case 0:
                result += kDraw;
                break;
            //lose
            case 2:
                result += kLose;
                break;
        }
        result += move;

        //throw away newline
        in.get();
    }

    cout << "Total Score: " << result << endl;

    return 0;
}
