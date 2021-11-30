#include "../inc/quick_sorter.h"



// TODO: implement quick sort with and without the extra memory requirement. 

unsigned long QuickSorter::ChooseFirstElement(std::vector<unsigned long>& vector) {
	return vector.front();
}

unsigned long QuickSorter::ChooseLastElement(std::vector<unsigned long>& vector) {
	return vector.back();
}

unsigned long QuickSorter::ChooseMedianOfThree(std::vector<unsigned long>& vector) {
	if (vector.size() < 3) return vector.front();
	auto firstElement = vector.front();
	auto middleElement = vector[vector.size() / 2];
	auto lastElement = vector.back();

	// Instead of some fancy, unreadable way to compute median of three, just cover the 6 cases.
	if ((firstElement <= middleElement) && (middleElement <= lastElement)) return middleElement;
	if ((firstElement <= lastElement) && (lastElement <= middleElement)) return lastElement; 
	if ((middleElement <= firstElement) && (firstElement <= lastElement)) return firstElement;
	if ((middleElement <= lastElement) && (lastElement <= firstElement)) return lastElement;  
	if ((lastElement <= firstElement) && (firstElement <= middleElement)) return firstElement;  
	return middleElement;
}
