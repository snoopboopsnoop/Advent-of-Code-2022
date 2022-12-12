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
    const std::vector<long long>& getItems() const;
    static std::vector<Monkey>& getMonkeys();
    static int& getEEAAO();
    // add item to items vector
    void addItem(long long item);
    void print();
private:
    // run operation
    void operation(long long& item);
    // run test case, return result
    bool test(long long& item);

    std::vector<long long> m_items;
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
    static int EEAAO;
};


#endif