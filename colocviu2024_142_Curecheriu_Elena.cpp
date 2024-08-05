/*
 * Curecheriu Elena - grupa 142
 * CLion g++ 13.1.0
 * Tutore: Szmeteanca Eduard
 */

#include <iostream>
#include <vector>
//copy constructor?
using namespace std;

int puncte = 50000;

static int counterID = 0;

class Zid
{
private:
    const int id;
    float inaltime;
    float lungime;
    float grosime;
public:
    Zid();
    Zid& operator = (const Zid& obj);
    float getInaltime() {return this->inaltime;}
    float getLungime() {return this->lungime;}
    float getGrosime() {return this->grosime;}
    const int getID () {return this->id;}

    void setInaltime(float inaltime) {this->inaltime = inaltime;}
    void setLungime(float lungime) {this->lungime = lungime;}
    void setGrosime(float grosime) {this->grosime = grosime;}

    void upgrade();
    ~Zid() = default;
};

Zid :: Zid() : id(counterID++)
{
    this->inaltime = 2;
    this->lungime = 1;
    this->grosime = 0.5;
}

Zid& Zid ::operator=(const Zid &obj){
    if (this != &obj)
    {
        this->lungime = obj.lungime;
        this->grosime= obj.grosime;
        this->inaltime = obj.inaltime;
    }
    return *this;
}

void Zid :: upgrade() {
    int cost = this -> inaltime * this -> lungime * this -> grosime * 100;
    puncte = puncte - cost;
    this -> inaltime +=1;
    this ->lungime +=1;
    this -> grosime +=1;
}

class Turn
{
private:
    const int id;
    int putere;
public:
    Turn();
    Turn& operator = (const Turn& obj);
    float getPutere() {return this->putere;}
    void setPutere(int putere) {this->putere = putere;}
    const int getID () {return this->id;}

    void upgrade();
    ~Turn() = default;
};

Turn :: Turn() : id(counterID++)
{
    this->putere = 1000;
}

void Turn :: upgrade() {
    int cost = this -> putere * 500;
    puncte = puncte - cost;
    this -> putere += 500;
}

Turn& Turn ::operator=(const Turn &obj) {
    if (this != &obj){
        this->putere = obj.putere;
    }
    return *this;
}
class Robot
{
    protected:
        int damage;
        int nivel;
        int viata;
public:
    Robot() = default;

    int getDamage() {return this->damage;}
    int getNivel() {return this->nivel;}
    int getViata() {return this->viata;}

    void setDamage(int damage) {this->damage = damage;}
    void setNivel(int nivel) {this->nivel = nivel;}
    void setViata(int viata) {this->viata = viata;}

    void afisare (ostream& out);
    friend ostream& operator << (ostream& out, const Robot& obj);

    virtual ~Robot() = default;
};


void Robot :: afisare(std::ostream &out) {
    out << this->damage << endl;
    out << this->nivel << endl;
    out << this->viata << endl;
}

ostream& operator << (ostream& out, Robot& obj)
{
    obj.afisare(out);
    return out;
}

class RobotAerian : public Robot
{
private:
    int autonomie;
    const int id;
public:
    RobotAerian();
    RobotAerian& operator = (const RobotAerian& obj);
    float getAutonomie() {return this->autonomie;}
    void setAutonomie(int autonomie) {this->autonomie = autonomie;}
    const int getID () {return this->id;}

    void upgrade();
    ~RobotAerian() = default;
};

RobotAerian ::RobotAerian() : id(counterID++){
    this->nivel = 1;
    this->damage = 100;
    this->viata = 100;
    this->autonomie = 10;
}

void RobotAerian ::upgrade() {
    int cost = 50 * this->autonomie;
    puncte = puncte - cost;
    this->autonomie += 1;
    this->nivel +=1;
    this -> damage += 25;

}

RobotAerian& RobotAerian ::operator=(const RobotAerian &obj) {
    if (this != &obj)
    {
        this->autonomie=obj.autonomie;
        this->damage = obj.damage;
        this->nivel  = obj.nivel;
        this->viata = obj.viata;
    }
    return *this;
}
class RobotTerestru : public Robot
{
private:
    int nrGloante;
    bool scut;
    const int id;
public:
    RobotTerestru();
    RobotTerestru& operator = (const RobotTerestru &obj);
    int getNrGloante() {return this->nrGloante;}
    bool getScut() {return this->scut;}
    const int getID () {return this->id;}

    void setNrGloante(int nrGloante) {this->nrGloante = nrGloante;}
    void setScut(bool scut) {this->scut = scut;}
    void upgrade();
    ~RobotTerestru() = default;
};

