/*
 Project 4 - Part 2 / 9
 Video: Chapter 3 Part 6

 Create a branch named Part2

New/This/Pointers/References conclusion

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 0) in the blank space below, declare/define an empty struct named 'A' on a single Line. 
     on the lines below it, write a struct named 'HeapA' that correctly shows how to own an instance of 'A' 
         on the heap without leaking, without using smart pointers. 
 */

#include <iostream>
#include <memory>

struct A {};

struct Heap
{
    A* ptrToA = nullptr;

    Heap() : ptrToA(new A) {}

    ~Heap()
    {
        delete ptrToA;
        ptrToA = nullptr;
    }
};

 /*
 1) Edit your 3 structs so that they own a heap-allocated primitive type without using smart pointers  
         IntType should own a heap-allocated int, for example.
 
 2) give it a constructor that takes the appropriate primitive
    this argument will initialize the owned primitive's value.
         i.e. if you're owning an int on the heap, your ctor argument will initialize that heap-allocated int's value.
 
 3) modify those add/subtract/divide/multiply member functions from chapter 2 on it
         a) make them modify the owned numeric type
         b) set them up so they can be chained together.
             i.e.
             DoubleType dt(3.5);
             dt.add(3.0).multiply(-2.5).divide(7.2); //an example of chaining
 
 4) write some add/subtract/divide/multiply member functions for each type that take your 3 UDTs
         for example, IntType::divide(const DoubleType& dt);
 
 5) print out the results with some creative couts 
    i.e.
         FloatType ft(0.1f);
         IntType it(3);
         std::cout << "adding 3 and subtracting 'it' from 'ft' results in the following value: " << *ft.add(2.f).subtract( it ).value << std::endl;  //note the dereference of the `value` member of `ft`
 
 6) Don't let your heap-allocated owned type leak!
 
 7) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

 Wait for my code review.
 */

struct IntType;
struct DoubleType;

struct FloatType
{
    float* value = nullptr;

    FloatType( float number_ ) : 
    value( new float(number_) )
    {}

    ~FloatType()
    {
        delete value;
        value = nullptr;
    }

    FloatType& add( float myNumber ); 
    FloatType& add( const DoubleType& dt );
    FloatType& add( const IntType& it);
    FIXME need 'add( const FloatType&); '
    
    FloatType& subtract( float myNumber );
    FloatType& subtract( const IntType& it );
    FloatType& subtract( const DoubleType& dt );
    FIXME see 90

    FloatType& multiply( float myNumber );
    FloatType& multiply( const DoubleType& dt );
    FloatType& multiply( const IntType& it );
    FIXME see 90

    FloatType& divide( float myNumber );
    FloatType& divide( const FloatType& dt );
    FloatType& divide( const IntType& it );
    FIXME see 90
};

FloatType& FloatType::add( float myNumber )
{
    *value += myNumber;
    return *this;
}

FloatType& FloatType::subtract( float myNumber )
{
    *value -= myNumber;
    return *this;
}

FloatType& FloatType::multiply( float myNumber )
{
    *value *= myNumber;
    return *this;
}

FloatType& FloatType::divide( float myNumber )
{
    *value /= myNumber; FIXME warn if myNumber is 0
    return *this;
}

struct DoubleType
{
    double* value = nullptr;

    DoubleType( double number_ ) : 
    value( new double(number_) )
    {}

    ~DoubleType()
    {
        delete value;
        value = nullptr;
    }

    DoubleType& add( double myNumber );
    DoubleType& add( const FloatType& dt );
    DoubleType& add( const IntType& it );
    FIXME see 90
    
    DoubleType& subtract( double myNumber );
    DoubleType& subtract( const IntType& it );
    DoubleType& subtract( const FloatType& ft );
    FIXME see 90

    DoubleType& multiply( double myNumber );
    DoubleType& multiply( const FloatType& ft );
    DoubleType& multiply( const IntType& it );
    FIXME see 90

    DoubleType& divide( double myNumber );
    DoubleType& divide( const DoubleType& dt );
    DoubleType& divide( const IntType& it );
    FIXME see 90
};

DoubleType& DoubleType::add( double myNumber )
{
    *value += myNumber;
    return *this;
}

DoubleType& DoubleType::subtract( double myNumber )
{
    *value -= myNumber;
    return *this;
}

DoubleType& DoubleType::multiply( double myNumber )
{
    *value *= myNumber;
    return *this;
}

DoubleType& DoubleType::divide( double myNumber )
{
    *value /= myNumber; FIXME warn if myNumber is 0
    return *this;
}

struct IntType
{
    int* value = nullptr;

    IntType( int number_ ) : 
    value( new int(number_) )
    {}

    ~IntType()
    {
        delete value;
        value = nullptr;
    }

    IntType& add( int myNumber );
    IntType& add( const FloatType& ft );
    IntType& add( const DoubleType& dt );
    FIXME see 90
    
