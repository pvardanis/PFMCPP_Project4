
#include <iostream>
/*
Project 4: Part 7 / 9
Video: Chapter 5 Part 4

Create a branch named Part7

Templates and Containers

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up. 

#1) if you're not using std::unique_ptr to own your heap-allocated type as a member variable, 
    replace your manual memory management techniques with a private std::unique_ptr member variable.

#2) replace your Heap-Allocated Numeric Type-owning class with a templated class called Numeric.
        replace all of your previous instances of your separate classes with this templated class.

#3) add a 'using <some name> = <your class template parameter>;' 
        treat this type declaration via 'using' as a static member variable
        use this Type alias as the argument everywhere you previously used the template argument.
        this will make it very easy to change the type if needed.
            i.e. if you have 'std::unique_ptr<NumericType> value;' before
                you'd replace NumericType in that variable declaration with '<some name>'
        
#4) you'll need to pair it with decltype() to help the compiler figure out the type of the object 
    your class owns when you make your lambda and free function that takes your unique_ptr.  
    i.e. like this for determining the template parameter of the unique_ptr function argument to your class's apply() function
        std::unique_ptr< decltype( <instance of class> )::<some name> >
    
#5) template your free function for the apply() that takes a function pointer so it can be used with your Wrapper class's apply() function

#6) add an explicit template specialization for 'double' of your wrapper class
        this template specialization will have one apply() function instead of 2. 

#7) this apply() function will be templated, and expect a Callable object, not std::function<>.   //need to see if I can do this.
        the function should allow for chaining.  
        the callable object should return void, like the function pointer-based apply() function in the primary class template

#8) instantiate your explicit template specialization

#9) call the apply function twice, once with a lambda and once with the free function
        the free function is templated, so you might need to call it including the template arguments.
        
#10) in addition to using the lambda argument to modify the owned object:  (your previous task's lambdas did this same thing) 
        make the lambda use your explicit template instance (maybe via a std::cout), 



compile/link/run to make sure you don't have any errors

Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.

If you need to view an example, see: https://bitbucket.org/MatkatMusic/pfmcpptasks/src/master/Projects/Project4/Part7Example.cpp
*/


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

    std::cout << "good to go!" << std::endl;

    return 0;    
}
