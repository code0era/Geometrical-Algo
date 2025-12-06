#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#define d 256  // number of possible characters (base)

// Rabin-Karp Algorithm 
void rabinKarp(string text, string pattern, int q) {
    int m = pattern.length(); // length of pattern
    int n = text.length();    // length of text
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for text window
    int h = 1;

    // The value of h would be "pow(d, m-1) % q"
    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Calculate hash value for pattern and first window of text
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    cout << "Pattern hash (" << pattern << ") = " << p << endl << endl;

    // Slide the pattern over text one by one
    for (i = 0; i <= n - m; i++) {
        cout << "Window \"" << text.substr(i, m) << "\" -> Hash = " << t;

        // If hash values match, check characters one by one
        if (p == t) {
            bool match = true;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }

            if (match)
                cout << "     Pattern found at index :- " << i << "  ";
        }

        cout << endl;

        // Calculate hash value for next window of text
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            // Make sure t is positive
            if (t < 0)
                t = (t + q);
        }
    }
}

int main() {
    string text = "DAACABCDBA";
    string pattern = "CAB";

    int q = 53; // A prime number

    
    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;
    cout << "\nChecking pattern using Rabin-Karp algorithm...\n" << endl;

    rabinKarp(text, pattern, q);

    return 0;
}
