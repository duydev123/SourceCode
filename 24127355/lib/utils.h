#pragma once
#include <string>
#include <vector>
#include <expected>

/**
 * @brief Initializes the application configuration.
 */
void appConfig();

/**
 * @brief Runs the main program logic.
 */
void appRun();

/**
 * @brief Requests an integer input from the user within [min, max].
 *
 * @param prompt The message to prompt the user.
 * @param min Minimum acceptable value.
 * @param max Maximum acceptable value.
 * @return std::expected<int, std::string> The valid integer or error message.
 */
std::expected<int, std::string> requestIntUseCase(std::string prompt, int min, int max);

/**
 * @brief Requests a prime number input from the user within [min, max].
 *
 * @param prompt The message to prompt the user.
 * @param min Minimum acceptable value.
 * @param max Maximum acceptable value.
 * @return std::expected<int, std::string> The valid prime number or error message.
 */
std::expected<int, std::string> requestPrimeUseCase(std::string prompt, int min, int max);

/**
 * @brief Repeatedly requests an integer input until it is valid.
 *
 * @param prompt The message to prompt the user.
 * @param min Minimum acceptable value.
 * @param max Maximum acceptable value.
 * @return int The valid integer input.
 */
int requestIntUntilValidUseCase(std::string prompt, int min, int max);

/**
 * @brief Repeatedly requests a prime number input until it is valid.
 *
 * @param prompt The message to prompt the user.
 * @param min Minimum acceptable value.
 * @param max Maximum acceptable value.
 * @return int The valid prime number input.
 */
int requestPrimeUntilValidUseCase(std::string prompt, int min, int max);

/**
 * @brief Requests multiple prime numbers from the user.
 *
 * @param n Number of primes to input.
 * @param prompt Message to show before inputs.
 * @param min Minimum acceptable value for primes.
 * @param max Maximum acceptable value for primes.
 * @return std::vector<int> List of valid prime numbers entered.
 */
std::vector<int> requestPrimesUseCase(int n, std::string prompt, int min, int max);

/**
 * @brief Prints a list of prime numbers with a preceding message.
 *
 * @param prompt Message to print before the list.
 * @param primes Vector of prime numbers to print.
 */
void print(std::string prompt, std::vector<int> primes);

/**
 * @brief Checks if a given number is prime.
 *
 * @param number The number to check.
 * @return true If the number is prime.
 * @return false Otherwise.
 */
bool isPrime(int number);
