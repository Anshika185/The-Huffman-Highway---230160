#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

// Function for addition
double add(double x, double y) {
    return x + y;
}

// Function for subtraction
double subtract(double x, double y) {
    return x - y;
}

// Function for multiplication
double multiply(double x, double y) {
    return x * y;
}

// Function for division
double divide(double x, double y) {
    if (y == 0) {
        cout << "Error! Cannot divide by zero!" << endl;
        return NAN; // Not a Number
    }
    return x / y;
}

// Function for custom modulus (to avoid conflict)
double custom_modulus(double x, double y) {
    return fmod(x, y);
}

// Function for remainder
double custom_remainder(double x, double y) {
    return remainder(x, y);
}

// Function for natural logarithm
double natural_logarithm(double x) {
    return log(x);
}

// Function for sine
double sine(double x) {
    return sin(x);
}

// Function for exponential
double exponential(double x, double y) {
    return pow(x, y);
}

// Function to evaluate expression
double evaluate_expression(vector<string> operators, vector<double> values) {
    double result = values[0];
    for (size_t i = 1; i < values.size(); ++i) {
        if (operators[i - 1] == "+") {
            result = add(result, values[i]);
        } else if (operators[i - 1] == "-") {
            result = subtract(result, values[i]);
        } else if (operators[i - 1] == "*") {
            result = multiply(result, values[i]);
        } else if (operators[i - 1] == "/") {
            result = divide(result, values[i]);
        } else if (operators[i - 1] == "%") {
            result = custom_modulus(result, values[i]);
        } else if (operators[i - 1] == "remainder") {
            result = custom_remainder(result, values[i]);
        } else if (operators[i - 1] == "ln") {
            result = natural_logarithm(result);
        } else if (operators[i - 1] == "sin") {
            result = sine(result);
        } else if (operators[i - 1] == "exp") {
            result = exponential(result, values[i]);
        } else {
            cout << "Error! Invalid operator" << endl;
            return NAN; // Not a Number
        }
    }
    return result;
}

int main() {
    vector<string> operators;
    vector<double> values;
    char choice;

    do {
        string op;
        cout << "Enter operator (+, -, *, /, %, remainder, ln, sin, exp): ";
        cin >> op;
        operators.push_back(op);

        double val;
        cout << "Enter value: ";
        cin >> val;
        values.push_back(val);

        cout << "Do you want to enter another operator and value? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    // Evaluate expression and print result
    cout << "Result: " << evaluate_expression(operators, values) << endl;

    return 0;
}
