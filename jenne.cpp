#include <iostream>
using namespace std;


char normalizeChar(const char& c) {
    if(c == ' '){
        return ' ';
    } 
    if(c >= 'A' && c <= 'Z'){
        return 'A';
    }  
    if(c >= 'a' && c <= 'z'){ 
        return 'a';
    }    
    if(c >= '0' && c <= '9'){ 
        return '0';
    }
    if(c == '.' || c == '?' || c == '!' || c == ',' || c == ';' || c == ':' || c == '-'){ 
        return '.';
    } else {
        return ' ';
    }
}


int* buildLPSArray(const string& pattern) {
    int patternLength = pattern.size();
    int* lps = new int[patternLength]();
    int len = 0;
    int i = 1;

    lps[0] = 0;
    while(i < patternLength) {
        if(pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if(len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}



bool containsPattern(const string& pattern) {
    int* lps = buildLPSArray(pattern);
    unsigned int matchIndex = 0;
    char currentChar = cin.get();

    while(currentChar != '\n') {
        char normalizedChar = normalizeChar(currentChar);
        if(normalizedChar == pattern[matchIndex]) {
            matchIndex++;
            if(matchIndex == pattern.length()) {
                delete[] lps;
                return true;
            }
        } else {
            if(matchIndex != 0) {
                matchIndex = lps[matchIndex - 1];
                continue;
            }
        }
        currentChar = cin.get();
    }

    delete[] lps;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string pattern;
    getline(cin, pattern);

    if(containsPattern(pattern)) {
        cout << "T\n";
    } else {
        cout << "N\n";
    }

    return 0;
}
