#include <iostream>
#include <fstream>
#include <string>
#include"coding.h"
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
	string text="";
	text = read_text("C:\\Users\\Дмитрий\\Desktop\\alice.txt");
	string abc;
	abc = get_alphabet(text);
	int* freq;
	freq = getFrequency(text, abc);
	/*cout << abc << endl;
	for (int i = 0; i < abc.size()+1; i++)
	{
		cout << freq[i] << endl;
	}
	*/
	string encoded = encode(text, freq, abc);
	cout << encoded << endl;
	return 0;
}