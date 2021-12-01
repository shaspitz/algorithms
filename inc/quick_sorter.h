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
	int QuickSort(std::vector<unsigned long>& vector, PivotMethod method);
private:
	int ChooseMedianOfThree(const std::vector<unsigned long>& vector);
	int PartitionSubroutine(std::vector<unsigned long>& vector);
};
