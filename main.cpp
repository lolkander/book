#include "catalog_book.h"
#include <iostream>
#include <vector>
#include <string>
#include <windows.h> // Для функций установки кодировки консоли
#include <locale.h> // Для работы с локалью

using namespace std;

// Функция печати информации о книге
void printBookInfo(const CatalogBook& book) {
    cout << "------------------------------------------" << endl;
    cout << "Информация о книге:" << endl;
    book.printInfo();
    cout << "------------------------------------------" << endl;
}

// Функция печати списка просроченных читателей
void printOverdueReaders(const vector<CatalogBook>& catalog) {
    cout << "------------------------------------------" << endl;
    cout << "Список читателей, не вернувших книги в течение года:" << endl;
    for (const CatalogBook& book : catalog) {
        for (const reader& r : book.getPicked()) {
            cout << "- " << r.name << " (" << r.date << ") - книга: " << book.getTitle() << endl;
        }
    }
    cout << "------------------------------------------" << endl;
}

unsigned int CatalogBook::count = 0;

int main() {
    SetConsoleOutputCP(CP_UTF8); // Установка кодировки консоли на UTF-8

    vector<CatalogBook> catalog; // Вектор для хранения книг-каталогов

    // Main menu loop
    while (true) {
        cout << "\n------------------------------------------" << endl;
        cout << "Меню библиотечного каталога:" << endl;
        cout << "1. Добавить книгу" << endl;
        cout << "2. Удалить книгу" << endl;
        cout << "3. Вывести информацию о книге" << endl;
        cout << "4. Поиск книги по названию" << endl;
        cout << "5. Поиск книги по автору" << endl;
        cout << "6. Выдать книгу читателю" << endl;
        cout << "7. Вернуть книгу" << endl;
        cout << "8. Список читателей, не вернувших книги" << endl;
        cout << "9. Вывести список всех книг" << endl;
        cout << "0. Выход" << endl;
        cout << "------------------------------------------" << endl;

        int choice;
        cout << "Введите свой выбор: ";
        cin >> choice;
        cin.ignore(); // Очистить буфер ввода перед использованием getline()

        switch (choice) {
        case 1: { // Добавить книгу
            string title, publisher;
            unsigned int year, pages, quantity;
            vector<string> authors;
            string authors_input;

            cout << "\nВведите название книги: ";
            getline(cin, title);

            cout << "\nВведите авторов книги (через запятую): ";
            getline(cin, authors_input);
            // Разделение строки авторов по запятым
            size_t pos = 0;
            while ((pos = authors_input.find(',')) != string::npos) {
                authors.push_back(authors_input.substr(0, pos));
                authors_input.erase(0, pos + 1);
            }
            authors.push_back(authors_input); // Добавить последний автор

            cout << "\nВведите год издания: ";
            cin >> year;
            cin.ignore();

            cout << "\nВведите издательство: ";
            getline(cin, publisher);

            cout << "\nВведите количество страниц: ";
            cin >> pages;

            cout << "\nВведите общее количество экземпляров: ";
            cin >> quantity;

            CatalogBook book(title, authors, year, publisher, pages,
                quantity, quantity, {});
            catalog.push_back(book);

            cout << "\nКнига успешно добавлена!" << endl;
            break;
        }

        case 2: { // Удалить книгу
            if (catalog.empty()) {
                cout << "\nКаталог пуст. Нечего удалять." << endl;
                break;
            }

            int id;
            cout << "\nВведите идентификатор книги для удаления: ";
            cin >> id;

            bool found = false;
            for (size_t i = 0; i < catalog.size(); ++i) {
                if (catalog[i].getId() == id) {
                    catalog.erase(catalog.begin() + i);
                    found = true;
                    break;
                }
            }

            if (found) {
                cout << "\nКнига успешно удалена!" << endl;
            }
            else {
                cout << "\nКнига с идентификатором " << id << " не найдена." << endl;
            }
            break;
        }

        case 3: {
            if (catalog.empty()) {
                cout << "\nКаталог пуст. Нет книг для отображения." << endl;
                break;
            }

            int id;
            cout << "\nВведите идентификатор книги для отображения: ";
            cin >> id;

            bool found = false;
            for (CatalogBook book : catalog) {
                if (book.getId() == id) {
                    printBookInfo(book);
                    cout << "\nСписок читателей, взявших эту книгу:" << endl;
                    if (book.getPicked().empty()) {
                        cout << "\t- Нет читателей." << endl;
                    }
                    else {
                        for (const reader& r : book.getPicked()) {
                            cout << "\t- " << r.name << " (" << r.date << ")" << endl;
                        }
                    }
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "\nКнига с идентификатором " << id << " не найдена." << endl;
            }
            break;
        }

        case 4: { // Поиск книги по названию
            if (catalog.empty()) {
                cout << "\nКаталог пуст. Книги отсутствуют." << endl;
                break;
            }

            string title;
            cout << "\nВведите название книги для поиска: ";
            cin >> title;

            bool found = false;
            for (const CatalogBook& book : catalog) {
                if (book.getTitle() == title) {
                    cout << "\nНайдена книга: " << endl;
                    printBookInfo(book);
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "\nКнига с названием \"" << title << "\" не найдена." << endl;
            }
            break;
        }

        case 5: { // Поиск книги по автору
            if (catalog.empty()) {
                cout << "\nКаталог пуст. Книги отсутствуют." << endl;
                break;
            }

            string author;
            cout << "\nВведите автора книги для поиска: ";
            cin >> author;

            bool found = false;
            for (const CatalogBook& book : catalog) {
                for (const string& a : book.getAuthors()) {
                    if (a == author) {
                        cout << "\nНайдена книга: " << endl;
                        printBookInfo(book);
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break; // Прекратить поиск после того, как найдется книга
                }
            }

            if (!found) {
                cout << "Книги с автором \"" << author << "\" не найдены." << endl;
            }
            break;
        }

        case 6: { // Выдать книгу читателю
            if (catalog.empty()) {
                cout << "\nКаталог пуст. Нельзя выдать книгу." << endl;
                break;
            }

            int id;
            string readerName, date;
            cout << "\nВведите идентификатор книги для выдачи: ";
            cin >> id;

            bool found = false;
            for (CatalogBook& book : catalog) {
                if (book.getId() == id && book.getInstances() > 0) {
                    cout << "\nВведите имя читателя: ";
                    cin >> readerName;
                    cout << "\nВведите дату: ";
                    cin >> date;
                    book.addReader(readerName, date);
                    found = true;
                    break;
                }
            }

            if (found) {
                cout << "\nКнига успешно выдана читателю " << readerName << endl;
            }
            else {
                cout << "\nКнига с идентификатором " << id << " не найдена." << endl;
            }
            break;
        }

        case 7: { // Возврат книги читателем
            if (catalog.empty()) {
                cout << "\nКаталог пуст. Нельзя вернуть книгу." << endl;
                break;
            }

            int id;
            string readerName;
            cout << "\nВведите идентификатор книги для возврата: ";
            cin >> id;

            bool found = false;
            for (CatalogBook& book : catalog) {
                if (book.getId() == id) {
                    cout << "\nВведите имя читателя, вернувшего книгу: ";
                    cin >> readerName;
                    book.returnBook(readerName);
                    found = true;
                    break;
                }
            }

            if (found) {
                cout << "\nКнига успешно возвращена." << endl;
            }
            else {
                cout << "\nКнига с идентификатором " << id << " не найдена." << endl;
            }
            break;
        }

        case 8: { // Вывод списка читателей
            printOverdueReaders(catalog);
            break;
        }

        case 9: { // Вывести список всех книг
            if (catalog.empty()) {
                cout << "Каталог пуст. Нет книг для отображения." << endl;
                break;
            }

            cout << "\n------------------------------------------" << endl;
            cout << "Список всех книг в каталоге:" << endl;

            for (const CatalogBook& book : catalog) {
                cout << "------------------------------------------" << endl;
                book.printInfo();
                cout << "------------------------------------------" << endl;
            }

            cout << "\n------------------------------------------" << endl;
            break;
        }

        case 0: { // Exit
            cout << "\nДо свидания!" << endl;
            return 0;
        }

        default:
            cout << "\nНеверный выбор." << endl;
        }
    }
}