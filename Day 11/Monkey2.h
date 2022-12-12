#ifndef MONKEY_H
#define MONKEY_H

#include <string>
#include <vector>

class Monkey {
public:
    Monkey(std::vector<int>& items, std::vector<std::string>& operationVals, int testVal, int testTrue, int testFalse);
    // run inspection on each item monkey is holding
    void inspect();
    // @return # of times monkey has inspected an item
    int getInspectionCount() const;
    // @return vector ref of items
    const std::vector<long long>& getItems() const;
    // @return vector ref of all monkeys
    static std::vector<Monkey>& getMonkeys();
    static int& getEEAAO();
    // add item to items vector
    // @param item - item to add to monkey
    void addItem(long long item);
    // cout monkey info
    void print();
private:
    // run operation
    // @param item to operate on
    void operation(long long& item);
    // run test case, return result
    // @param item to test divisibility
    // @return is divisible or not
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

    // btw you can't delete a monkey from the list
    // if you make one wrong you're fucked mb
    static std::vector<Monkey> m_monkeys;
    // Everything Everywhere All At Once (<3 MATH 230)
    // lcm of all the divisible-by primes in every monkey's test
    static int EEAAO;
};


#endif