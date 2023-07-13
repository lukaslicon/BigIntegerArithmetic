/*********************************************************************************
* Lukas Licon, llicon
* 2023 Winter CSE101 PA#6
* BigInteger.cpp
* 03/3/2023
* Implemention file for BigInteger functions
*********************************************************************************/ 
#include <iostream>
#include <stdexcept>
#include <string>
#include <cmath>
#include "List.h"
#include "BigInteger.h"

#define BASE 1000000000
#define POWER 9 
#define DIGITS "0123456789"

//---------------------------------------- Class Constructors & Destructors ----------------------------------------//
// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
    signum = 0;
    List digits;
}
// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    if (s.empty()) {
        throw std::invalid_argument("BigInteger Constructor Error: empty string");
    }
    signum = 0;
    if (s[0] == '+') {
        signum = 1;
        s.erase(0, 1);
    }
    else if (s[0] == '-') {
        signum = -1;
        s.erase(0, 1);
    }
    if (s.length() == 1 && s[0] == '0') {
        signum = 0;
        return;
    }
    if (s.length() == 0) {
        throw std::invalid_argument("BigInteger Constructor Error: non-numeric string");
    }
    if (s.find_first_not_of(DIGITS, 1) != std::string::npos) {
        throw std::invalid_argument("BigInteger Constructor Error: non-numeric string");
    }
    //erase leading zeros
    s.erase(0, s.find_first_not_of('0'));
    int s_len = s.length();
    std::string x = "";
    int count = 0;
    digits.moveFront();
    for (int i = s_len - 1; i >= 0; --i) {
        if (count == POWER) {
            long final = stol(x);
            this->digits.insertAfter(final);
            x = "";
            count = 0;
        }
        x.insert(0, 1, s[i]);
        count++;
    }
    //remaining
    if (x.empty() == false) {
        this->digits.insertAfter(stol(x));
    }
    if (signum == 0) {
        signum = 1;
    }
    return;
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    signum = N.signum;
    digits = N.digits;
}
// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is negative, 
// positive or 0, respectively.
int BigInteger::sign() const {
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    //signs
    if (signum > N.signum) {
        return 1;
    }
    else if (signum < N.signum) {
        return -1;
    }
    //lengths
    int this_length = digits.length();
    int N_length = N.digits.length();
    if (this_length > N_length) {
        return 1;
    }
    else if (this_length < N_length) {
        return -1;
    }

    //lists
    if (digits == N.digits) {
        return 0;
    }
    List A = digits;
    List B = N.digits;

    //lengths are the same, digits are not
    A.moveFront();
    B.moveFront();
    while (A.position() < A.length() && B.position() < B.length()) {
        long x = A.moveNext();
        long y = B.moveNext();
        if (x > y && signum == 1 && N.signum == 1) {
            return 1;
        }
        if (x < y && signum == 1 && N.signum == 1) {
            return -1;
        }
        if (signum == -1 && N.signum == -1 && x > y) {
            return -1;
        }
        if (signum == -1 && N.signum == -1 && x < y) {
            return 1;
        }
    }
    return 0;
}
//------------------------------------------------- Manipulation procedures -------------------------------------------------//

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    signum = 0;
    digits.clear();
}
// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
    if (signum != 0) {
        signum *= -1;
    }
}
//------------------------------------------------- Helper Functions -------------------------------------------------//
//negateList()
//flips the signs
void negateList(List& L) {
    if (L.length() > 0) {
        for (L.moveFront(); L.position() < L.length(); L.moveNext()) {
            L.setAfter(L.peekNext() * -1);
        }
    }
}

//sumList()
//A + sign*B
void sumList(List& S, List A, List B, int sign) {
    S.clear();
    if (A.length() == 0 && B.length() != 0) {
        S = B;
        return;
    }
    else if (A.length() != 0 && B.length() == 0) {
        S = A;
        return;
    }
    //combine
    A.moveBack();
    B.moveBack();
    S.moveBack();
    while (A.position() != 0 && B.position() != 0) {
        S.insertAfter(A.peekPrev() + (sign * B.peekPrev()));
        B.movePrev();
        A.movePrev();
    }
    //check
    if (A.position() != 0) {
        while (A.position() != 0) {
            S.insertAfter(A.peekPrev());
            A.movePrev();
        }
    }
    if (B.position() != 0) {
        while (B.position() != 0) {
            S.insertAfter(sign * B.peekPrev());
            B.movePrev();
        }
    }
    if (S.front() == 0) {
        S.moveFront();
        while (S.moveNext() == 0 && S.position() < S.length()) {
            S.eraseBefore();
        }
        if (S.length() == 1 && S.front() == 0) {
            S.clear();
        }
    }
    return;
}

