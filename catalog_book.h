#ifndef OOPZAD_CATALOG_BOOK_H
#define OOPZAD_CATALOG_BOOK_H

#include "book.h"

using namespace std;


struct reader {
    string name;
    string date;
};


class CatalogBook : public Book {
private:
    static unsigned int count;
    unsigned int id;
    unsigned int quantity;
    unsigned int instances;
    vector<reader> picked;

public:
    // Конструктор по умолчанию
    CatalogBook() : Book(), quantity(0), instances(0), picked({}) {
        count++;
        this->id = count;
    }

    // Конструктор с параметрами
    CatalogBook(const string& title_, const vector<string>& authors_,
                const unsigned int& year_, const string& publisher_,
                const unsigned int& pages_,
                const unsigned int& quantity_, const unsigned int& instances_,
                const vector<reader>& picked_)
            : Book(title_, authors_, year_, publisher_, pages_),
              quantity(quantity_),
              instances(instances_),
              picked(picked_) {
        count++;
        this->id = count;
    }

    // Getters
    static unsigned int getCount() { return count; }
    unsigned int getId() { return id; }
    unsigned int getQuantity() const { return quantity; }
    unsigned int getInstances() const { return instances; }
    const vector<reader>& getPicked() const { return picked; }

    // Setters
    void setQuantity(const unsigned int& quantity_) { quantity = quantity_; }
    void setInstances(const unsigned int& instances_) { instances = instances_; }
    void setPicked(const vector<reader>& picked_) { picked = picked_; }

    // Способ добавления читателя в список тех, кто взял книгу
    void addReader(const string& readerName, const string& date) {
        reader rdr;
        rdr.name = readerName;
        rdr.date = date;
        picked.push_back(rdr);
        instances--;
    }

    // Способ возврата книги читателем
    void returnBook(const string& readerName) {
        for (auto it = picked.begin(); it != picked.end(); ++it) {
            if (it->name == readerName) {
                picked.erase(it);
                instances++;
                return;
            }
        }
    }

    // Способ печати информации о книге и читателях
    void printInfo() const override {
        Book::printInfo();
        cout << "Идентификатор: " << id << endl;
        cout << "Общее количество экземпляров: " << quantity << endl;
        cout << "Количество экземпляров в наличии: " << instances << endl;
        cout << "Список читателей, взявших книгу:" << endl;
        for (const reader& r : picked) {
            cout << "\t- " << r.name << " (" << r.date << ")" << endl;
        }
    }
};

#endif // OOPZAD_CATALOG_BOOK_H