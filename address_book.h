#ifndef ADDRESS_BOOK_H__
#define ADDRESS_BOOK_H__

#include <iostream>

#include "avltree.hpp"

class Person {
   public:
    Person();
    ~Person();
    int add_phone(int phone);
    int del_phone(int phone);

   private:
    int change_length(int old_length, int new_length);
    std::string name;
    std::string address;
    int* phones;
    int number;
};

class Book {
   public:
    Book();
    ~Book();
    void search_name(std::string name);
    void search_phone(int phone);
    Person add();
    Person del(std::string name);
    Person del(int phone);
    Person mod(std::string name);
    Person mod(int phone);
    void sort();
    void show();

   private:
    AVLTree<Person>* book;
    AVLTree<std::string>* book_phone;
    int number;
};

#endif  // ADDRESS_BOOK_H__