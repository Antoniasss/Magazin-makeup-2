#include <iostream>
#include<string>
#include<vector>
#include<memory>
#include <algorithm>
#include<map>
#include <stdexcept>

using namespace std;

class AbstractFactory;

class DiorFactory;

class FentyFactory;

class HudaFactory;


class ParfumFactory;

class Basket;

class Parfum_info;


class Client {
protected :
    std::string name;
    int age;
public :
    //default constructor
    Client(std::string _name = "", double a = 0) : name(_name), age(a) {};

    virtual ~Client() {}

    virtual void citire() { std::cin >> name >> age; }

    virtual std::string afisare() const { return " "; }
};

// Clasa abstracta de baza pentru produsele din magazin
class Magazin {
public :
    std::string tip_produs;
    double pret;
    int stoc;

    //constructor
    Magazin(std::string _tip_produs = "", double p = 0, int s = 0) : tip_produs(_tip_produs), pret(p), stoc(s) {}

    //destructor virtual pt polimorfism
    virtual ~Magazin() {}

//funtie virtuala pura pentru a aplica promotii
    virtual void promotii(std::string tip_produs) = 0;

    virtual std::string afisare() const = 0;

//fct virtuala pt clonare
    virtual std::shared_ptr<Magazin> clone() const = 0;
};

class Dior : public Magazin {
public :
    std::string produs;
    std::string culoare;

    Dior(const std::string &produs_, const std::string &culoare_) : produs(produs_), culoare(culoare_) {}

    //funtie de suprascriere pt a afisa informatiile din produsele dior
    std::string afisare() const override { return produs + " " + culoare + " "; }

