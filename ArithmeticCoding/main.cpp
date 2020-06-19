#include <iostream>
#include <fstream>
#include <string>
#include"coder.h"
#include "decoder.h"
#include <vector>
#include <windows.h>
using namespace std;

string read_text(string filename)
{
	string text;
	ifstream input(filename, ios::in);
	while (!input.eof())
	{
		string temp;
		getline(input, temp);
		if (!input.eof())
		{
			temp += '\n';
		}
		text += temp;
	}
	input.close();
	return text;
};

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int arg;
	cout << "(1)-encode;(0)-decode" << endl;
	cin >> arg;
	switch (arg) {
		case(1):
		{	
			string filename = "";
			cout << "Enter a file name" << endl;
			cin >> filename;
			string filename_out = "";
			cout << "Save in....." << endl;
			cin >> filename_out;
			string text = "";
			text = read_text(filename);
			vector< std::pair< char, int > > freq = get_freq(text);
			/*for (auto p : freq) 
			std::cout << p.first << ' ' << p.second << std::endl;
			
			for (int i = 0; i < freq.size() + 1; i++)
				cout << frequency[i] << endl;*/
			int* frequency = get_accumulated_freq(freq);
			string abc;
			abc = alphabet(freq);
			//int* freq;
			//freq = get_frequency(text, abc);
			
			string encoded = encode(text, frequency, abc);
			//cout << encoded << endl;
			string message = getBufferFromString(encoded);
			int dif = message.size() * 8 - encoded.size();
			write_encoded(filename_out,message,abc,frequency,dif);
			break;
		}

		case(0):
		{
			string filename = "";
			cout << "Enter a file name" << endl;
			cin >> filename;
			string filename_out = "";
			cout << "Save in....." << endl;
			cin >> filename_out;
			string alphabet;
			int* frequency;
			int d;
			string en = read_encoded(filename, alphabet, frequency,d);
			string bit_en = getStringFromBuffer(en,d);
			string decoded = decode(bit_en, alphabet, frequency);
			write_decoded(filename_out, decoded);
			break;
		}
	}

	return 0;
}