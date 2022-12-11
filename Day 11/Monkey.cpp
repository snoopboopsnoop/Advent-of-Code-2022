#include "Monkey.h"
#include <math.h>

using namespace std;

Monkey::Monkey(vector<int>& items, vector<string>& operationVals, int testVal, int testTrue, int testFalse) {
    m_items = items;
    m_operationVals = operationVals;
    m_testVal = testVal;
    m_inspectionCount = 0;
    int m_testTrue = testTrue;
    int m_testFalse = testFalse;
}

int Monkey::inspect() {
    for(int& i : m_items) {
        operation(i);
        bored(i);
        bool result = test(i);
        if(result == true) m_monkeys[m_testTrue].addItem(i);
        else m_monkeys[m_testFalse].addItem(i);
    }   
}

int Monkey::getInspectionCount() { return m_inspectionCount; }

vector<Monkey> Monkey::monkeys() { return m_monkeys; }

void Monkey::addItem(int item) {
    m_items.push_back(item);
}

void Monkey::bored(int& item) {
    item = floor(item / 3);
}

//shit man i'm too tired to write this one tonight
void Monkey::operation(int& item) {

}

bool Monkey::test(int& item) {
    return false;
}

vector<Monkey> Monkey::m_monkeys;