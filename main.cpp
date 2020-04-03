/*
Project 4: Part 9 / 9
 video: Chapter 5 Part 8

Create a branch named Part9

 Rule of 3-5-0 and S.R.P.
 
 DO NOT EDIT YOUR PREVIOUS main(). 
 
 1) add the Leak Detector files from Project5
 
 2) add these macros after the JUCE_LEAK_DETECTOR macro :
 */

#define JUCE_DECLARE_NON_COPYABLE(className) \
            className (const className&) = delete;\
            className& operator= (const className&) = delete;

#define JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(className) \
            JUCE_DECLARE_NON_COPYABLE(className) \
            JUCE_LEAK_DETECTOR(className)

/*
 3) add JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Temporary) to the end of the  Temporary<> struct
 
 4) add JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Numeric) to the end of the Numeric<> struct
 
 if you compile it, you'll see lots of errors about deleted functions.
 
 5) Implement the Rule of 5 on Numeric<> and Temporary<> to fix this.
 
 You should end up with the same program output as Part 8's task if you did it right.
 */

/*
 If you did everything correctly, this is the output you should get:
 
I'm a Temporary<f> object, #0
I'm a Temporary<i> object, #0
I'm a Temporary<d> object, #0
f: -1.89
d: -3.024
i: -9
Point { x: -1.89, y: -9 }
d: 3.024
I'm a Temporary<d> object, #1
I'm a Temporary<d> object, #2
d: 1.49519e+08
Point { x: -2.82591e+08, y: -1.34567e+09 }
I'm a Temporary<f> object, #1
I'm a Temporary<i> object, #1
I'm a Temporary<i> object, #2
I'm a Temporary<i> object, #3
intNum: 5
I'm a Temporary<f> object, #2
f squared: 3.5721
I'm a Temporary<f> object, #3
f cubed: 45.5796
I'm a Temporary<d> object, #3
d squared: 2.2356e+16
I'm a Temporary<d> object, #4
d cubed: 1.11733e+49
I'm a Temporary<i> object, #4
i squared: 81
I'm a Temporary<i> object, #5
i cubed: 531441

Use a service like https://www.diffchecker.com/diff to compare your output. 

Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
*/

#include <iostream>
#include <cmath>
#include <functional>
#include <memory>
#include <typeinfo>

template<typename NumericType>
struct Temporary
{
    Temporary(NumericType t) : v(t)
    {
        std::cout << "I'm a Temporary<" << typeid(v).name() << "> object, #"
                  << counter++ << std::endl;
    }
    /*
     revise these conversion functions to read/write to 'v' here
     hint: what qualifier do read-only functions usually have?
     */
    operator NumericType() const { return v; } // not a pointer as before
    operator NumericType&() { return v; }
private:
    static int counter;
    NumericType v;
};

template<typename NumericType>
int Temporary<NumericType>::counter = 0;

template<typename NumericType>
struct Numeric
{
    using MyType = Temporary<NumericType>; 

    Numeric(MyType number_) : value(std::make_unique<MyType>(number_)) {} 
    
    Numeric& apply(std::function<Numeric&(std::unique_ptr<MyType>&)> f)  
    {
        std::cout << "std::function<>" << std::endl;

        if(f)
        {
            return f(value);  
        }
        
        return *this; 
    }

    ~Numeric() {}
    
    Numeric& apply(void(*f)(std::unique_ptr<MyType>&))
    {
        std::cout << "free function" << std::endl;

        if(f)
        {
            f(value); 
        }

        return *this; 
    }

    // Conversion
    operator NumericType() const {return *value;} 
    operator NumericType&() {return *value;} 

    // Assignment operators
    template<typename OtherType>
    Numeric& operator=(const OtherType& myNumber)
    {
        *value = static_cast<NumericType>(myNumber);
        return *this;
    }

    template<typename OtherType>
    Numeric& operator+=(const OtherType& myNumber)
    {
        *value += static_cast<NumericType>(myNumber);
        return *this;
    }

