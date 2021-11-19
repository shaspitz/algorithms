#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <math.h>

/// <summary>
/// Algorithms for integer multiplication. 
/// Uses strings due to the size of integers we're testing against. 
/// </summary>
class IntegerMultiplier {
public:
	std::string GradeSchoolMultiplication(const std::string& topInt, const std::string& bottomInt);
	std::string KaratsubaMultiply(const std::string& firstInt, const std::string& secondInt);
private:
	void AddValueToString(std::string& stringByRef, auto index, auto value);
	std::string AddIntStrings(std::string firstInt, std::string secondInt);
	std::string SubtractIntStrings(std::string firstInt, std::string secondInt);
	void PadWithZeros(std::string& firstInt, std::string& secondInt);
	std::string PowerOfTenAsString(std::string baseValue, auto exponentValue);
	std::pair<std::string, std::string> SplitInteger(std::string inputInt);
	size_t VerifyNumLength(const std::string& firstInt, const std::string& secondInt);
};

