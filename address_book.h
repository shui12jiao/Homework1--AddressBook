#ifndef ADDRESS_BOOK_H__
#define ADDRESS_BOOK_H__

#include <iostream>

#include "avltree.hpp"

class Person {
   public:
    Person(std::string n, std::a, int p);
    ~Person();

   private:
    std::string name;
    std::string address;
    int phone;
    int number;
};

class Book {
   public:
    Book();
    ~Book();
    Person* search(std::string name);
    Person* search(int phone);
    Person* add();
    Person* del(std::string name);
    Person* del(int phone);
    Person* mod(std::string name);
    Person* mod(int phone);
    void sort();
    void show();

   private:
    AVLTree<Person>* book;
    AVLTree<int>* book_phone;
    int number;
};

#endif  // ADDRESS_BOOK_H__