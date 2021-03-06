#ifndef ADDRESS_BOOK_H__
#define ADDRESS_BOOK_H__

#include <iostream>

#include "array.hpp"
#include "avltree.hpp"

class Person {
   public:
    std::string name;
    std::string address;
    Array<std::string> phones;

   public:
    Person(std::string n = "", std::string a = "") : name(n), address(a) {}
    Person(const Person& p) {
        name = p.name;
        address = p.address;
        phones = p.phones;
    }
    ~Person() {}
    friend std::ostream& operator<<(std::ostream& out, const Person& p);

    bool operator==(const Person& p) const { return name == p.name; }
    bool operator!=(const Person& p) const { return name != p.name; }
    bool operator>(const Person& p) const { return name > p.name; }
    bool operator<(const Person& p) const { return name < p.name; }
    bool operator>=(const Person& p) const { return name >= p.name; }
    bool operator<=(const Person& p) const { return name <= p.name; }
};

class Book {
    class Pair {
       public:
        std::string key;
        std::string val;

       public:
        Pair(std::string k, std::string v) : key(k), val(v) {}
        Pair(const Pair& p) {
            key = p.key;
            val = p.val;
        }
        ~Pair() {}

        bool operator>(const Pair& p) const { return key > p.key; }
        bool operator<(const Pair& p) const { return key < p.key; }
        bool operator>=(const Pair& p) const { return key >= p.key; }
        bool operator<=(const Pair& p) const { return key <= p.key; }
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
    void sort() const;
    void show() const;
    void showmenu() const;

   private:
    Person* search_name(std::string name) const;
    Person* search_phone(std::string phone) const;
    void trim(std::string& str) {
        str.erase(0, str.find_first_not_of(" \t"));
        str.erase(str.find_last_not_of(" \t") + 1);
    }
};

#endif  // ADDRESS_BOOK_H__
