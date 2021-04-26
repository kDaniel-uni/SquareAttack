/**
 * Projet tutoré SquareAttack
 **/

#include "AES.h"

int test_AES() {

	std::string testString = "theblockbreakers";
	key testKey = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

	tableau2D testTab = AES(createState(testString), testKey);

	tableau2D verifTab = { {0xc6, 0x9f, 0x25, 0xd0}, {0x02, 0x5a, 0x9e, 0xf3}, {0x23, 0x93, 0xf6, 0x3e}, {0x2f, 0x05, 0xb7, 0x47} };

	if (testTab != verifTab) {
		return 1;
	}

	return 0;
}

int test_RoundKey() {

	return 0;
}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		return 0;
	}

	if (strcmp("AES", argv[1]) == 0) {
		return test_AES();
	} 
	else if (strcmp("RoundKey", argv[1]) == 0) {
		return test_RoundKey();
	}

}