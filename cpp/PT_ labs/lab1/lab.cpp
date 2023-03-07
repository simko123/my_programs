#include <iostream>
#include <vector>

struct product {
    std::string name;
    unsigned price, amount;
};

product inputNewProduct() {
    product newProduct;
    std::cout << "Введите название товара: "; 
    std::cin >> newProduct.name;
    std::cout << "Введите цену товара: "; 
    std::cin >> newProduct.price;
    std::cout << "Введите количество товара: "; 
    std::cin >> newProduct.amount;
    return newProduct;
}

class Products {
public:
    Products(){ };

    // Вставка товара на определенную позицию.
    // 0 - начало, -1 - конец, 
    // любой другой номер - вставка после него.
    void insertTo(int pos, product newProduct) {
        // Проверим, существуют товары с тем же именем.
        // Если да, увеличим количество и спросим, желает ли пользователь сменить цену.
        for (product &prod : products) {
            if (newProduct.name == prod.name) {
                prod.amount += newProduct.amount;
                if (prod.price != newProduct.price) {
                    char decision;
                    std::cout << "Вы хотите сменить цену товара? [y/n]: ";
                    std::cin >> decision;
                    if (decision == 'y' || decision == 'Y') prod.price = newProduct.price;
                }
                return;
            }
        }
        if (pos == -1) products.push_back(newProduct);
        else if (pos >= 0) products.insert(products.begin() + pos, newProduct);
    }

    void removeFrom(unsigned pos) {
        products.erase(products.begin() + pos - 1);
    }

    void info(unsigned pos) {
        --pos;
        std::cout << std::endl <<
            "Название: " << products.at(pos).name << std::endl <<
            "Цена: " << products.at(pos).price << std::endl <<
            "Количество: " << products.at(pos).amount << std::endl 
        << std::endl;
    }

    void printAll() {
        std::cout << std::endl;
        for (int i = 0; i < products.size(); ++i) {
            std::cout << i+1 << ". " << products.at(i).name << std::endl;
        }
        std::cout << std::endl;
    }

    bool isEmpty() {
        return products.empty();
    }

    size_t size() {
        return products.size();
    }

private:
    std::vector<product> products;
};

int main() {
    setlocale(LC_ALL, "Russian");
    Products products;
    while (true) {
        std::cout <<
            "1. Добавить новый товар в начало списка." << std::endl <<
            "2. Добавить новый товар в конец списка." << std::endl <<
            "3. Добавить новый товар перед существующем выбранным товаром в списке." << std::endl <<
            "4. Добавить новый товар после существующего товара в списке." << std::endl <<
            "5. Удалить определенный товар из списка." << std::endl <<
            "6. Вывести на экран информацию о выбранном товаре." << std::endl <<
            "7. Вывести на экран весь список целиком." << std::endl <<
            "0. Выйти из программы." 
        << std::endl;
        char option;
        std::cin >> option;
        switch (option) {
            case '1': {
                product newProduct = inputNewProduct();
                products.insertTo(0, newProduct);
                std::cout << "Товар успешно добавлен!" << std::endl;
                break;
            }
            case '2': {
                product newProduct = inputNewProduct();
                products.insertTo(-1, newProduct);
                std::cout << "Товар успешно добавлен!" << std::endl;
                break;
            }
            case '3': {
                product newProduct = inputNewProduct();
                unsigned pos;
                products.printAll(); 
                std::cout << "Введите номер позиции, перед которой добавить товар: "; 
                std::cin >> pos;
                products.insertTo(pos - 1, newProduct);
                std::cout << "Товар успешно добавлен!" << std::endl;
                break;
            }
            case '4': {
                product newProduct = inputNewProduct();
                unsigned pos;
                products.printAll();
                std::cout << "Введите номер позиции, после которой добавить товар: "; 
                std::cin >> pos;
                products.insertTo(pos, newProduct);
                std::cout << "Товар успешно добавлен!" << std::endl;
                break;
            }
            case '5': {
                if (products.isEmpty()) {
                    std::cout << "Список пуст." << std::endl;
                    break;
                }
                products.printAll();
                unsigned pos;
                std::cout << "Введите номер позиции для удаления: "; 
                std::cin >> pos;
                if (pos > products.size()) {
                    std::cout << "Позиции не существует." << std::endl;
                    break;
                }
                products.removeFrom(pos);
                break;
            }
            case '6': {
                if (products.isEmpty()) {
                    std::cout << "Список пуст." << std::endl;
                    break;
                }
                unsigned pos;
                products.printAll();
                std::cout << "Введите номер позиции, о которой хотите получить информацию: "; 
                std::cin >> pos;
                if (pos > products.size()) {
                    std::cout << "Позиции не существует." << std::endl;
                    break;
                }
                products.info(pos);
                break;
            }
            case '7': {
                if (products.isEmpty()) {
                    std::cout << "Список пуст." << std::endl;
                    break;
                }
                products.printAll();
                break;
            }
            case '0': {
                return 0;
            }
        }
        std::cout << std::endl;
    }
}