#include "pretty_print_STD.cpp"

int main() {
	using namespace pretty_print_STD;
	using namespace std;
	
	int x = 2;
	string myString = "hello";
	
	print(myString, x, "the", "world");
	print_raw(myString, x, "the", "world\n");
	print_custom("---", "!!!\n\n", "example", "of", "print", "custom");

	pair<int, string> brotha = { 3, "hello" };
	tuple<int, double, string> sista = { 1, 3.14, "so long" };
	
	array<int, 3> arr = { 1, 2, 3 };
	vector<int> vec = { 3, 6, 9 };
	list<int> myList = { 2, 3, 5, 7 };
	forward_list<int> myFList = { 2, 20, 10, 100 };
	deque<char> myDeck = { '9', 'D', 'J', 'Q', 'K' };

	set<double> mySet = { 3.14, 2.71 };
	multiset<int> multi = { 3, 3, 3};
	unordered_set<string> mySillySet = { "ooh", "ah" , "ee" };
	unordered_multiset<string> myMSet = { "ooh", "ah" , "ee", "ah", "ooh"};

	map<string, string> myMap = { { "name", "Bilbo" }, { "gender", "male" } };
	unordered_map<string, int> myHashmap = { { "Planets", 8 }, { "Moons", 290} };
	multimap<int, int> myMultimap = { {0, 0}, {0, 1}, {0, 2} };
	unordered_multimap<string, string> myCrazymap = { {"greet", "hi"}, {"greet", "hello"}, {"greet", "hey"} };
	
	// nested types are fine
	vector<pair<int, int>> coords = {{0, 0}, { 0, 1 }, { 1, 0 }, { 1, 1 } };
	array<array<int, 3>, 3> ndarr = { { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} } };
	map<string, set<int> > nest = { {"Cool numbers", {73, 496, 2047}}, {"Empty set", {}} };
	
	print("std::pair: ", brotha);
	print("std::tuple: ", sista);
	print("std::array: ", arr);
	print("vector: ", vec);
	print("list: ", myList);
	print("forward_list: ", myFList);
	print("deque: ", myDeck);

	print("set: ", mySet);
	print("multiset: ", multi);
	print("unordered_set: ", mySillySet);
	print("unordered_multiset: ", myMSet);
	
	print("map: ", myMap);
	print("unordered_map: ", myHashmap);
	print("unordered_multimap: ", myCrazymap);
	print("multimap: ", myMultimap);

	print("\nvector of pair: ", coords);
	print("array of array ", ndarr);
	print("Map of string to set of int: ", nest);
	
	return 0;
}