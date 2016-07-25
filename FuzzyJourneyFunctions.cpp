#include "FuzzyJourneyFunctions.hpp"

using namespace std;

string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

string sha256_file(const string &fn)
{
    // FILE *file = fopen("../test.txt", "rb");
    ifstream ifs(fn);

    stringstream ss;

    bool go = true;

    if (ifs.is_open()){    
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        const int bufSize = 32768;
        char *buffer = new char[bufSize];
        int bytesRead = 0;
        // while((bytesRead = fread(buffer, 1, bufSize, file)))
        while (go){
            ifs.read(buffer, bufSize);
            if (ifs.eof()){
                go = false;
                buffer[ifs.gcount()] = '\0';
            }
            string tmp = buffer;
            bytesRead = tmp.size();
            SHA256_Update(&sha256, buffer, bytesRead);
            // cout << "1 | Read " << bytesRead << " bytes: |" << buffer << "|" << endl;
        }
        SHA256_Final(hash, &sha256);
        for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        {
            ss << hex << setw(2) << setfill('0') << (int)hash[i];
        }
        delete [] buffer;
    }
    ifs.close();
    return ss.str();
}

bool file_sha256_check(const string &fn, const string &str){
    if (str.compare(sha256_file(fn)) == 0){
        return true;
    }
    else {
        return false;
    }
}

bool file_sha256_check(const string &fn, const string &str, string &ret){
    ret = sha256_file(fn);
    if (str.compare(ret) == 0){
        return true;
    }
    else {
        return false;
    }
}
