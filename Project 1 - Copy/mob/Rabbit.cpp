///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Rabbit.cpp
//	Description:                    This is a class to hold all the attributes of a Rabbit.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Wednesday February 3, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include "Rabbit.h"

using namespace std;

string nameBank_Rabbit[] = {"Waterton", "Sargos", "Blooding", "Carrotton", "Hareington", "Hopsville USA", "Florida", "Eggerton", "Volta",
                            "Eleyvine"};

/**
* Knight
*
* no arg constructor
*/
Rabbit::Rabbit ()
{
    SetHealth(100);
    SetAttackRate(4);
    SetStrongAttackDmg(15);
    SetWeakAttackDmg(8);
    SetAOEDamage(10);
};

void Rabbit::SetName(int inName)
{
    string temp = "Killer Rabbit of " + nameBank_Rabbit[inName];
    rName = temp;
}

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
 * @returns Health
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