#include"coder.h"

bool cmp(const std::pair<char, int>& first, const std::pair<char, int>& second)
{
	return first.second > second.second;
}
std::vector< std::pair< char, int > > get_freq(std::string text)
{
	std::map<char, int> freq;
	for (char b : text)
	{
		freq[b]++;
	}
	std::vector< std::pair< char, int > > vec(freq.begin(), freq.end());
	std::sort(vec.begin(), vec.end(), cmp);
	return vec;
}
int* get_accumulated_freq(std::vector< std::pair< char, int > > vec)
{
	int* freq = new int[vec.size() + 1];
	freq[0] = 0;
	int i = 1;
	for (auto p : vec)
	{
		freq[i] = freq[i - 1] + p.second;
		i++;
	}
	return freq;
}
std::string alphabet(std::vector< std::pair< char, int > > vec)
{
	std::string abc = "";
	for (auto p : vec)
	{
		char b = p.first;
		abc += b;
	}
	return abc;
}
int get_index(char symbol, std::string alphabet)
{
	int i = 0;
	for (; i < alphabet.size(); i++)
	{
		if (symbol == alphabet.at(i)) return (i + 1);
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
	unsigned int del = freq[alphabet.size()];
	unsigned short int FIRST_QTR = (h[0] + 1) / 4;
	unsigned short int HALF = 2 * FIRST_QTR;
	unsigned short int THIRD_QTR = 3 * FIRST_QTR;
	int bitsToFollow = 0;
	std::string code;
	int sym = 0;
	int i = 0;
	for (i = 0; i < length;)
	{
		int symbol = get_index(input.at(i), alphabet);
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
	bitsToFollow = 1;
	if (l[i] < FIRST_QTR) add_bit(1, bitsToFollow, code);
	else add_bit(0, bitsToFollow, code);
	return code;
}

std::string getBufferFromString(std::string bitstring)
{
	std::string result = "";
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

void write_encoded(std::string filename, std::string text, std::string alphabet, int* freq, int dif)
{
	std::fstream tab(filename, std::ios::binary | std::ios::out);
	int alphabet_size = alphabet.size();
	tab.write((char*)&dif, sizeof(char));
	tab.write((char*)&alphabet_size, sizeof(int));
	for (int i = 0, j = 1; i < alphabet_size, j < alphabet_size + 1; i++, j++)
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
