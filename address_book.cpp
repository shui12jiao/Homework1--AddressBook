#include "address_book.h"

#include <sstream>
#include <type_traits>

std::ostream& operator<<(std::ostream& out, const Person& p) {
    out << "姓名: " << p.name << "  地址: " << p.address << "  电话号码: ";
    for (int i = 0; i < p.phones.number; ++i) {
        out << p.phones.array[i] << ' ';
    }
    return out;
}

void Book::search() {
    std::cout << "请输入联系人名称或电话号码:" << std::endl;

    std::string input;
    std::cin >> input;

    bool digit = true;
    for (char c : input) {
        if (c < '0' || c > '9') {
            digit = false;
        }
    }

    Person* person;
    if (digit) {
        person = search_phone(std::stoi(input));
    } else {
        person = search_name(input);
    }

    if (person == nullptr) {
        std::cout << "不存在该联系人, 是否添加?" << std::endl;
    } else {
        std::cout << person << std::endl;
    }
}

void Book::add() {
    std::cout << "请依次输入联系人姓名, 地址, 联系电话 (回车键输入, 如有多个电话, 请以空格分隔开来)" << std::endl;
    std::string name, address, phones;

    // std::cin >> std::noskipws;
    // std::cin >> name >> address >> phones;
    getline(std::cin, name);
    getline(std::cin, address);
    getline(std::cin, phones);

    Person person(name, address);

    if (search_name(name) != nullptr) {
        std::cout << "该联系人已存在: " << std::endl;
        std::cout << person << std::endl;
        return;
    }

    std::istringstream phonesStream(phones);
    int phone;
    while (phonesStream >> phone) {
        person.phones.push(phone);
    }
    book.insert(person);

    if (search_name(name) == nullptr) {
        std::cout << "添加失败, 请重试" << std::endl;
    } else {
        std::cout << "添加成功! 已添加联系人: " << std::endl;
        std::cout << person << std::endl;
    }
}

void Book::del() {
    std::cout << "请输入联系人姓名" << std::endl;
    std::string name;
    std::cin >> name;

    Person* person = search_name(name);

    if (person == nullptr) {
        std::cout << "不存在该联系人" << std::endl;
    } else {
        std::cout << "查询到联系人: " << std::endl;
        std::cout << *person << std::endl;
        std::cout << "是否删除该联系人(输入yes/no)" << std::endl;
        std::string input;
        while (std::cin >> input) {
            if (input == "yes") {
                book.remove(name);
                break;
            } else if (input == "no") {
                break;
            } else {
                continue;
            }
        }
    }
}

void Book::mod() {
    std::cout << "请输入联系人姓名" << std::endl;
    std::string name;
    std::cin >> name;

    Person* person = search_name(name);

    if (person == nullptr) {
        std::cout << "不存在该联系人" << std::endl;
    } else {
        std::cout << "查询到联系人: " << std::endl;
        std::cout << *person << std::endl;

        std::cout << "请输入新地址(若不改变地址则不进行输入)" << std::endl;
        std::string address;
        std::cin >> address;
        if (address != "") {
            person->address = address;
        }
        std::cout << "请输入新添加的电话号码(若不添加则不进行输入)" << std::endl;
        std::string phones;
        std::cin >> phones;
        std::istringstream phonesStream(phones);
        int phone;
        while (phonesStream >> phone) {
            person->phones.push(phone);
        }

        std::cout << "请输入欲删除的电话号码(若不删除则不进行输入)" << std::endl;
        std::cin >> phones;
        std::istringstream phonesStream_(phones);
        while (phonesStream_ >> phone) {
            person->phones.remove(phone);
        }

        std::cout << "修改成功: " << std::endl;
        std::cout << *person << std::endl;
    }
}

void Book::sort() {}

void Book::show() { book.print_tree(); }

Person* Book::search_name(std::string name) {
    Person temp(name);
    AVLTNode<Person>* node = book.search(temp);
    if (node == nullptr) {
        return nullptr;
    } else {
        return &node->key;
    }
}

Person* Book::search_phone(int phone) {
    Person temp(book_phone.search(Pair(phone, ""))->key.val);
    AVLTNode<Person>* node = book.search(temp);
    if (node == nullptr) {
        return nullptr;
    } else {
        return &node->key;
    }
}
