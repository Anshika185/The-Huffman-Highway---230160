#include <iostream>
#include <string>
using namespace std;

// Function to find the lexicographically smallest rotation
string smallestLexicographicalRotation(const string& s) {
    int n = s.size();
    string doubled = s + s;

    // Start with the first character as the initial smallest rotation index
    int smallestRotationIndex = 0;
    
    // Iterate through each possible rotation starting index
    for (int i = 1; i < n; ++i) {
        // Compare the substring starting from the current index with the current smallest
        if (doubled.substr(i, n) < doubled.substr(smallestRotationIndex, n)) {
            smallestRotationIndex = i;
        }
    }

    // Return the smallest rotation
    return doubled.substr(smallestRotationIndex, n);
}

int main() {
    string s;
    cout << "Enter the string: ";
    cin >> s;

    string smallestRotation = smallestLexicographicalRotation(s);
    cout << "Lexicographically smallest rotation: " << smallestRotation << endl;

    return 0;
}