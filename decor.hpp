#ifndef DECOR_HPP
#define DECOR_HPP
#include <iostream>
#include <vector>

#include "List.hpp"

// оформление
 void header(const std::string& name) {
    static size_t numberTest = 1;
    std::cout << "Test number "<<numberTest <<". Name test:  "<< name;
    numberTest++;
}

 void testPassed() {
    std::cout << "....excellent!" << std::endl;
}

template<typename T>
bool checkList(const List<T>& list, const std::vector<T>& expected) {
    if (list.getSize() != expected.size()) {
        return false;
    }
    
    auto* current = list.getHead();
    size_t i = 0;

    while (current && i < expected.size()) {
        if (current->data_ != expected[i]) {
            return false;
        }
        current = current->next_;
        i++;
    }
    return true;
}
#endif 