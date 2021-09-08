#include <ctime>

#include "address_book.h"

using namespace std;
// void test() {
//     Person p("Alice", "东百");
//     cout << p << endl;
// }

int main() {
    srand(time(NULL));

    Book b;
    b.add();
    // b.search_name("Alice");
    // AVLTree<Person> avl;

    // Person a("Alice", "308");
    // a.phones.push(10086);
    // a.phones.push(10087);
    // a.phones.push(10088);

    // Person b("Tom", "414");
    // b.phones.push(10011);
    // b.phones.push(10012);
    // b.phones.push(10013);

    // avl.insert(a);
    // avl.insert(b);
    // AVLTNode<Person>* p = avl.search(Person("Tom"));
    // cout << p->key << endl;

    return 0;
}