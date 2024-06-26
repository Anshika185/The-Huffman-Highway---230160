#include <opencv2/opencv.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <bitset>

using namespace cv;
using namespace std;

// HuffmanNode class definition
class HuffmanNode {
public:
    uchar data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(uchar d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};

// Custom comparator for priority queue
class Compare {
public:
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->freq > right->freq;
    }
};

// Function to calculate frequencies of pixel values
unordered_map<uchar, int> calculateFrequencies(const Mat& image) {
    unordered_map<uchar, int> freqMap;
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            freqMap[image.at<uchar>(i, j)]++;
        }
    }
    return freqMap;
}

// Function to build the Huffman tree
HuffmanNode* buildHuffmanTree(const unordered_map<uchar, int>& freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (auto& pair : freqMap) {
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

// Function to generate Huffman codes
void generateCodes(HuffmanNode* root, const string& str, unordered_map<uchar, string>& huffmanCode) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffmanCode[root->data] = str;
    }
    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}

// Function to encode the image
string encodeImage(const Mat& image, const unordered_map<uchar, string>& huffmanCode) {
    string encodedStr = "";
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            encodedStr += huffmanCode.at(image.at<uchar>(i, j));
        }
    }
    return encodedStr;
}

int main() {
    // Load the image in grayscale mode
    Mat image = imread(""C:\\Users\\anshi\\Downloads\\download.png"", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // Calculate frequencies of pixel values
    unordered_map<uchar, int> freqMap = calculateFrequencies(image);

    // Build Huffman Tree
    HuffmanNode* root = buildHuffmanTree(freqMap);

    // Generate Huffman codes
    unordered_map<uchar, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    // Encode the image
    string encodedStr = encodeImage(image, huffmanCode);

    // Output the Huffman codes
    cout << "Huffman Codes:\n";
    for (auto& pair : huffmanCode) {
        cout << (int)pair.first << ": " << pair.second << "\n";
    }

    // Output the encoded string (for demonstration purposes)
    cout << "Encoded Image String: " << encodedStr << endl;

    return 0;
}
