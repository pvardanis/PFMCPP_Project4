/*
 Project 4 - Part 1 / 9
 video: Chapter 2 Part 7
 Returning Values tasks 

 Create a branch named Part1
 
 1) write 3 UDTs named FloatType, DoubleType, IntType.
 
 2) give each UDT the following member functions:
        add( lhs, rhs );
        subtract( lhs, rhs );
        multiply( lhs, rhs );
        divide( lhs, rhs );
 
 3) make them return the correct primitive type. e.g. if you're implementing the FloatType::add function, your implementation would start like this:
        float FloatType::add( float lhs, float rhs )
 
 4) declare a few instances of each class in main() and call the member functions with the appropriate arguments.
        FloatType ft;
        auto result = ft.add(3.2f, 23.f );
 
 5) print out those results using std::cout:
        std::cout "result of ft.add(): " << result << std::endl;
 
 6) After you finish defining each type/function, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

 Wait for my code review.
 */

#include <iostream>

struct FloatType
{
    float add( float lhs, float rhs );
    float subtract( float lhs, float rhs );
    float multiply( float lhs, float rhs );
    float divide( float lhs, float rhs );
};

float FloatType::add( float lhs, float rhs )
{
    return lhs + rhs;
}

float FloatType::subtract( float lhs, float rhs )
{
    return lhs - rhs;
}

float FloatType::multiply( float lhs, float rhs )
{
    return lhs * rhs;
}

float FloatType::divide( float lhs, float rhs )
{
    return lhs / rhs;
}

struct DoubleType
{
    double add( double lhs, double rhs );
    double subtract( double lhs, double rhs );
    double multiply( double lhs, double rhs );
    double divide( double lhs, double rhs );
};

double DoubleType::add( double lhs, double rhs )
{
    return lhs + rhs;
}

double DoubleType::subtract( double lhs, double rhs )
{
    return lhs - rhs;
}

double DoubleType::multiply( double lhs, double rhs )
{
    return lhs * rhs;
}

double DoubleType::divide( double lhs, double rhs )
{
    return lhs / rhs;
}

struct IntType
{
    int add( int lhs, int rhs );
    int subtract( int lhs, int rhs );
    int multiply( int lhs, int rhs );
    int divide( int lhs, int rhs );
};

int IntType::add( int lhs, int rhs )
{
    return lhs + rhs;
}

int IntType::subtract( int lhs, int rhs )
{
    return lhs - rhs;
}

int IntType::multiply( int lhs, int rhs )
{
    return lhs * rhs;
}

int IntType::divide( int lhs, int rhs )
{
    if (rhs == 0)
    {
        std::cout << "Cannot divide by zero!" << std::endl;
    }
    return lhs / rhs;
}

int main()
{
    FloatType ft;
    auto ftAdd = ft.add( 5.25f, 4.75f );
    std::cout << "result of ft.add(): " << ftAdd << std::endl;
    auto ftDivide = ft.divide( 2.25f, 0.f );
    std::cout << "result of ft.divide(): " << ftDivide << std::endl;


    DoubleType dt;
    auto dtSubtract = dt.subtract( 5.2597, -1.75256 );
    std::cout << "result of dt.subtract(): " << dtSubtract << std::endl;
    auto dtDivide = dt.divide( 25.45, 0. );
    std::cout << "result of dt.divide(): " << dtDivide << std::endl;

    IntType it;
    auto itMultiply = it.multiply( 25, -4 );
    std::cout << "result of it.multiply(): " << itMultiply << std::endl;
    auto itDivide = it.divide( 22, 0 );
    std::cout << "result of it.divide(): " << itDivide << std::endl;

    std::cout << "good to go!" << std::endl;
}
