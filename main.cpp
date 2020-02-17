
#include <iostream>
/*
Project 4: Part 5 / 9
 video: Chapter 5 Part 2
 Operator Overloading.

 Create a branch named Part5

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) replace the add/subtract/multiply/etc functions with overloaded math operators 
        e.g. add() would become operator+=() because it modifies the internal heap-allocated object.
 
 2) Your overloaded operators should only take primitives, passed by value.
 
 3) don't delete your conversion functions.
         if you removed them in Chapter 4 Part 7, put them back in.
         uncomment them if you commented them in Chapter 4 Part 7
 
 4) your main() function should be the same as Chapter 4 Part 7
     
 5) if your Chapter4 Part7 task didn't use any [+ - * or /], 
         add some in and fix the build errors that might result via the techniques you have learned in the previous weeks (hint: casting)
         i.e.
 */

 /*
 6) compile/link/run to make sure you don't have any errors
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

 Wait for my code review.
 */

#include <iostream>
#include <cmath>

struct IntType;
struct FloatType;
struct DoubleType;

#if false

namespace Example
{
    int main()
    {
        FloatType floatNum(4.3f);
        IntType intNum(2);
        IntType intNum2(6);

        /* 
        if you previously had a line like this demonstrating chaining:
            
            intNum.add(3).add(4.5f).divide(floatNum); 
        it should become:
        */
        intNum += 3;
        intNum += 4.5f;
        intNum /= floatNum;
        std::cout << "intNum: " << intNum << std::endl;

        intNum = 2 + (intNum2 - 4) + floatNum / 2.3;
        std::cout << "intNum: " << intNum << std::endl;
        
        return 0;
    }
}
#endif

struct Point
{
    Point(float, float);

    Point& multiply(float);
    Point& multiply(const IntType&);
    Point& multiply(const FloatType&);
    Point& multiply(const DoubleType&);

    void toString();
    
private:
    float x{0}, y{0};
};

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

    operator float() const {return *value;} 
    
    FloatType& operator+=(float myNumber);
    FloatType& operator-=(float myNumber);
    FloatType& operator*=(float myNumber);
    FloatType& operator/=(float myNumber);
    
    FloatType& pow(float myNumber);
    FloatType& pow(const IntType& myNumber);
    FloatType& pow(const FloatType& myNumber);
    FloatType& pow(const DoubleType& myNumber);

private:
    float* value = nullptr;
    FloatType& powInternal(float myNumber);
};

FloatType& FloatType::operator+=(float myNumber)
{
    *value += myNumber;
    return *this;
}

FloatType& FloatType::operator-=(float myNumber)
{
    *value -= myNumber;
    return *this;
}

FloatType& FloatType::operator*=(float myNumber)
{
    *value /= myNumber;
    return *this;
}

FloatType& FloatType::operator/=(float myNumber)
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

    operator double() const {return *value;} 

    DoubleType& operator+=(double myNumber);
    DoubleType& operator-=(double myNumber);
    DoubleType& operator*=(double myNumber);
    DoubleType& operator/=(double myNumber);

    DoubleType& pow(double myNumber);
    DoubleType& pow(const IntType& myNumber);
    DoubleType& pow(const FloatType& myNumber);
    DoubleType& pow(const DoubleType& myNumber);

private:
    double* value = nullptr;
    DoubleType& powInternal(double myNumber);
};

DoubleType& DoubleType::operator+=(double myNumber)
{
    *value += myNumber;
    return *this;
}

DoubleType& DoubleType::operator-=(double myNumber)
{
    *value -= myNumber;
    return *this;
}

DoubleType& DoubleType::operator*=(double myNumber)
{
    *value /= myNumber;
    return *this;
}

DoubleType& DoubleType::operator/=(double myNumber)
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

    operator int() const {return *value;} 

    IntType& operator+=(int myNumber);
    IntType& operator-=(int myNumber);
    IntType& operator*=(int myNumber);
    IntType& operator/=(int myNumber);

    IntType& pow(int myNumber);
    IntType& pow(const IntType& myNumber);
    IntType& pow(const FloatType& myNumber);
    IntType& pow(const DoubleType& myNumber);

