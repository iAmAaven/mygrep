#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <fstream>
#include <exception>

using namespace std;

// Muuntaa merkkijonon pieniksi kirjaimiksi
string to_lower(const string& str);

// Tarkistaa, sisältääkö rivi haetun merkkijonon
bool contains_string(const string& line, const string& search, bool ignore_case);

// Tulostaa ohjelman käyttöohjeet
void print_usage() {
    cerr << "Usage: mygrep -o[OPTIONS] <SEARCH TERM> <FILE>" << endl;
    cerr << "Options:\n  -l  Print line numbers\n  -r  Invert search\n  -i  Ignore case\n  -o  Count occurrences" << endl;
}

int main(int argc, char* argv[]) {
    // Jos komentoriviparametreja ei ole, pyydetään syöte käyttäjältä
    if (argc == 1) {
        string input_string, search_string;
        cout << "Enter the string to search in: ";
        getline(cin, input_string);
        cout << "Enter the string to search for: ";
        getline(cin, search_string);

        // Etsitään merkkijonoa syötteestä
        size_t found = to_lower(input_string).find(to_lower(search_string));
        if (found != string::npos)
            cout << "String \"" << search_string << "\" found at position " << found << endl;
        else
            cout << "String \"" << search_string << "\" NOT found." << endl;

        return EXIT_SUCCESS;
    }

    // Tarkistetaan komentoriviparametrien määrä
    if (argc != 4) {
        print_usage();
        return EXIT_FAILURE;
    }

    // Parsitaan komentoriviparametrit
    string options = string(argv[1]).substr(2);
    string search_string = argv[2];
    string file_name = argv[3];

    // Määritetään valintojen tila
    bool print_line_numbers = options.find('l') != string::npos;
    bool count_occurrences = options.find('o') != string::npos;
    bool ignore_case = options.find('i') != string::npos;
    bool reverse_search = options.find('r') != string::npos;

    // Avataan tiedosto
    ifstream file(file_name);
    if (!file) {
        cerr << "Could not open file." << endl;
        return EXIT_FAILURE;
    }

    string line;
    int line_number = 0;
    int occurrence_count = 0;

    try {
        // Luetaan tiedosto rivi kerrallaan
        while (getline(file, line)) {
            line_number++;
            bool found = contains_string(line, search_string, ignore_case);
            if (reverse_search) found = !found;

            // Tulostetaan osumat
            if (found) {
                if (print_line_numbers) cout << line_number << ": ";
                cout << line << endl;
                occurrence_count++;
            }
        }
    }
    catch (const exception& e) {
        cerr << "An exception occurred: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    // Tulostetaan osumien määrä, jos tarpeen
    if (count_occurrences)
        cout << "Occurrences of lines " << (reverse_search ? "NOT " : "") << "containing \"" << search_string << "\": " << occurrence_count << endl;

    return occurrence_count == 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

// Tarkistaa, sisältääkö rivi haetun merkkijonon
bool contains_string(const string& line, const string& search, bool ignore_case) {
    if (ignore_case)
        return to_lower(line).find(to_lower(search)) != string::npos;
    return line.find(search) != string::npos;
}

// Muuntaa merkkijonon pieniksi kirjaimiksi
string to_lower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
