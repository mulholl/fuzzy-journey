#include "FuzzyJourney.hpp"

using namespace std;

int main(int argc, char *argv[]){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	string fn = "eff_large_wordlist.txt";
	int opt = EFF_LARGE;

	bool show_info = true; // If this is true the indices for each of the chosen words are given

	int numWords = 5;

	vector<string> wl;
	// string fn = "../test.txt";
	string sha256_str;

	mt19937 RNG(seed);

	inpopts::InpOptsClass opts(argc, argv);

	opts.addOpt('h', "help", "Print this help message");

	if (opts.Used("help") || opts.Used('h')){
		cout << "\nfuzzy-journey Version " << FUZZY_JOURNEY_VERSION_MAJOR << "." << FUZZY_JOURNEY_VERSION_MINOR << "\n" << endl;
		cout << "fuzzy-journey generates passphrases using the Electronic Frontier Foundation's large wordlist for Diceware (available at https://www.eff.org/files/2016/07/18/eff_large_wordlist.txt). A Mersenne-twister based pseudorandom number generator is used to simulate the rolling of a die (i.e. to pseudorandomly pick five non-unique integers in the range [1, 6] with uniform distribution) for each of five words, with the result of each set of rolls being used to select one of the words in the list.\n\nThe program verifies that the hash of eff_large_wordlist.txt is correct (using SHA-256) before generating a passphrase.\n\n\t\t  *** NB - THIS PROGRAM WAS CREATED FOR FUN,  ***\n\t\t***** IT'S PROBABLY BEST TO ASSUME IT DOESN'T *****\n\t\t  ***        CREATE GOOD PASSPHRASES!         ***\n\n" << endl;

		return 1;
	}

	cout << "\nfuzzy-journey Version " << FUZZY_JOURNEY_VERSION_MAJOR << "." << FUZZY_JOURNEY_VERSION_MINOR << "\n" << endl;

	if (opt == EFF_LARGE){
		/* Verify that the wordlist file has not been tampered with by checking 
		 * its SHA256 hash 
		 */
	    if (!file_sha256_check(fn, SHA256_EFF_LARGE_WORDLIST_TXT, sha256_str)){
	    	cout << "FATAL ERROR: The SHA-256 hash for the file " << fn << " was not as expected.\n\nExpected: " << SHA256_EFF_LARGE_WORDLIST_TXT << "\nActual:   " << sha256_str << "\n\nQuitting!" << endl;

	    	return -1;
	    }

	    /* Load the wordlist file */
	    wl.reserve(EFF_LARGE_SIZE);

	    loadDicewareWordlist(fn, wl);

		string passphrase;
		string passphrase_with_info;

		passphrase = dicewareGeneratePassphrase(wl, numWords, passphrase_with_info, RNG);

		if (show_info){
			cout << "Words chosen from the wordlist in " << fn << ": \n" << passphrase_with_info << "\n" << endl;
		}

		cout << "Passphrase: \n" << passphrase << "\n" << endl;
	}
    else {
    	cout << "Invalid option. Quitting." << endl;

    	return -2;
    }
    return 0;	
}