//normalize()
//carrying function
int normalize(List& L) {
    if (L.length() == 0) {
        return 0;
    }
    L.moveBack();
    while (L.position() > 0) {
        L.movePrev();
        long temp = L.peekNext();
        if (temp >= BASE) {
            long multi = floor(temp / BASE);
            L.setAfter(temp - (multi * BASE));
            if (L.position() == 0) {
                L.insertBefore(multi);
                return 1;
            }
            else {
                long prev_temp = L.peekPrev();
                L.setBefore(prev_temp + multi);
            }
        }
        else if (temp < 0) {
            long multi = (-1 * floor(temp / BASE)) == 0 ? 1 : (-1 * (temp / BASE));
            if (L.front() == temp) {
                negateList(L);
                normalize(L);
                return -1;
            }
            L.setAfter(temp + (multi * BASE));
            if (L.position() == 0) {
                L.insertBefore(multi);
                return -1;
            }
            else {
                long prev_ele = L.peekPrev();
                L.setBefore(prev_ele - multi);
            }
        }
    }
    return 1;
}

//shiftList() 
//appends to the list
void shiftList(List& L, int p) {
    int ele_nums = p;
    L.moveBack();
    for (int i = 0; i < ele_nums; ++i) {
        L.insertBefore(0);
    }
    L.moveFront();
    return;
}


//scalarMultiList()
//multiples List by m
void scalarMultiList(List& L, ListElement m) {
    if (m == 1) {
        return;
    }
    if (m == 0) {
        L.clear();
        return;
    }
    L.moveFront();
    while (L.position() < L.length()) {
        L.setBefore(L.moveNext() * m);
    }
    return;
}

