/**
 * Projet tutor� SquareAttack
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

int test_AddRoundKey(){
	tableau2D Tab_1 = { {0x6a, 0x6a, 0x5c, 0x45} , {0x2c, 0x6d, 0x33, 0x51} , {0xb0, 0xd9, 0x5d, 0x61} ,
	{0x27, 0x9c, 0x21, 0x5c} };
	tableau2D Tab_2 = { {0xd6, 0xaa, 0x74, 0xfd} , {0xd2, 0xaf, 0x72, 0xfa} , {0xda, 0xa6, 0x78, 0xf1} ,
	{0xd6, 0xab, 0x76, 0xfe} };
	tableau2D Tab_AddRoundkey = { {0xbc, 0xc0, 0x28, 0xb8} , {0xfe, 0xc2, 0x41, 0xab} , {0x6a, 0x7f, 0x25, 0x90} ,
	{0xf1, 0x37, 0x57, 0xa2} };
	tableau2D resultat = AddRoundKey(Tab_1,Tab_2);
	printTableau(resultat);
	if (resultat == Tab_AddRoundkey){
		return 0;
	}
	return 1;
}

int test_ShiftRow(){
	return 0;
}

int test_MixColumns(){
	return 0;
}

int test_SubBytes(){
	return 0;
}

int test_Round(){
	return 0;
}

int test_FinalRound(){
	return 0;
}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		return 0;
	}

	if (strcmp("AES", argv[1]) == 0) {
		return test_AES();
	}
	else if (strcmp("AddRoundKey", argv[1]) == 0) {
		return test_AddRoundKey();
	}
	else if (strcmp("ShiftRow", argv[1]) == 0) {
		return test_ShiftRow();
	}
	else if (strcmp("MixColumns", argv[1]) == 0) {
		return test_MixColumns();
	}
	else if (strcmp("SubBytes", argv[1]) == 0) {
		return test_SubBytes();
	}
	else if (strcmp("Round", argv[1]) == 0) {
		return test_Round();
	}
	else if (strcmp("FinalRound", argv[1]) == 0) {
		return test_FinalRound();
	}

}
