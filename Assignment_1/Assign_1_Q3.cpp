#include <iostream>
using namespace std;
int main(){
    int exam_score[10];
    cout << "Enter 10 exam scores: ";
    for (int i = 0; i<10; i++){
        cin >> exam_score[i];
    }
    int sum = 0;
    for (int i = 0; i<10; i++){
        sum = sum + exam_score[i];
    }
    double avg_exam_score = sum / 10 ;
    cout << "Average Exam Score:" << avg_exam_score << "\n";
    
    int max = exam_score[0];
    for (int i = 0; i<10; i++){
        if(exam_score[i] > max){
            max = exam_score[i];
        }
    }
    cout<< "Highest Exam Score: " << max<< "\n";
    
    int min = exam_score[0];
    for (int i = 0; i<10; i++){
        if(exam_score[i] < min){
            min = exam_score[i];
        }
    }
    cout<< "Lowest Exam Score: " << min << "\n";
    
    int j=0;
    for (int i = 0; i<10; i++){
        if(exam_score[i]< avg_exam_score){
            j++;
        }
        else {
            continue;
        }
    }
    
    cout << "Number of exam scores below the average: " << j << "\n";
    
    int k=0;
    for (int i = 0; i<10; i++){
        if(exam_score[i] > avg_exam_score){
            k++;
        }
        else {
            continue;
        }
    }
    
    cout << "Number of exam scores above the average: " << k << "\n";
}