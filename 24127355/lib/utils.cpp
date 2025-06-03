#include "utils.h"
#include <iostream>
#include <regex>

using namespace std;

void appConfig() {
    // Application initialization - currently empty
}

void appRun() {
    int min = 2, max = 10;
    int n = requestIntUntilValidUseCase("Enter integer n in [2, 10]: ", min, max);

    min = 1;
    max = 100;
    vector<int> primes = requestPrimesUseCase(n, "Enter " + to_string(n) + " prime numbers in [1, 100]: ", min, max);

    print("The prime numbers you entered are: ", primes);
}

expected<int, string> requestIntUseCase(string prompt, int min, int max) {
    cout << prompt;
    string buffer;
    getline(cin, buffer);

    if (buffer.empty()) {
        return unexpected("Input cannot be empty.");
    }

    regex pattern("^\\d+$");
    if (!regex_match(buffer, pattern)) {
        return unexpected("Invalid integer format.");
    }

    int value = stoi(buffer);
    if (value < min || value > max) {
        return unexpected("Value out of allowed range.");
    }

    return value;
}

int requestIntUntilValidUseCase(string prompt, int min, int max) {
    expected<int, string> result;
    do {
        result = requestIntUseCase(prompt, min, max);
        if (!result) {
            cout << "Error: " << result.error() << " Please try again.\n";
        }
    } while (!result);
    return result.value();
}

expected<int, string> requestPrimeUseCase(string prompt, int min, int max) {
    auto result = requestIntUseCase(prompt, min, max);
    if (!result) return result;
    if (!isPrime(result.value())) {
        return unexpected("Not a prime number.");
    }
    return result.value();
}

int requestPrimeUntilValidUseCase(string prompt, int min, int max) {
    expected<int, string> result;
    do {
        result = requestPrimeUseCase(prompt, min, max);
        if (!result) {
            cout << "Error: " << result.error() << " Please try again.\n";
        }
    } while (!result);
    return result.value();
}

vector<int> requestPrimesUseCase(int n, string prompt, int min, int max) {
    cout << prompt << "\n";
    vector<int> result;
    for (int i = 1; i <= n; ++i) {
        string message = "Enter prime number #" + to_string(i) + ": ";
        int value = requestPrimeUntilValidUseCase(message, min, max);
        result.push_back(value);
    }
    return result;
}

void print(string prompt, vector<int> primes) {
    cout << prompt;
    for (const auto& num : primes) {
        cout << num << " ";
    }
    cout << "\n";
}

bool isPrime(int number) {
    if (number < 2) return false;
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) return false;
    }
    return true;
}
