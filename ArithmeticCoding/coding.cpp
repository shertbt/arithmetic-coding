#include"coding.h"

bool cmp(const std::pair<char, int>& first,const std::pair<char, int>& second)
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
		if (symbol == alphabet.at(i)) return (i+1);
	}
}
void add_bit(bool bit, int bitsToFollow, std::string& code)
{
	code.push_back(bit+48);
	while (bitsToFollow > 0)
	{
		code.push_back(!bit+48);
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
	for ( i = 0; i < length;)
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
	bitsToFollow=1;
	if (l[i] < FIRST_QTR) add_bit(1, bitsToFollow, code);  
	else add_bit(0, bitsToFollow, code);
	return code;
}

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
	for (int i = 1; i < del+1; i++)
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
