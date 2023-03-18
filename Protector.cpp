#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"
#include "Protector.h"

using namespace std;

namespace WarriorCraft{
    //Output Operator for Protector
    ostream& operator<<(ostream& os, const Protector& rhs){
        rhs.display(os);
        return os;
    }

    //Protector class methods
    Protector::Protector(const string& name, double strength):name(name),strength(strength){}

    const string& Protector::getName() const{ return name;}

    Lord* Protector::getLord() const{ return my_lord;}

    void Protector::setLord(Lord* lord) { my_lord = lord;}

    double Protector::getStrength() const { return strength;}

    void Protector::setDead(){ strength=0;}

    void Protector::loseStrength(double fraction){ strength *= (1-fraction); }

    bool Protector::runaway(){
        // fail if warrior is dead
        if (strength == 0) {
            cout << name << " is already dead!" << endl;
            return false;
        }
        // fail if the warrior doesn't have a lord
        if (my_lord==nullptr) {
            cout << name << " doesn't have a lord!";
            return false;
        }

        //need to store the noble's name before remove
        string lord_name=my_lord->get_name();
        if (my_lord->remove_soldier(*this)) {
            cout << name << " flees in terror, abandoning his lord, "<< lord_name << endl;
            return true;
        }
        return false;
    }

    void Wizard::display(ostream& os) const{ os << "Wizard: " <<getName() <<"   Strength: "<< getStrength(); }

    void Wizard::loseStrength(double fraction){
        cout << "POOF!" << endl;
        Protector::loseStrength(fraction);
    }

    void Warrior::loseStrength(double fraction){
        cout<<getName()<<" says: Take that in the name of my lord, "<<getLord()->get_name()<<endl;
        Protector::loseStrength(fraction);
    }

    void Archer::display(ostream& os) const { os << "Archer: " <<getName() <<"   Strength: "<< getStrength(); }

    void Archer::loseStrength(double fraction){
        cout<<"TWANG! ";
        Warrior::loseStrength(fraction);
    }

    void Swordsman::display(ostream& os) const { os << "Swordsman: " <<getName() <<"   Strength: "<< getStrength(); }

    void Swordsman::loseStrength(double fraction){
        cout << "CLANG! ";
        Warrior::loseStrength(fraction);
    }
}
