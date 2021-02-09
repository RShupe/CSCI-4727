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

#include <string>

using namespace std;

class Knight
{
private:
    string kName;                   //The name of the character
    int kHealth;                 //The rHealth of the mob
    int kAttackRate;             //The attack rate of the mod
    int kStrongAttackDamage;     //The strong attack damage
    int kWeakAttackDamage;       //The weak attack damage
    int kAOEDamage;              //The AOE damage

public:
    Knight();

    void SetName(int i);
    string GetName() const;
    void SetName(string inName);

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
