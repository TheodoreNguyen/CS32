// Theodore Nguyen 704-156-701 CS32 homework 3 winter 2015



#include <iostream>
#include <string>
using namespace std;




//Your declarations and implementations would go here


//SOME NOTES:
//- each constructor initalizes the base class, with the exception of elf which initalizes m_arrows
//- name() remains unchanged from the base class onward, a totally nonvirtual function
//- printweapon is made to be totally virtual because the base class does not have a weapon
//	- this is important distinction: I DID NOT have a weapon as a member in the base class, LET ALONE 
//	AT ALL. This was due to two reasons
//		(1) if i had m_weapon in the base class, then it would be a private variable. Each of the 
//		derived classes have a different m_weapon, but I cannot access the base class's member vars.
//		Therefore I did not put weapon in the base class
//		(2) however, if i added m_weapon to each of the derived classes, the code for printWeapon() 
//		would be identical in each of them, more or less being "return m_weapon", which violated
//		a rule in the homework specification
//- attackAction() is just normally virtual; only Boggie has an override\
//- And of course, each destructor is made virtual. 


class Character
{
  public:
	Character(string str) : m_name(str) {} ;
	virtual ~Character(){};
	string name() const { return m_name;}
	virtual void printWeapon() const = 0;
	virtual string attackAction() const { return "rushes toward the enemy";}
  private:
	string m_name;
	
};

class Dwarf: public Character
{
  public:
	Dwarf(string str): Character(str){}
	virtual ~Dwarf(){ cout << "Destroying " << name() << " the dwarf" << endl; }
  	virtual void printWeapon() const {cout << "an axe";}
 
};

class Elf: public Character
{
  public:
	Elf(string str, int arrows): Character(str), m_arrows(arrows){}
	virtual ~Elf(){ cout << "Destroying " << name() << " the elf" << endl; }
	virtual void printWeapon() const {cout << "a bow and a quiver of " << m_arrows << " arrows";}
  private:
	int m_arrows;
};


class Boggie: public Character
{
  public:
	Boggie(string str): Character(str){}
	virtual ~Boggie(){ cout << "Destroying " << name() << " the boggie" << endl; }
	virtual void printWeapon() const {cout << "a short sword";}
	virtual string attackAction() const { return "whimpers";}
};


/*

void strike(const Character* cp)
{
    cout << cp->name() << ", wielding ";
    cp->printWeapon();
    cout << ", " << cp->attackAction() << "." << endl;
}

int main()
{

	Character* swag[4];
	swag[0] = new Dwarf("gimley");
	strike(swag[0]);
	delete swag[0];

	

    Character* characters[4];
    characters[0] = new Dwarf("Gimlet");
        // Elves have a name and initial number of arrows in their quiver
             characters[1] = new Elf("Legolam", 10);
                 characters[2] = new Boggie("Frito");
                     characters[3] = new Boggie("Spam");
        
                         cout << "The characters strike!" << endl;
                             for (int k = 0; k < 4; k++)
                                     strike(characters[k]);
        
                                            // Clean up the characters before exiting
                                                cout << "Cleaning up" << endl;
                                                     for (int k = 0; k < 4; k++)
                                                     	delete characters[k];

}
*/
