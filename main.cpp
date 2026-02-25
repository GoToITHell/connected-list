#include <iostream>
#include <cassert>

#include "List.hpp"
#include "decor.hpp"
#include "testSimpleOperation.hpp"
#include "testMethodsFromTask2.hpp"
#include "testMethodsFromTask3.hpp"


int main(){
     std::cout << "##########################################" << std::endl;
    std::cout << "            TESTS LIST         "          << std::endl;
    std::cout << "##########################################" << std::endl;
    std::cout << std::endl;

    try
    {
        testConstructors();
        testCopyAssignment();
        testInsert();
        testRemoveHead();
        testClear();
        testAccessors();
        testSearch();
        //
        testPlusEquals();
        testRemoveKey();
        //
        testReplace();
        testMerge();

        std::cout << std::endl;
        std::cout << " All tests passed! " << std::endl;


    }
    catch(const std::exception& e)
    {
         std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}