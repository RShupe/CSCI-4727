///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Rabbit.cpp
//	Description:                    This is a class to hold all the attributes of a bunny.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Wednesday February 3, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "Rabbit.h"
#include <string>

using namespace std;

string name;
int health = 100;
int attackRate = 4;
int strongAttackDamage = 15;
int weakAttackDamage = 6;
int aoeDamage = 10;

string nameBank_Rabbit[] = {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth"};

Rabbit::Rabbit ()
{

};
Rabbit::Rabbit (string inName)
{
    SetName("Killer Rabbit the " + inName);
};

Rabbit::Rabbit(int nameNum)
{
    SetName("Killer Rabbit the " + nameBank_Rabbit[nameNum]);
};

void Rabbit::SetName(string inName)
{
    name = inName;
}

string Rabbit::GetName() const
{
    return name;
}

void Rabbit::SetHealth(int inHealth)
{
    health = inHealth;
}
int Rabbit::GetHealth() const
{
    return health;
}

void Rabbit::SetAttackRate(int inAttkRt)
{
    attackRate = inAttkRt;
}
int Rabbit::GetAttackRate() const
{
    return attackRate;
}

void Rabbit::SetStrongAttackDmg(int inSAttkDmg)
{
    strongAttackDamage = inSAttkDmg;
}
int Rabbit::GetStrongAttackDmg() const
{
    return strongAttackDamage;
}

void Rabbit::SetWeakAttackDmg(int inWAttkdmg)
{
    weakAttackDamage = inWAttkdmg;
}
int Rabbit::GetWeakAttackDmg() const
{
    return weakAttackDamage;
}

void Rabbit::SetAOEDamage(int inAOEDmg)
{
    aoeDamage = inAOEDmg;
}
int Rabbit::GetAOEDamage() const
{
    return aoeDamage;
}