private:
    int* value = nullptr;
    IntType& powInternal(int myNumber);
};

IntType& IntType::operator+=(int myNumber)
{
    *value += myNumber;
    return *this;
}

IntType& IntType::operator-=(int myNumber)
{
    *value -= myNumber;
    return *this;
}

IntType& IntType::operator*=(int myNumber)
{
    *value /= myNumber;
    return *this;
}

IntType& IntType::operator/=(int myNumber)
{
     if (myNumber == 0)
    {
        std::cout << "You're dividing by 0!" << std::endl;
        return *this; 
    }
    *value /= myNumber;
    return *this;
}

Point::Point(float _x, float _y) : x(_x), y(_y) { }

Point& Point::multiply(float m)
{
    x *= m;
    y *= m;
    return *this;
}

Point& Point::multiply(const IntType& myNumber)
{
    return multiply(static_cast<float>(myNumber)); // this needs to be here? 
}

Point& Point::multiply(const FloatType& myNumber)
{
    return multiply(static_cast<float>(myNumber));;
}

Point& Point::multiply(const DoubleType& myNumber)
{
    return multiply(static_cast<float>(myNumber));;
}

void Point::toString()
{
    std::cout << "x: " << x << ", y: " << y << std::endl;
}

/*
pow implementations
*/

FloatType& FloatType::powInternal(float myNumber)
{
    *value = std::pow(*value, myNumber);
    return *this;
}

FloatType& FloatType::pow(float myNumber)
{
    return powInternal(myNumber);
}

FloatType& FloatType::pow(const IntType& myNumber)
{
    return powInternal(myNumber);
}

FloatType& FloatType::pow(const FloatType& myNumber)
{
    return powInternal(myNumber);
}

FloatType& FloatType::pow(const DoubleType& myNumber)
{
    return powInternal(static_cast<float>(myNumber));
}

DoubleType& DoubleType::powInternal(double myNumber)
{
    *value = std::pow(*value, myNumber);
    return *this;
}

DoubleType& DoubleType::pow(double myNumber)
{
    return powInternal(myNumber);
}

DoubleType& DoubleType::pow(const IntType& myNumber)
{
    return powInternal(myNumber);
}

DoubleType& DoubleType::pow(const FloatType& myNumber)
{
    return powInternal(static_cast<double>(myNumber));
}

DoubleType& DoubleType::pow(const DoubleType& myNumber)
{
    return powInternal(myNumber);
}

IntType& IntType::powInternal(int myNumber)
{
    *value = static_cast<int>(std::pow(*value, myNumber));
    return *this;
}

IntType& IntType::pow(int myNumber)
{
    return powInternal(myNumber);
}

IntType& IntType::pow(const IntType& myNumber)
{
    return powInternal(myNumber);
}

IntType& IntType::pow(const FloatType& myNumber)
{
    return powInternal(static_cast<int>(myNumber));
}

IntType& IntType::pow(const DoubleType& myNumber)
{
    return powInternal(static_cast<int>(myNumber));
}

int main()
{
    // test pow
    IntType it1(4);
    FloatType ft1(2.25f);
    DoubleType dt1(5.4);

    IntType it2(2);
    FloatType ft2(5.5f);
    DoubleType dt2(1.25);

    IntType it3(3);
    FloatType ft3(1.15f);
    DoubleType dt3(3.25); 

    // // I put small numbers to prevent overflow

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

    Point p2(itp, static_cast<float>(dtp));
    std::cout << "\np2 values: " << std::endl;
    p2.toString();
    p2.multiply(ftp); 
    std::cout << "\np2 values after multiplication with 5.25f: " << std::endl;
    p2.toString();

    Point p3(ftp, static_cast<float>(dtp));
    std::cout << "\np3 values: " << std::endl;
    p3.toString();
    p3.multiply(itp); 
    std::cout << "\np3 values after multiplication with 4: " << std::endl;
    p3.toString();

    return 0;    
}
