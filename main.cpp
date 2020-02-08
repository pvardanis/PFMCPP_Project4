/*
 Project 4 - Part 3 / 9
 Video: Chapter 4 Part 3 
 Casting

 Create a branch named Part3
 
    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.

 1) remove your functions that accepted a User-Defined Type
 
 2) remove any getValue() functions if you added them
 
 3) move all of your add/subtract/multiply/divide implementations out of the class.
  
 4) add user-defined conversion functions that convert to the numeric type your object holds.
        i.e. if your type holds an int, you'll need an operator int() function.
 
 5) make your member variable private.
         this conversion function should be the ONLY WAY to access the held value.
 
 6) clean up any forward declaration that you might have.
 
 7) make sure it compiles & runs without errors.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

 Wait for my code review.
 */

#include <iostream>

struct FloatType
{
    FloatType( float number_ ) : 
    value( new float(number_) )
    {}

    ~FloatType()
    {
        delete value;
        value = nullptr;
    }

    operator float*() {return value;}

    FloatType& add(float myNumber);
    FloatType& subtract(float myNumber);
    FloatType& multiply(float myNumber);
    FloatType& divide(float myNumber);

private:
    float* value = nullptr;
};

FloatType& FloatType::add(float myNumber)
{
    *value += myNumber;
    return *this;
}

FloatType& FloatType::subtract(float myNumber)
{
    *value -= myNumber;
    return *this;
}

FloatType& FloatType::multiply(float myNumber)
{
    *value *= myNumber;
    return *this;
}

FloatType& FloatType::divide(float myNumber)
{
    if (myNumber == 0.f)
    {
        std::cout << "You're dividing by float 0!" << std::endl;
    }
    *value /= myNumber; 
    return *this;
}

struct DoubleType
{
    DoubleType(double number_) : 
    value(new double(number_))
    {}

    ~DoubleType()
    {
        delete value;
        value = nullptr;
    }

    operator double*() {return value;}

    DoubleType& add(double myNumber);
    DoubleType& subtract(double myNumber);
    DoubleType& multiply(double myNumber);
    DoubleType& divide(double myNumber);

private:
    double* value = nullptr;
};

DoubleType& DoubleType::add(double myNumber)
{
    *value += myNumber;
    return *this;
}

DoubleType& DoubleType::subtract(double myNumber)
{
    *value -= myNumber;
    return *this;
}

DoubleType& DoubleType::multiply(double myNumber)
{
    *value *= myNumber;
    return *this;
}

DoubleType& DoubleType::divide(double myNumber)
{
    if (myNumber == 0.)
    {
        std::cout << "You're dividing by double 0!" << std::endl;
    }
    *value /= myNumber; 
    return *this;
}

struct IntType
{
    IntType(int number_) : 
    value(new int(number_))
    {}

    ~IntType()
    {
        delete value;
        value = nullptr;
    }

    operator int*() {return value;}

    IntType& add(int myNumber);
    IntType& subtract(int myNumber);
    IntType& multiply(int myNumber);
    IntType& divide(int myNumber);

private:
    int* value = nullptr;
};

IntType& IntType::add(int myNumber)
{
    *value += myNumber;
    return *this;
}

IntType& IntType::subtract(int myNumber)
{
    *value -= myNumber;
    return *this;
}

IntType& IntType::multiply(int myNumber)
{
    *value *= myNumber;
    return *this;
}

IntType& IntType::divide(int myNumber)
{
    if (myNumber == 0)
    {
        std::cout << "You're dividing by 0!" << std::endl;
        return *this; 
    }
    *value /= myNumber;
    return *this;
}

int main()
{
    // DoubleType dt1(5.45);
    // FloatType ft1(0.1f);
    // IntType it1(3);
    // std::cout << "ft1: adding 2.f and subtracting 'it1' from 'ft1', then multiply by 'dt1' results in the following value: " << *ft1.add(2.f).subtract(it1).multiply(dt1).value << std::endl;

    std::cout << "good to go!" << std::endl;
    return 0;    
}
