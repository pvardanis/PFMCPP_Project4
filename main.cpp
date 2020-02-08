/*
Project 4: Part 4 / 9
 Chapter 4 Part 7
 Function/Constructor Overloading

 Create a branch named Part4

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add pow() functions, and a powInternal() function to each of your UDTs
     a) your pow() functions should call powInternal()
     b) add a pow() whose argument type is the primitive your UDT owns.  the argument should be passed by copy.
     c) for each UDT in the file, your class should have pow() overloads that take that UDT as the function argument.
         the argument should be passed as const ref
         i.e. if you had UDTs named IntType, FloatType, DoubleType
             in your IntType class, you'd have:
                 pow(const IntType&),
                 pow(const FloatType&),
                 pow(const DoubleType&),
                 and pow(int)
     d) be sure to remember the rules about what member functions can be called on const objects.
             (const objects can only call their const member functions)
 
 2) your powInternal() function should do something like this in its body:    *val = std::pow( *val, arg );
         where 'arg' is the passed-in type, converted to whatever type your object is holding.
             if your UDT owns an int, then arg would be an int.
             if your UDT owns a float, then arg would be a float.
         std::pow's documentation is found here: https://en.cppreference.com/w/cpp/numeric/math/pow so be sure to include
             the proper header file listed there.
 
 3) modify the Point class below to have Constructors that accept your UDTs.
     a) make the Constructor's UDT arguments initialize the Point class's two member variables.
     b) overload the multiply() function so it can accept each of your UDTs.  I've added an implementation you can mimick for this function.
     c) add a toString() function to the Point class that prints out the x and y members via std::cout.
 
 4) clear out your old main()
     a) use your new pow() function in main for all of your types and print out the results.
     b) use the Point class in main and multiply some Point instances with your UDTs
     c) use the Point::toString() function to print out the results.
 
 
 5) make sure it compiles without errors.
 
 You will need to use Forward Declaration and out-of-class definitions to complete this.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

 Wait for my code review.
 */

struct Point
{
    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
private:
    float x{0}, y{0};
};



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

    operator float() {return *value;} 

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

    operator double() {return *value;} 

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

    operator int() {return *value;} 

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
    DoubleType dt1(5.45);
    FloatType ft1(0.1f);
    IntType it1(3);
    std::cout << "ft1: adding 2.f and subtracting 'it1' from 'ft1', then multiply by 'dt1' results in the following value: " << ft1.add(2.f).subtract(it1).multiply(static_cast<float> (dt1)) << std::endl;

    DoubleType dt2(0.); // let's see what happens here
    FloatType ft2(1.25f);
    IntType it2(10);
    std::cout << "it1: adding -5 and dividing with 'dt2' and multiplying by 'ft2' results in the following value: " << it2.add(static_cast<int> (ft2)).divide(0).divide(0) << std::endl;  // it returns 11 instead of 11.25 because it's IntType and returns *this

    std::cout << "good to go!" << std::endl;
    return 0;    
}
