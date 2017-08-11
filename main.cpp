#include <iostream>
#include <type_traits>

#include "ultimate_swapper.h"

#define PRINT(x) std::cout << #x << std::endl

// Structs to test

struct FirstStruct
{
    static void swap(FirstStruct& lhs, FirstStruct& rhs)
    {
        PRINT("Swapping two FirstStruct objects");
    }
};

struct SecondStruct
{
    void swap(SecondStruct& rhs)
    {
        PRINT("Swapping two SecondStruct objects");
    }
};

struct ThirdStruct
{
    ThirdStruct() = default;

    ThirdStruct(const ThirdStruct&)
    {
        PRINT("Copy ctor of ThirdStruct");
    }

    ThirdStruct& operator = (const ThirdStruct&)
    {
        PRINT("Assignment of ThirdStruct");
        return *this;
    }
};

struct FourthStruct
{
    FourthStruct() = default;

    FourthStruct(const FourthStruct&) = delete;
    FourthStruct& operator = (const FourthStruct&) = delete;

    FourthStruct(FourthStruct&&)
    {
        PRINT("Move ctor of FourthStruct");
    }

    FourthStruct& operator = (FourthStruct&&)
    {
        PRINT("Move assignment of FourthStruct");
        return *this;
    }
};

struct FifthStruct
{
    FifthStruct() = default;
    FifthStruct(const FifthStruct&) = delete;
    FifthStruct& operator= (const FifthStruct&) = delete;
};

// main

int main()
{
    FirstStruct obj1, obj2;
    ultimate_swapper::swap(obj1, obj2);

    SecondStruct obj3, obj4;
    ultimate_swapper::swap(obj3, obj4);

    ThirdStruct obj5, obj6;
    ultimate_swapper::swap(obj5, obj6);

    FourthStruct obj7, obj8;
    ultimate_swapper::swap(obj7, obj8);

    //FifthStruct obj9, obj10;
    //ultimate_swapper::swap(obj9, obj10);
}
