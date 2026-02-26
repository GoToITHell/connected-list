#ifndef TEST_METHODS_FROM_TASK_2_HPP
#define TEST_METHODS_FROM_TASK_2_HPP
#include <iostream>
#include <cassert>

#include "List.hpp"
#include "decor.hpp"

void testPlusEquals() {
    header("test +=");

    List<int> list;
    list += 5;
    list += 3;
    assert(checkList(list, {3, 5}));

    // Тест с перемещением
    List<std::string> strList;
    strList += "hello";
    strList += std::string("world");
    assert(strList.getSize() == 2);
    assert(checkList(strList, {"hello", "world"}));

testPassed();
}

// удаление диапозона
void testRemoveKey() {
    header("test remove key");

    List<int> list;
    std::vector<int> values = {1, 2, 3, 4, 5, 3, 6, 7, 3, 8};
    for (int v : values) {
        list.insert(v);
    }
    
    list.removeKey(3, 5);
    
    assert(checkList(list, {1, 2, 6, 7, 8}));
    
    list.removeKey(10, 20);
    assert(checkList(list, {1, 2, 6, 7, 8}));
    
    // Удаляем с некорректными границами
    list.removeKey(5, 1);  // ошибка
    assert(checkList(list, {1, 2, 6, 7, 8}));
    
    testPassed();
}
    

#endif