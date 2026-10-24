
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

class Buffer {
private:
    char* data;
    size_t taille;

public:
    // 1. Constructeur par défaut
    Buffer() : data(nullptr), taille(0) {
        cout << "Buffer vide cree" << endl;
    }

    // 2. Constructeur parametre
    explicit Buffer(size_t t) : data(new char[t]()), taille(t) {
        cout << "Buffer de " << taille << " octets cree" << endl;
    }

    // 3. Constructeur de copie
    Buffer(const Buffer& autre)
        : data(new char[autre.taille]),
          taille(autre.taille) {

        for (size_t i = 0; i < taille; i++) {
            data[i] = autre.data[i];
        }

        cout << "Constructeur de copie" << endl;
    }

    // 4. Constructeur de deplacement
    Buffer(Buffer&& autre) noexcept
        : data(autre.data), taille(autre.taille) {

        autre.data = nullptr;
        autre.taille = 0;

        cout << "Constructeur de deplacement" << endl;
    }

    // 5. Operateur d'affectation par copie
    Buffer& operator=(const Buffer& autre) {
        if (this != &autre) {
            char* nouveau = new char[autre.taille];

            for (size_t i = 0; i < autre.taille; i++) {
                nouveau[i] = autre.data[i];
            }

            delete[] data;

            data = nouveau;
            taille = autre.taille;
        }

        cout << "Affectation par copie" << endl;
        return *this;
    }

    // 6. Operateur d'affectation par deplacement
    Buffer& operator=(Buffer&& autre) noexcept {
        if (this != &autre) {
            delete[] data;

            data = autre.data;
            taille = autre.taille;

            autre.data = nullptr;
            autre.taille = 0;
        }

        cout << "Affectation par deplacement" << endl;
        return *this;
    }

    // 7. Destructeur
    ~Buffer() {
        delete[] data;
        cout << "Destruction du buffer" << endl;
    }

    // 8. Accesseurs
    char* getData() const {
        return data;
    }

    size_t getTaille() const {
        return taille;
    }
};

int main() {
    Buffer b1(128);

    Buffer b2 = b1;          // Constructeur de copie
    Buffer b3 = move(b1);    // Constructeur de deplacement

    b2 = b3;                 // Affectation par copie
    b3 = Buffer(64);         // Affectation par deplacement

    cout << "Taille de b2 : " << b2.getTaille() << endl;
    cout << "Taille de b3 : " << b3.getTaille() << endl;

    return 0;
}
