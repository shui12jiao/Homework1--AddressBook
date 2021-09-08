#ifndef ADDRESS_BOOK_H__
#define ADDRESS_BOOK_H__

#include <iostream>

#include "array.hpp"
#include "avltree.hpp"

class Person {
   public:
    std::string name;
    std::string address;
    Array<int> phones;

   public:
    Person(std::string n = "", std::string a = "") : name(n), address(a) {}
    ~Person() {}
    friend std::ostream& operator<<(std::ostream& out, const Person& p);

    bool operator==(const Person& p) { return name == p.name; }
    bool operator!=(const Person& p) { return name != p.name; }
    bool operator>(const Person& p) { return name > p.name; }
    bool operator<(const Person& p) { return name < p.name; }
    bool operator>=(const Person& p) { return name >= p.name; }
    bool operator<=(const Person& p) { return name <= p.name; }
};

class Book {
    class Pair {
       public:
        int key;
        std::string val;

       public:
        Pair(int p, std::string n) : key(p), val(n) {}
        ~Pair() {}

        bool operator==(const Pair& p) { return key == p.key; }
        bool operator!=(const Pair& p) { return key != p.key; }
        bool operator>(const Pair& p) { return key > p.key; }
        bool operator<(const Pair& p) { return key < p.key; }
        bool operator>=(const Pair& p) { return key >= p.key; }
        bool operator<=(const Pair& p) { return key <= p.key; }
    };

   private:
    AVLTree<Person> book;
    AVLTree<Pair> book_phone;
    int number = 0;

   public:
    Book() {}
    ~Book() {}
    void search();
    void add();
    void del();
    void mod();
    void sort();
    void show();

   private:
    Person* search_name(std::string name);
    Person* search_phone(int phone);
};

#endif  // ADDRESS_BOOK_H__
