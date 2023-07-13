/*********************************************************************************
* Lukas Licon, llicon
* 2023 Winter CSE101 PA#6
* ListTest.cpp
* 03/3/2023
* Test File for LIST ADT
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string>
#include "List.h"

using namespace std;

int main(int argc, char* argv[]){

   List list1, list2, list3, list4, list5;

   list1.insertBefore(1);
   list1.insertBefore(2);
   list1.insertBefore(1);
   list1.insertBefore(2);
   list1.insertBefore(3);
   list1.findPrev(3);
   list1.cleanup();

   list2.insertBefore(1);
   list2.insertBefore(2);
   list2.insertBefore(1);
   list2.insertBefore(2);
   list2.insertBefore(3);
   list2.insertBefore(4);
   list2.findPrev(4);
   list2.movePrev();
   list2.movePrev();
   list2.cleanup();

   cout << endl;
   cout << "list1 length = " << list1.length() << endl;
   cout << "list1.position() = " << list1.position() << endl;
   list1.moveNext();
   cout << "list1.position() after moveNext() = " << list1.position() << endl;
   list1.movePrev();
   cout << "list1.position() after movePrev() = " << list1.position() << endl;
   list1.moveBack();
   cout << "list1.position() after moveBack() = " << list1.position() << endl;

   cout << endl;
   cout << "list1 length = " << list2.length() << endl;
   cout << "list1.position() = " << list2.position() << endl;
   list2.moveNext();
   cout << "list1.position() after moveNext() = " << list2.position() << endl;
   list2.movePrev();
   cout << "list1.position() after movePrev() = " << list2.position() << endl;
   list2.moveBack();
   cout << "list1.position() after moveBack() = " << list2.position() << endl;
   cout << endl;
  
   list1.clear();
   list2.clear();
  
   for (int i = 0 ; i < 10; i++){
      list3.insertBefore(i);
   }
  
   cout << "list3 length = " << list3.length() << endl;

   list3.moveFront();
   List test1, test2, test3;
   for (int i = 0; i < (list3.length()/2); i++){
      test1.insertBefore(list3.peekNext());
      list3.moveNext();
   }
   for (int j = list3.length()/2 ; j < list3.length(); j++){
      test2.insertBefore(list3.peekNext());
      list3.moveNext();
   }
   test1.moveFront();
   test2.moveFront();
   while(test3.length() != list3.length()){
      if (test2.position() != test2.length()){
         test3.insertBefore(test2.peekNext());
         test2.moveNext();
      }
      if (test1.position() != test1.length()){
         test3.insertBefore(test1.peekNext());
         test1.moveNext();
      }
   }
   cout << "test3 length = " << test3.length() << endl;
   cout << "list3 == test3 is " << (list3==test3?"true":"false") << endl;
   list3 = test3;
   cout << "list3 set to test3" << endl;
   cout << "list3 length = " << list3.length() << endl;
   cout << "list3 == test3 is " << (list3==test3?"true":"false") << endl;
   cout << endl;

   cout << "list3 mini test = " << endl;
   list3.moveFront();
   printf("%d\n", list3.findNext(17));
   cout << list3.position() << endl;


   list1.clear();
   list2.clear();
   list3.clear();
   return(0);
}
