#pragma once
#include <iostream>
#include <string>
#include<map>
std::string get_alphabet(std::string input);
int* get_frequency(std::string input, std::string alphabet);
int get_index(char symbol, std::string alphabet);
void add_bit(bool bit, int bitsToFollow, std::string& code);
std::string encode(std::string input, int* freq, std::string alphabet);
unsigned short int read16bit(std::string code);
unsigned short int readbit(char s);
std::string decode(std::string code, std::string alphabet, int* frequency);