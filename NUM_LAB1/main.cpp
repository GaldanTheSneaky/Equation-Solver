#include<iostream>
#include<string>
#include<sstream>
#include <fstream>
#include"eq_solv.h"
#include"PolStr.h"


int main()
{
	std::string buffer;

	std::ifstream inputFile("input.txt");

	if (!inputFile.is_open())
		std::cout << "File cannot be open!" << std::endl;
	else
	{
		std::getline(inputFile, buffer);
		std::istringstream methodBuffer(buffer);
		int chosen_method;
		methodBuffer >> chosen_method;

		std::string equation;
		std::getline(inputFile, equation);

		std::getline(inputFile, buffer);
		std::istringstream intervalBuffer(buffer);
		double lowerBound, upperBound;
		intervalBuffer >> lowerBound >> upperBound;

		std::getline(inputFile, buffer);
		std::istringstream epsBuffer(buffer);
		double eps;
		epsBuffer >> eps;

		inputFile.close();
		std::ofstream outputFile("output.txt");

		switch (chosen_method)
		{
			case 1:
			{
				Result answer;
				answer = bisection(equation.c_str(), eps, lowerBound, upperBound);

				outputFile << answer.solution << std::endl;
				const char* polEquation = CreatePolStr(equation.c_str(), 0);
				outputFile << EvalPolStr(polEquation, answer.solution) << std::endl;

				outputFile << answer.error << std::endl;
			} break;

			case 2:
			{
				Result answer;
				answer = chord(equation.c_str(), eps, lowerBound, upperBound);

				outputFile << answer.solution << std::endl;
				const char* polEquation = CreatePolStr(equation.c_str(), 0);
				outputFile << EvalPolStr(polEquation, answer.solution) << std::endl;

				outputFile << answer.error << std::endl;
			} break;

			case 3:
			{
				Result answer;
				answer = goldenSection(equation.c_str(), eps, lowerBound, upperBound);

				outputFile << answer.solution << std::endl;
				const char* polEquation = CreatePolStr(equation.c_str(), 0);
				outputFile << EvalPolStr(polEquation, answer.solution) << std::endl;

				outputFile << answer.error << std::endl;
			} break;

			case 4:
			{
				Result answer;
				answer = newtonRaphson(equation.c_str(), eps, lowerBound, upperBound);

				outputFile << answer.solution << std::endl;
				const char* polEquation = CreatePolStr(equation.c_str(), 0);
				outputFile << EvalPolStr(polEquation, answer.solution) << std::endl;

				outputFile << answer.error << std::endl;
			} break;

			case 5:
			{
				Result answer;
				answer = fixedPointIteration(equation.c_str(), eps, lowerBound, upperBound);

				outputFile << answer.solution << std::endl;
				const char* polEquation = CreatePolStr(equation.c_str(), 0);
				outputFile << EvalPolStr(polEquation, answer.solution) << std::endl;

				outputFile << answer.error << std::endl;
			} break;

			case 6:
			{
				Result answer;
				answer = combined(equation.c_str(), eps, lowerBound, upperBound);

				outputFile << answer.solution << std::endl;
				const char* polEquation = CreatePolStr(equation.c_str(), 0);
				outputFile << EvalPolStr(polEquation, answer.solution) << std::endl;

				outputFile << answer.error << std::endl;
			} break;
		}

	}

	return 0;
}