Introduction.
Ultimate swapper is a TMP technique which is to give us an opportunity to swap objects of any type in the most acceptible way.

Interface.
We've got an 'ultimate_swapper' class, which has just one public static template function called 'swap'.
If the type has a static 'swap' function, this function swaps the objects with it.
Otherwise, if the type has a member 'swap' function, 'ultimate_swapper::swap' swaps them with it.
Otherwise, if the type is move constructible and assignable, the objects are being swapped traditionally (with the help of a temporary one).
Otherwise, if the type is copy constructible and assignable, the objects are being swapped traditionally (with the help of a temporary one).
Otherwise, a static assert will fail at compile time.