    template<typename OtherType>
    Numeric& operator-=(const OtherType& myNumber)
    {
        *value -= static_cast<NumericType>(myNumber);
        return *this;
    }

    template<typename OtherType>
    Numeric& operator*=(const OtherType& myNumber)
    {
        *value *= static_cast<NumericType>(myNumber);
        return *this;
    }

    template<typename OtherType>
    Numeric& operator/=(const OtherType& myNumber)
    {
        if constexpr(std::is_same<NumericType, int>::value) 
        {
            if constexpr(std::is_same<OtherType, int>::value) 
            {
                if (myNumber == 0)
                {
                    std::cout << "Dividing by int 0!  Don't do the division!" << std::endl;
                    return *this;
                }
            }
            else if (std::abs(myNumber) <= std::numeric_limits<OtherType>::epsilon())
            {
                std::cout << "Dividing by a value smaller then epsilon! Don't do the division!" << std::endl;
                return *this;
            }
        }
        // else if MyNumber is float or double
        else if (std::abs(myNumber) <= std::numeric_limits<OtherType>::epsilon())
        {
            // do the division, but give a warning
            std::cout << "Warning! Dividing by a value smaller than epsilon!" << std::endl;
        }

        *value /= static_cast<NumericType>(myNumber); 
        return *this;
    }

    template<typename OtherType>
    Numeric& pow(const OtherType& myNumber)
    {
        *value = std::pow(*value, static_cast<NumericType>(myNumber));
        return *this;
    }

private:
    std::unique_ptr<MyType> value;
};

// templated free function
template<typename numType>
void updateValue(std::unique_ptr<numType>& value)
{
    *value += 5;
}

template<typename numType>
void cube(std::unique_ptr<numType>& value)
{
    *value = *value * *value * *value;
}

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

#include <iostream>
int main()
{
    Numeric<float> f(0.1f);
    Numeric<int> i(3);
    Numeric<double> d(4.2);
    
    f += 2.f;
    f -= i;
    f *= d;
    f /= 2.f;
    std::cout << "f: " << f << std::endl;
    
    d += 2.f;
    d -= i;
    d *= f;
    d /= 2.f;
    std::cout << "d: " << d << std::endl;
    
    i += 2.f; i -= f; i *= d; i /= 2.f;
    std::cout << "i: "<< i << std::endl;
    
    Point p(f, i);
    p.toString();
    
    d *= -1;
    std::cout << "d: " << d << std::endl;
    
    p.multiply(static_cast<float>(d.pow(static_cast<double>(f)).pow(static_cast<double>(i))));
    std::cout << "d: " << d << std::endl;
    
    p.toString();
    
    Numeric<float> floatNum(4.3f);
    Numeric<int> intNum(2);
    Numeric<int> intNum2(6);
    intNum = 2 + (intNum2 - 4) + static_cast<double>(floatNum) / 2.3;
    std::cout << "intNum: " << intNum << std::endl;
    
    {
        using Type = decltype(f)::MyType;
        f.apply([&f](std::unique_ptr<Type>&value) -> decltype(f)&
                {
                    auto& v = *value;
                    v = v * v;
                    return f;
                });
        std::cout << "f squared: " << f << std::endl;
        
        f.apply( cube<Type> );
        std::cout << "f cubed: " << f << std::endl;
    }
    
    {
        using Type = decltype(d)::MyType;
        d.apply([&d](std::unique_ptr<Type>&value) -> decltype(d)&
                {
                    auto& v = *value;
                    v = v * v;
                    return d;
                });
        std::cout << "d squared: " << d << std::endl;
        
        d.apply( cube<Type> );
        std::cout << "d cubed: " << d << std::endl;
    }
    
    {
        using Type = decltype(i)::MyType;
        i.apply([&i](std::unique_ptr<Type>&value) -> decltype(i)&
                {
                    auto& v = *value;
                    v = v * v;
                    return i;
                });
        std::cout << "i squared: " << i << std::endl;
        
        i.apply( cube<Type> );
        std::cout << "i cubed: " << i << std::endl;
    }
}

