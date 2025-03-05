#include <iostream>
#include <locale>
#include <string>
#include <cctype>
#include <algorithm>
#include <fstream>

using namespace std;

// PROTOTYYPIT
string string_to_lower(string);

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Finnish");

	string merkkijono = "", haettavaMerkkijono = "";

	if (argc == 3)
	{
		haettavaMerkkijono = argv[1];
		ifstream file(argv[2]);
		if (!file)
		{
			cerr << "Tiedostoa ei voitu avata." << endl;
			return EXIT_FAILURE;
		}
		string line;
		while (getline(file, line))
		{
			if (string_to_lower(line).find(string_to_lower(haettavaMerkkijono)) != string::npos)
			{
				cout << line << endl;
			}
		}
		file.close();
		return EXIT_SUCCESS;
	}

	while (merkkijono.empty())
	{
		cout << "Anna merkkijono, josta etsitään: ";
		getline(cin, merkkijono);
	}

	while (haettavaMerkkijono.empty())
	{
		cout << "Anna merkkijono, joka haetaan: ";
		getline(cin, haettavaMerkkijono);
	}

	size_t found = string_to_lower(merkkijono).find(string_to_lower(haettavaMerkkijono));

	if (found != string::npos)
		cout << "Merkkijono \"" << string_to_lower(haettavaMerkkijono) << "\" löytyi \"" << string_to_lower(merkkijono) << "\":sta kohdasta " << found << endl;
	else
		cout << "Merkkijonoa \"" << string_to_lower(haettavaMerkkijono) << "\" EI löytynyt \"" << string_to_lower(merkkijono) << "\":sta." << endl;

	return EXIT_SUCCESS;
}

string string_to_lower(string str)
{
	string palautus = "";
	for (char c : str)
	{
		palautus += tolower(c);
	}
	return palautus;
}