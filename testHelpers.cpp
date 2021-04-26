/**
 * Projet tutoré SquareAttack
 **/

#include "helpers.h"

int test_Shift() {
	column testCol = { 0x00, 0x01, 0x02, 0x03 };
	column verifCol = { 0x01, 0x02, 0x03, 0x00 };
	testCol = Shift(testCol);

	if (testCol != verifCol) {
		return 1;
	}

	return 0;
}

int test_SBox() {
	column testCol = { 0x01, 0xc2, 0x9e, 0x00 };
	column verifCol = { 0x7c, 0x25, 0x0b, 0x63 };

	testCol = SBox(testCol);

	if (testCol != verifCol) {
		return 1;
	}

	return 0;
}

int test_Rcon() {

	column verifCol = { 0x8d, 0x00, 0x00, 0x00 };

	column testCol = Rcon(0);

	if (testCol != verifCol) {
		return 1;
	}

	return 0;
}

int test_ParseKey() {

	key testKey = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

	tableau2D testTab = ParseKey(testKey);

	tableau2D verifTab = { {0x2b, 0x7e, 0x15, 0x16} , {0x28, 0xae, 0xd2, 0xa6} , {0xab, 0xf7, 0x15, 0x88} , {0x09, 0xcf, 0x4f, 0x3c} };

	if (testTab != verifTab) {
		return 1;
	}

	return 0;
}

int test_ParseTableau() {

	tableau2D testTab = { {0x2b, 0x7e, 0x15, 0x16} , {0x28, 0xae, 0xd2, 0xa6} , {0xab, 0xf7, 0x15, 0x88} , {0x09, 0xcf, 0x4f, 0x3c} };

	key testKey = ParseTableau(testTab);

	key verifKey = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

	if (testKey != verifKey) {
		return 1;
	}

	return 0;
}

int test_ArrayXor() {
	column testCol1 = { 0x2b, 0x7e, 0x15, 0x16 };
	column testCol2 = { 0x28, 0xae, 0xd2, 0xa6 };

	column verifCol = { 0x03, 0xd0, 0xc7, 0xb0 };

	testCol1 = ArrayXor(testCol1, testCol2);

	if (testCol1 != verifCol) {
		return 1;
	}

	return 0;
}

int test_concat() {
	column testCol1 = { 0x2b, 0x7e, 0x15, 0x16 , 0x89 };
	column testCol2 = { 0x28, 0xae, 0xd2 };

	column verifCol = { 0x2b, 0x7e, 0x15, 0x16 , 0x89, 0x28, 0xae, 0xd2 };

	testCol1 = concat(testCol1, testCol2);

	if (testCol1 != verifCol) {
		return 1;
	}

	return 0;
}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		return 0;
	}

	if (strcmp("Shift", argv[1]) == 0) {
		return test_Shift();
	}
	else if (strcmp("SBox", argv[1]) == 0) {
		return test_SBox();
	}
	else if (strcmp("Rcon", argv[1]) == 0) {
		return test_Rcon();
	}
	else if (strcmp("ParseKey", argv[1]) == 0) {
		return test_ParseKey();
	}
	else if (strcmp("ParseTableau", argv[1]) == 0) {
		return test_ParseTableau();
	}
	else if (strcmp("ArrayXor", argv[1]) == 0) {
		return test_ArrayXor();
	}
	else if (strcmp("concat", argv[1]) == 0) {
		return test_concat();
	}

}