///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	File Name:                      Logger.cpp
//	Description:                    A Log file that is used to display messages to the console or file.
//	Author:                         Ryan Shupe, East Tennessee State University
//  Email:                          shuper@etsu.edu
//	Created:                        Friday January 30, 2021
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include "Logger.h"
using namespace std;

string logFileName; //variable to hold the file path for the logger
ofstream logFile;

/**
 * Logger
 *
 * The constructor for the logger class, defaults to "log"
 *
 */
Logger::Logger()
{
    Log("MESSAGE", "Logger Initialized.");
}

/**
 * SetLogFileName
 *
 * Sets the log file name
 *
 * @param logFileName
 */
void Logger::SetLogFileName(string fileName)
{
    logFileName = fileName;
}

void Logger::OpenFile()
{
    logFile.open(logFileName);
}

void Logger::CloseFile()
{
    logFile.close();
}

/**
 * GetLogFileName
 *
 * Returns the log file name
 *
 * @return fileName
 */
string Logger::GetLogFileName()
{
    return logFileName;
}

/**
 * Log
 *
 * Log to the console the message
 *
 * @param message
 */
void Logger::Log(string message)
{
    cout << message << endl;
}

/**
 * Log
 *
 * Log to the console the message with [message] context
 *
 * @param context
 * @param message
 */
void Logger::Log(string context, string message)
{
    cout << "[" << context << "] " << message << endl;
}

/**
 * LogToBoth
 *
 * Log to the console and the file with message with [message] context
 *
 * @param context
 * @param message
 */
void Logger::LogToBoth(string context, string message)
{
    cout << "[" << context << "] " << message << endl;
    logFile << "[" << context << "] " << message << endl;
}

/**
 * LogToBoth
 *
 * Log to the console and the file with message with [message] context
 *
 * @param context
 * @param message
 */
void Logger::LogToBoth(string message)
{
    cout << message << endl;
    logFile << message << endl;
}

/**
 * LogToFile
 *
 * Log to the file the message
 *
 * @param message
 */
void Logger::LogToFile(string message)
{
    logFile << message << endl;
}

/**
 * LogToFile
 *
 * Log to the file the message with context brackets
 *
 * @param context
 * @param message
 */
void Logger::LogToFile(string context, string message) {
    logFile << "[" << context << "] " << message << endl;
}







