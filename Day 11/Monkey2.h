#ifndef MONKEY_H
#define MONKEY_H

#include <string>
#include <vector>

class Monkey {
public:
    Monkey(std::vector<int>& items, std::vector<std::string>& operationVals, int testVal, int testTrue, int testFalse);
    // run inspection on each item monkey is holding
    void inspect();
    int getInspectionCount() const;
    std::vector<int>& getItems() const;
    static std::vector<Monkey>& getMonkeys();
    // add item to items vector
    void addItem(int item);
    void print();
private:
    // divide item by 3 and floor
    void bored(int& item);
    // run operation
    void operation(int& item);
    // run test case, return result
    bool test(int& item);

    std::vector<int> m_items;
    // operation, val2
    std::vector<std::string> m_operationVals;
    // number to be divisble by
    int m_testVal;
    // keep track of number of items inspected
    int m_inspectionCount;
    // monkey # to throw to
    int m_testTrue;
    int m_testFalse;

    static std::vector<Monkey> m_monkeys;
};


#endif