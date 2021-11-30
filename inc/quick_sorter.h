#pragma once

#include <functional>

/// <summary>
/// Implements the quick sort algorithm using various methods of choosing a pivot element.
/// </summary>
class QuickSorter {
public: 
	enum class PivotMethod {
		ChooseFirst,
		ChooseLast,
		ChooseMedianOfThree,
	};
	unsigned long QuickSort(std::vector<unsigned long>& vector, PivotMethod method);
// TODO, remove comment here. 
//private:
	unsigned long QuickSortWithCallback(std::vector<unsigned long>& vector,
		std::function<unsigned long(std::vector<unsigned long>& vector)> choosePivotCallback);
	unsigned long ChooseFirstElement(std::vector<unsigned long>& vector);
	unsigned long ChooseLastElement(std::vector<unsigned long>& vector);
	unsigned long ChooseMedianOfThree(std::vector<unsigned long>& vector);
};
