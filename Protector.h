#ifndef PROTECTOR_H_INCLUDED
#define PROTECTOR_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft{
    class Noble;

    class Protector{
        friend std::ostream& operator<<(std::ostream& os, const Protector& rhs);
    public:
        //Display methods are different in each subclass of Protector
        virtual void display(std::ostream& os) const=0;

        Protector(const std::string& name, double strength);

        const std::string& getName() const;

        Lord* getLord() const;

        void setLord(Lord* lord);

        double getStrength() const;

        //When warriors lose a battle, they lose all their strength
        void setDead();

        //When warriors win a battle, they lose some strength
        virtual void loseStrength(double fraction)=0;

        bool runaway();

    private:
        std::string name;
        double strength;
        Lord* my_lord=nullptr;
    };

    class Wizard : public Protector{
    public:
        using Protector::Protector;
        void display(std::ostream& os) const;
        void loseStrength(double fraction);
    };

    class Warrior : public Protector{
    public:
        using Protector::Protector;
        void display(std::ostream& os) const=0;
        virtual void loseStrength(double fraction)=0;
    };

    class Archer : public Warrior{
    public:
        using Warrior::Warrior;
        void display(std::ostream& os) const;
        void loseStrength(double fraction);
    };

    class Swordsman : public Warrior{
    public:
        using Warrior::Warrior;
        void display(std::ostream& os) const;
        void loseStrength(double fraction);
    };
}


#endif // PROTECTOR_H_INCLUDED