    void promotii(std::string tip_produs) override {
        std::cout << "Promotii pentru produsele Dior." << std::endl;
        if (tip_produs == "lips") {
            try {
                if (pret / 2 < 0) {
                    throw std::runtime_error("Pret negativ dupa promotie");
                }
                pret /= 2;
                std::cout << "Reducere la jumatate pentru produsul Dior: " << produs << std::endl;
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }

    //fct de suprascriere pt clonarea obiectelor dior
    std::shared_ptr<Magazin> clone() const override {
        return std::make_shared<Dior>(*this);
    }
};

class Fenty : public Magazin {
public :
    std::string produs;
    std::string culoare;

    Fenty(const std::string &produs_, const std::string &culoare_) : produs(produs_), culoare(culoare_) {}

    std::string afisare() const override { return produs + " " + culoare + " "; }

    void promotii(std::string tip_produs) override {
        std::cout << "Promotii pentru produsele Fenty." << std::endl;
        if (tip_produs == "eyes") {
            try {
                if (pret / 2 < 0) {
                    throw std::runtime_error("Pret negativ dupa promotie");
                }
                pret /= 2;
                std::cout << "Reducere la jumatate pentru produsul Fenty: " << produs << std::endl;
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }

    std::shared_ptr<Magazin> clone() const override {
        return std::make_shared<Fenty>(*this);
    }

};

class Huda : public Magazin {
public:
    std::string produs;
    std::string culoare;

    Huda(const std::string &produs_, const std::string &culoare_) : produs(produs_), culoare(culoare_) {}

    std::string afisare() const override { return produs + " " + culoare + " "; }

    void promotii(std::string tip_produs) override {
        std::cout << "Promotii pentru produsele Huda." << std::endl;
        if (tip_produs == "lips") {
            try {
                if (pret / 2 < 0) {
                    throw std::runtime_error("Pret negativ dupa promotie");
                }
                pret /= 2;
                std::cout << "Reducere la jumatate pentru produsul Huda: " << produs << std::endl;
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }

    std::shared_ptr<Magazin> clone() const override {
        return std::make_shared<Huda>(*this);
    }

};

class Parfum : public Magazin {
public:
    std::string name;
    std::string scent;

    Parfum(const std::string &name_, const std::string &scent_, std::string _tip_produs = "", double p = 0, int s = 0)
            : Magazin(_tip_produs, p, s), name{name_}, scent{scent_} {}

    friend class Parfum_info;

    std::string afisare() const override { return name + " " + scent + " "; }

    void promotii(std::string tip_produs) override {
        std::cout << " Nu exista Promotii pentru parfumuri." << std::endl;
    }

    std::shared_ptr<Magazin> clone() const override {
        return std::make_shared<Parfum>(*this);
    }
};

//clasa statica pt informatiile despre parfumuri
class Parfum_info {
public:
    // Functie pt a verifica daca 2 parfumuri au acelasi miros
    static bool haveSameScent(const std::shared_ptr<Parfum> &perfume1, const std::shared_ptr<Parfum> &perfume2) {
        return perfume1->scent == perfume2->scent;
    }
};

//clasa statica pentru a determina tipul produselor(fata,ochi,buze)
class Tip {
public:
    //functie pentru a det tipul folosind dynamic_pointer_cast
    static void getProductType(const shared_ptr<Magazin> &product) {
        if (auto diorProduct = dynamic_pointer_cast<Dior>(product)) {
            cout << "Dior Product: " << diorProduct->tip_produs << std::endl;

        } else if (auto fentyProduct = dynamic_pointer_cast<Fenty>(product)) {
            cout << "Fenty Product: " << fentyProduct->tip_produs << std::endl;

        } else if (auto hudaProduct = dynamic_pointer_cast<Huda>(product)) {
            cout << "Huda Product: " << hudaProduct->tip_produs << std::endl;

        } else {
            cerr << "Unknown Product Type" << std::endl;
        }
    }
};

//cos de cumparaturi
class Basket {
public:
    vector<shared_ptr<Magazin>> cumparaturi;
    bool isVIP;

    Basket(bool vip = false) : isVIP(vip) {}

//functie pentru a adauga produse in cos
    void adaugaProdus(shared_ptr<Magazin> produs) {
        cumparaturi.push_back(produs);
    }

    void afisareCos() const {
        for (const auto &cumparat: cumparaturi) {
            std::cout << cumparat->afisare() << " - Pret: " << cumparat->pret << std::endl;
        }
    }

    void aplicarePromotii() {
        for (const auto &cumparat: cumparaturi) {
            if (isVIP) {
                cumparat->promotii(cumparat->tip_produs);
            }
        }
    }
};

class AbstractFactory {
public:
    virtual std::shared_ptr<Magazin> createProduct(const std::string &produs, const std::string &culoare) const = 0;

    virtual std::shared_ptr<Magazin> createParfum(const std::string &name, const std::string &scent) const = 0;

    virtual ~AbstractFactory() {}
};

class ClientVIP : public Client {
public:
    int discount;

    // Default constructor
    ClientVIP(std::string _name = "", double a = 0, int d = 0) : Client(_name, a), discount(d) {}

    void citire() override {
        Client::citire();
        std::cin >> discount;
    }

    std::string afisare() const override {
        return "VIP " + name + " " + std::to_string(age) + " " + std::to_string(discount) + "%";
    }
};

class ClientFactory {
public:
    virtual std::shared_ptr<Client> createClient() const = 0;
};

class ClientSimpleFactory : public ClientFactory {
public:
    std::shared_ptr<Client> createClient() const override {
        return std::make_shared<Client>();
    }
};

class ClientVIPFactory : public ClientFactory {
public:
    std::shared_ptr<Client> createClient() const override {
        return std::make_shared<ClientVIP>();
    }
};

class DiorFactory : public AbstractFactory {
public:
    std::shared_ptr<Magazin> createProduct(const std::string &produs, const std::string &culoare) const override {
        return std::make_shared<Dior>(produs, culoare);
    }

    std::shared_ptr<Magazin> createParfum(const std::string &name, const std::string &scent) const override {
        // DiorFactory does not create perfumes
        throw std::invalid_argument("DiorFactory cannot create perfumes.");
    }
};

class FentyFactory : public AbstractFactory {
public:
    std::shared_ptr<Magazin> createProduct(const std::string &produs, const std::string &culoare) const override {
        return std::make_shared<Fenty>(produs, culoare);
    }

    std::shared_ptr<Magazin> createParfum(const std::string &name, const std::string &scent) const override {
        // FentyFactory does not create perfumes
        throw std::invalid_argument("FentyFactory cannot create perfumes.");
    }
};

class HudaFactory : public AbstractFactory {
public:
    std::shared_ptr<Magazin> createProduct(const std::string &produs, const std::string &culoare) const override {
        return std::make_shared<Huda>(produs, culoare);
    }

    std::shared_ptr<Magazin> createParfum(const std::string &name, const std::string &scent) const override {
        // HudaFactory does not create perfumes
        throw std::invalid_argument("HudaFactory cannot create perfumes.");
    }
};

class ParfumFactory : public AbstractFactory {
public:
    std::shared_ptr<Magazin> createProduct(const std::string &produs, const std::string &culoare) const override {
        // ParfumFactory does not create makeup products
        throw std::invalid_argument("ParfumFactory cannot create makeup products.");
    }

    std::shared_ptr<Magazin> createParfum(const std::string &name, const std::string &scent) const override {
        return std::make_shared<Parfum>(name, scent);
    }
};

class Meniu {
private:
    std::vector<std::shared_ptr<Magazin>> produse;
    std::shared_ptr<AbstractFactory> currentFactory;
    std::vector<std::shared_ptr<ClientVIP>> vipClients;
    static Meniu *instanta;

    Meniu() = default;

    Meniu(Meniu &) = default;

    Meniu &operator=(Meniu &other) = default;

    vector<shared_ptr<Basket>> prod;
    map<Client *, Basket> cosuri;

public:
    void setFactory(std::shared_ptr<AbstractFactory> factory) {
        currentFactory = factory;
    }

    static Meniu *getinstanta() {
        if (!instanta)
            instanta = new Meniu;
        return instanta;
    }

    void start() {
        std::cout << "Add VIP clients:\n";
        int nrVip;
        std::cout << "Enter the number of VIP clients: ";
        std::cin >> nrVip;

        for (int i = 0; i < nrVip; i++) {
            ClientVIP vipClient;
            std::cout << "VIP Client " << i + 1 << ":\n";
            vipClient.citire();
            vipClients.push_back(std::make_shared<ClientVIP>(vipClient));
        }
        currentFactory = std::make_shared<DiorFactory>();
        auto sp1 = currentFactory->createProduct("ruj", "roz");

        currentFactory = std::make_shared<ParfumFactory>();
        auto parfum1 = currentFactory->createParfum("Chanel No. 5", "floral");
        while (true) {
            int raft;
            cout << "Alegeti raftul";
            cin >> raft;
            switch (raft) {
                case 1:
                    raft1();
                    break;
                case 2:
                    raft2();
                    break;
                case 3:
                    raft3();
                    break;
                case 4:
                    raft4();
                    break;
                default:
                    cout << "numar gresit\n";
                    break;
            }
        }
    }

    void raft1() {
        std::cout << "Add VIP clients to cosuri:\n";
        for (auto &vipClient: vipClients) {
            cosuri[vipClient.get()] = Basket(true);
            std::cout << vipClient->afisare() << " added to cosuri.\n";
        }
        vector<Client *> c;
        //map pt a asocia clientii cu cosurile lor de cumparaturi
        map<Client *, Basket> cosuri;
        int nr;
        cout << "dati un nr de clienti: ";
        cin >> nr;
        for (int i = 0; i < nr; i++) {
            double a;
            string n;
            cout << "Nume: ";
            cin >> n;
            cout << "Varsta: ";
            cin >> a;
            c.push_back(new Client(n, a));
            cosuri[c.back()] = Basket();
        }
        auto sp1 = make_shared<Dior>("ruj", "roz");
        auto sp2 = make_shared<Dior>(" ruj", "mov");
        auto sp3 = make_shared<Fenty>(" creion de buze", "roz");
        auto sp4 = make_shared<Huda>(" ruj", "roz");

        sp1->tip_produs = "lips";
        sp2->tip_produs = "lips";
        sp3->tip_produs = "lips";
        sp4->tip_produs = "lips";

        sp1->pret = 50.0;
        sp2->pret = 30.0;
        sp3->pret = 40.0;
        sp4->pret = 55.0;
        cosuri[c[0]].adaugaProdus(sp1);
        cosuri[c[0]].adaugaProdus(sp2);
        cosuri[c[0]].adaugaProdus(sp3);
        cosuri[c[0]].adaugaProdus(sp4);

        cout << c[0]->afisare() << endl;
        cosuri[c[0]].afisareCos();
        cosuri[c[0]].aplicarePromotii();
        for (auto client: c) {
            delete client;
        }

        cout << " dupa aplicarea promotiilor:" << endl;
        cosuri[c[0]].afisareCos();


        cout << "Alegeti un client pentru a adauga produse in cos\n";
        int clientChoice;
        cin >> clientChoice;

        if (clientChoice >= 0 && clientChoice < c.size()) {

            int choice;
            cout << " Alegeti un produs din lista pentru a-l adauga in cos (numerotarea incepe de la 1)\n";
            cin >> choice;
            switch (choice) {
                case 1:
                    cosuri[c[0]].adaugaProdus(sp1->clone());
                    cout << "Ati adaugat in cos: " << sp1->afisare() << endl;
                    break;
                case 2:
                    cosuri[c[0]].adaugaProdus(sp2->clone());
                    cout << "Ati adaugat in cos: " << sp2->afisare() << endl;
                    break;
                case 3:
                    cosuri[c[0]].adaugaProdus(sp3->clone());
                    cout << "Ati adaugat in cos: " << sp3->afisare() << endl;
                    break;
                case 4:
                    cosuri[c[0]].adaugaProdus(sp4->clone());
                    cout << "Ati adaugat in cos: " << sp4->afisare() << endl;
                    break;
                default:
                    cout << "Optiune invalida." << endl;
                    break;
            }
        } else {
            cout << "Optiune invalida pentru client." << endl;
        }


    }

    void raft2() {
        std::cout << "Add VIP clients to cosuri:\n";
        for (auto &vipClient: vipClients) {
            cosuri[vipClient.get()] = Basket(true);
            std::cout << vipClient->afisare() << " added to cosuri.\n";
        }
        vector<Client *> c;
        //map pt a asocia clientii cu cosurile lor de cumparaturi
        map<Client *, Basket> cosuri;
        int nr;
        cout << "dati un nr de clienti: ";
        cin >> nr;
        for (int i = 0; i < nr; i++) {
            double a;
            string n;
            cout << "Nume: ";
            cin >> n;
            cout << "Varsta: ";
            cin >> a;
            c.push_back(new Client(n, a));
            cosuri[c.back()] = Basket();
        }
        auto sp1 = make_shared<Dior>("mascara", "negru");
        auto sp2 = make_shared<Dior>(" paleta", "nude");
        auto sp3 = make_shared<Fenty>(" dermatograf", "maro");
        auto sp4 = make_shared<Huda>(" gel de sprancene", "transparent");

        sp1->tip_produs = "eyes";
        sp2->tip_produs = "eyes";
        sp3->tip_produs = "eyes";
        sp4->tip_produs = "eyes";

        sp1->pret = 171.0;
        sp2->pret = 600.0;
        sp3->pret = 123.0;
        sp4->pret = 90.0;
        cosuri[c[0]].adaugaProdus(sp1);
        cosuri[c[0]].adaugaProdus(sp2);
        cosuri[c[0]].adaugaProdus(sp3);
        cosuri[c[0]].adaugaProdus(sp4);

        cout << c[0]->afisare() << endl;
        cosuri[c[0]].afisareCos();
        cosuri[c[0]].aplicarePromotii();
        for (auto client: c) {
            delete client;
        }

        cout << " dupa aplicarea promotiilor:" << endl;
        cosuri[c[0]].afisareCos();


        cout << "Alegeti un client pentru a adauga produse in cos\n";
        int clientChoice;
        cin >> clientChoice;

        if (clientChoice >= 0 && clientChoice < c.size()) {

            int choice;
            cout << " Alegeti un produs din lista pentru a-l adauga in cos (numerotarea incepe de la 1)\n";
            cin >> choice;
            switch (choice) {
                case 1:
                    cosuri[c[0]].adaugaProdus(sp1->clone());
                    cout << "Ati adaugat in cos: " << sp1->afisare() << endl;
                    break;
                case 2:
                    cosuri[c[0]].adaugaProdus(sp2->clone());
                    cout << "Ati adaugat in cos: " << sp2->afisare() << endl;
                    break;
                case 3:
                    cosuri[c[0]].adaugaProdus(sp3->clone());
                    cout << "Ati adaugat in cos: " << sp3->afisare() << endl;
                    break;
                case 4:
                    cosuri[c[0]].adaugaProdus(sp4->clone());
                    cout << "Ati adaugat in cos: " << sp4->afisare() << endl;
                    break;
                default:
                    cout << "Optiune invalida." << endl;
                    break;
            }
        } else {
            cout << "Optiune invalida pentru client." << endl;
        }


    }

    void raft3() {
        std::cout << "Add VIP clients to cosuri:\n";
        for (auto &vipClient: vipClients) {
            cosuri[vipClient.get()] = Basket(true);
            std::cout << vipClient->afisare() << " added to cosuri.\n";
        }

        vector<Client *> c;
        //map pt a asocia clientii cu cosurile lor de cumparaturi
        map<Client *, Basket> cosuri;
        int nr;
        cout << "dati un nr de clienti: ";
        cin >> nr;
        for (int i = 0; i < nr; i++) {
            double a;
            string n;
            cout << "Nume: ";
            cin >> n;
            cout << "Varsta: ";
            cin >> a;
            c.push_back(new Client(n, a));
            cosuri[c.back()] = Basket();
        }
        auto sp1 = make_shared<Dior>("pudra", "translucida");
        auto sp2 = make_shared<Dior>(" fond de ten", "c1");
        auto sp3 = make_shared<Fenty>(" corector", "c0");
        auto sp4 = make_shared<Huda>(" contur", "maro deschis");

        sp1->tip_produs = "face";
        sp2->tip_produs = "face";
        sp3->tip_produs = "face";
        sp4->tip_produs = "face";

        sp1->pret = 50.0;
        sp2->pret = 30.0;
        sp3->pret = 40.0;
        sp4->pret = 55.0;
        cosuri[c[0]].adaugaProdus(sp1);
        cosuri[c[0]].adaugaProdus(sp2);
        cosuri[c[0]].adaugaProdus(sp3);
        cosuri[c[0]].adaugaProdus(sp4);

        cout << c[0]->afisare() << endl;
        cosuri[c[0]].afisareCos();
        cosuri[c[0]].aplicarePromotii();
        for (auto client: c) {
            delete client;
        }

        cout << " dupa aplicarea promotiilor:" << endl;
        cosuri[c[0]].afisareCos();


        cout << "Alegeti un client pentru a adauga produse in cos\n";
        int clientChoice;
        cin >> clientChoice;

        if (clientChoice >= 0 && clientChoice < c.size()) {

            int choice;
            cout << " Alegeti un produs din lista pentru a-l adauga in cos (numerotarea incepe de la 1)\n";
            cin >> choice;
            switch (choice) {
                case 1:
                    cosuri[c[0]].adaugaProdus(sp1->clone());
                    cout << "Ati adaugat in cos: " << sp1->afisare() << endl;
                    break;
                case 2:
                    cosuri[c[0]].adaugaProdus(sp2->clone());
                    cout << "Ati adaugat in cos: " << sp2->afisare() << endl;
                    break;
                case 3:
                    cosuri[c[0]].adaugaProdus(sp3->clone());
                    cout << "Ati adaugat in cos: " << sp3->afisare() << endl;
                    break;
                case 4:
                    cosuri[c[0]].adaugaProdus(sp4->clone());
                    cout << "Ati adaugat in cos: " << sp4->afisare() << endl;
                    break;
                default:
                    cout << "Optiune invalida." << endl;
                    break;
            }
        } else {
            cout << "Optiune invalida pentru client." << endl;
        }


    }

    void raft4() {
        std::cout << "Add VIP clients to cosuri:\n";
        for (auto &vipClient: vipClients) {
            cosuri[vipClient.get()] = Basket(true);
            std::cout << vipClient->afisare() << " added to cosuri.\n";
        }
        vector<Client *> c;
        //map pt a asocia clientii cu cosurile lor de cumparaturi
        map<Client *, Basket> cosuri;
        int nr;
        cout << "dati un nr de clienti: ";
        cin >> nr;
        for (int i = 0; i < nr; i++) {
            double a;
            string n;
            cout << "Nume: ";
            cin >> n;
            cout << "Varsta: ";
            cin >> a;
            c.push_back(new Client(n, a));
            cosuri[c.back()] = Basket();
        }
        auto sp1 = std::make_shared<Parfum>("Parfum1", "Scent1");
        auto sp2 = std::make_shared<Parfum>("Parfum2", "Scent2");
        auto sp3 = std::make_shared<Parfum>("Parfum3", "Scent3");
        auto sp4 = std::make_shared<Parfum>("Parfum4", "Scent4");

        sp1->tip_produs = "scent";
        sp2->tip_produs = "scent";
        sp3->tip_produs = "scent";
        sp4->tip_produs = "scent";

        sp1->pret = 50.0;
        sp2->pret = 30.0;
        sp3->pret = 40.0;
        sp4->pret = 55.0;
        cosuri[c[0]].adaugaProdus(sp1);
        cosuri[c[0]].adaugaProdus(sp2);
        cosuri[c[0]].adaugaProdus(sp3);
        cosuri[c[0]].adaugaProdus(sp4);

        cout << c[0]->afisare() << endl;
        cosuri[c[0]].afisareCos();
        cosuri[c[0]].aplicarePromotii();
        for (auto client: c) {
            delete client;
        }


        if (Parfum_info::haveSameScent(std::dynamic_pointer_cast<Parfum>(sp4),
                                       std::dynamic_pointer_cast<Parfum>(sp1))) {
            std::cout << "The two perfumes have the same scent." << std::endl;
        } else {
            std::cout << "The two perfumes have different scents." << std::endl;
        }
        auto clonedDior = sp1->clone();
        std::cout << "Cloned Dior: " << clonedDior->afisare() << std::endl;

        auto clonedFenty = sp3->clone();
        std::cout << "Cloned Fenty: " << clonedFenty->afisare() << std::endl;

        auto clonedHuda = sp4->clone();
        std::cout << "Cloned Huda: " << clonedHuda->afisare() << std::endl;

        auto clonedParfum = sp4->clone();
        std::cout << "Cloned Parfum: " << clonedParfum->afisare() << std::endl;


        cout << "Alegeti un client pentru a adauga produse in cos\n";
        int clientChoice;
        cin >> clientChoice;

        if (clientChoice >= 0 && clientChoice < c.size()) {

            int choice;
            cout << " Alegeti un produs din lista pentru a-l adauga in cos (numerotarea incepe de la 1)\n";
            cin >> choice;
            switch (choice) {
                case 1:
                    cosuri[c[0]].adaugaProdus(sp1->clone());
                    cout << "Ati adaugat in cos: " << sp1->afisare() << endl;
                    break;
                case 2:
                    cosuri[c[0]].adaugaProdus(sp2->clone());
                    cout << "Ati adaugat in cos: " << sp2->afisare() << endl;
                    break;
                case 3:
                    cosuri[c[0]].adaugaProdus(sp3->clone());
                    cout << "Ati adaugat in cos: " << sp3->afisare() << endl;
                    break;
                case 4:
                    cosuri[c[0]].adaugaProdus(sp4->clone());
                    cout << "Ati adaugat in cos: " << sp4->afisare() << endl;
                    break;
                default:
                    cout << "Optiune invalida." << endl;
                    break;
            }
        } else {
            cout << "Optiune invalida pentru client." << endl;
        }
    }
};

Meniu *Meniu::instanta = nullptr;

int main() {
    Meniu *meniu = Meniu::getinstanta();
    meniu->start();

    return 0;
}