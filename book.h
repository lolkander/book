#ifndef OOPZAD_BOOK_H
#define OOPZAD_BOOK_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;


class Book {
private:
    string title;
    vector<string> authors;
    unsigned int year;
    string publisher;
    unsigned int pages;

public:
    // Конструктор по умолчанию
    Book() : title(""), authors({}), year(0), publisher(""), pages(0) {}

    // Конструктор с параметрами
    Book(const string& title_, const vector<string>& authors_, const unsigned int& year_,
         const string& publisher_, const unsigned int& pages_)
            : title(title_),
              authors(authors_),
              year(year_),
              publisher(publisher_),
              pages(pages_) {}

    // Getters
    const string& getTitle() const { return title; }
    const vector<string>& getAuthors() const { return authors; }
    unsigned int getYear() const { return year; }
    const string& getPublisher() const { return publisher; }
    unsigned int getPages() const { return pages; }

    // Setters
    void setTitle(const string& title_) { title = title_; }
    void setAuthors(const vector<string>& authors_) { authors = authors_; }
    void setYear(const unsigned int& year_) { year = year_; }
    void setPublisher(const string& publisher_) { publisher = publisher_; }
    void setPages(const unsigned int& pages_) { pages = pages_; }

    // Способ печати информации о книге
    virtual void printInfo() const {
        cout << "Название: " << title << endl;
        cout << "Авторы: ";
        for (const string& author : authors) {
            cout << author << ", ";
        }
        cout << endl;
        cout << "Год издания: " << year << endl;
        cout << "Издательство: " << publisher << endl;
        cout << "Количество страниц: " << pages << endl;
    }
};

#endif // OOPZAD_BOOK_H