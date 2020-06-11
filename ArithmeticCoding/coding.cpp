#include"coding.h"
std::string get_alphabet(std::string input)
{
	std::string alphabet;
	for (int i = 0; i < input.size(); i++)
	{
		int j;
		for (j = 0; j < alphabet.size(); j++)
		{
			if (alphabet[j] == input[i])
			{
				break;
			}
		}
		if (j >= alphabet.size())
		{
			alphabet.push_back(input[i]);
		}

	}
	return alphabet;
}

int* getFrequency(std::string input, std::string alphabet)
{
	int* helper = new int[alphabet.size()];
	helper = new int[alphabet.size()];
	for (int i = 0; i < alphabet.size(); i++)
	{
		helper[i] = 0;
	}
	for (int j = 0; j < alphabet.size(); j++)
	{
		for (int i = 0; i < input.size(); i++)
		{
			if (alphabet[j] == input[i])
			{
				helper[j]++;
			}
		}
		if (j > 0)
		{
			helper[j] += helper[j - 1];
		}
	}
	int* freq = new int[alphabet.size() + 1];
	freq[0] = 0;
	for (int i = 1; i < alphabet.size() + 1; i++)
	{
		freq[i] = helper[i - 1];
	}
	return freq;
}
int get_Index(char symbol, std::string alphabet)
{
	int i = 0;
	for (; i < alphabet.size(); i++)
	{
		if (symbol == alphabet.at(i)) return (i+1);
	}
}
void add_bit(bool bit, int bitsToFollow, std::string& code)
{
	code.push_back(bit + 48);
	while (bitsToFollow > 0)
	{
		code.push_back(!bit + 48);
		bitsToFollow--;
	}
}

std::string encode(std::string input, int* freq, std::string alphabet)
{
	int length = input.length();
	unsigned short int* h = new unsigned short int[input.length()];
	unsigned short int* l = new unsigned short int[input.length()];
	h[0] = 65535;
	l[0] = 0;
	unsigned int del = freq[alphabet.size() - 1];
	unsigned short int FIRST_QTR = (h[0] + 1) / 4;
	unsigned short int HALF = 2 * FIRST_QTR;
	unsigned short int THIRD_QTR = 3 * FIRST_QTR;
	int bitsToFollow = 0;
	std::string code;
	int sym = 0;
	for (int i = 0; i < length;)
	{
		int symbol = get_Index(input.at(i), alphabet);
		i++;
		l[i] = l[i - 1] + ((h[i - 1] - l[i - 1] + 1) * freq[symbol - 1]) / del;
		h[i] = l[i - 1] + ((h[i - 1] - l[i - 1] + 1) * freq[symbol]) / del - 1;
		for (;;)
		{
			if (h[i] < HALF)
			{
				add_bit(0, bitsToFollow, code);
				bitsToFollow = 0;
			}
			else if (l[i] >= HALF)
			{
				add_bit(1, bitsToFollow, code);
				bitsToFollow = 0;
				l[i] -= HALF;
				h[i] -= HALF;
			}
			else if ((l[i] >= FIRST_QTR) && (h[i] < THIRD_QTR))
			{
				bitsToFollow++;
				l[i] -= FIRST_QTR;
				h[i] -= FIRST_QTR;
			}
			else  break;


			l[i] = 2 * l[i];
			h[i] = 2 * h[i] + 1;
		}

	}
	return code;
}
