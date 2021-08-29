#pragma once

struct Result
{
	double solution, error;
};

Result bisection(const char* equation, double eps, double lowerBound, double upperBound);

Result chord(const char* equation, double eps, double lowerBound, double upperBound);

Result goldenSection(const char* equation, double eps, double lowerBound, double upperBound);

Result newtonRaphson(const char* equation, double eps, double lowerBound, double upperBound);

Result fixedPointIteration(const char* equation, double eps, double lowerBound, double upperBound);

Result combined(const char* equation, double eps, double lowerBound, double upperBound);