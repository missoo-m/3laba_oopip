#include <iostream>
#include <list>
#include <vector>
#include <array>
#include <algorithm>
#include <fstream>
#include <string>
#include <locale.h>
using namespace std;

class Property 
{
private:
    int id;
    string owner;
    string type;
    double price;
    string address;

public:
    Property() = default;//типо по умолчанию чтобы точно создал для своей же безопастности 
    Property(int id, string owner, string type, double price, string address)
        : id(id), owner(owner), type(type), price(price), address(address) {}

    int getId() const { return id; }
    string getOwner() const { return owner; }
    string getType() const { return type; }
    double getPrice() const { return price; }
    string getAddress() const { return address; }

    void setOwner(string newOwner) { owner = newOwner; }
    void setType(string newType) { type = newType; }
    void setPrice(double newPrice) { price = newPrice; }
    void setAddress(string newAddress) { address = newAddress; }

    void print() const
    {
        cout << "ID: " << id << "\nOwner: " << owner << "\nType: " << type
            << "\nPrice: " << price << "\nAddress: " << address << endl;
    }
};

void addProperty(list<Property>& properties, const Property& property) 
{
    properties.push_back(property);
}

void addProperty(vector<Property>& properties, const Property& property) 
{
    properties.push_back(property);
}

// Для массива (так как размер фиксированный)
template<size_t N>
void addProperty(array<Property, N>& properties, const Property& property, size_t& currentSize)
{
    if (currentSize < N) 
    {
        properties[currentSize] = property;
        currentSize++;
    }
    else
    {
        cerr << "Массив заполнен!" << endl;
    }
}

void removePropertyById(list<Property>& properties, int id) 
{
    properties.remove_if([id](const Property& p) { return p.getId() == id; });
}

void removePropertyById(vector<Property>& properties, int id)
{
    properties.erase(remove_if(properties.begin(), properties.end(),//ремуф не удаляет ,а возвращает итератор ,а вот ирасе уже удаляет по этомму итератору 
        [id](const Property& p) { return p.getId() == id; }), properties.end());
}

Property* findPropertyById(list<Property>& properties, int id)
{
    auto it = find_if(properties.begin(), properties.end(), [id](const Property& p) { return p.getId() == id; });
    if (it != properties.end()) return &(*it);
    return nullptr;
}

Property* findPropertyById(vector<Property>& properties, int id)
{
    auto it = find_if(properties.begin(), properties.end(), [id](const Property& p) { return p.getId() == id; });
    if (it != properties.end()) return &(*it);
    return nullptr;
}

template<size_t N>
Property* findPropertyById(array<Property, N>& properties, int id) 
{
    for (size_t i = 0; i < N; ++i) {
        if (properties[i].getId() == id) {
            return &properties[i];
        }
    }
    return nullptr;
}

void printProperties(const list<Property>& properties)
{
    for (const auto& property : properties) //авто  вывод типа с использованием ссылки
    {
        property.print();
        cout << "----------------------\n";
    }
}

void printProperties(const vector<Property>& properties) 
{
    for (const auto& property : properties) 
    {
        property.print();
        cout << "----------------------\n";
    }
}

template<size_t N>
void printProperties(const array<Property, N>& properties, size_t currentSize)
{
    for (size_t i = 0; i < currentSize; ++i) 
    {
        properties[i].print();
        cout << "----------------------\n";
    }
}

void writeToFile(const list<Property>& properties, const string& filename) 
{
   ofstream file(filename);
    if (file.is_open()) 
    {
        for (const auto& property : properties) 
        {
            file << "ID: " << property.getId() << "\nOwner: " << property.getOwner()
                << "\nType: " << property.getType() << "\nPrice: " << property.getPrice()
                << "\nAddress: " << property.getAddress() << "\n----------------------\n";
        }
        file.close();
    }
    else 
    {
        cerr << "Ошибка открытия файла" << endl;
    }
}

void writeToFile(const vector<Property>& properties, const string& filename) 
{
    ofstream file(filename);
    if (file.is_open())
    {
        for (const auto& property : properties) 
        {
            file << "ID: " << property.getId() << "\nOwner: " << property.getOwner()
                << "\nType: " << property.getType() << "\nPrice: " << property.getPrice()
                << "\nAddress: " << property.getAddress() << "\n----------------------\n";
        }
        file.close();
    }
    else 
    {
        cerr << "Ошибка открытия файла" << endl;
    }
}

void showMenu() 
{
    cout << "Меню:\n";
    cout << "1. Добавить недвижимость\n";
    cout << "2. Удалить недвижимость по ID\n";
    cout << "3. Найти недвижимость по ID\n";
    cout << "4. Вывести все объекты\n";
    cout << "5. Сохранить данные в файл\n";
    cout << "6. Выйти\n";
}

int main()
{
    setlocale(LC_ALL, "Rus");
    list<Property> propertyList;
    vector<Property> propertyVector;
    array<Property, 10> propertyArray;
    size_t currentArraySize = 0; // Текущее количество элементов в массиве

    int choice;
    int id;
    string owner, type, address;
    double price;

    do 
    {
        showMenu();
       cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) 
        {
        case 1:
            cout << "Введите ID: ";
            cin >> id;
            cout << "Введите владельца: ";
            cin.ignore();
            getline(cin, owner);
            cout << "Введите тип недвижимости: ";
            getline(cin, type);
            cout << "Введите цену: ";
            cin >> price;
            cout << "Введите адрес: ";
            cin.ignore();
            getline(cin, address);
            {
                Property property(id, owner, type, price, address);
                addProperty(propertyList, property);
                addProperty(propertyVector, property);
                addProperty(propertyArray, property, currentArraySize);
            }
            break;

        case 2:
            cout << "Введите ID для удаления: ";
            cin >> id;
            removePropertyById(propertyList, id);
            removePropertyById(propertyVector, id);
            break;

        case 3:
            cout << "Введите ID для поиска: ";
            cin >> id;
            if (Property* p = findPropertyById(propertyList, id)) 
            {
                p->print();
            }
            else 
            {
                cout << "Недвижимость не найдена в списке." << endl;
            }
            if (Property* p = findPropertyById(propertyVector, id))
            {
                p->print();
            }
            else 
            {
                cout << "Недвижимость не найдена в векторе." << endl;
            }
            if (Property* p = findPropertyById(propertyArray, id))
            {
                p->print();
            }
            else
            {
                cout << "Недвижимость не найдена в массиве." << endl;
            }
            break;

        case 4:
            cout << "Вывод всех объектов в списке:\n";
            printProperties(propertyList);
            cout << "Вывод всех объектов в векторе:\n";
            printProperties(propertyVector);
            cout << "Вывод всех объектов в массиве:\n";
            printProperties(propertyArray, currentArraySize);
            break;

        case 5:
            writeToFile(propertyList, "properties_list.txt");
            writeToFile(propertyVector, "properties_vector.txt");
            cout << "Данные сохранены в файлы." << endl;
            break;

        case 6:
            cout << "Выход." << endl;
            break;

        default:
            cout << "Неверный выбор, попробуйте снова." << endl;
        }

    } while (choice != 6);

    return 0;
}