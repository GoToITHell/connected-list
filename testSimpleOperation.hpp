#ifndef TEST_SIMPLE_OPERATION_HPP
#define TEST_SIMPLE_OPERATION_HPP
#include <iostream>
#include <cassert>

#include "List.hpp"
#include"decor.hpp"

// Проверка конструкториов
void testConstructors() {
    header("Tests constructors");
    
    List<int> list;
    assert(list.getSize() == 0);
    assert(list.isEmpty());
    assert(list.getHead() == nullptr);
    assert(list.getTail() == nullptr);

   
    List<int> list1(52);
    
    assert(list1.getSize() == 1);
    assert(!list1.isEmpty());
    assert(list1.getHead()->data_ == 52);
    assert(list1.getTail()->data_ == 52);

    // Тест с другим типом
    List<std::string> strList("hello");
    assert(strList.getSize() == 1);
    assert(strList.getHead()->data_ == "hello");

    List<int> original;
    original.insert(5);
    original.insert(3);
    original.insert(7);
    original.insert(3); 
    
    List<int> copy(original);
    
    assert(copy.getSize() == 4);
    
    // Проверка  независимости
    copy.insert(1);
    assert(original.getSize() == 4);
    assert(copy.getSize() == 5);
    

    List<int> original1;
    original1.insert(5);
    original1.insert(3);
    original1.insert(7);
    
    // перемещение
    List<int> moved(std::move(original1));
    assert(moved.getSize() == 3);
    assert(original1.getSize() == 0);
    assert(original1.getHead() == nullptr);
    assert(original1.getTail() == nullptr);
    
    testPassed();
}

void testCopyAssignment() {
    header("test copy assignment");

    List<int> list1;
    list1.insert(5);
    list1.insert(3);
    list1.insert(7);
    
    List<int> list2;
    list2 = list1;
    
    assert(list2.getSize() == 3);
    
    // Проверка самоприсваивания
    list1 = list1;
    assert(list1.getSize() == 3);

    
    List<int> list3;
    list3.insert(5);
    list3.insert(3);
    list3.insert(7);
    
    // перемещение
    List<int> list4;
    list4 = std::move(list3);
    assert(list4.getSize() == 3);
    assert(list3.getSize() == 0);
    
    testPassed();
}

//Вставка
void testInsert() {
    header("test Insert");
    
    List<int> list;
    
    list.insert(5);
    list.insert(3);
    list.insert(7);
    assert(checkList(list, {3, 5, 7}));
    
    // Вставка в середину
    list.insert(4);
    assert(checkList(list, {3, 4, 5, 7}));
    
    // Вставка дубликата
    list.insert(5);
    assert(checkList(list, {3, 4, 5, 5, 7}));
    
    // Вставка с перемещением
    List<std::string> strList;
    std::string s = "world";
    strList.insert("hello"); 
    strList.insert(s);      
    assert(strList.getSize() == 2);
    assert(checkList(strList, {"hello", "world"}));
    
     testPassed();
}


// удаление
void testRemoveHead() {
    header("test Remove Head");
    
    List<int> list;
    list.insert(3);
    list.insert(5);
    list.insert(7);
    
    list.removeHead();
    assert(checkList(list, {5, 7}));
    
    list.removeHead();
    assert(checkList(list, {7}));
    
    list.removeHead();
    assert(list.getSize() == 0);
    assert(list.isEmpty());
    
    // Удаление из пустого списка 
    list.removeHead();
    assert(list.getSize() == 0);

    testPassed();
}

void testClear() {
    header("test clear");

    
    List<int> list;
    list.insert(3);
    list.insert(5);
    list.insert(7);
    list.insert(3);
    list.clear();
    assert(list.getSize() == 0);
    assert(list.isEmpty());
    assert(list.getHead() == nullptr);
    assert(list.getTail() == nullptr);

    // Повторная очистка пустого списка
    list.clear(); 
    assert(list.isEmpty());
   testPassed();
}

// 
void testAccessors() {
    header("test Accessors");

    List<int> list;
    list.insert(3);
    list.insert(5);
    list.insert(7);
    
    assert(list.getHead()->data_ == 3);
    assert(list.getTail()->data_ == 7);

    
   testPassed();
}


// поиск
void testSearch() {
    header("test Search");
    
    List<int> list;
    list.insert(3);
    list.insert(5);
    list.insert(7);
    list.insert(3);
    
    assert(list.isSearch(5));
    assert(list.isSearch(3));
    assert(list.isSearch(10) == false);
    assert(List<int>().isSearch(1) == false);
    
    testPassed();
}

#endif