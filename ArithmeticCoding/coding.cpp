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
	int* frequency = new int[alphabet.size()];

	for (int i = 0; i < alphabet.size(); ++i)
	{
		frequency[i] = 0;
	}

	for (int i = 0; i < input.size(); i++)
	{

		for (int j = 0; j < alphabet.size(); j++)
		{
			if (alphabet[j] == input[i])
			{
				frequency[j]++;
				break;
			}
		}
	}
	return frequency;
}