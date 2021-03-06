/**
 * Projet tutor� SquareAttack
 **/

#include "AES.h"
#include <algorithm>
#include <chrono>
#include <numeric>
#include <thread>

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

int test_AESDecipher() {

	key testKey = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

	printVector(testKey);

	tableau2D encryptedTab = { {0xc6, 0x9f, 0x25, 0xd0}, {0x02, 0x5a, 0x9e, 0xf3}, {0x23, 0x93, 0xf6, 0x3e}, {0x2f, 0x05, 0xb7, 0x47} };

	tableau2D plainTab = AES(encryptedTab, testKey, true);
	printVector(testKey);

	std::string verifString = "theblockbreakers";

	if (reverseCypher(plainTab) != verifString) {
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
	tableau2D Tab_init = { {0x63, 0x7c, 0x77, 0x7b} , {0xf2, 0x6b, 0x6f, 0xc5} , {0x30, 0x01, 0x67, 0x2b} ,
	{0xfe, 0xd7, 0xab, 0x76} };
	tableau2D Tab_ShiftRow = { {0x63, 0x6b, 0x67, 0x76} , {0xf2, 0x01, 0xab, 0x7b} , {0x30, 0xd7, 0x77, 0xc5} ,
	{0xfe, 0x7c, 0x6f, 0x2b} };
	tableau2D result = ShiftRow(Tab_init);
	printTableau(result);
	if (result != Tab_ShiftRow){
		return 1;
	}
	return 0;
}

int test_MixColumns(){
	tableau2D Tab_init = { {0x63, 0x6b, 0x67, 0x76} , {0xf2, 0x01, 0xab, 0x7b} , {0x30, 0xd7, 0x77, 0xc5} ,
	{0xfe, 0x7c, 0x6f, 0x2b} };
	tableau2D Tab_MixColums = { {0x6a, 0x6a, 0x5c, 0x45} , {0x2c, 0x6d, 0x33, 0x51} , {0xb0, 0xd9, 0x5d, 0x61} ,
	{0x27, 0x9c, 0x21, 0x5c} };
	tableau2D result = MixColumns(Tab_init,false);
	if (result != Tab_MixColums){
		return 1;
	}
	return 0;
}

int test_SubBytes(){
	tableau2D Tab_init = { {0x00, 0x01, 0x02, 0x03} , {0x04, 0x05, 0x06, 0x07} , {0x08, 0x09, 0x0a, 0x0b} ,
	{0x0c, 0x0d, 0x0e, 0x0f} };
	tableau2D Tab_SubBytes = { {0x63, 0x7c, 0x77, 0x7b} , {0xf2, 0x6b, 0x6f, 0xc5} , {0x30, 0x01, 0x67, 0x2b} ,
	{0xfe, 0xd7, 0xab, 0x76} };
	tableau2D result = SubBytes(Tab_init,false);
	if (result != Tab_SubBytes){
		return 1;
	}
	return 0;
}

int test_Round(){
	return 0;
}

int test_FinalRound(){
	return 0;
}

int generalCypher(uint8_t i) {
	std::string testString = "testStringTesttt";
	key testKey = { 0x2b, 0x7e, 0x15, i, 0x28, 0xae, 0xd2, 0xa6, 0xab, i, 0x15, 0x88, i, 0xcf, 0x4f, 0x3c };

	tableau2D testTab = AES(createState(testString), testKey);
	//printTableau(testTab);

	return 0;
}

int generalDecypher(uint8_t i) {

	key testKey = { 0x2b, i, 0x15, i, 0x28, 0xae, 0xd2, 0xa6, i, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
	tableau2D encryptedTab = { {0x55, 0x26, 0x2c, 0xf8}, {0xa4, 0x2a, 0xde, 0x7d}, {0x96, 0xb3, 0x75, 0x44}, {0x9c, 0x39, 0x5f, 0x14} };

	tableau2D plainTab = AES(encryptedTab, testKey, true);
	
	//std::cout << reverseCypher(plainTab) << std::endl;

	return 0;
}

int generalCypherAverage() {
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;

	std::vector<int> durations;
	int tot = 250;

	for (size_t i = 0; i < tot; i++) {
		auto t1 = high_resolution_clock::now();
		generalCypher(i);
		auto t2 = high_resolution_clock::now();
		durations.push_back(duration_cast<std::chrono::microseconds>(t2 - t1).count());
	}

	std::sort(durations.begin(), durations.end());

	std::cout << "Nombre d'iterations : " << tot << "\n\n";
	std::cout << "1er Quartile : " << durations[durations.size() / 4] << "micros\n";
	std::cout << "Mediane : " << durations[durations.size() / 2] << "micros\n";
	std::cout << "3eme Quartile : " << durations[durations.size() * 3 / 4] << "micros\n";
	std::cout << "Lower : " << durations[0] << "micros\n";
	std::cout << "Upper : " << durations[durations.size() - 1] << "micros\n";
	std::cout << "Moyenne : " << std::accumulate(durations.begin(), durations.end(), 0) / durations.size() << "micros\n";

}

int generalDecypherAverage() {
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;

	std::vector<int> durations;
	int tot = 250;

	for (size_t i = 0; i < tot; i++) {
		auto t1 = high_resolution_clock::now();
		generalDecypher(i);
		auto t2 = high_resolution_clock::now();
		durations.push_back(duration_cast<std::chrono::microseconds>(t2 - t1).count());
	}

	std::sort(durations.begin(), durations.end());

	std::cout << "Nombre d'iterations : " << tot << "\n\n";
	std::cout << "1er Quartile : " << durations[durations.size() / 4] << "micros\n";
	std::cout << "Mediane : " << durations[durations.size() / 2] << "micros\n";
	std::cout << "3eme Quartile : " << durations[durations.size() * 3 / 4] << "micros\n";
	std::cout << "Lower : " << durations[0] << "micros\n";
	std::cout << "Upper : " << durations[durations.size() - 1] << "micros\n";
	std::cout << "Moyenne : " << std::accumulate(durations.begin(), durations.end(), 0) / durations.size() << "micros\n";

}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		return 0;
	}

	if (strcmp("AES", argv[1]) == 0) {
		return test_AES();
	}
	else if (strcmp("AESDecipher", argv[1]) == 0) {
		return test_AESDecipher();
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
	else if (strcmp("generalCypher", argv[1]) == 0) {
		return generalCypher(0);
	}
	else if (strcmp("generalDecypher", argv[1]) == 0) {
		return generalDecypher(0);
	}
	else if (strcmp("generalCypherAverage", argv[1]) == 0) {
		return generalCypherAverage();
	}
	else if (strcmp("generalDecypherAverage", argv[1]) == 0) {
		return generalDecypherAverage();
	}

}
