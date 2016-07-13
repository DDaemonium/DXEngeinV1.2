#pragma once
#include <fstream>
#include <ctime>
#include <string>


template<typename T>
void ErrorLog(const string &moduleName, const T &error) {
	std::ofstream out("ErrorLog.txt", std::ios::app);
	out << "\n_______________________________________________\n";
	time_t td;
	td = time(NULL);
	out << ctime(&td);
	out << "In Module: " << moduleName;
	out << "\nError: " << error;
	out.close();
}

template<typename T>
void DebugLog(const string &moduleName, const T &debugLine) {
	std::ofstream out("DebugLog.txt", std::ios::app);
	cout << "\n_______________________________________________\n";
	time_t td;
	td = time(NULL);
	cout << ctime(&td);
	cout << "In Module: " << moduleName;
	cout << '\n' << debugLine;
}
