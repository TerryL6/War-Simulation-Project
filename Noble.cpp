#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"
#include "Protector.h"

using namespace std;

namespace WarriorCraft{
    //Output Operator for noble
    ostream& operator<<(ostream& os, const Noble& rhs){
        rhs.display(os);
        return os;
    }

    //Noble class methods
    //Constructor and Getters
    Noble::Noble (const string& name, double strength): name(name), strength (strength){}
    const string Noble::get_name()const {return name;}
    double Noble::get_strength()const {return strength;}
    bool Noble::get_alive() const {return alive;}

    //Setters
    void Noble::set_strength(double newStrength){
        if (newStrength <= 0){
            strength = 0;
            alive = false;
        }else{
            strength = newStrength;
        }
    }

    void Noble::setAlive(bool status){alive=status;}

    //Battle method
    void Noble::battle(Noble& opponent){
        //Display who are fighting now
        cout<<name<<" battles "<<opponent.name<<endl;

        //Get the opponent's strength
        double opponent_strength=opponent.get_strength();

        //SituationI: both nobles are alive
        if(alive && opponent.get_alive()){

            //Situation for Mutual Annihilation
            if(strength == opponent_strength){
                change_strength(opponent_strength);
                opponent.change_strength(strength);
                cout<<"Mutual Annihilation: "<<name<<" and "<<opponent.name<<" die at each other's hands"<<endl;
            }

            //Situation that one of them wins and the other dies
            else if(strength > opponent_strength){
                change_strength(opponent_strength);
                opponent.change_strength(strength);
                cout<< name <<" defeats "<< opponent.name <<endl;
            }
            else{
                change_strength(opponent_strength);
                opponent.change_strength(strength);
                cout<<opponent.name<<" defeats "<<name<<endl;
            }
        }

        //SituationII: one alive, one dead
        else if( (!alive || !opponent.get_alive()) && (strength!=opponent_strength) ){
            if(strength==0){
                //If I am dead, I will not battle cry, my opponent however, still battle cry
                opponent.change_strength(strength);
                cout<<"He's dead, "<<opponent.name<<endl;
            }
            else{
                change_strength(opponent_strength);
                //If my opponent is dead, he will not battle cry, I however, still battle cry
                cout<<"He's dead, "<<name<<endl;
            }
        }

        //SituationIII: both warriors are dead
        else if(!alive && !opponent.get_alive())
        {
            cout<<"Oh, NO! They're both dead! Yuck!"<<endl;
        }
    }

    //Lord class methods
    //Display for lord
    void Lord::display(ostream& os) const { os << "Lord: " <<get_name() << "    Strength :" << get_strength(); }

    //Constructor
    Lord::Lord(const string& name):Noble(name,0){}

    bool Lord :: hires(Protector& soldier){
        // fail if Noble is dead
        if (!get_alive()) {
            cout << "Lord " << get_name() << " is already dead! Failed to hire " << soldier.getName() << endl;
            return false;
        }
        // fail if the warrior is already hired
        if (soldier.getLord()!=nullptr) {
            cout << "Warrior " << soldier.getName() << " is already hired!"<< endl;
            return false;
        }
        //else hire will be successful
        soldier.setLord(this);
        army.push_back(&soldier);
        set_strength(get_strength() + soldier.getStrength());
        return true;
    }

    bool Lord::remove_soldier(Protector& soldier){
        bool fired=false;
        //Go through the army and look for the warrior
        for(size_t i=0; i<army.size(); i++){
            //If warrior is found, he will be put into the last position of the army.
            if(soldier.getName()==army[i]->getName()){
                fired=true;         //fire is successful now
                army[i]=army[i+1];
                army[i+1]=&soldier;
            }
        }
        if(fired==true){
            army.pop_back();
            soldier.setLord(nullptr);
        }
        else{
            cout<< soldier.getName() << " is not in " << get_name() << "'s army !"<< endl;
        }

        //Update the strength
        set_strength(get_strength()-soldier.getStrength());
        return fired;
    }

    bool Lord::fire(Protector& soldier){
        //Check is noble alive
        if(!get_alive()){
            cout<<"Noble " << get_name() << " is already dead!" << endl;
            return false;
        }
        else if(remove_soldier(soldier)){
            cout << "You don't work for me anymore " << soldier.getName()<< "! -- " << get_name() << "." << endl;
            return true;
        }
        return false;
    }

    void Lord:: change_strength(double change){
        double fraction;
        if(change>=get_strength()){
            set_strength(0);
        }
        else{
            fraction=change/get_strength();
        }
        for (Protector* protector: army){
            protector->loseStrength(fraction);
        }
    }


    //PersonWithStrengthToFight methods
    void PersonWithStrengthToFight::display(ostream& os) const { os << "PersonWithStrengthToFight: " <<get_name() <<"   Strength: "<< get_strength(); }

    void PersonWithStrengthToFight :: change_strength(double change){
        set_strength(get_strength()-change);

        //Battle cry every time they fight and get hurt
        cout<<"Ugh!"<<endl;
    }
}
