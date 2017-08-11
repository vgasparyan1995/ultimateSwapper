#pragma once

#include <type_traits>

template <typename T>
struct is_copyable_and_assignable
{
    static const bool value = std::is_copy_constructible<T>::value &&
                              std::is_copy_assignable<T>::value;
};

template <typename T>
struct is_movable_and_assignable
{
    static const bool value = std::is_move_constructible<T>::value &&
                              std::is_move_assignable<T>::value;
};

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
        constexpr auto imaa = is_movable_and_assignable<T>::value;
        constexpr auto icaa = is_copyable_and_assignable<T>::value;
        static_assert(imaa || icaa, "This type is not copyable, assignable or movable, thus can not be swapped.");
        if constexpr (imaa) {
            T tmp(std::move(lhs));
            lhs = std::move(rhs);
            rhs = std::move(tmp);
        } else if (icaa) {
            T tmp(lhs);
            lhs = rhs;
            rhs = tmp;
        }
    }
};
