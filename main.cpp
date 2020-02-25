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
#include <functional>
#include <memory>

template<typename numType>
struct Numeric
{
    using myType = numType;

    Numeric(myType number_) : value(std::make_unique<myType>(number_)) {} 
    
    Numeric& apply(std::function<Numeric&(std::unique_ptr<myType>&)> f)  
    {
        std::cout << "std::function<>" << std::endl;

        if(f)
        {
            return f(value);  // 5)
        }
        
        return *this; // 1)
    }
    
    Numeric& apply(void(*f)(std::unique_ptr<myType>&)) // 1), 3), 4) 
    {
        std::cout << "free function" << std::endl;

        if(f)
        {
            f(value); // 5)
        }

        return *this; // 1)
    }

    operator myType() const {return *value;} 

    Numeric& operator+=(myType myNumber)
    {
        *value += myNumber;
        return *this;
    }

    Numeric& operator-=(myType myNumber)
    {
        *value -= myNumber;
        return *this;
    }

    Numeric& operator*=(myType myNumber)
    {
        *value *= myNumber;
        return *this;
    }

    Numeric& operator/=(myType myNumber)
    {
        *value /= myNumber;
        return *this;
    }

    Numeric& pow(myType myNumber)
    {
        *value = static_cast<myType>(std::pow(*value, myNumber));
        return *this;
    }

private:
    std::unique_ptr<myType> value;
};

// double
template<>
struct Numeric<double>
{
    using myType = double;

    Numeric(myType number_) : value(std::make_unique<myType>(number_)){} 
    
    template<typename Callable>
    Numeric& apply(Callable c)  
    {
        std::cout << "Callable function" << std::endl;
        
        c(value); 
        
        return *this; 
    }

    operator myType() const {return *value;} 

    Numeric& operator+=(myType myNumber)
    {
        *value += myNumber;
        return *this;
    }

    Numeric& operator-=(myType myNumber)
    {
        *value -= myNumber;
        return *this;
    }

    Numeric& operator*=(myType myNumber)
    {
        *value *= myNumber;
        return *this;
    }

    Numeric& operator/=(myType myNumber)
    {
        *value /= myNumber;
        return *this;
    }

    Numeric& pow(myType myNumber)
    {
        *value = static_cast<double>(std::pow(*value, myNumber));
        return *this;
    }
        
private:
    std::unique_ptr<myType> value;
};

// templated free function
template<typename numType>
void updateValue(std::unique_ptr<numType>& value)
{
    *value += 5;
}

// template<typename numType>
struct Point
{
    Point(float _x, float _y): x(_x), y(_y) { } 

    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
    
    void toString();
    
private:
    float x{0}, y{0};
};

void Point::toString()
{
    std::cout << "x: " << x << ", y: " << y << std::endl;
}

int part6main()
{
    // test pow
    Numeric<int> it1(4);
    Numeric<float> ft1(2.25f);
    Numeric<double> dt1(5.4);

    Numeric<int> it2(2);
    Numeric<float> ft2(5.5f);
    Numeric<double> dt2(1.25);

    Numeric<int> it3(3);
    Numeric<float> ft3(1.15f);
    Numeric<double> dt3(3.25); 

    // I put small numbers to prevent overflow

    std::cout << "Test IntType: " << std::endl;
    std::cout << "4 ^ 2.25f ^ 5.4  = " << it1.pow(ft1).pow(dt1) << std::endl; 

    using NumericIt2 = decltype(it2)::myType;
    using NumericDt2 = decltype(dt2)::myType;
    std::cout << "\nTest FloatType: " << std::endl;
    std::cout << "5.5f ^ 2 ^ 1.25  = " << ft2.pow(static_cast<NumericIt2>(it2)).pow(static_cast<NumericDt2>(dt2)) << std::endl;

    using NumericFt3 = decltype(it3)::myType;
    using NumericIt3 = decltype(dt3)::myType;
    // std::cout << "\nTest DoubleType: " << std::endl;
    std::cout << "3.25 ^ 1.15f ^ 3  = " << dt3.pow(static_cast<NumericFt3>(ft3)).pow(static_cast<NumericIt3>(it3)) << std::endl;
    std::cout << "\n" << std::endl;

    // test Point
    Numeric<int> itp(4);
    Numeric<float> ftp(5.25f);
    Numeric<double> dtp(2.25);

    Point p1(itp, ftp);
    std::cout << "p1 values: " << std::endl;
    p1.toString();
    p1.multiply(static_cast<float>(dtp)); 
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
    
    // deleted this because it's my new main

    return 0;    
}

int main()
{
    part6main();
    std::cout << "********************" << std::endl;   
    Numeric<float> ft(2.5f);
    
    using NumericFt = decltype(ft)::myType;

    std::cout << "FloatType: " << ft << std::endl;
    
    ft.apply([&](std::unique_ptr<NumericFt>& value) -> decltype(ft)&
            {
                *value *= 2;
                return ft;
            });
    
    std::cout << "Multiply by 2 FloatType (lambda): " << ft << std::endl;

    ft.apply(updateValue<float>);
    std::cout << "updateValue (adds 5): " << ft << std::endl;

    ft += 3; // operation +=
    ft -= 4.5f; // operation -=
    ft /= 2; // operation /=
    ft *= static_cast<float>(2.5); // operation *=
    std::cout << "+ 3 - 4.5f / 2 * 2.5 = " << ft << std::endl;

    ft.pow(2.5f); // pow
    std::cout << "pow ^ 2.5f: " << ft << std::endl;

    // double
    Numeric<double> dt(5.75);
    
    std::cout << "********************" << std::endl;

    std::cout << "DoubleType: " << dt << std::endl;
    
    dt.apply([&](std::unique_ptr<double>& value) 
            {
                *value *= 2;
                std::cout << "Multiply by 2 DoubleType (lambda): " << *value << std::endl;
            });

    dt.apply(updateValue<double>); // why do I need to specify <double>? Otherwise it won't work.
    std::cout << "updateValue (adds 5): " << dt << std::endl;

    dt += 5; // operation +=
    dt -= 2.5; // operation -=
    dt /= static_cast<double>(4.5f); // operation /=
    dt *= 2; // operation *=
    std::cout << "+ 5 - 2.5 / 4.5f * 2 = " << dt << std::endl;

    dt.pow(4); // pow
    std::cout << "pow ^ 4: " << dt << std::endl;

    std::cout << "********************" << std::endl;

    // int
    Numeric<int> it(3);
    
    using NumericIt = decltype(it)::myType;

    std::cout << "IntType: " << it << std::endl;
    
    it.apply([&](std::unique_ptr<NumericIt>& value) -> decltype(it)&
            {
                *value *= 4.5f;
                return it;
            });
    
    std::cout << "Multiply by 4.5f DoubleType (lambda): " << it << std::endl;

    it.apply(updateValue<int>);
    std::cout << "updateValueInt (adds 5): " << it << std::endl;
    
    it += 5; // operation +=
    it -= 4.25f; // operation -=
    it /= 2.5; // operation /=
    it *= static_cast<int>(3); // operation *=
    std::cout << "+ 5 - 4.25f / 2.5 * 3 = " << it << std::endl;

    it.pow(3.5); // why do I get a warning here? 
    std::cout << "pow ^ 3.5: " << it << std::endl; // I don't get what I get implicit conversion here.
    // I think because in line 305, it has been promoted to double, but I'm not sure.

    std::cout << "good to go!" << std::endl;

    return 0;    
}
