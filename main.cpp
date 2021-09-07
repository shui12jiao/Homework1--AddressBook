#include <ctime>

#include "address_book.h"

using namespace std;

int main() {
    srand(time(NULL));

    // Book b;
    // // b.add();
    // b.show();
    Person p("Alice", "曹县");

    // cout << p.name << endl;
    // cout << p.address << endl;
    // cout << *p.phones.array << endl;

    p.phones.push(10086);
    cout << p << endl;

    return 0;
}