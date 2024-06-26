#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Define the HuffmanNode class
class HuffmanNode {
public:
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};

// Comparison object for the priority queue
class Compare {
public:
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->freq > right->freq;
    }
};

// Function to print Huffman codes
void printCodes(HuffmanNode* root, string str, unordered_map<char, string>& huffmanCode) {
    if (!root)
        return;

    if (!root->left && !root->right) {
        huffmanCode[root->data] = str;
    }

    printCodes(root->left, str + "0", huffmanCode);
    printCodes(root->right, str + "1", huffmanCode);
}

// Function to build the Huffman tree
HuffmanNode* buildHuffmanTree(vector<pair<char, int>>& charFreq) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    for (auto& pair : charFreq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* sum = new HuffmanNode('\0', left->freq + right->freq);
        sum->left = left;
        sum->right = right;
        pq.push(sum);
    }

    return pq.top();
}

// Function to decode a Huffman encoded string
string decodeHuffman(HuffmanNode* root, const string& encodedStr) {
    string decodedStr = "";
    HuffmanNode* current = root;

    for (char bit : encodedStr) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        // If we reach a leaf node, append the character to the result
        if (!current->left && !current->right) {
            decodedStr += current->data;
            current = root; // Go back to the root for the next character
        }
    }

    return decodedStr;
}

int main() {
    // Character frequencies
    vector<pair<char, int>> charFreq = {
        {'k', 2}, {'j', 1}, {'p', 8}, {'x', 1}, {'K', 1}, {'.', 3},
        {'h', 7}, {'c', 4}, {'e', 17}, {'d', 7}, {'y', 2}, {'C', 1},
        {'o', 16}, {'n', 8}, {'a', 6}, {'w', 1}, {' ', 29}, {'g', 6},
        {'t', 14}, {'r', 7}, {'u', 6}, {'l', 4}, {'i', 5}, {'s', 5},
        {'I', 1}, {'f', 2}, {',', 1}
    };

    // Build Huffman Tree
    HuffmanNode* root = buildHuffmanTree(charFreq);

    // Generate Huffman codes
    unordered_map<char, string> huffmanCode;
    printCodes(root, "", huffmanCode);

    // Print Huffman codes
    cout << "Huffman Codes:\n";
    for (auto& pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << "\n";
    }

    // Given encoded string
    string encodedStr = "100000101000011010111001101001101101100000110100110110001010000110010100001111100110101010110111110000110011101011000011110001111101101110111111101011001100011011111010000011100011110101010110111111011011101111110001000100101011011011111001111100010000101100000111100001011110111010001001111100110101010110111000010111010011001000101111000111101001110000101011011110101001111111001110100001001110110010110110010111110110111110010101011010101101111111101101111000110010111001011001010100000001100111110100000111001100101101100101111011000101111101101110111111010101001011000111100111001011001100110111101000001110001111001100110110010111001011001010101011100101110010100101000100011010100000111";

    // Decode the encoded string
    string decodedStr = decodeHuffman(root, encodedStr);

    cout << "\nDecoded string: " << decodedStr << "\n";

    return 0;
}
