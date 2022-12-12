#ifndef BIGNUM_H
#define BIGNUM_H

#include <string>

//bruh

class BigNum {
public:
    BigNum(std::string data);
    std::string getData() const;
    BigNum operator+(const BigNum& rhs) const;
    BigNum operator*(const BigNum& rhs) const;
    int operator%(int rhs) const;
private:
    std::string m_data;
};

#endif