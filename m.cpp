#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int modulo = 101;
const int d = 256;

int compute_hash(const vector<int>& arr, int length) {
    int hashValue = 0;
    for (int i = 0; i < length; ++i) {
        hashValue = (hashValue * modulo + arr[i]) % modulo;
    }
    return hashValue;
}

int recalculate_hash(const vector<int>& arr, int oldIndex, int newIndex, int oldHash, int patternLength) {
    int newHash = (oldHash - arr[oldIndex] * static_cast<int>(pow(modulo, patternLength - 1)) % modulo + modulo) % modulo;
    newHash = (newHash * modulo + arr[newIndex]) % modulo;
    return newHash;
}

vector<int> rabin_karp(const vector<int>& text, const vector<int>& pattern) {
    vector<int> indices;
    int textLength = text.size();
    int patternLength = pattern.size();
    int patternHash = compute_hash(pattern, patternLength);
    int textHash = compute_hash(text, patternLength);

    for (int i = 0; i <= textLength - patternLength; ++i) {
        if (textHash == patternHash) {
            bool match = true;
            for (int j = 0; j < patternLength; ++j) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                indices.push_back(i);
            }
        }
        if (i < textLength - patternLength) {
            textHash = recalculate_hash(text, i, i + patternLength, textHash, patternLength);
        }
    }
    return indices;
}

void compute_sequence(const vector<int>& indices, int textSize) {
    if (indices.size() < 2) {
        cout << "Subsequence not found twice" << endl;
        return;
    }

    int first = indices[0];
    int second = indices[1];
    

    vector<int> tab(3);
    tab[0] = first;
    tab[1] = second;

    for (int i = 2;; ++i) {
        tab[i % 3] = tab[(i - 1) % 3] + tab[(i - 2) % 3];

        if (tab[i % 3] >= textSize) {
            cout << tab[i % 3] - textSize << "\n";
            break;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int v;
    cin >> v;

    vector<int> orbits(v);
    for (int i = 0; i < v; ++i) {
        cin >> orbits[i];
    }

    int p;
    cin >> p;

    vector<int> pattern(p);
    for (int i = 0; i < p; ++i) {
        cin >> pattern[i];
    }

    vector<int> indices = rabin_karp(orbits, pattern);
    compute_sequence(indices, v);

    return 0;
}
