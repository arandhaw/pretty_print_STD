#include <iostream>
#include <utility>
#include <tuple>

#include <array>
#include <vector>
#include <forward_list>
#include <deque>
#include <list>

#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

using namespace std;

namespace pretty_print_STD_impl{

	// Define concepts
	// Metaprogramming
	namespace janky_meta_programming {
		template<template<typename...> class Template, typename Class>
		struct is_instantiation : std::false_type {};
		template<template<typename...> class Template, typename... Args>
		struct is_instantiation<Template, Template<Args...>> : std::true_type {};
	}
	// Test if a class is an instance of a template
	// Doesn't work with non-type parameters, e.g., std::array<type, int>
	// This works for everything in the STL except std::array
	template<typename Class, template<typename...> class Template>
	concept is_instance_of = janky_meta_programming::is_instantiation<Template, Class>::value;

	// True if type can be printed using std::cout
	template <typename T>
	concept Printable = requires(T t) {
		std::cout << t; 
	};

	//True for map, unordered_map, multimap, unordered_multimap
	template <typename T>
	concept IsMap = !Printable<T> && (
		is_instance_of<T, std::map> ||
		is_instance_of<T, std::multimap> ||
		is_instance_of<T, std::unordered_map> ||
		is_instance_of<T, std::unordered_multimap>
	);

	//True for set, unordered_set, multiset, unordered_multiset
	template <typename T>
	concept IsSet = !Printable<T> && (
		is_instance_of<T, std::set> ||
		is_instance_of<T, std::multiset> ||
		is_instance_of<T, std::unordered_set> ||
		is_instance_of<T, std::unordered_multiset>
		);
	// True if a type meets requirements, and doesn't fit into other categories
	// For array, vector, list, etc.
	template<typename T>
	concept IsIterable = !Printable<T> && !IsSet<T> && !IsMap<T> && requires (T a) {
		a.begin();
		a.end();
		a.begin() != a.end();
		*(a.begin());
		++a.begin();
	};
	// True for std::pair
	template <typename T>
	concept IsPair = is_instance_of<T, std::pair>;

	// True for std::tuple
	template <class T>
	concept IsTuple = is_instance_of<T, std::tuple>;

	// declare templated functions
	template<IsIterable T> void print_single(const T& sequence);
	template<IsMap T> void print_single(const T& map);
	template<IsSet T> void print_single(const T& map);
	template<Printable T> void print_single(const T& value);
	template<IsPair T> void print_single(T a);
	template<IsTuple TupleT, std::size_t TupSize> void print_single(const TupleT& tp);
	
	// for any iterable (except maps)
	// e.g., array, vector, list, deque, set, unordered_set, etc.
	template<IsIterable T>
	void print_single(const T& sequence) {
		cout << "[";
		auto it = sequence.begin();
		auto end = sequence.end();
		if (it != end) {
			print_single(*it);
			++it;
			for (; it != end; ++it) {
				std::cout << ", ";
				print_single(*it);
			}
		}
		std::cout << "]";
	}
	
	template<IsSet T>
	void print_single(const T& sequence) {
		cout << "{";
		auto it = sequence.begin();
		auto end = sequence.end();
		if (it != end) {
			print_single(*it);
			++it;
			for (; it != end; ++it) {
				std::cout << ", ";
				print_single(*it);
			}
		}
		std::cout << "}";
	}

	// for map, unordered_map, multimap, unordered_multimap
	template<IsMap T>
	void print_single(const T& map) {
		std::cout << "{";
		auto it = map.begin();
		auto end = map.end();
		if (it != end) {
			print_single(it->first);
			std::cout << " : ";
			print_single(it->second);
			++it;
			for (; it != end; ++it) {
				std::cout << ", ";
				print_single(it->first);
				std::cout << " : ";
				print_single(it->second);
			}
		}
		std::cout << "}";
	}
	// for std::pair
	template<IsPair T>
	void print_single(T a) {
		std::cout << "(";
		print_single(a.first);
		std::cout << ", ";
		print_single(a.second);
		std::cout << ")";
	}
	
	template <typename TupleT, std::size_t... Is>
	void printTupleHelper(const TupleT& tp, std::index_sequence<Is...>) {
		std::cout << "(";
		((print_single(std::get<Is>(tp)), std::cout << ", "), ...);
		std::cout << ")";
	}

	// for std::tuple
	template <IsTuple TupleT, std::size_t TupSize = std::tuple_size<TupleT>::value>
	void print_single(const TupleT& tp) {
		printTupleHelper(tp, std::make_index_sequence<TupSize>{});
	}
	
	// for type's where cout << T is defined.
	// this has the highest priority
	template<Printable T>
	void print_single(const T& value) {
		std::cout << value;
	}

}

namespace pretty_print_STD {
	//print each arguement (except first two)
	//@sep is printed between each arguement
	//@end is printed at the end
	template<typename T, typename...A>
	void print_custom(const char* sep, const char* end, const T& first, const A&...args) {
		using namespace pretty_print_STD_impl;
		print_single(first);
		((std::cout << sep, print_single(args)), ...);
		std::cout << end;
	}

	// print each arguement
	// no spaces/newline added in
	template<typename...A>
	void print_raw(const A&...args) {
		using namespace pretty_print_STD_impl;
		((print_single(args)), ...);
	}

	// Print each arguement separated by " "
	// std::endl at end
	template<typename T, typename...A>
	void print(const T& first, const A&...args) {
		using namespace pretty_print_STD_impl;
		print_single(first);
		((std::cout << " ", print_single(args)), ...);
		std::cout << std::endl;
	}

}