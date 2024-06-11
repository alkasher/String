// String.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <cstring>

class Exception : public std::exception {
protected:
    char* str;
public:
    Exception(const char* s) {
        str = new char[strlen(s)];
        strcpy_s(str, strlen(s) + 1, s);
    }
    void print() const {
        std::cout << "\nException" << str;
    }
};

class InvalidLengthException : public Exception {
public:
    InvalidLengthException(const char* s) : Exception(s) {}
    void print() const {
        std::cout << "\nInvalidLengthException" << str;
    }
};

class NotEnoughSpaceException : public Exception {
public:
    NotEnoughSpaceException(const char* s) : Exception(s) {}
    void print() const {
        std::cout << "\nNotEnoughSpaceException" << str;
    }
};

class NullptrException : public Exception {
public:
    NullptrException(const char* s) : Exception(s) {}
    void print() const {
        std::cout << "\nNullptrException" << str;
    }
};

class String {
private:
    char* buffer;
    int len;
public:
    String(const char* buffer) {
        len = strlen(buffer);
        if (!(this->buffer = new char[len])) throw NotEnoughSpaceException("String Constructor: NotEnoughSpace");
        for (int i = 0; i < len; ++i) {
            this->buffer[i] = buffer[i];
        }
    }

    String(const String& str) {
        if (str.buffer == nullptr) throw NullptrException("String CopyConstructor: Nullptr");
        this->len = str.len;
        if (!(this->buffer = new char[len])) throw NotEnoughSpaceException("String CopyConstructor: NotEnoughSpace");
        for (int i = 0; i < len; ++i) {
            buffer[i] = str.buffer[i];
        }
    }

    String operator=(const String& str) {
        len = str.len;
        if (str.buffer == this->buffer) return *this;
        if (str.buffer == nullptr) { throw NullptrException("operator=: Nullptr"); }
        delete[] buffer;
        if (!(buffer = new char[len])) throw NotEnoughSpaceException("operator=: NotEnoughSpaceException");
        for (int i = 0; i < len; ++i) {
            buffer[i] = str.buffer[i];
        }
        return *this;
    }

    bool operator==(const String& str) {
        if (len != str.len) return false;
        if (str.buffer == nullptr || this->buffer == nullptr) return false;
        for (int i = 0; i < len; ++i) {
            if (!(this->buffer[i] == str.buffer[i])) {
                return false;
            }
        }
        return true;
    }

    int get_len() const {
        return this->len;
    }

    char* get_buffer() const {
        return this->buffer;
    }

    char operator[](int index) const {
        if (index < 0 || index > len) throw InvalidLengthException("operator[]: InvalidLength");
        return buffer[index];
    }

    friend std::ostream& operator<<(std::ostream& ustream, const String& str) {
        if (typeid(ustream).name() == typeid(std::ofstream).name())
        {

            ustream << str.len << '\n';
            for (int i = 0; i < str.len; ++i)
            {
                ustream << str.buffer[i];
            }
            ustream << '\n';
            return ustream;
        }
        for (int i = 0; i < str.len; ++i)
        {
            ustream << str.buffer[i];
        }
        ustream << '\n';
        return ustream;
    }

    ~String() {
        delete[] buffer;
    }

};

int main()
{
    char buffer[7] = "qwerty";
    String s1(buffer);
    std::cout << s1;
    String s2(s1);
    std::cout << s2;
}
