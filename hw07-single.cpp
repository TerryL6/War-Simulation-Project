#include <iostream>
#include <vector>
using namespace std;

class Protector;

class Noble{
    friend ostream& operator<<(ostream& os, const Noble& rhs);
public:
    //Display methods are different in each subclass of Noble
    virtual void display(ostream& os) const=0;

    //Constructor
    Noble (const string& name, double strength);

    //Getters
    const string get_name()const;
    double get_strength()const;
    bool get_alive()const;

    //Setters
    //Change the strength of the noble, Lord and PersonWithStrengthToFight are different in changing their strength.
    virtual void change_strength(double change) = 0;

    //Set the noble's strength to a new value
    void set_strength(double newStrength);

    //Set the noble's alive
    void setAlive(bool status);

    //Battle method
    void battle(Noble& opponent);

private:
    string name;
    double strength;
    bool alive=true;
};

class Lord: public Noble{
public:
    //Lord's display method
    void display(ostream& os) const;

    Lord(const string& name);

    bool hires(Protector& soldier);

    bool remove_soldier(Protector& soldier);

    bool fire(Protector& soldier);

    void change_strength(double change);

private:
    vector<Protector*> army;

};

class PersonWithStrengthToFight : public Noble{
    using Noble::Noble;

    //PersonWithStrengthToFight's display method
    void display(ostream& os) const;

    void change_strength(double change);
};

class Protector{
    friend ostream& operator<<(ostream& os, const Protector& rhs);
public:
    //Display methods are different in each subclass of Protector
    virtual void display(ostream& os) const=0;

    Protector(const string& name, double strength);

    const string& getName() const;

    Lord* getLord() const;

    void setLord(Lord* lord);

    double getStrength() const;

    //When warriors lose a battle, they lose all their strength
    void setDead();

    //When warriors win a battle, they lose some strength
    virtual void loseStrength(double fraction)=0;

    bool runaway();

private:
    string name;
    double strength;
    Lord* my_lord=nullptr;
};

class Wizard : public Protector{
public:
    using Protector::Protector;
    void display(ostream& os) const;
    void loseStrength(double fraction);
};

class Warrior : public Protector{
public:
    using Protector::Protector;
    virtual void display(ostream& os) const=0;
    virtual void loseStrength(double fraction)=0;
};

class Archer : public Warrior{
public:
    using Warrior::Warrior;
    void display(ostream& os) const;
    void loseStrength(double fraction);
};

class Swordsman : public Warrior{
public:
    using Warrior::Warrior;
    void display(ostream& os) const;
    void loseStrength(double fraction);
};

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
//    cout<<samantha<<endl;      //test for Protector's output operator
    sam.hires(samantha);
//    cout<<sam<<endl;          //test for Noble's output operator
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
//    cout<<randy<<endl;        //test for Noble's output operator
    joe.battle(randy);
    joe.battle(sam);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
//    cout<<hardy<<endl;         //test for Protector's output operator
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hires(samantha);      //janet should fail to hire since he is already dead
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
//    cout<<merlin<<endl;        //test for Protector's output operator
    janet.hires(pethora);       //janet should fail to hire since he is already dead
    janet.hires(thora);         //janet should fail to hire since he is already dead
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
}

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



