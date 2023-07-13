/*********************************************************************************
* Lukas Licon, llicon
* 2023 Winter CSE101 PA#6
* Arithmetic.cpp
* 03/3/2023
* Implemention file for Arithemetic Operations
*********************************************************************************/
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

#include "BigInteger.h"

using namespace std;

int main(int argc, char* argv[]) {

	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " <input file> <output file" << endl;
		return EXIT_FAILURE;
	}

	ifstream input;
	ofstream output;

	input.open(argv[1]);
	if (!input.is_open()) {
		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
		return EXIT_FAILURE;
	}

	output.open(argv[2]);
	if (!output.is_open()) {
		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
		return EXIT_FAILURE;
	}

	BigInteger temp1, temp2;

	//string for each line
	string line;

	// collect first, blank, second
	getline(input, line);
	temp1 = BigInteger(line);
	output << temp1 << endl << endl;
	getline(input, line);
	getline(input, line);
	temp2 = BigInteger(line);
	output << temp2 << endl << endl;

	// sum = temp1+temp2
	BigInteger sum = temp1 + temp2;
	output << sum << endl << endl;

	// sub = temp1-temp2
	BigInteger sub = temp1 - temp2;
	output << sub << endl << endl;

	// temp1-temp1
	BigInteger subTemp1;
	output << subTemp1 << endl << endl;

	BigInteger scalarTemp = BigInteger("2");

	// sub = temp1-temp2
	// subMult = 3(temp1)-2(temp2) = 2(temp1) - 2(temp2) + temp1
	BigInteger subMult = scalarTemp * sub;
	subMult += temp1;
	output << subMult << endl << endl;

	// mult = temp1*temp2
	BigInteger mult = temp1 * temp2;
	output << mult << endl << endl;

	// (temp1)*(temp1) = (temp1)^2
	BigInteger multTemp1 = temp1 * temp1;
	output << multTemp1 << endl << endl;

	// (temp2)*(temp2) = (temp2)^2
	BigInteger multTemp2 = temp2 * temp2;
	output << multTemp2 << endl << endl;

	// mult4 = multTemp1*multTemp1 = (temp1)^2*(temp1)^2 = (temp1)^4
	// mult5 = multTemp2*multTemp2 = (temp2)^2*(temp2)^2 = (temp2)^4
	// (temp2)^5 = (temp2)^4 * (temp2)
	BigInteger mult4 = multTemp1 * multTemp1;
	BigInteger mult5 = multTemp2 * multTemp2;
	mult5 *= temp2;

	// mult4 = 9 * (temp1)^4
	scalarTemp = BigInteger("9");
	mult4 *= scalarTemp;

	// mult4 = 16 * (temp2)^5
	scalarTemp = BigInteger("16");
	mult5 *= scalarTemp;

	// multAddtemp = 9(temp1)^4 + 16(temp2)^5
	BigInteger multAddTemp = mult4 + mult5;
	output << multAddTemp << endl << endl;

	input.close();
	output.close();

	return 0;
}
