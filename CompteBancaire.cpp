
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;

class CompteBancaire {
private:
    string numero;
    double solde;
    string* historique;
    size_t capacite;
    size_t nbOps;

    // Agrandir le tableau si nécessaire
    void agrandirHistorique() {
        size_t nouvelleCap = (capacite == 0) ? 2 : capacite * 2;

        string* nouveau = new string[nouvelleCap];

        for (size_t i = 0; i < nbOps; i++) {
            nouveau[i] = historique[i];
        }

        delete[] historique;

        historique = nouveau;
        capacite = nouvelleCap;
    }

    // Ajouter une opération à l'historique
    void ajouterOperation(const string& operation) {
        if (nbOps == capacite) {
            agrandirHistorique();
        }

        historique[nbOps] = operation;
        nbOps++;
    }

public:
    // 1. Constructeur par défaut
    CompteBancaire()
        : numero("NON_DEFINI"), solde(0),
          historique(new string[10]), capacite(10), nbOps(0) {
        cout << "Compte cree" << endl;
    }

    // 2. Constructeur paramétré
    CompteBancaire(string num, double s)
        : numero(num), solde(s),
          historique(new string[10]), capacite(10), nbOps(0) {
        ajouterOperation("Creation du compte");
    }

    // 3. Constructeur de copie
    CompteBancaire(const CompteBancaire& autre)
        : numero(autre.numero), solde(autre.solde),
          historique(new string[autre.capacite]),
          capacite(autre.capacite), nbOps(autre.nbOps) {

        for (size_t i = 0; i < nbOps; i++) {
            historique[i] = autre.historique[i];
        }

        cout << "Copie du compte" << endl;
    }

    // 4. Constructeur de déplacement
    CompteBancaire(CompteBancaire&& autre) noexcept
        : numero(move(autre.numero)), solde(autre.solde),
          historique(autre.historique),
          capacite(autre.capacite), nbOps(autre.nbOps) {

        autre.historique = nullptr;
        autre.capacite = 0;
        autre.nbOps = 0;
        autre.solde = 0;

        cout << "Deplacement du compte" << endl;
    }

    // 5. Destructeur
    ~CompteBancaire() {
        delete[] historique;
        cout << "Destruction du compte " << numero << endl;
    }

    // 6. Dépôt
    void deposer(double montant) {
        if (montant <= 0) {
            cout << "Montant invalide" << endl;
            return;
        }

        solde += montant;
        ajouterOperation("Depot de " + to_string(montant));

        cout << "Depot effectue" << endl;
    }

    // 7. Retrait
    void retirer(double montant) {
        if (montant <= 0 || montant > solde) {
            cout << "Retrait impossible" << endl;
            return;
        }

        solde -= montant;
        ajouterOperation("Retrait de " + to_string(montant));

        cout << "Retrait effectue" << endl;
    }

    // 8. Affichage du compte
    void afficher() const {
        cout << "\nNumero : " << numero << endl;
        cout << "Solde : " << solde << " DH" << endl;
        cout << "Historique :" << endl;

        for (size_t i = 0; i < nbOps; i++) {
            cout << "- " << historique[i] << endl;
        }
    }
};

int main() {
    CompteBancaire c1("FR123456", 500);

    c1.deposer(200);
    c1.retirer(150);
    c1.afficher();

    // Test de la copie
    CompteBancaire c2 = c1;
    c2.afficher();

    // Test du déplacement
    CompteBancaire c3 = move(c1);
    c3.afficher();

    return 0;
}
