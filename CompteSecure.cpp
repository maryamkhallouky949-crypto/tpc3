
#include <iostream>
#include <stdexcept>

using namespace std;

class CompteSecure {
private:
    double solde;

public:
    // Constructeur securise
    explicit CompteSecure(double soldeInitial)
        : solde(soldeInitial) {

        if (soldeInitial < 0) {
            throw invalid_argument(
                "Erreur : le solde initial ne peut pas etre negatif"
            );
        }
    }

    // Afficher le solde
    void afficher() const {
        cout << "Solde : " << solde << " DH" << endl;
    }
};

int main() {
    try {
        CompteSecure c1(500);
        c1.afficher();

        CompteSecure c2(-100);
        c2.afficher();
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }

    return 0;
}
