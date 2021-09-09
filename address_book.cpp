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
    std::cin.ignore();
name_or_phone:
    getline(std::cin, input);
    trim(input);
    if (input.empty()) {
        std::cout << "输入为空, 请重新输入\n" << std::endl;
        goto name_or_phone;
    }

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
        std::cout << "不存在该联系人, 是否添加? (输入yes/no)" << std::endl;
        std::string input;
        while (std::cin >> input) {
            if (input == "yes") {
                add();
                break;
            } else if (input == "no") {
                break;
            } else {
                continue;
            }
        }
    } else {
        std::cout << *person << std::endl;
    }
}

void Book::add() {
    std::cout << "请依次输入联系人姓名, 地址, 联系电话 (回车键输入, 如有多个电话, 请以空格分隔开来)" << std::endl;
    std::string name, address, phones;
    std::cin.ignore();

wr_name:
    std::cout << "姓名: ";
    getline(std::cin, name);
    trim(name);
    bool space = true;
    for (char c : name) {
        if (!isspace(c)) {
            space = false;
            break;
        }
    }
    if (space) {
        std::cout << "输入姓名为空, 请重新输入\n" << std::endl;
        goto wr_name;
    }
    Person* exist = search_name(name);
    if (exist != nullptr) {
        std::cout << "该联系人已存在: ";
        std::cout << *exist << '\n' << std::endl;
        goto wr_name;
    }

wr_address:
    std::cout << "地址: ";
    getline(std::cin, address);
    trim(address);
    space = true;
    for (char c : address) {
        if (!isspace(c)) {
            space = false;
            break;
        }
    }
    if (space) {
        std::cout << "输入地址为空, 请重新输入\n" << std::endl;
        goto wr_address;
    }

wr_phones:
    std::cout << "电话号码: ";
    getline(std::cin, phones);

    Person person(name, address);

    std::istringstream phonesStream(phones);
    int phone;
    while (phonesStream >> phone) {
        Person* temp = search_phone(phone);
        if (temp != nullptr) {
            std::cout << "\n电话号码" << phone << "已存在, 不予保存" << std::endl;
            std::cout << *temp << '\n' << std::endl;
        } else {
            person.phones.push(phone);
            book_phone.insert(Pair(phone, name));
        }
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
    std::cout << "请输入联系人姓名: ";
    std::string name;
    std::cin.ignore();
    getline(std::cin, name);
    trim(name);
    std::cout << std::endl;

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
                for (int i = 0; i < person->phones.number; ++i) {
                    book_phone.remove(Pair(person->phones[i], ""))
                }
                int ret = book.remove(*person);
                if (ret == 1) {
                    std::cout << "删除成功!" << std::endl;
                } else if (ret == 0) {
                    std::cout << "删除失败!" << std::endl;
                }
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
    std::cout << "请输入联系人姓名: ";
    std::string name;
    std::cin.ignore();
    getline(std::cin, name);
    trim(name);
    std::cout << std::endl;

    Person* person = search_name(name);

    if (person == nullptr) {
        std::cout << "不存在该联系人" << std::endl;
    } else {
        std::cout << "查询到联系人: " << std::endl;
        std::cout << *person << std::endl;

        std::cout << "请输入新地址(若不改变地址则不进行输入): ";
        std::string address;
        getline(std::cin, address);
        trim(address);
        if (!address.empty()) {
            person->address = address;
        }

        std::cout << "请输入新添加的电话号码(若不添加则不进行输入): ";
        std::string phones;
        getline(std::cin, phones);
        std::istringstream phonesStream(phones);
        int phone;
        while (phonesStream >> phone) {
            Person* temp = search_phone(phone);
            if (temp != nullptr) {
                std::cout << "\n电话号码" << phone << "已存在, 不予保存" << std::endl;
                std::cout << *temp << '\n' << std::endl;
            } else {
                person->phones.push(phone);
                book_phone.insert(Pair(phone, name));
            }
        }

        std::cout << "请输入欲删除的电话号码(若不删除则不进行输入): ";
        getline(std::cin, phones);
        std::istringstream phonesStream_(phones);
        while (phonesStream_ >> phone) {
            person->phones.remove(phone);
            book_phone.remove(Pair(phone, ""));
        }

        std::cout << "修改成功: " << std::endl;
        std::cout << *person << std::endl;
    }
}

void Book::sort() {
    std::cout << "联系人: " << std::endl;
    // book_phone.print_tree();

    Array<Person*> people;

    AVLTNode<Pair>* root = book_phone.root;
    Array<AVLTNode<Pair>*> nodes;

    while (!nodes.empty() || root != nullptr) {
        if (root != nullptr) {
            nodes.push(root);
            root = root->left;
        } else {
            root = nodes.top();
            nodes.pop();
            people.push(search_name(root->key.val));
            root = root->right;
        }
    }

    for (int i = 0; i < people.number; ++i) {
        Person* person = people[i];
        std::cout << *person << std::endl;
    }
}

void Book::show() {
    std::cout << "联系人: " << std::endl;
    book.print_tree();
}

void Book::showmenu() {
    std::cout << "=======通讯录=======" << '\n'
              << "1. 查看联系人" << '\n'
              << "2. 添加联系人" << '\n'
              << "3. 搜索联系人" << '\n'
              << "4. 修改联系人" << '\n'
              << "5. 删除联系人" << '\n'
              << "6. 排序联系人" << '\n'
              << "0. 退出通讯录" << '\n'
              << std::endl;
}

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
    AVLTNode<Pair>* pair = book_phone.search(Pair(phone, ""));
    if (pair == nullptr) {
        return nullptr;
    }
    Person temp(pair->key.val);
    AVLTNode<Person>* node = book.search(temp);
    if (node == nullptr) {
        return nullptr;
    } else {
        return &node->key;
    }
}
