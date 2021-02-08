///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Knight.h
//	Description:                    Header file for the knight class
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Wednesday February 3, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
using namespace std;

class Rabbit
{
private:
    string rName;                  //The name of the character
    int rHealth;                 //The rHealth of the mob
    int rAttackRate;             //The attack rate of the mod
    int rStrongAttackDamage;     //The strong attack damage
    int rWeakAttackDamage;       //The weak attack damage
    int rAOEDamage;              //The AOE damage

public:
    Rabbit();

    void SetName(int inName);
    string GetName() const;

    void SetHealth(int inHealth);
    int GetHealth() const;

    void SetAttackRate(int inAttkRt);
    int GetAttackRate() const;

    void SetStrongAttackDmg(int inSAttkDmg);
    int GetStrongAttackDmg() const;

    void SetWeakAttackDmg(int inWAttkdmg);
    int GetWeakAttackDmg() const;

    void SetAOEDamage(int inAOEDmg);
    int GetAOEDamage() const;

};
