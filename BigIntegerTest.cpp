/*********************************************************************************
* Lukas Licon, llicon
* 2023 Winter CSE101 PA#6
* BigIntegerTest.cpp
* 03/3/2023
* Test file for BigInteger functions
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){
	BigInteger test, test1, test2, A,B,C,D;
	cout << "A before init: " << A << endl;
	cout << "B before init: " << B << endl;
	cout << "C before init: " << C << endl;
	cout << "D before init: " << D << endl;

	string s1 = "123456789";
	string s2 = "123456789100000000";
	string s3 = "1234567891000000000";

  
  test1 = BigInteger("+111122223333");
  test2 = BigInteger("-111122223333");
	A = BigInteger(s1);
	B = BigInteger(s2);
  D = BigInteger(s3);

  cout << endl;
	test = test1 + test2;
  cout << "Testing pos + neg same number:" << endl;
	cout << "test1: " << test1 << endl;
	cout << "test2: " << test2 << endl;
	cout << "test = test1 + test2: " << test << endl;
  cout << endl;

  test = test2 + test1;
  cout << "Testing neg + pos same number:" << endl;
	cout << "test1: " << test1 << endl;
	cout << "test2: " << test2 << endl;
	cout << "test = test2 + test1: " << test << endl;
	cout << endl;
  
	C = A+B;
  cout << "Testing pos + pos:" << endl;
	cout << "A: " << A << endl;
	cout << "B: " << B << endl;
	cout << "C = A+B: " << C << endl;
	cout << endl;
  
	D.negate();
	C = D+A;
	cout << "Testing neg + pos:" << endl;
	cout << "A: " << A << endl;
	cout << "D: " << D << endl;
	cout << "C = D+A: " << C << endl;
	cout << endl;
  
	C = A+D;
	cout << "Testing pos + neg:" << endl;
	cout << "A: " << A << endl;
	cout << "D: " << D << endl;
	cout << "C = A+D: " << C << endl;

	cout << endl;

	A.negate();
	C = A+D;
	cout << "Testing neg + neg:" << endl;
	cout << "A: " << A << endl;
	cout << "D: " << D << endl;
	cout << "C = A+D: " << C << endl;
	cout << endl;

	D = A;
	cout << "D before makeZero(): " << D << endl;
	D.makeZero();
	cout << "D after makezero(): " << D << endl;
	cout << "A at D after makezero(): " << A << endl;
	cout << endl;

  
	D = BigInteger(s3);
	cout << "D before negate(): " << D << endl;
	D.negate();
	cout << "D after negate(): " << D << endl;

  D.negate();
	C = D - A;
	cout << "Testing pos - neg:" << endl;
	cout << "A: " << A << endl;
	cout << "D: " << D << endl;
	cout << "C = D-A: " << C << endl;
	
	cout << endl;
	
	C = A-D;
	cout << "Testing neg - pos:" << endl;
	cout << "A: " << A << endl;
	cout << "D: " << D << endl;
	cout << "C = A-D: " << C << endl;

	cout << endl;

	A.negate();
	A += A;
	cout << "Testing +=" << endl;
	cout << "A: " << A << endl;
	
	cout << endl;
	
	A = BigInteger(s1);
	A -= A;
	cout << "Testing -=" << endl;
	cout << "A: " << A << endl;

	cout << endl;

	A = BigInteger(s1);
  D = BigInteger(s3); 
	C = A*B;
	cout << "Testing pos * pos:" << endl;
	cout << "A: " << A << endl;
	cout << "B: " << B << endl;
	cout << "C = AB: " << C << endl;
	cout << endl;
  
  A.negate();
  C = A*B;
	cout << "Testing neg * pos:" << endl;
	cout << "A: " << A << endl;
	cout << "B: " << B << endl;
	cout << "C = AB: " << C << endl;
 
	cout << endl;
  B.negate();
  C = A*B;
	cout << "Testing neg * neg:" << endl;
	cout << "A: " << A << endl;
	cout << "B: " << B << endl;
	cout << "C = AB: " << C << endl;
	cout << endl;
  
  A.negate();
  C = A*B;
	cout << "Testing pos * neg:" << endl;
	cout << "A: " << A << endl;
	cout << "B: " << B << endl;
	cout << "C = AB: " << C << endl;

  cout << endl;
	A *= A;
	cout << "Test *=" << endl;
	cout << "A = " << A << endl;

	cout << endl;
	return 0;
}