    IntType& subtract( int myNumber );
    IntType& subtract( const IntType& it );
    IntType& subtract( const DoubleType& dt );
    FIXME see 90

    IntType& multiply( int myNumber );
    IntType& multiply( const FloatType& ft );
    IntType& multiply( const DoubleType& dt );
    FIXME see 90

    IntType& divide( int myNumber );
    IntType& divide( const DoubleType& dt );
    IntType& divide( const FloatType& ft );
    FIXME see 90
};

IntType& IntType::add( int myNumber )
{
    *value += myNumber;
    return *this;
}

IntType& IntType::subtract( int myNumber )
{
    *value -= myNumber;
    return *this;
}

IntType& IntType::multiply( int myNumber )
{
    *value *= myNumber;
    return *this;
}

IntType& IntType::divide( int myNumber )
{
    if (myNumber == 0)
    {
        return *this; FIXME add the warning back in.
    }
    *value /= myNumber;
    return *this;
}

// FloatType functions with inputs as references
FloatType& FloatType::add( const DoubleType& dt )
{
    *value += *dt.value;
    return *this;
}

FloatType& FloatType::add( const IntType& it )
{
    *value += *it.value;
    return *this;
}

FloatType& FloatType::subtract( const IntType& it )
{
    *value -= *it.value;
    return *this;
}

FloatType& FloatType::subtract( const DoubleType& dt )
{
    *value -= *dt.value;
    return *this;
}

FloatType& FloatType::multiply( const DoubleType& dt )
{
    *value *= *dt.value;
    return *this;
}

FloatType& FloatType::multiply( const IntType& it )
{
    *value *= *it.value;
    return *this;
}

FloatType& FloatType::divide( const FloatType& ft )
{
    *value /= *ft.value;
    return *this;
}

FloatType& FloatType::divide( const IntType& it )
{
    if (*it.value == 0)
    {
        return *this; FIXME floating point division by 0 is legal.  don't return, just warn.
    }
    *value /= *it.value;
    return *this;
}

// DoubleType functions with inputs as references
DoubleType& DoubleType::add( const FloatType& dt )
{
    *value += *dt.value;
    return *this;
}

DoubleType& DoubleType::add( const IntType& it )
{
    *value += *it.value;
    return *this;
}

DoubleType& DoubleType::subtract( const IntType& it )
{
    *value -= *it.value;
    return *this;
}

DoubleType& DoubleType::subtract( const FloatType& ft )
{
    *value -= *ft.value;
    return *this;
}

DoubleType& DoubleType::multiply( const FloatType& dt )
{
    *value *= *dt.value;
    return *this;
}

DoubleType& DoubleType::multiply( const IntType& it )
{
    *value *= *it.value;
    return *this;
}

DoubleType& DoubleType::divide( const DoubleType& dt )
{
    *value /= *dt.value;
    return *this;
}

DoubleType& DoubleType::divide( const IntType& it )
{
    if (*it.value == 0)
    {
        return *this; FIXME floating point division by 0 is legal.  don't return, just warn.
    }
    *value /= *it.value;
    return *this;
}

// IntType functions with inputs as references
IntType& IntType::add( const FloatType& ft )
{
    *value += *ft.value;
    return *this;
}

IntType& IntType::add( const DoubleType& dt )
{
    *value += *dt.value;
    return *this;
}

IntType& IntType::subtract( const IntType& it )
{
    *value -= *it.value;
    return *this;
}

IntType& IntType::subtract( const DoubleType& dt )
{
    *value -= *dt.value;
    return *this;
}

IntType& IntType::multiply( const FloatType& ft )
{
    *value *= *ft.value;
    return *this;
}

IntType& IntType::multiply( const DoubleType& dt )
{
    *value *= *dt.value;
    return *this;
}

IntType& IntType::divide( const DoubleType& dt )
{
    *value /= *dt.value; FIXME if dt == 0 this will crash. 
    return *this;
}

IntType& IntType::divide( const FloatType& ft )
{
    *value /= *ft.value; FIXME if ft == 0 this will crash. 
    return *this;
}

int main()
{
    DoubleType dt1(5.45);
    FloatType ft1(0.1f);
    IntType it1(3);
    std::cout << "ft1: adding 2.f and subtracting 'it1' from 'ft1', then multiply by 'dt1' results in the following value: " << *ft1.add(2.f).subtract( it1 ).multiply( dt1 ).value << std::endl;

    DoubleType dt2(0.); // let's see what happens here
    FloatType ft2(1.25f);
    IntType it2(10);
    std::cout << "it1: adding -5 and dividing with 'dt2' and multiplying by 'ft2' results in the following value: " << *it2.add(ft2).divide( 0 ).divide( 0 ).value << std::endl;  // it returns 11 instead of 11.25 because it's IntType and returns *this
}
