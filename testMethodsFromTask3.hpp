#ifndef TEST_METHODS_FROM_TASK_3_HPP
#define TEST_METHODS_FROM_TASK_3_HPP
#include <iostream>
#include <cassert>

#include "List.hpp"
#include "decor.hpp"

void testReplace() {
   header ("Testing Replace ");
    
    List<int> list;
    std::vector<int> values = {1, 2, 3, 4, 3, 5, 3, 6};
    for (int v : values) {
        list.insert(v);
    }
    
    // Заменяем все 3 на 7
    list.replace(3, 7);
    
    assert(checkList(list, {1, 2, 4, 5, 6, 7, 7, 7}));
    
    // Замена несуществующего ключа
    list.replace(10, 20);
    assert(checkList(list, {1, 2, 4, 5, 6, 7, 7, 7}));
    
    // Тот же ключ
    list.replace(7, 7);
    assert(checkList(list, {1, 2, 4, 5, 6, 7, 7, 7}));
    
   testPassed();
}

void testMerge() {
    header("test merge");
    
    List<int> list1;
    list1.insert(1);
    list1.insert(3);
    list1.insert(5);
    list1.insert(7);
    
    List<int> list2;
    list2.insert(2);
    list2.insert(4);
    list2.insert(6);
    list2.insert(3); 
    
    // Сливаем list2 в list1
    list1.merge(list2);

    assert(checkList(list1, {1, 2, 3, 3, 4, 5, 6, 7}));
    assert(list1.getSize() == 8);
    
    assert(list2.getSize() == 0);
    assert(list2.getHead() == nullptr);
    assert(list2.getTail() == nullptr);
    
    // Слияние с пустым списком
    List<int> list3;
    list3.insert(10);
    list3.insert(20);
    
    List<int> emptyList;
    list3.merge(emptyList);
    
    assert(checkList(list3, {10, 20}));
    assert(list3.getSize() == 2);
    
    // Проверка самослияния 
    List<int> list4;
    list4.insert(5);
    list4.insert(3);
    size_t oldSize = list4.getSize();
    list4.merge(list4);
    assert(list4.getSize() == oldSize);
    
    testPassed();
}


#endif