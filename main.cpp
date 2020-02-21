
#include <iostream>
/*
Project 4 - Part 6 / 9
Video: Chapter 5 Part 3
 
Create a branch named Part6
 
 Lambdas
 
    Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add two member functions named "apply()" to your Heap-Allocated Numeric Type wrapper.
         both apply() functions should work with chaining
 
 2) One of the apply() functions should takes a std::function<> object as the function argument that returns *this;
 
 3) the other apply() function should take a function pointer that returns void.
 
 4) Make both of the member functions's Callable Function Parameter use your owned object as it's single parameter.
         e.g. if you manage your owned object via std::unique_ptr<T>, you'd use this for your std::function argument:
             std::function< OwnedT&(std::unique_ptr<T>&)>
             
         if you managed your owned object via a raw pointer, you'd use this for your std::function argument:
             std::function<OwnedT&(T&)>    
 
 5) call that Callable Function Parameter in the apply() member function.
         be sure to practice safe std::function usage (make sure it's not a nullptr function being called)
 
 6) Call your member function twice:
         a) once with a lambda as the argument
         b) once with a free function as the argument.
         If this confuses you, rewatch the video where I pass a free function in to a function that wants a function pointer
 
 8) Make your lambda/free function update the value of your held object
 
 9) use std::cout statements to print out the results of calling apply()
 
build/run to make sure you don't have any errors

Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */

//example:

#include <functional>
#include <memory>
namespace Example {
//====================================================


// 1) 
/*
note: this example omits the math operators.
your task should still include them.
*/
struct Int
{
    // Int(int v) : ui( new int(v) ) { }        //old style of member init with explicit 'new'
    Int(int v) : ui( std::make_unique<int>(v) ) {} //new style of member init with make_unique instead
    
    Int& apply( std::function<Int&(std::unique_ptr<int>&)> f)   // 1), 2), 4)
    {
        std::cout << "std::function<>" << std::endl;

        if( f )
        {
            return f(ui);  // 5)
        }
        
        return *this; // 1)
    }
    
    Int& apply( void(*f)(std::unique_ptr<int>&) ) // 1), 3), 4) 
    {
        std::cout << "free function" << std::endl;

        if( f )
            f(ui); // 5)
        
        return *this; // 1)
    }
    
    operator int() { return *ui; }
private:
    std::unique_ptr<int> ui;
};
//====================================================
void cube( std::unique_ptr<int>& ui )
{
    int& i = *ui;
    i = i * i * i; // 7)
}
//====================================================
int main()
{
    Int i(3);
    
    std::cout << "Int: " << i << std::endl;
    
    i.apply( [&](std::unique_ptr<int>& ui) -> Int& // 6a)
            {
                *ui = *ui * *ui; // 7)
                return i;
            });
    
    std::cout << "square Int (lambda): " << i << std::endl;  // 8)
    
    i.apply( cube ); // 6b)
    
    std::cout << "cube Int: " << i << std::endl; // 9)
    
    return 0;
}
} //end namespace Example

#include <iostream>
#include <cmath>

struct IntType;
struct FloatType;
struct DoubleType;

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

// freeFunc

void updateValueFloat(std::unique_ptr<float>& value)
{
    *value += 5.f;
}

void updateValueDouble(std::unique_ptr<double>& value)
{
    *value += 5.;
}

void updateValueInt(std::unique_ptr<int>& value)
{
    *value += 5;
}

struct FloatType
{
    FloatType(float number_) : value(std::make_unique<float>(number_)) {} 
    
    FloatType& apply(std::function<FloatType&(std::unique_ptr<float>&)> f)   // 1), 2), 4)
    {
        std::cout << "std::function<>" << std::endl;

        if(f)
        {
            return f(value);  // 5)
        }
        
        return *this; // 1)
    }
    
