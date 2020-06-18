#include <iostream>
#include <fstream>
#include <string>
#include"coding.h"
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
string getBufferFromString(string bitstring)
{
	string result = "";
	int count = 0;
	unsigned char byte = 0;

	for (int i = 0; i < bitstring.size(); i++)
	{
			byte = (byte << 1) | (bitstring[i] - '0');
			count++;
			if (count == 8)
			{
				count = 0;
				result += byte;
				byte = 0;
			}
		
	}
	if (count != 0)
	{
		while (count != 8)
		{
			byte = (byte << 1);
			count++;
		}
		result += byte;
	}
	return result;
}
void write_encoded(string filename, string text,string alphabet,int *freq,int dif)
{
	fstream tab(filename, ios::binary | ios::out);
	int alphabet_size = alphabet.size();
	tab.write((char*)&dif, sizeof(char));
	tab.write((char*)&alphabet_size, sizeof(int));
	for (int i=0, j=1; i< alphabet_size,j < alphabet_size+1;i++,j++)
	{
		tab.write((char*)&alphabet[i], sizeof(char));
		tab.write((char*)&freq[j], sizeof(int));
	}
	for (int i = 0; i < text.size(); i++)
	{
		tab << text[i];
	}
	tab.close();
}
string read_encoded(string filename,string &alphabet,int *&freq,int &d)
{
	fstream file(filename, ios::binary | ios::in);
	int alphabet_size = 0;
	int dif = 0;
	file.read((char*)&dif, sizeof(char));
	file.read((char*)&alphabet_size, sizeof(int));
	int* frequency = new int[alphabet_size + 1];
	frequency[0] = 0;
	char s = 0;
	string abc = "";
	for (int j = 1;j < alphabet_size + 1; j++)
	{
		file.read((char*)&s, sizeof(char));
		abc += s;
		file.read((char*)&frequency[j], sizeof(int));
	}
	string text = "";
	while (!file.eof())
	{
		string temp;
		getline(file, temp);
		if (!file.eof())
		{
			temp += '\n';
		}
		text += temp;
	}
	file.close();
	d = dif;
	alphabet = abc;
	freq = frequency;
	return text;
}
string toBinary(unsigned char a)
{
	string output = "";
	while (a != 0)
	{
		string bit = a % 2 == 0 ? "0" : "1";
		output += bit;
		a /= 2;
	}
	if (output.size() < 8)
	{
		int deficit = 8 - output.size();
		for (int i = 0; i < deficit; i++)
		{
			output += "0";
		}
	}

	reverse(output.begin(), output.end());
	return output;
}
string getStringFromBuffer(string encoded,int d)
{
	string bitstring = "";
	for (int i = 0; i < encoded.size(); i++)
	{
		bitstring += toBinary(encoded[i]);
	}
	bitstring = bitstring.substr(0, bitstring.size() - d);
	return bitstring;

}
void write_decoded(string filename, string text)
{
	ofstream file(filename,ios::out);
	for (int i = 0; i < text.size(); i++)
	{
		file << text[i];
	}
}
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