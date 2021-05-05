/**
 * Projet tutoré SquareAttack
 **/

#include "squareAttack.h"
#include "keyExpension.h"
#include <algorithm>
#include <chrono>
#include <numeric>

int test_setup() {

	key cypherKey = { 0xaa, 0x00, 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 };

	lambdaSet set = setup(cypherKey,3);

	//printDeltaSet(set);

	std::vector<key> keySet;
	for (size_t setindex = 0; setindex < set.size(); setindex++) {
		keySet.push_back(ParseTableau(set[setindex]));
	}

	for (size_t posIndex = 0; posIndex < 16; posIndex++) {
		uint8_t xorBuffer = 0x00;
		for (size_t setindex = 0; setindex < keySet.size(); setindex++) {
			xorBuffer ^= keySet[setindex][posIndex];
		}
		if (xorBuffer == 0x00) {
			std::cout << "All bytes xored from encrypted lambdaSet on pos " << posIndex + 1 << " is equal to 0x00" << std::endl;
		}
	}

	return 0;
}

int test_4round() {

	key cypherKey = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

	std::vector<lambdaSet> neededLambdaSet;

	lambdaSet set = setup(cypherKey, 4);

	neededLambdaSet.push_back(set);

	size_t currentSet = 0;

	key guessedKey;

	for (size_t posIndex = 0; posIndex < 16; posIndex++) {

		std::vector<uint8_t> currentGuesses = checkAllKeyGuess(neededLambdaSet[currentSet], posIndex);

		if (currentGuesses.size() == 0) {
			std::cout << "Something went wrong" << std::endl;
			return 1;
		}

		while (currentGuesses.size() > 1)
		{
			std::vector<uint8_t> buffer;
			currentSet++;
			if (currentSet = neededLambdaSet.size()) {
				neededLambdaSet.push_back(setup(cypherKey, 4));
			}

			std::vector<uint8_t> diff = checkAllKeyGuess(neededLambdaSet[currentSet], posIndex);

			for (size_t i = 0; i < currentGuesses.size(); i++) {
				if (std::count(diff.begin(), diff.end(), currentGuesses[i]) == 1) {
					buffer.push_back(currentGuesses[i]);
				}
			}

			currentGuesses = buffer;
		}

		currentSet = 0;
		guessedKey.push_back(currentGuesses[0]);
	}
	/*std::cout << "Cypher key : ";
	printVector(cypherKey);
	guessedKey = KeyExpensionReverse(guessedKey, 4);
	std::cout << "Guessed key : ";
	printVector(guessedKey);*/

	return 0;
}

int test_4roundAverage() {
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;

	std::vector<int> durations;
	int tot = 150;

	for (size_t i = 0; i < tot; i++) {
		auto t1 = high_resolution_clock::now();
		test_4round();
		auto t2 = high_resolution_clock::now();
		durations.push_back(duration_cast<milliseconds>(t2 - t1).count());
	}

	std::sort(durations.begin(), durations.end());

	std::cout << "Nombre d'iterations : " << tot << "\n\n";
	std::cout << "1er Quartile : " << durations[durations.size() / 4] << "ms\n";
	std::cout << "Mediane : " << durations[durations.size() / 2] << "ms\n";
	std::cout << "3eme Quartile : " << durations[durations.size()*3 / 4] << "ms\n";
	std::cout << "Lower : " << durations[0] << "ms\n";
	std::cout << "Upper : " << durations[durations.size()-1] << "ms\n";
	std::cout << "Moyenne : " << std::accumulate(durations.begin(), durations.end(), 0) / durations.size() << "ms\n";

}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		return 0;
	}

	if (strcmp("setup", argv[1]) == 0) {
		return test_setup();
	}
	else if (strcmp("4round", argv[1]) == 0) {
		return test_4round();
	}
	else if (strcmp("4roundAverage", argv[1]) == 0) {
		return test_4roundAverage();
	}

	return 0;
}