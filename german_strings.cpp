#include <iostream>
#include <cstring>
#include <stdexcept> //ovie 3 ili bits
using namespace std;

//klasa
class GermanString {
private:
    static const size_t SHORT_STRING_SIZE = 15; // Max size za short string
    union {
        char shortString[SHORT_STRING_SIZE + 1]; //ako null terminator = +1size
        char* longString;
    };
    size_t length;
    bool isShortString;

public:
    // konstuktor za short strings
    GermanString(const char* str) {
        if (strlen(str) <= SHORT_STRING_SIZE) {
            strcpy(shortString, str);
            length = strlen(str);
            isShortString = true;
        } else {
            longString = new char[strlen(str) + 1];
            strcpy(longString, str);
            length = strlen(str);
            isShortString = false;
        }
    }
 
    // kopiraj konstuktor za posle
    GermanString(const GermanString& other) {
        length = other.length;
        isShortString = other.isShortString;
        if (isShortString) {
            strcpy(shortString, other.shortString);
        } else {
            longString = new char[length + 1];
            strcpy(longString, other.longString);
        }
    }

    // za demontiranje
    ~GermanString() {
        if (!isShortString) {
            delete[] longString;
        }
    }

    // metod za nogjanje dolzina
    size_t getLength() const {
        return length;
    }

    // metod za string data
    const char* c_str() const {
        return isShortString ? shortString : longString; //moj omilen operator
    }

    // Za operatorot so strings da rabotit
    GermanString& operator=(const GermanString& other) {
        if (this != &other) {
            if (!isShortString) {
                delete[] longString;
            }
            length = other.length;
            isShortString = other.isShortString;
            if (isShortString) {
                strcpy(shortString, other.shortString);
            } else {
                longString = new char[length + 1];
                strcpy(longString, other.longString);
            }
        }
        return *this;
    }
};



int main() {
    
    //neka primeri E
    GermanString shortStr("Hello");
    GermanString longStr("Neka ima dolga recenica long longer longest.");

    cout << "Short: " << shortStr.c_str() << " (Length: " << shortStr.getLength() << ")" << endl;
    cout << "Long: " << longStr.c_str() << " (Length: " << longStr.getLength() << ")" << endl;

    return 0;
}
