#ifndef BIGNUM_H
#define BIGNUM_H

#include <string>

class BigNum {
public:
    std::string& getData() const;
    BigNum operator+(const BigNum& rhs) const;
    BigNum operator*(const BigNum& rhs) const;
    BigNum operator%(int rhs) const;
private:
    std::string data;
};

#endif