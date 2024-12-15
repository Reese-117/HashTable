
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Function: compare
// Sort tokens by frequency in descending order. If two tokens have the same frequency, sort alphabetically.
bool compare(const pair<string, int>& a, const pair<string, int>& b) {
    if (a.second == b.second)
        return a.first < b.first; // Alphabetical order if frequencies match
    return a.second > b.second; // Descending frequency order
}

// Function to split a string into tokens (words)
vector<string> tokenize(const string& str) {
    vector<string> tokens;
    string token;
    for (size_t i = 0; i < str.size(); ++i) {
        char ch = str[i];
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += ch;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

int main(int argc, char* argv[]) {
    istream* inputStream = &cin; // Default input is stdin
    ifstream inputFile;

    // Check if a filename was provided
    if (argc > 1) {
        inputFile.open(argv[1]);
        if (!inputFile) {
            cerr << "Error: Cannot open input file: " << argv[1] << endl;
            return 1;
        }
        inputStream = &inputFile; // Use file input if provided
    }

    map<string, int> tokenFrequency; // Map to store each token and its frequency
    string inputText, line;

    // Read the entire input into a string
    while (getline(*inputStream, line)) {
        inputText += line + '\n';
    }

    // Tokenize and count frequencies
    vector<string> tokens = tokenize(inputText);
    for (size_t i = 0; i < tokens.size(); ++i) {
        tokenFrequency[tokens[i]]++;
    }

    // Close the input file if used
    if (inputFile.is_open()) inputFile.close();

    // Step 2: Transfer map to vector and sort it
    vector<pair<string, int> > sortedTokens(tokenFrequency.begin(), tokenFrequency.end());
    sort(sortedTokens.begin(), sortedTokens.end(), compare);

    // Step 3: Create a mapping of tokens to their sorted positions
    map<string, int> tokenPosition;
    for (size_t i = 0; i < sortedTokens.size(); ++i) {
        tokenPosition[sortedTokens[i].first] = i + 1; // Position starts at 1
    }

    // Step 4: Output the sorted tokens
    for (size_t i = 0; i < sortedTokens.size(); ++i) {
        cout << sortedTokens[i].first;
        if (i != sortedTokens.size() - 1) cout << " "; // Space between tokens
    }
    cout << endl;
    cout << "**********" << endl;

    // Step 5: Encode the input text with token positions
    for (size_t i = 0; i < tokens.size(); ++i) {
        cout << tokenPosition[tokens[i]] << " ";
    }
    cout << endl;

    return 0;
};