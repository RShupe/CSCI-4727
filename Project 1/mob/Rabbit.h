///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Rabbit.h
//	Description:                    Header file for the bunny class
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Wednesday February 3, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
using namespace std;

class Rabbit
{
public:
    Rabbit();
    Rabbit(int nameNum);

    void GenerateName();
    void SetName(string inName);
    string GetName() const;
    Rabbit (string inName);
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