//------------------------------------------------- BigInteger Arithmetic Operations -------------------------------------------------//

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    if (sign() == 0)
        return N;
    if (N.sign() == 0)
        return *this;

    List left1 = this->digits;
    List right1 = N.digits;
    int final;
    List ans;
    BigInteger temp1;

    //  -A + -B
    if (sign() == -1 && N.sign() == -1) {
        BigInteger left2 = *this;
        BigInteger right2 = N;
        left2.signum = 1;
        right2.signum = 1;
        temp1 = left2.add(right2);
        temp1.signum = -1;
        return temp1;
    }
    //  -A + B
    if (sign() == -1 && N.sign() == 1) {
        BigInteger left2 = *this;
        BigInteger right2 = N;
        left2.signum = 1;
        right2.signum = 1;
        if (left2 == right2) { // A is equal to B
            temp1 = left2.sub(right2);
            return temp1;
        }
        if (left2 > right2) { // A bigger than B
            temp1 = left2.sub(right2);
            temp1.signum = -1;
            return temp1;
        }
        else { //B bigger than A
            temp1 = right2.sub(left2);
            temp1.signum = 1;
            return temp1;
        }
    }
    //   A + -B 
    if (sign() == 1 && N.sign() == -1) {
        BigInteger left2 = *this;
        BigInteger right2 = N;
        left2.signum = 1;
        right2.signum = 1;
        if (left2 == right2) { // A is equal to B
            temp1 = left2.sub(right2);
            return temp1;
        }
        if (left2 > right2) { // A bigger than B
            temp1 = left2.sub(right2);
            temp1.signum = 1;
            return temp1;
        }
        else { // B bigger than A
            temp1 = right2.sub(left2);
            temp1.signum = -1;
            return temp1;
        }
    }

    //   A + B     
    else {
        sumList(ans, left1, right1, N.signum);
        final = normalize(ans);
        if (ans.length() == 0) {
            final = 0;
        }
        temp1.signum = final;
        temp1.digits = ans;
        return temp1;
    }

}
// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    List left = digits;
    List right = N.digits;
    int comparison = this->compare(N);
    BigInteger temp1;
    if (comparison == -1) {
        temp1 = N.sub(*this);
        temp1.signum = -1;
        return temp1;
    }
    if (N.signum == -1 && signum == -1) {
        BigInteger temp2 = N;
        BigInteger temp3 = *this;
        temp2.signum = 1;
        temp3.signum = 1;
        temp1 = temp2.sub(temp3);
        return temp1;
    }
    List ans;
    sumList(ans, left, right, -1 * N.signum);
    int final_sign = normalize(ans);
    temp1.signum = final_sign;
    temp1.digits = ans;
    return temp1;
}
// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
    List left = this->digits;
    List right = N.digits;
    List ans;
    List prev;
    BigInteger temp1;
    if (N.signum == 0) {
        temp1.signum = 0;
        return temp1;
    }
    int count = 0;
    for (right.moveBack(); right.position() > 0; right.movePrev()) {
        List vector = left;
        shiftList(vector, count);
        scalarMultiList(vector, right.peekPrev());
        sumList(ans, vector, prev, 1);
        normalize(ans);
        prev = ans;
        count++;
    }
    if ((signum == -1 && N.signum == -1)) {
        temp1.signum = 1;
    }
    else if (signum == -1 || N.signum == -1) {
        temp1.signum = -1;
    }
    else {
        temp1.signum = 1;
    }
    temp1.digits = ans;
    return temp1;
}
//------------------------------------------------- Other Functions -------------------------------------------------//
// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    std::string final = "";
    if (digits.length() > 0) {
        if (signum == -1) {
            final += "-";
        }
        for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
            std::string convert = std::to_string(digits.peekNext());
            if (digits.position() == 0) {
                final += convert;

                //add leading zeros if the element is less than POWER digits
            }
            else if (convert.length() < POWER) {
                int num_of_chars = POWER - convert.length();
                convert.insert(0, num_of_chars, '0');
                final += convert;
            }
            else {
                final += convert;
            }
        }
        return final;
    }
    return "0";
}
//------------------------------------------------- Overridden Operators -------------------------------------------------//

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<(std::ostream& stream, BigInteger N) {
    return stream << N.BigInteger::to_string();
}
// operator==()
// Returns true if and only if A equals B. 
bool operator==(const BigInteger& A, const BigInteger& B) {
    return (A.compare(B) == 0) ? true : false;
}
// operator<()
// Returns true if and only if A is less than B. 
bool operator<(const BigInteger& A, const BigInteger& B) {
    return (A.compare(B) == -1) ? true : false;
}
// operator<=()
// Returns true if and only if A is less than or equal to B.
bool operator<=(const BigInteger& A, const BigInteger& B) {
    int comparison = A.compare(B);
    return (comparison == -1 || comparison == 0) ? true : false;
}
// operator>()
// Returns true if and only if A is greater than B.
bool operator>(const BigInteger& A, const BigInteger& B) {
    return (A.compare(B) == 1) ? true : false;
}
// operator>=()
// Returns true if and only if A is greater than or equal to B.
bool operator>=(const BigInteger& A, const BigInteger& B) {
    int comparison = A.compare(B);
    return (comparison == 1 || comparison == 0) ? true : false;
}
// operator+()
// Returns the sum A+B. 
BigInteger operator+(const BigInteger& A, const BigInteger& B) {
    return A.add(B);
}
// operator+=()
// Overwrites A with the sum A+B.
BigInteger operator+=(BigInteger& A, const BigInteger& B) {
    A = A.add(B);
    return A;
}
// operator-()
// Returns the difference A-B. 
BigInteger operator-(const BigInteger& A, const BigInteger& B) {
    return A.sub(B);
}
// operator-=()
// Overwrites A with the difference A-B.
BigInteger operator-=(BigInteger& A, const BigInteger& B) {
    A = A.sub(B);
    return A;
}
// operator*()
// Returns the product A*B. 
BigInteger operator*(const BigInteger& A, const BigInteger& B) {
    return A.mult(B);
}
// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=(BigInteger& A, const BigInteger& B) {
    A = A.mult(B);
    return A;
}
