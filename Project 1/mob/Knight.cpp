///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Knight.cpp
//	Description:                    This is a class to hold all the attributes of a knight.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Wednesday February 3, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "Knight.h"
#include <string>

using namespace std;

string name;
int health = 100;
int attackRate = 2;
int strongAttackDamage = 10;
int weakAttackDamage = 5;
int aoeDamage = 8;

string nameBank_Knight[] = {"King Arthur", "Sir Bedevere the Wise", "Sir Lancelot the Brave", "Sir Galahad the Chaste/Pure",
                            "Sir Robin the Not-Quite-So-Brave-As-Sir-Lancelot", "Sir Bors", "Sir Gawain", "Sir Ector", "Guillot the Truthful"
        ,"Gerould the Loyal", "Symon of the Fall", "Dodge the Bald", "Han the Smiling", "Sir Harrison"};

Knight::Knight ()
{

};
Knight::Knight (string inName)
{
    SetName(inName);
};

Knight::Knight(int nameNum)
{
    SetName(nameBank_Knight[nameNum]);
};

void Knight::SetName(string inName)
{
    name = inName;
}

string Knight::GetName() const
{
    return name;
}

void Knight::SetHealth(int inHealth)
{
    health = inHealth;
}
int Knight::GetHealth() const
{
    return health;
}

void Knight::SetAttackRate(int inAttkRt)
{
    attackRate = inAttkRt;
}
int Knight::GetAttackRate() const
{
    return attackRate;
}

void Knight::SetStrongAttackDmg(int inSAttkDmg)
{
    strongAttackDamage = inSAttkDmg;
}
int Knight::GetStrongAttackDmg() const
{
    return strongAttackDamage;
}

void Knight::SetWeakAttackDmg(int inWAttkdmg)
{
    weakAttackDamage = inWAttkdmg;
}
int Knight::GetWeakAttackDmg() const
{
    return weakAttackDamage;
}

void Knight::SetAOEDamage(int inAOEDmg)
{
    aoeDamage = inAOEDmg;
}
int Knight::GetAOEDamage() const
{
    return aoeDamage;
}