#include "Diceware.hpp"

using namespace std;

int loadDicewareWordlist(const std::string &fn, std::vector<std::string> &wl){
    ifstream ifs(fn);
    string str;
    stringstream ss;
    int a;
    int count = 0;

    if (ifs.is_open()){
        while(getline(ifs, str)){
            ss.clear();
            ss.str(str);
            ss >> a;
            ss >> str;
            wl.push_back(str);
            count++;
        }
    }

    return count;
}

std::string dicewarePickRandomWord(const std::vector<std::string> &wl, std::string &str1, std::mt19937 &RNG){
	int numWords = wl.size();

	string str2;

	int mult = 1;
	int numDice = 1;

	while (true){
		mult *= 6;
		if (mult == numWords){
			break;
		}
		else if (mult > numWords){
			cout << "numWords = " << numWords << endl << "mult = " << mult << endl;
			throw BadListSize{ };
		}
		numDice++;
	}

 	uniform_int_distribution<int> distribution(1, numDice);	

 	stringstream ss1;
 	stringstream ss2;

 	int rand_int;

 	for (int i = 0; i < numDice; ++i){
		rand_int = distribution(RNG);
 		ss1 << rand_int;
 		ss2 << rand_int - 1;
 	}


 	rand_int = stoi(ss1.str());

 	str1 += to_string(rand_int) + ": ";

 	rand_int = stoi(ss2.str());

 	rand_int = changeBase(rand_int, 6, 10);

 	str1 += wl[rand_int] + '\n';
 	str2 = wl[rand_int];

    return str2;
}

std::string dicewarePickRandomWord(const std::vector<std::string> &wl, std::mt19937 &RNG){
	string str;
	return dicewarePickRandomWord(wl, str, RNG);
}

std::string dicewareGeneratePassphrase(const std::vector<std::string> &wl, const int &numWords, std::string &str1, std::mt19937 &RNG){
	str1 = "";
    string str2 = "";

    for (int i = 0; i < numWords - 1; ++i){
        str2 = str2 + dicewarePickRandomWord(wl, str1, RNG) + " ";
    }
    str2 = str2 + dicewarePickRandomWord(wl, str1, RNG) + "\n";

    return str2;
}

std::string dicewareGeneratePassphrase(const std::vector<std::string> &wl, const int &numWords, std::mt19937 &RNG){
	string str;
	return dicewareGeneratePassphrase(wl, numWords, str, RNG);
}

int changeBase(const int &inp, const int &fromBase, const int &toBase){
	// cout << "calling toBase10" << endl;
    int tmp = toBase10(inp, fromBase);
	// cout << "tmp = " << tmp << endl << "calling fromBase10" << endl;
    return fromBase10(tmp, toBase);
}

int toBase10(const int &inp, const int &fromBase){
    if (fromBase == 10){
        return inp;
    }

    // cout << "inp = " << inp << endl;

    int out = 0;
    stringstream ss;

    string str(to_string(inp));

    int origDigits = str.length();
    // int base10Digits = 0;
    int maxVal = 1;

    for (int i = 0; i <= origDigits; ++i){
    	maxVal *= fromBase;
    }
    maxVal--;

    // base10Digits = to_string(maxVal).size();

    int divisor = (maxVal + 1) / (fromBase * fromBase);
    int tmp;

    for (int i = 0; i < origDigits; ++i){
    	ss << str[i];
    	ss >> tmp;
    	// cout << tmp << " * " << divisor << " = " << tmp * divisor << endl;
    	out += tmp * divisor;
    	divisor = divisor / fromBase;
    	// cout << endl << endl;
    	ss.clear();
    }

    // cout << "out = " << out << endl;

    // exit(0);

    return out;
}

int fromBase10(const int &inp, const int &toBase){
    if (toBase == 10){
        return inp;
    }

    int out = 0;

    string str = to_string(inp);
    int len = str.length();

    int rem;
    int tmp = inp;
    int mult = 1;

    bool go = true;
    int i = 0;

    while (go){
        mult = 1;
        for (int j = 1; j <= i; ++j){
            mult *= 10;
        }
        out += (tmp % toBase) * mult;
        tmp = tmp / toBase;
        if (tmp == 0){
            // cout << "TMP = 0" << endl;
            go = false;
        }
        // cout << "out = " << out << " | mult = " << mult << endl;
        ++i;
    }
    cout << endl;

    return out;
}
