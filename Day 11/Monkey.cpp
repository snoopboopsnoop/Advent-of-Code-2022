#include "Monkey.h"
#include <math.h>
#include <iostream>

using namespace std;

// ton of debug couts because today fucking sucked
// see "Monkey.h" for function doc

Monkey::Monkey(std::vector<int>& items, std::vector<std::string>& operationVals, int testVal, int testTrue, int testFalse)
    : m_items(items.begin(), items.end()), m_operationVals(operationVals) {
    m_testVal = testVal;
    m_inspectionCount = 0;
    m_testTrue = testTrue;
    m_testFalse = testFalse;

    m_monkeys.push_back(*this);
}

void Monkey::inspect() {
    int sendMonkey = 0;
    
    auto beg = m_items.begin();
    while(beg != m_items.end()) {
        // cout << "monkey inspects an item with worry level of " << *beg << endl;
        operation(*beg);
        bored(*beg);
        bool result = test(*beg);
        if(result == true) {
            // cout << "current worry level is divisible by " << m_testVal << endl;
            // cout << "item with worry level " << *beg << " is thrown to monkey " << m_testTrue << endl;
            m_monkeys[m_testTrue].addItem(*beg);
        } 
        else {
            // cout << "current worry level is not divisible by " << m_testVal << endl;
            // cout << "item with worry level " << *beg << " is thrown to monkey " << m_testFalse << endl;
            m_monkeys[m_testFalse].addItem(*beg);
        }
        // cout << "erasing item with worry level " << *beg << endl;
        beg = m_items.erase(beg);
        m_inspectionCount++;
        // cout << endl;
    }
}

int Monkey::getInspectionCount() const { return m_inspectionCount; }

const vector<int>& Monkey::getItems() const { return m_items; }

vector<Monkey>& Monkey::getMonkeys() { return m_monkeys; }

void Monkey::print() {
    cout << "monkey has items ";
    for(int i : m_items) {
        cout << i << ", ";
    }
    cout << "operation ";
    for(const string& i : m_operationVals) {
        cout << i << " ";
    }
    cout << " and test is divisible by " << m_testVal
        << ", if true send to monkey " << m_testTrue
        << ", if not send to monkey " << m_testFalse << endl;
}

void Monkey::addItem(int item) { m_items.push_back(item); }

void Monkey::bored(int& item) {
    item = floor(item / 3);
    // cout << "monkey gets bored with item. worry level is divided by 3 to " << item << endl;
}

void Monkey::operation(int& item) {
    // cout << "worry level ";
    if(m_operationVals[0] == "+") {
        // cout << "increases by ";
        if(m_operationVals[1] == "old") {
            // cout << "itself to ";
            item = item + item;
            // cout << item << endl;
        }
        else {
            // cout << stoi(m_operationVals[1]) << " to ";
            item = item + stoi(m_operationVals[1]);
            // cout << item << endl;
        } 
    }
    else {
        // cout << "is multiplied by ";
        if(m_operationVals[1] == "old") {
            // cout << "itself to ";
            item = item * item;
            // cout << item << endl;
        }
        else {
            // cout << stoi(m_operationVals[1]) << " to ";
            item = item * stoi(m_operationVals[1]);
            // cout << item << endl;
        }
    }
}

bool Monkey::test(int& item) {
    if(item % m_testVal == 0) return true;
    return false;
}

vector<Monkey> Monkey::m_monkeys;