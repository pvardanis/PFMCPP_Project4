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
    FloatType& add( const FloatType& ft);
    
    FloatType& subtract( float myNumber );
    FloatType& subtract( const IntType& it );
    FloatType& subtract( const DoubleType& dt );
    FloatType& subtract( const FloatType& ft);

    FloatType& multiply( float myNumber );
    FloatType& multiply( const DoubleType& dt );
    FloatType& multiply( const IntType& it );
    FloatType& multiply( const FloatType& ft );

    FloatType& divide( float myNumber );
    FloatType& divide( const FloatType& ft );
    FloatType& divide( const IntType& it );
    FloatType& divide( const DoubleType& it );
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
    if (myNumber == 0.f)
    {
        std::cout << "You're dividing by float 0!" << std::endl;
    }
    *value /= myNumber; 
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
    DoubleType& add( const FloatType& ft );
    DoubleType& add( const IntType& it );
    DoubleType& add( const DoubleType& dt );
    
    DoubleType& subtract( double myNumber );
    DoubleType& subtract( const IntType& it );
    DoubleType& subtract( const FloatType& ft );
    DoubleType& subtract( const DoubleType& dt );

    DoubleType& multiply( double myNumber );
    DoubleType& multiply( const FloatType& ft );
    DoubleType& multiply( const IntType& it );
    DoubleType& multiply( const DoubleType& dt );

    DoubleType& divide( double myNumber );
    DoubleType& divide( const DoubleType& dt );
    DoubleType& divide( const IntType& it );
    DoubleType& divide( const FloatType& ft );
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
    if (myNumber == 0.)
    {
        std::cout << "You're dividing by double 0!" << std::endl;
    }
    *value /= myNumber; 
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
    IntType& add( const IntType& it );
    
    IntType& subtract( int myNumber );
    IntType& subtract( const IntType& it );
    IntType& subtract( const DoubleType& dt );
    IntType& subtract( const FloatType& ft );

    IntType& multiply( int myNumber );
    IntType& multiply( const FloatType& ft );
    IntType& multiply( const DoubleType& dt );
    IntType& multiply( const IntType& it );

    IntType& divide( int myNumber );
    IntType& divide( const DoubleType& dt );
    IntType& divide( const FloatType& ft );
    IntType& divide( const IntType& it );
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
        std::cout << "You're dividing by 0!" << std::endl;
        return *this; 
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

FloatType& FloatType::add( const FloatType& ft )
{
    *value += *ft.value;
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

FloatType& FloatType::subtract( const FloatType& ft )
{
    *value -= *ft.value;
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

FloatType& FloatType::multiply( const FloatType& ft )
{
    *value *= *ft.value;
    return *this;
}

FloatType& FloatType::divide( const FloatType& ft )
{
    if (*ft.value == 0.f)     {
        std::cout << "You're dividing by 0!" << std::endl;
    }
    *value /= *ft.value;
    return *this;
}

FloatType& FloatType::divide( const IntType& it )
{
    if (*it.value == 0)
    {
        std::cout << "You're dividing by 0!" << std::endl;
    }
    *value /= *it.value;
    return *this;
}

FloatType& FloatType::divide( const DoubleType& dt )
{
    if (*dt.value == 0.)
    {
        std::cout << "You're dividing by 0!" << std::endl;
    }
    *value /= *dt.value;
    return *this;
}

// DoubleType functions with inputs as references
DoubleType& DoubleType::add( const FloatType& ft )
{
    *value += *ft.value;
    return *this;
}

DoubleType& DoubleType::add( const IntType& it )
{
    *value += *it.value;
    return *this;
}

DoubleType& DoubleType::add( const DoubleType& dt )
{
    *value += *dt.value;
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

DoubleType& DoubleType::subtract( const DoubleType& dt )
{
    *value -= *dt.value;
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

DoubleType& DoubleType::multiply( const DoubleType& dt )
{
    *value *= *dt.value;
    return *this;
}

DoubleType& DoubleType::divide( const DoubleType& dt )
{
    if (*dt.value == 0.)
    {
        std::cout << "You're dividing by 0!" << std::endl;
    }
    *value /= *dt.value;
    return *this;
}

DoubleType& DoubleType::divide( const IntType& it )
{
    if (*it.value == 0)
    {
        std::cout << "You're dividing by 0!" << std::endl;
    }
    *value /= *it.value;
    return *this;
}

DoubleType& DoubleType::divide( const FloatType& ft )
{
    if (*ft.value == 0.f)
    {
        std::cout << "You're dividing by 0!" << std::endl;
    }
    *value /= *ft.value;
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

IntType& IntType::add( const IntType& it )
{
    *value += *it.value;
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

IntType& IntType::subtract( const FloatType& ft )
{
    *value -= *ft.value;
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

IntType& IntType::multiply( const IntType& it )
{
    *value *= *it.value;
    return *this;
}

IntType& IntType::divide( const DoubleType& dt )
{
    if (*dt.value == 0.)
    {
        std::cout << "Dividing int by 0!" << std::endl; 
        return *this; // else I'll get an error
    }
    *value /= *dt.value;  
    return *this;
}

IntType& IntType::divide( const FloatType& ft )
{
    if (*ft.value == 0.f)
    {
        std::cout << "Dividing int by 0!" << std::endl;
        return *this; // else I'll get an error
    }
    *value /= *ft.value;  
    return *this;
}

IntType& IntType::divide( const IntType& it )
{
    if (*it.value == 0) // oops
    {
        std::cout << "Dividing int by 0!" << std::endl;
        return *this; // else I'll get an error
    }
    *value /= *it.value;  
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
