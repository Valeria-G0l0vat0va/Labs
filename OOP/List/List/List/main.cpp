#include "List.h"

int main()
{
	List<std::string> list;
	std::cout << list.max();
    list.push_front("3");
    list.push_front("2");
    list.push_front("5");

    std::cout << "List after pushing elements to front: ";
    list.print(); 

    list.append("7");
    list.append("11");

    std::cout << "List after appending elements: ";
    list.print(); 

    list.insert(2, "10"); \

    std::cout << "List after inserting 10 at position 2: ";
    list.print(); 

    list.insert_after("3", "15");

    std::cout << "List after inserting 15 after 3: ";
    list.print(); 

    list.erase("3");

    std::cout << "List after erasing element at position 3: ";
    list.print(); 

    list.erase("10"); 

    std::cout << "List after erasing value 10: ";
    list.print(); 

    list.pop_front(); 

    std::cout << "List after popping front: ";
    list.print(); 

    list.pop_back(); 

    std::cout << "List after popping back: ";
    list.print(); 

    std::cout << "Current size of the list: " << list.size() << std::endl; 
    std::cout << "Is the list empty? " << (list.isEmpty() ? "Yes" : "No") << std::endl; 

    auto it = list.find("15");
    if (it != list.end()) {
        std::cout << "Element 15 found in the list." << std::endl;
    }
    else {
        std::cout << "Element 15 not found in the list." << std::endl;
    }

    list.clear();
    std::cout << "List cleared." << std::endl;
    std::cout << "Is the list empty after clearing? " << (list.isEmpty() ? "Yes" : "No") << std::endl; 
	return 0;
}