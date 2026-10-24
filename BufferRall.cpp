
#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;

class BufferRAII {
private:
    unique_ptr<char[]> data;
    size_t taille;

public:
    // Constructeur
    explicit BufferRAII(size_t t)
        : data(make_unique<char[]>(t)), taille(t) {

        fill_n(data.get(), taille, 0);

        cout << "Buffer de " << taille
             << " octets cree" << endl;
    }

    // Accesseur
    char* get() const {
        return data.get();
    }

    // Obtenir la taille
    size_t size() const {
        return taille;
    }
};

int main() {
    BufferRAII b(256);

    cout << "Taille du buffer : "
         << b.size() << " octets" << endl;

    return 0;
}
