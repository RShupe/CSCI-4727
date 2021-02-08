///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Logger.h
//	Description:                    Header file for the Logger class.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Friday January 30, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

class Logger
{
public:
    Logger();

    void SetLogFileName(std::string fileName);
    std::string GetLogFileName();
    void CloseFile();
    void OpenFile();
    void Log(std::string message);
    void Log(std::string context, std::string message);
    void LogToFile(std::string message);
    void LogToFile(std::string context, std::string message);
    void LogToBoth(std::string context, std::string message);
    void LogToBoth(std::string message);
    void LogToFile(std::string context, std::string name, std::string action, std::string targetName, std::string damage);
};