RobotTerestru ::RobotTerestru() : id(counterID++) {
    this->nivel = 1;
    this->damage = 100;
    this->viata = 100;
    this -> nrGloante = 500;
    this -> scut = false;
}

void RobotTerestru ::upgrade() {
    int cost = 50 * this->nrGloante;
    puncte = puncte - cost;
    this->nrGloante += 100;
    this->nivel +=1;
    this -> damage += 25;
    if (this->nivel == 5) {
        this->scut = true;
        this->viata += 50;
    }
}

RobotTerestru& RobotTerestru ::operator=(const RobotTerestru &obj) {
    if (this != &obj)
    {
        this->nrGloante=obj.nrGloante;
        this->damage = obj.damage;
        this->nivel  = obj.nivel;
        this->scut = obj.scut;
        this->viata = obj.viata;
    }
    return *this;
}


class Inventar
{
private:
    static Inventar* instance;
    Inventar() = default;
    Inventar (const Inventar&) = delete;
    Inventar& operator = (const Inventar&) = delete;
    vector <Zid> ziduri;
    vector <Turn> turnuri;
    vector <Robot*> roboti;

public:

    static Inventar* getInstance()
    {
        if (Inventar::instance != NULL)
        {
            return instance;
        }
        else
        {
            Inventar::instance = new Inventar();
            return instance;
        }
    }
    ~Inventar()
    {
        for (auto i : roboti)
        {
            delete i;
        }
    }

    void adaugareElement();
    void upgradeElement();
    void afisareCostUpgrade();
    void afisareRoboti();
    void sell();
};

void Inventar :: adaugareElement()
{
    cout << "Selectati tipul de element: " <<endl;
    cout << "1) Zid" << endl;
    cout << "2) Turn" << endl;
    cout << "3) Robot aerian" << endl;
    cout << "4) Robot terestru" << endl;

    int optiune;
    cin >> optiune;

    switch(optiune)
    {
        case 1:
        {
            Zid zidNou = Zid();
            ziduri.push_back(zidNou);
            puncte -= 300;
            break;
        }
        case 2:
        {
            Turn turnNou = Turn();
            turnuri.push_back(turnNou);
            puncte -= 500;
            break;
        }
        case 3:
        {
            RobotAerian* robotAerianNou = new RobotAerian();
            roboti.push_back(robotAerianNou);
            puncte -= 100;
            break;
        }
        case 4:
        {
            RobotTerestru* robotTerestruNou =new RobotTerestru();
            roboti.push_back(robotTerestruNou);
            puncte -=50;
            break;
        }
        default:
        {
            cout<<"Optiune invalida." << endl;
            break;
        }
    }
}

void Inventar :: upgradeElement()
{
    cout << "Introduceti id-ul elementului: " << endl;
    int nr;
    cin >> nr;
    bool efectuat = 0;
    for (auto i : ziduri)
    {
        if (i.getID() == nr)
            i.upgrade(), efectuat = 1;
    }
    for (auto i : turnuri)
    {
        if (i.getID() == nr)
            i.upgrade(), efectuat = 1;
    }
//    for (auto i : roboti)
//    {
//        if (i->getID() == nr)
//            i->upgrade(), efectuat = 1;
//    }
    if(efectuat == 0)
        cout << "Nu exista elementul cu id-ul cerut." << endl;

}

void Inventar ::afisareCostUpgrade() {
    //vector <pair<>> cu id-ul elementului si costul, sortam crescator in functie de costul upgrade-ului, apoi afisam toate elementele
}

void Inventar ::afisareRoboti() {
    for (auto i : roboti)
    {
        //voiam sa fac downcasting si sa mostenesc din clasa de baza Robot afisarile pentru a afisa cei doi copii,
        //RobotAerian si RobotTerestru
    }
}

void Inventar :: sell()
{
    cout << "Introduceti id-ul elementului: " << endl;
    int nr;
    cin >> nr;
    bool efectuat = 0;
    for (auto i : ziduri)
    {
        if (i.getID() == nr)
            i.upgrade(), efectuat = 1;
    }
    for (auto i : turnuri)
    {
        if (i.getID() == nr)
            i.upgrade(), efectuat = 1;
    }
//    for (auto i : roboti)
//    {
//        if (i->getID() == nr)
//            i->upgrade(), efectuat = 1;
//    }
    if (efectuat == 1)
        puncte += 500;
    if(efectuat == 0)
        cout << "Nu exista elementul cu id-ul cerut." << endl;

}

Inventar* Inventar :: instance = NULL;

int main() {
    return 0;
}
