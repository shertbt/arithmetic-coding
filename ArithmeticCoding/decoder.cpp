#include"decoder.h"
unsigned short int read16bit(std::string code)
{
	int i;
	unsigned short int value = 0;
	for (i = 0; i < 16; i++)
	{
		if (i == code.size())
		{
			return value;
		}
		if ('1' == code[i])
		{
			value = value | (1 << (15 - i));
		}
	}
	return value;

}

unsigned short int readbit(char s)
{
	if ('1' == s)
	{
		return 1;
	}
	return 0;
}

std::string decode(std::string code, std::string alphabet, int* frequency)
{
	unsigned short int* h = new unsigned short int[code.length()];
	unsigned short int* l = new unsigned short int[code.length()];
	l[0] = 0;
	h[0] = 65535;
	unsigned int del = frequency[alphabet.size()];
	unsigned short int FIRST_QTR = (h[0] + 1) / 4;
	unsigned short int HALF = 2 * FIRST_QTR;
	unsigned short int THIRD_QTR = 3 * FIRST_QTR;

	std::string output;
	unsigned short int value;
	int codeIdx = 16;
	value = read16bit(code);
	unsigned short int newBit = 0;
	for (int i = 1; i < del + 1; i++)
	{
		unsigned int freq = ((value - l[i - 1] + 1) * del - 1) / (h[i - 1] - l[i - 1] + 1);
		int j;
		for (j = 1; frequency[j] <= freq; j++) {};
		l[i] = l[i - 1] + ((h[i - 1] - l[i - 1] + 1) * frequency[j - 1]) / del;
		h[i] = l[i - 1] + ((h[i - 1] - l[i - 1] + 1) * frequency[j]) / del - 1;



		for (;;)
		{
			if (h[i] < HALF)
				;
			else if (l[i] >= HALF)
			{
				value -= HALF;
				l[i] -= HALF;
				h[i] -= HALF;
			}
			else if ((l[i] >= FIRST_QTR) && (h[i] < THIRD_QTR))
			{
				value -= FIRST_QTR;
				l[i] -= FIRST_QTR;
				h[i] -= FIRST_QTR;
			}
			else break;

			l[i] = 2 * l[i];
			h[i] = 2 * h[i] + 1;


			if (codeIdx < code.length())
			{
				newBit = readbit(code.at(codeIdx++));
			}

			value += value + newBit;


		}

		output.push_back(alphabet.at(j - 1));
	}
	return output;
}

std::string read_encoded(std::string filename, std::string& alphabet, int*& freq, int& d)
{
	std::fstream file(filename, std::ios::binary | std::ios::in);
	int alphabet_size = 0;
	int dif = 0;
	file.read((char*)&dif, sizeof(char));
	file.read((char*)&alphabet_size, sizeof(int));
	int* frequency = new int[alphabet_size + 1];
	frequency[0] = 0;
	char s = 0;
	std::string abc = "";
	for (int j = 1; j < alphabet_size + 1; j++)
	{
		file.read((char*)&s, sizeof(char));
		abc += s;
		file.read((char*)&frequency[j], sizeof(int));
	}
	std::string text = "";
	while (!file.eof())
	{
		std::string temp;
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
std::string toBinary(unsigned char a)
{
	std::string output = "";
	while (a != 0)
	{
		std::string bit = a % 2 == 0 ? "0" : "1";
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
std::string getStringFromBuffer(std::string encoded, int d)
{
	std::string bitstring = "";
	for (int i = 0; i < encoded.size(); i++)
	{
		bitstring += toBinary(encoded[i]);
	}
	bitstring = bitstring.substr(0, bitstring.size() - d);
	return bitstring;

}
void write_decoded(std::string filename, std::string text)
{
	std::ofstream file(filename, std::ios::out);
	for (int i = 0; i < text.size(); i++)
	{
		file << text[i];
	}
}