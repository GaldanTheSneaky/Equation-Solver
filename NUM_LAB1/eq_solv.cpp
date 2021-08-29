#include<cmath>
#include<iostream>
#include"eq_solv.h"
#include"PolStr.h"

const double GoldenRatio = (sqrt(5) - 1) / 2;

Result bisection(const char* equation, double eps, double lowerBound, double upperBound)
{
    const char* polEquation = CreatePolStr(equation, 0);
    double x = lowerBound;

    while (upperBound - lowerBound >= eps)
    {
        x = (lowerBound + upperBound) / 2;
        if (EvalPolStr(polEquation, x) * EvalPolStr(polEquation, lowerBound) < 0)
            upperBound = x;
        else
            lowerBound = x;
    }
    Result answer;
    answer.solution = x;
    answer.error = (upperBound - lowerBound) / 2;
    return answer;
}


Result chord(const char* equation, double eps, double lowerBound, double upperBound)
{
    const char* polEquation = CreatePolStr(equation, 0);
    double x = (lowerBound * EvalPolStr(polEquation, upperBound) - lowerBound * EvalPolStr(polEquation, lowerBound)) /
        (EvalPolStr(polEquation, upperBound) - EvalPolStr(polEquation, lowerBound));
    double prevX;

    do 
    {
        if (EvalPolStr(polEquation, x) * EvalPolStr(polEquation, lowerBound) < 0)
        {
            prevX = x;
            x = (x * EvalPolStr(polEquation, lowerBound) - lowerBound * EvalPolStr(polEquation, x))
                / (EvalPolStr(polEquation, lowerBound) - EvalPolStr(polEquation, x));
        }

        else
        {
            prevX = x;
            x = (x * EvalPolStr(polEquation, upperBound) - upperBound * EvalPolStr(polEquation, x))
                / (EvalPolStr(polEquation, upperBound) - EvalPolStr(polEquation, x));
        }
    } while (fabs(x - prevX) > eps);

    Result answer;
    answer.solution = x;
    answer.error = fabs(x - prevX);
    return answer;
}

Result goldenSection(const char* equation, double eps, double lowerBound, double upperBound)
{
    const char* polEquation = CreatePolStr(equation, 0);
    double lowerInterval = lowerBound + (1 - GoldenRatio) * (upperBound - lowerBound);
    double upperInterval= lowerBound + GoldenRatio * (upperBound - lowerBound);

    while (upperBound - lowerBound >= eps)
    {
        if (EvalPolStr(polEquation, lowerInterval) * EvalPolStr(polEquation, upperInterval) <=0)
        {
            lowerBound = lowerInterval;
            lowerInterval = upperInterval;
            upperInterval = lowerBound + GoldenRatio * (upperBound - lowerBound);
        }
        else
        {
            upperBound = upperInterval;
            upperInterval = lowerInterval;
            lowerInterval = lowerBound + (1 - GoldenRatio) * (upperBound - lowerBound);
        }
    }

    Result answer;
    answer.solution = (upperBound + lowerBound) / 2;
    answer.error = (upperBound - lowerBound) / 2;
    return answer;
}


Result newtonRaphson(const char* equation, double eps, double lowerBound, double upperBound)
{
    const char* polEquation = CreatePolStr(equation, 0);

    double x;
    if (EvalPolStr(polEquation, lowerBound) * EvalPolStr(polEquation, lowerBound, 2) > 0)
        x = lowerBound;
    else
        x = upperBound;

    double shift = EvalPolStr(polEquation, x) / EvalPolStr(polEquation, x, 1);
    while (fabs(shift) >= eps)
    {
        shift = EvalPolStr(polEquation, x) / EvalPolStr(polEquation, x, 1);
        x = x - shift;
    }

    Result answer;
    answer.solution = x;
    answer.error = shift;
    return answer;
}

Result fixedPointIteration(const char* equation, double eps, double lowerBound, double upperBound)
{
    const char* polEquation = CreatePolStr(equation, 0);
    double x = lowerBound;
    double preX;
    do
    {
        preX = x;
        x = EvalPolStr(polEquation, x);
    } while (fabs(preX - x) >= eps);

    Result answer;
    answer.solution = x;
    answer.error = fabs(preX - x);
    return answer;
}

Result combined(const char* equation, double eps, double lowerBound, double upperBound)
{
    const char* polEquation = CreatePolStr(equation, 0);
    double x;

    do
    {
        double lowerValue = EvalPolStr(polEquation, lowerBound);
        if (lowerValue * EvalPolStr(polEquation, lowerBound, 2) > 0)
        {
            upperBound = lowerBound - lowerValue * (upperBound - lowerBound) / (EvalPolStr(polEquation, upperBound) - lowerValue);
            lowerBound = lowerBound - lowerValue / EvalPolStr(polEquation, lowerBound, 1);
        }
        else
        {
            double upperValue = EvalPolStr(polEquation, upperBound);
            lowerBound = lowerBound - lowerValue * (upperBound - lowerBound) / (upperValue - lowerValue);
            upperBound = upperBound - upperValue / EvalPolStr(polEquation, upperBound, 1);
        }
         x = (lowerBound + upperBound) / 2;

    } while ((upperBound - lowerBound) / 2 >= eps);

    Result answer;
    answer.solution = x;
    answer.error = (upperBound - lowerBound) / 2;
    return answer;
}
