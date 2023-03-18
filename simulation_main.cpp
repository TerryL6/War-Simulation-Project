#include "Noble.h"
#include "Protector.h"
using namespace std;
using namespace WarriorCraft;

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



