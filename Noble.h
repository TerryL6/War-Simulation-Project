#ifndef NOBLE_H_INCLUDED
#define NOBLE_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft{
    class Protector;

    class Noble{
        friend std::ostream& operator<<(std::ostream& os, const Noble& rhs);
    public:
        //Display methods are different in each subclass of Noble
        virtual void display(std::ostream& os) const=0;

        //Constructor
        Noble (const std::string& name, double strength);

        //Getters
        const std::string get_name()const;
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
        std::string name;
        double strength;
        bool alive=true;
    };

    class Lord: public Noble{
    public:
        //Lord's display method
        void display(std::ostream& os) const;

        Lord(const std::string& name);

        bool hires(Protector& soldier);

        bool remove_soldier(Protector& soldier);

        bool fire(Protector& soldier);

        void change_strength(double change);

    private:
        std::vector<Protector*> army;
    };

    class PersonWithStrengthToFight : public Noble{
        using Noble::Noble;

        //PersonWithStrengthToFight's display method
        void display(std::ostream& os) const;

        void change_strength(double change);
    };
}

#endif // NOBLE_H_INCLUDED
