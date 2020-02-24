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
FIXME no blank lines between template<typename T> and the rest of the templated class/function
FIXME no blank lines between template<typename T> and the rest of the templated class/function
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
            f(value); // 5)
        
        return *this; // 1)
    }

    operator myType() const {return *value;} 

    FIXME where are all of your pow() functions? 
    FIXME where are your overloaded math operators?

private:
    std::unique_ptr<myType> value;
};

// double
template<>
FIXME no blank lines between template<typename T> and the rest of the templated class/function
struct Numeric<double>
{
    using myType = double;

    Numeric(myType number_) : value(std::make_unique<myType>(number_)) {} 
    
    template<typename Callable>
FIXME no blank lines between template<typename T> and the rest of the templated class/function
    Numeric& apply(Callable c)  
    {
        std::cout << "Callable function" << std::endl;
        
        c(value); 
        
        return *this; 
    }

    operator myType() const {return *value;} 
        
    FIXME where are all of your pow() functions? 
    FIXME where are your overloaded math operators?
private:
    std::unique_ptr<myType> value;
};

// templated free function
template<typename numType>
FIXME no blank lines between template<typename T> and the rest of the templated class/function
void updateValue(std::unique_ptr<numType>& value)
{
    *value += 5;
}

int main()
{
    FIXME Where is your old main that used all of your overloaded math operators and pow() functions?
    std::cout << "********************" << std::endl;   
    Numeric<float> ft(2.5f);
    
    using NumericFt = decltype(ft)::myType;

    std::cout << "FloatType: " << ft << std::endl;
    
    ft.apply([&](std::unique_ptr<NumericFt>& value) -> decltype(ft)& FIXME what exactly are you capturing by reference?
            {
                *value *= 2;
                return ft; FIXME return value, not ft. 
            });
    
    std::cout << "Multiply by 2 FloatType (lambda): " << ft << std::endl;

    ft.apply(updateValue);
    std::cout << "updateValue (adds 5): " << ft << std::endl;

    Numeric<double> dt(5.75);
    
    std::cout << "********************" << std::endl;

    std::cout << "DoubleType: " << dt << std::endl;
    
    dt.apply([&](std::unique_ptr<double>& value) FIXME what exactly are you capturing by reference?
            {
                *value *= 2;
                std::cout << "Multiply by 2 DoubleType (lambda): " << *value << std::endl;
            });

    dt.apply(updateValue<double>); // why do I need to specify <double>? Otherwise it won't work.
    std::cout << "updateValue (adds 5): " << dt << std::endl;

    std::cout << "********************" << std::endl;

    Numeric<int> it(3);
    
    using NumericIt = decltype(it)::myType;

    std::cout << "IntType: " << it << std::endl;
    
    it.apply([&](std::unique_ptr<NumericIt>& value) -> decltype(it)& FIXME what exactly are you capturing by reference?
            {
                *value *= 4.5f;
                return it; FIXME return value, not ft. 
            });
    
    std::cout << "Multiply by 4.5f DoubleType (lambda): " << it << std::endl;

    it.apply(updateValue);
    std::cout << "updateValueInt (adds 5): " << it << std::endl;

    std::cout << "good to go!" << std::endl;

    return 0;    
}
