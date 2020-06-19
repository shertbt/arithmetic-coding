#pragma once
#include <iostream>
#include <string>
#include <fstream>
unsigned short int read16bit(std::string code);
unsigned short int readbit(char s);
std::string decode(std::string code, std::string alphabet, int* frequency);
std::string read_encoded(std::string filename, std::string& alphabet, int*& freq, int& d);
std::string toBinary(unsigned char a);
std::string getStringFromBuffer(std::string encoded, int d);
void write_decoded(std::string filename, std::string text);