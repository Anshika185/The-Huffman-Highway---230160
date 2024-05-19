#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;

    // Print the pattern
    if(n%2 != 0){
        for (int i = 1; i <= n; ++i) {
        // Print the left side of the pattern
        for (int j = 1; j <= i; ++j) {
            cout << j;
        }

        // Print the spaces in the middle
        for (int j = 1; j <= 2 * (n - i); ++j) {
            cout << " " ;
        }
        // Middle pattern
        for(int k=1 ; k <= (n-1)/2 ; k++){
                for (int j = i; j >= 1; --j) {
            cout << j;
            }
                for (int j = 1; j <= i; ++j) {
            cout << j;
            }
                for (int j = 1; j <= 2 * (n - i); ++j) {
            cout << " ";
            }
        }
        cout<<"\n";
    }
    }
    else {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                cout << j;
            }
            // Print the spaces in the middle
            for (int j = 1; j <= 2 * (n - i); ++j) {
                cout << " " ;
            }
        
            for(int k=1 ; k <= (n-2)/2 ; ++k){
                for (int j = i; j >= 1; --j) {
                    cout << j;
                }
                for (int j = 1; j <= i; ++j) {
                    cout << j;
                }
                for (int j = 1; j <= 2 * (n - i); ++j) {
                    cout << " ";
                }
            }
                for (int j = i; j >= 1; --j) {
                    cout << j;
                }
                cout<<"\n";
        }   
        
    }  
    cout << endl;
    return 0;
}