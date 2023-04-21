#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 
#include <string> 
#include <fstream>
#include <chrono>
#include <ctime>  

using std::endl;
using std::string;

struct LogSystem : private std::streambuf, public std::ofstream
{
	LogSystem(std::string fileName = "LogFile.dat") : std::ofstream(fileName) {}

	void init(int argc, char** argv)
	{
		(*this) << "Software name: " << " жи_есть_братуха_sph" << endl;
		(*this) << "Compilation time: " << __DATE__ << " " << __TIME__ << endl;
		(*this) << "Run time start: " << current_time();
		(*this) << "command line: " << endl; for (int i = 0; i < argc; i++) (*this) << i << ": " << argv[i] << endl;

	}
	void blanked(int n = 1)
	{
		for (int i = 0; i < n; i++)
			(*this) << endl;
	}
	std::string current_time()
	{
		auto clock = std::chrono::system_clock::now();
		std::time_t time = std::chrono::system_clock::to_time_t(clock);
		return std::ctime(&time);
	}
};
