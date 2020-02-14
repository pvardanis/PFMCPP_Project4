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

#include <iostream>
#include <cmath>

struct IntType;
struct DoubleType;

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

    FloatType& pow(float myNumber);
    FloatType& pow(const IntType& myNumber);
    FloatType& pow(const FloatType& myNumber);
    FloatType& pow(const DoubleType& myNumber);

private:
    float* value = nullptr;
    FloatType& powInternal(float myNumber);
    FloatType& powInternal(const IntType& myNumber);
    FloatType& powInternal(const FloatType& myNumber);
    FloatType& powInternal(const DoubleType& myNumber);
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

    DoubleType& pow(double myNumber);
    DoubleType& pow(const IntType& myNumber);
    DoubleType& pow(const FloatType& myNumber);
    DoubleType& pow(const DoubleType& myNumber);

private:
    double* value = nullptr;
    DoubleType& powInternal(double myNumber);
    DoubleType& powInternal(const IntType& myNumber);
    DoubleType& powInternal(const FloatType& myNumber);
    DoubleType& powInternal(const DoubleType& myNumber);
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

    IntType& pow(int myNumber);
    IntType& pow(const IntType& myNumber);
    IntType& pow(const FloatType& myNumber);
    IntType& pow(const DoubleType& myNumber);

private:
    int* value = nullptr;
    IntType& powInternal(int myNumber);
    IntType& powInternal(const IntType& myNumber);
    IntType& powInternal(const FloatType& myNumber);
    IntType& powInternal(const DoubleType& myNumber);
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

/* 
Point implementation
*/
struct Point
{
    Point(const IntType& myNumber1, const FloatType& myNumber2);
    Point(const IntType& myNumber1, const DoubleType& myNumber2);
    Point(const FloatType& myNumber1, const DoubleType& myNumber2);

    Point& multiply(float m);
    Point& multiply(const IntType& myNumber);
    Point& multiply(const FloatType& myNumber);
    Point& multiply(const DoubleType& myNumber);

    void toString();
    
private:
    float x{0}, y{0};
};

Point::Point(const IntType& myNumber1, const FloatType& myNumber2) : 
x(static_cast<float>(const_cast<IntType&>(myNumber1))), 
y(const_cast<FloatType&>(myNumber2)) 
{ }

Point::Point(const IntType& myNumber1, const DoubleType& myNumber2) : 
x(static_cast<float>(const_cast<IntType&>(myNumber1))), 
y(static_cast<float>(const_cast<DoubleType&>(myNumber2))) 
{ }

Point::Point(const FloatType& myNumber1, const DoubleType& myNumber2) : 
x(const_cast<FloatType&>(myNumber1)), 
y(static_cast<float>(const_cast<DoubleType&>(myNumber2))) 
{ }

Point& Point::multiply(float m)
{
    x *= m;
    y *= m;
    return *this;
}

Point& Point::multiply(const IntType& myNumber)
{
    x *= static_cast<float>(const_cast<IntType&>(myNumber));
    y *= static_cast<float>(const_cast<IntType&>(myNumber));
    return *this;
}

Point& Point::multiply(const FloatType& myNumber)
{
    x *= static_cast<float>(const_cast<FloatType&>(myNumber));
    y *= static_cast<float>(const_cast<FloatType&>(myNumber));
    return *this;
}

Point& Point::multiply(const DoubleType& myNumber)
{
    x *= static_cast<float>(const_cast<DoubleType&>(myNumber));
    y *= static_cast<float>(const_cast<DoubleType&>(myNumber));
    std::cout << x;
    return *this;
}

void Point::toString()
{
    std::cout << "x: " << x << ", y: " << y << std::endl;
}

/*
pow implementations
*/

FloatType& FloatType::pow(float myNumber)
{
    return powInternal(myNumber);
}

FloatType& FloatType::powInternal(float myNumber)
{
    *value = std::pow(*value, myNumber);
    return *this;
}

FloatType& FloatType::pow(const IntType& myNumber)
{
    return powInternal(myNumber);
}

FloatType& FloatType::powInternal(const IntType& myNumber)
{
    *value = std::pow(*value, static_cast<float>(const_cast<IntType&>(myNumber)));
    return *this; 
}

FloatType& FloatType::pow(const FloatType& myNumber)
{
    return powInternal(myNumber);
}

FloatType& FloatType::powInternal(const FloatType& myNumber)
{
    *value = std::pow(*value, static_cast<float>(const_cast<FloatType&>(myNumber)));
    return *this; 
}

