#pragma once
#include <iostream>
#include <string>
#include<map>
#include <vector>
#include <algorithm>
bool cmp(const std::pair<char, int>& first, const std::pair<char, int>& second);
std::vector< std::pair< char, int > > get_freq(std::string text);
int* get_accumulated_freq(std::vector< std::pair< char, int > > vec);
std::string alphabet(std::vector< std::pair< char, int > > vec);
int get_index(char symbol, std::string alphabet);
void add_bit(bool bit, int bitsToFollow, std::string& code);
std::string encode(std::string input, int* freq, std::string alphabet);
unsigned short int read16bit(std::string code);
unsigned short int readbit(char s);
std::string decode(std::string code, std::string alphabet, int* frequency);