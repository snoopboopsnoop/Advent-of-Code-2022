#include "BigNum.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

BigNum::BigNum(std::string data) : m_data(data) {}

std::string BigNum::getData() const { return m_data; }

// "borrowed" from https://www.geeksforgeeks.org/sum-two-large-numbers/
BigNum BigNum::operator+(const BigNum& rhs) const {
    string str1, str2;
    string result;
    if(m_data.size() > rhs.m_data.size()) {
        str1 = rhs.m_data;
        str2 = m_data;
    }
    else {
        str1 = m_data;
        str2 = rhs.m_data;
    }
    
    size_t len1 = str1.size(), len2 = str2.size();
    int diff = len2 - len1;

    int carry = 0;
    for(int i = len1-1; i >= 0; i--) {
        int sum = ((str1[i] - '0') + (str2[i+diff] - '0') + carry);
        result.push_back(sum % 10 + '0');

        carry = sum / 10;
    }

    for(int i = len2-len1-1; i >= 0; i--) {
        int sum = ((str2[i] - '0') + carry);
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    if(carry) {
        result.push_back(carry + '0');
    }

    reverse(result.begin(), result.end());

    return BigNum(result);
}

// "culled" from https://www.geeksforgeeks.org/multiply-large-numbers-represented-as-strings/
// shit doesn't work for negatives, read main
BigNum BigNum::operator*(const BigNum& rhs) const {
    size_t len1 = m_data.size();
    size_t len2 = rhs.m_data.size();
    vector<int> result(len1+len2, 0);

    if(len1 == 0 || len2 == 0) return BigNum("0");

    int i1 = 0;
    int i2 = 0;

    for(int i = len1-1; i >= 0; --i) {
        int carry = 0;
        int n1 = m_data[i] - '0';

        i2 = 0;

        for(int j = len2 - 1; j >= 0; --j) {
            int n2 = rhs.m_data[j] - '0';

            int sum = n1 * n2 + result[i1+i2] + carry;

            carry = sum / 10;

            result[i1 + i2] = sum % 10;

            i2++;
        }

        if(carry > 0) result[i1 + i2] += carry;

        i1++;
    }

    int i = result.size()-1;
    while(i >= 0 && result[i] == 0) {
        i--;
    }

    if(i == -1) {
        return BigNum("0");
    }

    string sResult;

    while (i >= 0) sResult += to_string(result[i--]);

    return BigNum(sResult);
}

// "appropriated" from https://www.geeksforgeeks.org/how-to-compute-mod-of-a-big-number/
int BigNum::operator%(int rhs) const {
    int result = 0;

    for(int i = 0; i < m_data.size(); i++) {
        result = (result * 10 + m_data[i] - '0') % rhs;
    }
    return result;
}