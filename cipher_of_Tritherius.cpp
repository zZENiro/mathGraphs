#include "pch.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

void to_cipher(char *&pText,char *&pKey, const int &textSize, const int &KeySize)
{
	int *DpText = new int[textSize];

	int *DpKey = new int[textSize];

	for (int i = 0; i < textSize; i++)	// pText
	{
		DpText[i] = (int)pText[i];
	}

	for (int i = 0; i < textSize; i++)	// pKey
	{
		DpKey[i] = (int)pKey[i];
	}

	//////////////////////////////////////////////////////////
	
	/*const int *mass = new const int[textSize + KeySize];

	for (int i = 0; i < textSize / KeySize + 1; i+= KeySize)
	{
		mass = mass + DpKey;
	}

	*/

	//////////////////////////////////////////////////////////

	int *DpSiphered = new int[textSize];

	for (int i = 0; i < textSize; i++)
	{
		DpSiphered[i] = DpText[i] + DpKey[i];

		if (DpSiphered[i] >= 255)
		{
			DpSiphered[i] -= 255;
		}
	}

	for (size_t i = 0; i < textSize; i++)
	{
		pText[i] = (char)DpSiphered[i];
	}
}

void to_decipher(char *&pText, char *&pKey, const const int &textSize, const const int &KeySize)
{
	int *DpText = new int[textSize];

	int *DpKey = new int[KeySize];

	for (int i = 0; i < textSize; i++)	// pText
	{
		DpText[i] = (int)pText[i];
	}

	for (int i = 0; i < KeySize; i++)	// pKey
	{
		DpKey[i] = (int)pKey[i];
	}

	int *DpDeSiphered = new int[textSize]; 

	for (int i = 0; i < textSize; i++)
	{
		DpDeSiphered[i] = DpText[i] - DpKey[i];

		if (DpDeSiphered[i] >= 255)
		{
			DpDeSiphered[i] += 255;
		}
	}

	for (size_t i = 0; i < textSize; i++)
	{
		pText[i] = (char)DpDeSiphered[i];
	}
}


int main()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	srand(static_cast<unsigned int>(time(0)));

	int razmText;
	cin >> razmText;						// размеры текста

	int razmKey;							// ключ
	cin >> razmKey;

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	char *pText = new char[razmText];		// text in

	for (size_t i = 0; i < razmText; i++)
	{
		pText[i] = (char)(rand() % 255);
	}

	char *pKey = new char[razmKey];			// key in

	for (size_t i = 0; i < razmKey; i++)
	{
		char a;
		cin >> a;
		pKey[i] = a;
	}

	for (size_t i = 0; i < razmText; i++)
	{
		cout << pText[i] << endl;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	to_cipher(pText, pKey, razmText, razmKey);

	cout << "to_cipher" << endl;

	for (size_t i = 0; i < razmText; i++)
	{
		cout << pText[i] << endl;
	}

	/*to_decipher(pText, pKey, razmText, razmKey);

	cout << "to_decipher" << endl;

	for (size_t i = 0; i < razmText; i++)
	{
		cout << pText[i] << endl;
	}*/

}

