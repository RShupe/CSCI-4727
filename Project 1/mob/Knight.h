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

class Knight
{
private:
    string kName;                //The name of the character
    string kCurrentAttack;       //The current attack the mob just casted
    int kHealth;                 //The rHealth of the mob
    int kAttackRate;             //The attack rate of the mod
    int kStrongAttackDamage;     //The strong attack damage
    int kWeakAttackDamage;       //The weak attack damage
    int kAOEDamage;              //The AOE damage

public:
    Knight();
    Knight(int nameNum);
    Knight (string inName);

    int Attack();

    void SetName(string inName);
    string GetName() const;

    void SetCurrentAttack(string inString);
    string GetCurrentAttack() const;

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
