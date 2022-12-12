#include "Monkey2.h"
#include <math.h>
#include <iostream>

using namespace std;

Monkey::Monkey(std::vector<BigNum>& items, std::vector<std::string>& operationVals, int testVal, int testTrue, int testFalse)
    : m_items(items.begin(), items.end()), m_operationVals(operationVals) {
    m_testVal = testVal;
    m_inspectionCount = 0;
    m_testTrue = testTrue;
    m_testFalse = testFalse;
    cout<< "created new monkey with items ";
    for(BigNum& i : m_items) {
        cout<< i.getData() << ", ";
    }
    cout<< "operation ";
    for(const string& i : m_operationVals) {
        cout<< i << " ";
    }
    cout<< " and test is divisible by " << m_testVal
        << ", if true send to monkey " << m_testTrue
        << ", if not send to monkey " << m_testFalse << endl;

    m_monkeys.push_back(*this);
}

void Monkey::inspect() {
    int sendMonkey = 0;
    auto beg = m_items.begin();

    while(beg != m_items.end()) {

        cout<< "monkey inspects an item with worry level of " << beg->getData() << endl;
        operation(*beg);
        bool result = test(*beg);
        if(result == true) {
            cout<< "current worry level is divisible by " << m_testVal << endl;
            cout<< "item with worry level " << beg->getData() << " is thrown to monkey " << m_testTrue << endl;
            m_monkeys[m_testTrue].addItem(beg->getData());
        } 
        else {
            cout<< "current worry level is not divisible by " << m_testVal << endl;
            cout<< "item with worry level " << beg->getData() << " is thrown to monkey " << m_testFalse << endl;
            m_monkeys[m_testFalse].addItem(beg->getData());
        }
        beg = m_items.erase(beg);
        //if(m_items.size() == 0) break;
        m_inspectionCount++;
        cout<< endl;
    }
}

int Monkey::getInspectionCount() const { return m_inspectionCount; }

const vector<BigNum>& Monkey::getItems() const { return m_items; }

vector<Monkey>& Monkey::getMonkeys() {
    return m_monkeys;
}

void Monkey::print() {
    cout<< "monkey has items ";
    for(const BigNum& i : m_items) {
        cout<< i.getData() << ", ";
    }
    cout<< "operation ";
    for(const string& i : m_operationVals) {
        cout<< i << " ";
    }
    cout<< " and test is divisible by " << m_testVal
        << ", if true send to monkey " << m_testTrue
        << ", if not send to monkey " << m_testFalse << endl;
}

void Monkey::addItem(BigNum item) {
    m_items.push_back(item);
}

void Monkey::operation(BigNum& item) {
    cout<< "worry level ";
    if(m_operationVals[0] == "+") {
        cout<< "increases by ";
        if(m_operationVals[1] == "old") {
            cout<< "itself to ";
            item = item + item;
            cout<< item.getData() << endl;
        }
        else {
            cout<< stoi(m_operationVals[1]) << " to ";
            item = item + BigNum(m_operationVals[1]);
            cout<< item.getData() << endl;
        } 
    }
    else {
        cout<< "is multiplied by ";
        if(m_operationVals[1] == "old") {
            cout<< "itself to ";
            item = item * item;
            cout << item.getData() << endl;
        }
        else {
            cout<< stoi(m_operationVals[1]) << " to ";
            item = item * BigNum(m_operationVals[1]);
            cout<< item.getData() << endl;
        }
    }
}

bool Monkey::test(BigNum& item) {
    if(item % m_testVal == 0) return true;
    return false;
}

vector<Monkey> Monkey::m_monkeys;