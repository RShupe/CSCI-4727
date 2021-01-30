#pragma once

extern std::string logFileName;
void SetLogFileName(std::string fileName);
void Log(std::string message);
void Log(std::string context, std::string message);

