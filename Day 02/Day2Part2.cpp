#include <iostream>
#include <fstream>

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

        // moves: 1 = rock, 2 = paper, 3 = scissors
        in >> c;
        int elfMove = c - 'A' + 1;
        
        in >> c;
        // desired outcome
        int end = c - 'X' + 1;

        int permutation = 0;
        switch (end) {
            // PERMUTATION SHIFTS MOD 3: draw = 0, win = 1, lose = 2

            // switch: 1 = lose, 2 = draw, 3 = win
            case 1:
                result += kLose;
                permutation = 2;
                break;
            case 2:
                result += kDraw;
                permutation = 0;
                break;
            case 3:
                result += kWin;
                permutation = 1;
                break;
        }

        // but 0 = 3
        int move = (elfMove + permutation) % 3;
        result += (!move) ? 3 : move;

        //throw away newline
        in.get();
    }

    cout << "Total Score: " << result << endl;

    return 0;
}
