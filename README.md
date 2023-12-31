# pretty_print_STD
A C++20 library offering simplified syntax for printing things, with inbuilt support for containers in the standard library.
Has the following functions:

void print(...) <br>
void print_raw(...) <br>
void print_custom(sep, end, ...) <br>

These functions can take an arbitrary number of parameters, and print them.
The print() function has similar syntax to print in python. Every arguement will be printed separated by a space " ", with a newline at the end "\n".
print_raw() does not add any spaces or a newline.
print_custom() allows you to choose the separator (printed between each arguement) and end of line (printed at the end).

The library is capable of recursively printing any data structure composed of the following:
- Types for which cout << is defined
- Types that provide an iterator
- std::array, std::vector, std::deque, std::list, std::forward_list
- std::set, std::multiset, std::unordered_set, std::unordered_multiset
- std::map, std::unordered_map, std::multimap, std::unordered_multimap
- std::pair and std::tuple

Limitations:
- Requires at least C++20
- Some unsupported types, such as std::stack, std::queue, std::priority_queue
- Not optimized for performance, rather for ease of use

Implementation: 
- A single header file
- Heavy reliance on templates, and C++20 concepts
- main.cpp provides examples of use

If you run main.cpp, you should get something like this:
<img width="440" alt="image" src="https://github.com/arandhaw/pretty_print_STD/assets/72634664/cd8933de-41c3-47a6-bce2-f184c3bacc69">

