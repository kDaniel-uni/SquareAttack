/**
 * Projet tutoré SquareAttack
 **/

#include "tools.h"

void printTableau(tableau2D tab) {
	for (auto it = tab.begin(); it != tab.end(); it++)
		printVector(*it);
}

void printVector(std::vector<uint8_t> vec) {

	for (auto it = vec.begin(); it != vec.end(); it++)
		std::cout << hex(*it) << " ";
	std::cout << std::endl;

}