///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Log.cpp
//	Description:                    A Log file that is used to display messages to the console or file.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Friday January 30, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Log.h"

using namespace std;

extern string logFileName = "log";

void SetLogFileName(string fileName)
{
    logFileName = fileName;
}

void Log(string message)
{
    cout << message << endl;
}

void Log(string context, string message)
{
    cout << "[" << context << "] " << message << endl;
}
