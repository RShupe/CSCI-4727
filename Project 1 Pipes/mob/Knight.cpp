///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Knight.cpp
//	Description:                    This is a class to hold all the attributes of a knight.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Wednesday February 3, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Knight.h"

using namespace std;

//name bank for naming knights and rabbits.
string nameBank_Knight[] = {"King Arthur", "Sir Bedevere the Wise", "Sir Lancelot the Brave", "Sir Galahad the Chaste/Pure",
                            "Sir Robin the Not-Quite-So-Brave-As-Sir-Lancelot", "Sir Bors", "Sir Gawain", "Sir Ector", "Guillot the Truthful"
        ,"Gerould the Loyal", "Symon of the Fall", "Dodge the Bald", "Han the Smiling", "Sir Harrison"};

/**
* Knight
*
* no arg constructor
*/
Knight::Knight ()
{
    SetName(0);
    SetHealth(100);
    SetAttackRate(2);
    SetStrongAttackDmg(15);
    SetWeakAttackDmg(10);
    SetAOEDamage(16);
};

/**
 * SetName
 *
 * sets the name to the string passed in
 * @param Name
 */
void Knight::SetName(int inName)
{
    kName = nameBank_Knight[inName];
}

/**
 * SetName
 *
 * sets the name to the string passed in
 * @param Name
 */
void Knight::SetName(string inName)
{
    kName = inName;
}

/**
 * GetName
 *
 * Returns the name
 * @returns Name
 */
string Knight::GetName() const
{
    return kName;
}

/**
 * SetHealth
 *
 * sets the rHealth to the int passed in
 * @param Health
 */
void Knight::SetHealth(int inHealth)
{
    kHealth = inHealth;
}
/**
 * GetHealth
 *
 * Returns the rHealth
 * @returns Health
 */
int Knight::GetHealth() const
{
    return kHealth;
}
/**
 * SetAttackRate
 *
 * sets the attack rate to the int passed
 * @param Attack Rate
 */
void Knight::SetAttackRate(int inAttkRt)
{
    kAttackRate = inAttkRt;
}

/**
 * AttackRate
 *
 * Returns the AttackRate
 * @returns AttackRate
 */
int Knight::GetAttackRate() const
{
    return kAttackRate;
}
/**
 * SetName
 *
 * sets the string attack damage to the int passed
 * @param Damage
 */
void Knight::SetStrongAttackDmg(int inSAttkDmg)
{
    kStrongAttackDamage = inSAttkDmg;
}

/**
 * GetStrongAttackDmg
 *
 * Returns the StrongAttackDmg
 * @returns StrongAttackDmg
 */
int Knight::GetStrongAttackDmg() const
{
    return kStrongAttackDamage;
}

/**
 * SetWeakAttackDmg
 *
 * sets the weak attack damage to the int passed
 * @param Damage
 */
void Knight::SetWeakAttackDmg(int inWAttkdmg)
{
    kWeakAttackDamage = inWAttkdmg;
}

/**
 * GetWeakAttackDmg
 *
 * Returns the WeakAttackDmg
 * @returns WeakAttackDmg
 */
int Knight::GetWeakAttackDmg() const
{
    return kWeakAttackDamage;
}
/**
 * SetAOE
 *
 * sets the AOE damage to the int passed in
 * @param Damage
 */
void Knight::SetAOEDamage(int inAOEDmg)
{
    kAOEDamage = inAOEDmg;
}

/**
 * GetAOEDamage
 *
 * Returns the AOEDamage
 * @returns AOEDamage
 */
int Knight::GetAOEDamage() const
{
    return kAOEDamage;
}