    FloatType& apply(void(*f)(std::unique_ptr<float>&)) // 1), 3), 4) 
    {
        std::cout << "free function" << std::endl;

        if(f)
            f(value); // 5)
        
        return *this; // 1)
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
    std::unique_ptr<float> value;
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
    *value *= myNumber;
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
    DoubleType(double number_) : value(std::make_unique<double>(number_)) {} 
    
    DoubleType& apply(std::function<DoubleType&(std::unique_ptr<double>&)> f)   // 1), 2), 4)
    {
        std::cout << "std::function<>" << std::endl;

        if(f)
        {
            return f(value);  // 5)
        }
        
        return *this; // 1)
    }
    
    DoubleType& apply(void(*f)(std::unique_ptr<double>&)) // 1), 3), 4) 
    {
        std::cout << "free function" << std::endl;

        if(f)
            f(value); // 5)
        
        return *this; // 1)
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
    std::unique_ptr<double> value;
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
    *value *= myNumber;
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
    IntType(int number_) : value(std::make_unique<int>(number_)) {} 
    
    IntType& apply(std::function<IntType&(std::unique_ptr<int>&)> f)   // 1), 2), 4)
    {
        std::cout << "std::function<>" << std::endl;

        if(f)
        {
            return f(value);  // 5)
        }
        
        return *this; // 1)
    }
    
    IntType& apply(void(*f)(std::unique_ptr<int>&)) // 1), 3), 4) 
    {
        std::cout << "free function" << std::endl;

        if(f)
            f(value); // 5)
        
        return *this; // 1)
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
    std::unique_ptr<int> value;
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
    *value *= myNumber;
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
    Example::main();
    // // test pow
    // IntType it1(4);
    // FloatType ft1(2.25f);
    // DoubleType dt1(5.4);

    // IntType it2(2);
    // FloatType ft2(5.5f);
    // DoubleType dt2(1.25);

    // IntType it3(3);
    // FloatType ft3(1.15f);
    // DoubleType dt3(3.25); 

    // // // I put small numbers to prevent overflow

    // std::cout << "Test IntType: " << std::endl;
    // std::cout << "4 ^ 2.25f ^ 5.4  = " << it1.pow(ft1).pow(dt1) << std::endl; 

    // std::cout << "\nTest FloatType: " << std::endl;
    // std::cout << "5.5f ^ 2 ^ 1.25  = " << ft2.pow(it2).pow(dt2) << std::endl;

    // std::cout << "\nTest DoubleType: " << std::endl;
    // std::cout << "3.25 ^ 1.15f ^ 3  = " << dt3.pow(ft3).pow(it3) << std::endl;
    // std::cout << "\n" << std::endl;

    // // test Point
    // IntType itp(4);
    // FloatType ftp(5.25f);
    // DoubleType dtp(2.25);

    // Point p1(itp, ftp);
    // std::cout << "p1 values: " << std::endl;
    // p1.toString();
    // p1.multiply(dtp); 
    // std::cout << "\np1 values after multiplication with 2.25: " << std::endl;
    // p1.toString();

    // Point p2(itp, static_cast<float>(dtp));
    // std::cout << "\np2 values: " << std::endl;
    // p2.toString();
    // p2.multiply(ftp); 
    // std::cout << "\np2 values after multiplication with 5.25f: " << std::endl;
    // p2.toString();

    // Point p3(ftp, static_cast<float>(dtp));
    // std::cout << "\np3 values: " << std::endl;
    // p3.toString();
    // p3.multiply(itp); 
    // std::cout << "\np3 values after multiplication with 4: " << std::endl;
    // p3.toString();
    FloatType ft(2.5f);
    
    std::cout << "FloatType: " << ft << std::endl;
    
    ft.apply([&](std::unique_ptr<float>& value) -> FloatType&
            {
                *value *= 2;
                return ft;
            });
    
    std::cout << "Multiply by 2 FloatType (lambda): " << ft << std::endl;

    ft.apply(updateValueFloat);
    std::cout << "updateValueFloat (adds 5): " << ft << std::endl;

    DoubleType dt(5.75);
    
    std::cout << "DoubleType: " << dt << std::endl;
    
    dt.apply([&](std::unique_ptr<double>& value) -> DoubleType&
            {
                *value /= 2;
                return dt;
            });
    
    std::cout << "Divide by 2 DoubleType (lambda): " << dt << std::endl;

    dt.apply(updateValueDouble);
    std::cout << "updateValueDouble (adds 5): " << dt << std::endl;

    IntType it(3);
    
    std::cout << "IntType: " << it << std::endl;
    
    it.apply([&](std::unique_ptr<int>& value) -> IntType&
            {
                *value *= 4.5f;
                return it;
            });
    
    std::cout << "Multiply by 4.5f DoubleType (lambda): " << it << std::endl;

    it.apply(updateValueInt);
    std::cout << "updateValueInt (adds 5): " << it << std::endl;

    return 0;    
}
