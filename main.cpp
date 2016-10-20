#include <iostream>
#include <type_traits>

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
    FourthStruct& operator= (const FourthStruct&) = delete;
};

// Is copyable and assignable
template <typename T>
struct is_copyable_and_assignable
{
    static const bool value = std::is_copy_constructible<T>::value
                            && std::is_assignable<T, T>::value;
};

// Swap helpers
class ultimate_swapper
{
public:
    template <typename T>
    static void swap(T& lhs, T& rhs)
    {
        try_static(lhs, rhs, test_static(&lhs));
    }

private:
    class No {};
    class Yes { No m_dummy[2]; };

    template <typename T, void (*)(T&, T&)>
    class YesStatic : public Yes {};

    template <typename T, void (T::*)(T&)>
    class YesMember : public Yes {};

    template <typename T>
    static YesStatic<T, &T::swap>* test_static(T*)
    {
        return nullptr;
    }

    static No* test_static(void*)
    {
        return nullptr;
    }

    template <typename T>
    static void try_static(T& lhs, T& rhs, Yes*)
    {
        T::swap(lhs, rhs);
    }

    template <typename T>
    static void try_static(T& lhs, T& rhs, No*)
    {
        try_member(lhs, rhs, test_member(&lhs));
    }

    template <typename T>
    static YesMember<T, &T::swap>* test_member(T*)
    {
        return nullptr;
    }

    static No* test_member(void*)
    {
        return nullptr;
    }

    template <typename T>
    static void try_member(T& lhs, T& rhs, Yes*)
    {
        lhs.swap(rhs);
    }

    template <typename T>
    static void try_member(T& lhs, T& rhs, No*)
    {
        static_assert(is_copyable_and_assignable<T>::value, "This type is not copyable and assignable, thus cannot be swapped.");
        T tmp(lhs);
        lhs = rhs;
        rhs = tmp;
    }
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

    //FourthStruct obj7, obj8;
    //ultimate_swapper::swap(obj7, obj8);
}
