#include "address_book.h"

using std::cin;
using std::cout;
using std::endl;

int main() {
    Book addressBook;
    while (true) {
        addressBook.showmenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                addressBook.show();
            } break;
            case 2: {
                addressBook.add();
            } break;
            case 3: {
                addressBook.search();
            } break;
            case 4: {
                addressBook.mod();
            } break;
            case 5: {
                addressBook.del();
            } break;
            case 6: {
                addressBook.sort();
            } break;
            case 0: {
                exit(0);
            } break;
            default: {
                continue;
            } break;
        }

        system("pause");
        system("cls");
    }
    return 0;
}