FloatType& FloatType::pow(const DoubleType& myNumber)
{
    return powInternal(myNumber);
}

FloatType& FloatType::powInternal(const DoubleType& myNumber)
{
    *value = std::pow(*value, static_cast<float>(const_cast<DoubleType&>(myNumber)));
    return *this; 
}

DoubleType& DoubleType::pow(double myNumber)
{
    return powInternal(myNumber);
}

DoubleType& DoubleType::powInternal(double myNumber)
{
    *value = std::pow(*value, myNumber);
    return *this;
}

DoubleType& DoubleType::pow(const IntType& myNumber)
{
    return powInternal(myNumber);
}

DoubleType& DoubleType::powInternal(const IntType& myNumber)
{
    *value = std::pow(*value, static_cast<double>(const_cast<IntType&>(myNumber)));
    return *this;
}

DoubleType& DoubleType::pow(const FloatType& myNumber)
{
    return powInternal(myNumber);
}

DoubleType& DoubleType::powInternal(const FloatType& myNumber)
{
    *value = std::pow(*value, static_cast<double>(const_cast<FloatType&>(myNumber)));
    return *this;
}

DoubleType& DoubleType::pow(const DoubleType& myNumber)
{
    return powInternal(myNumber);
}

DoubleType& DoubleType::powInternal(const DoubleType& myNumber)
{
    *value = std::pow(*value, static_cast<double>(const_cast<DoubleType&>(myNumber)));
    return *this;
}

IntType& IntType::pow(int myNumber)
{
    return powInternal(myNumber);
}

IntType& IntType::powInternal(int myNumber)
{
    *value = std::pow(*value, myNumber);
    return *this;
}

IntType& IntType::pow(const IntType& myNumber)
{
    return powInternal(myNumber);
}

IntType& IntType::powInternal(const IntType& myNumber)
{
    *value = std::pow(*value, static_cast<int>(const_cast<IntType&>(myNumber)));
    return *this;
}

IntType& IntType::pow(const FloatType& myNumber)
{
    return powInternal(myNumber);
}

IntType& IntType::powInternal(const FloatType& myNumber)
{
    *value = std::pow(*value, static_cast<int>(const_cast<FloatType&>(myNumber)));
    return *this;
}

IntType& IntType::pow(const DoubleType& myNumber)
{
    return powInternal(myNumber);
}

IntType& IntType::powInternal(const DoubleType& myNumber)
{
    *value = std::pow(*value, static_cast<int>(const_cast<DoubleType&>(myNumber)));
    return *this;
}

int main()
{
    // test pow
    IntType it1(4);
    FloatType ft1(2.25f);
    FloatType dt1(5.4);

    IntType it2(2);
    FloatType ft2(5.5f);
    FloatType dt2(1.25);

    IntType it3(3);
    FloatType ft3(1.15f);
    FloatType dt3(3.25); 

    // I put small numbers to prevent overflow

    std::cout << "Test IntType: " << std::endl;
    std::cout << "4 ^ 2.25f ^ 5.4  = " << it1.pow(ft1).pow(dt1) << std::endl; 

    std::cout << "\nTest FloatType: " << std::endl;
    std::cout << "5.5f ^ 2 ^ 1.25  = " << ft2.pow(it2).pow(dt2) << std::endl;

    std::cout << "\nTest DoubleType: " << std::endl;
    std::cout << "3.25 ^ 1.15f ^ 3  = " << dt3.pow(ft3).pow(it3) << std::endl;
    std::cout << "\n" << std::endl;

    // test Point
    IntType itp(4);
    FloatType ftp(5.25f);
    DoubleType dtp(2.25);

    Point p1(itp, ftp);
    std::cout << "p1 values: " << std::endl;
    p1.toString();
    p1.multiply(dtp); 
    std::cout << "\np1 values after multiplication with 2.25: " << std::endl;
    p1.toString();

    Point p2(itp, dtp);
    std::cout << "\np2 values: " << std::endl;
    p2.toString();
    p2.multiply(ftp); 
    std::cout << "\np2 values after multiplication with 5.25f: " << std::endl;
    p2.toString();

    Point p3(ftp, dtp);
    std::cout << "\np3 values: " << std::endl;
    p3.toString();
    p3.multiply(itp); 
    std::cout << "\np3 values after multiplication with 4: " << std::endl;
    p3.toString();

    return 0;    
}
