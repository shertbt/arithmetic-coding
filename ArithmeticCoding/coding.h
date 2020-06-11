#pragma once
#include <iostream>
#include <string>
#include<map>
std::string get_alphabet(std::string input);
int* getFrequency(std::string input, std::string alphabet);
int get_Index(char symbol, std::string alphabet);
void add_bit(bool bit, int bitsToFollow, std::string& code);
std::string encode(std::string input, int* freq, std::string alphabet);