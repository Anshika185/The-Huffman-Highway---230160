#include <bits/stdc++.h>
using namespace std;

// Function to calculate maximum project value
int maxProjectValue(int N, vector<int>& values, vector<vector<string>>& required_languages, set<string>& known_languages) {
    int max_value = 0;

    // Iterate over each project
    for (int i = 0; i < N; ++i) {
        bool can_do_project = true;

        // Check if all required languages for the project are known
        for (const string& language : required_languages[i]) {
            if (known_languages.find(language) == known_languages.end()) {
                can_do_project = false;
                break;
            }
        }

        // If the project can be done, add its value to the total
        if (can_do_project) {
            max_value += values[i];
        }
    }

    return max_value;
}

int main() {
    int N ;
    cout<< "Enter the number of projects: ";
    cin >> N ;

    vector<int> values(N);
    cout<<"Enter the values of projects: ";
    for(int i =0;i<N;++i){
        cin >> values[i];
    }
    vector<vector<string>> required_languages(N);
    cout << "Enter the required languages for each project: " << endl;
    for (int i = 0; i < N; ++i) {
        int lang_count;
        cout << "Number of languages required for project " << i + 1 << ": ";
        cin >> lang_count;
        required_languages[i].resize(lang_count);
        cout << "Enter the languages: ";
        for (int j = 0; j < lang_count; ++j) {
            cin >> required_languages[i][j];
        }
    }
    set<string> known_languages;
    int known_count;
    cout << "Enter the number of languages you know: ";
    cin >> known_count;
    cout << "Enter the languages: ";
    for (int i = 0; i < known_count; ++i) {
        string lang;
        cin >> lang;
        known_languages.insert(lang);
    }

    int result = maxProjectValue(N, values, required_languages, known_languages);
    cout << "Maximum Project Value: " << result << endl;

    return 0;
}
