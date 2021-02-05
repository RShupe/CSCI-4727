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


string nameBank_Rabbit[] = {"Waterton", "Sargos", "Blooding", "Carrotton", "Hareington", "Hopsville USA", "Florida", "Eggerton", "Volta",
                            "Eleyvine"};
//rName bank for naming rabbits

/**
 * Rabbit
 *
 * No arg default constructor
 */
Rabbit::Rabbit ()
{
    SetHealth(100);
    SetAttackRate(4);
    SetStrongAttackDmg(15);
    SetWeakAttackDmg(6);
    SetAOEDamage(10);
};

/**
 * Rabbit
 *
 * constructor that sets a custom rName
 * @param Name
 */
Rabbit::Rabbit (string inName)
{
    SetName("Killer Rabbit of " + inName);
};

/**
 * Rabbit
 *
 * constructor that sets a rName from the word bank
 * @param Name number
 */
Rabbit::Rabbit(int nameNum)
{
    SetName("Killer Rabbit of " + nameBank_Rabbit[nameNum]);
};

/**
 * Attack
 *
 * Generates an attack, sets the current attack string to the attack chosen, as well as return the damage number
 * @returns Damage Dealt
 */
int Rabbit::Attack()
{
    srand (time(NULL));
    int randomNumber = rand() % 10 + 1;

    if(randomNumber <= 15)
    {
        SetCurrentAttack("Throat Leap");
        return GetStrongAttackDmg();
    }
    else if(randomNumber <= 75)
    {
        SetCurrentAttack("Bite");
        return GetWeakAttackDmg();
    }
    else
    {
        SetCurrentAttack("Flying Nibble");
        return GetAOEDamage();
    }
}

/**
 * SetCurrentAttack
 *
 * sets the attack string to the string passed in
 * @param Attack String
 */
void Rabbit::SetCurrentAttack(string inString)
{
    rCurrentAttack = inString;
}

/**
 * GetCurrentAttack
 *
 * Returns the current attack
 * @returns Attack String
 */
string Rabbit::GetCurrentAttack() const
{
    return rCurrentAttack;
}

/**
 * SetName
 *
 * sets the rName to the string passed in
 * @param Name
 */
void Rabbit::SetName(string inName)
{
    rName = inName;
}

/**
 * GetName
 *
 * Returns the rName
 * @returns Name
 */
string Rabbit::GetName() const
{
    return rName;
}

/**
 * SetHealth
 *
 * sets the rHealth to the int passed in
 * @param Health
 */
void Rabbit::SetHealth(int inHealth)
{
    rHealth = inHealth;
}
/**
 * GetHealth
 *
 * Returns the rHealth
 * @returns rHealth
 */
int Rabbit::GetHealth() const
{
    return rHealth;
}
/**
 * SetAttackRate
 *
 * sets the attack rate to the int passed
 * @param Attack Rate
 */
void Rabbit::SetAttackRate(int inAttkRt)
{
    rAttackRate = inAttkRt;
}

/**
 * AttackRate
 *
 * Returns the AttackRate
 * @returns AttackRate
 */
int Rabbit::GetAttackRate() const
{
    return rAttackRate;
}
/**
 * SetName
 *
 * sets the string attack damage to the int passed
 * @param Damage
 */
void Rabbit::SetStrongAttackDmg(int inSAttkDmg)
{
   rStrongAttackDamage = inSAttkDmg;
}

/**
 * GetStrongAttackDmg
 *
 * Returns the StrongAttackDmg
 * @returns StrongAttackDmg
 */
int Rabbit::GetStrongAttackDmg() const
{
    return rStrongAttackDamage;
}

/**
 * SetWeakAttackDmg
 *
 * sets the weak attack damage to the int passed
 * @param Damage
 */
void Rabbit::SetWeakAttackDmg(int inWAttkdmg)
{
    rWeakAttackDamage = inWAttkdmg;
}

/**
 * GetWeakAttackDmg
 *
 * Returns the WeakAttackDmg
 * @returns WeakAttackDmg
 */
int Rabbit::GetWeakAttackDmg() const
{
    return rWeakAttackDamage;
}
/**
 * SetAOE
 *
 * sets the AOE damage to the int passed in
 * @param Damage
 */
void Rabbit::SetAOEDamage(int inAOEDmg)
{
    rAOEDamage = inAOEDmg;
}

/**
 * GetAOEDamage
 *
 * Returns the AOEDamage
 * @returns AOEDamage
 */
int Rabbit::GetAOEDamage() const
{
    return rAOEDamage;
}