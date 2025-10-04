/**
 * @file log_generator.cpp
 * @brief A utility to generate a sample log file for testing the Log Analyzer.
 *
 * @details This program creates a synthetic log file with a consistent, structured
 * format. This allows us to focus on the analysis logic rather than dealing with
 * inconsistent real-world log data. The format is designed to be relevant for
 * both financial and cybersecurity analysis.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>    // For modern C++ random number generation.
#include <ctime>     // For seeding the random number generator.
#include <iomanip>   // For formatting output (e.g., setting decimal precision).

 // --- Template Helper Function ---
 // This is a generic function that can get a random element from a vector of any type.
 // 'std::mt19937& gen' is the random number engine we'll be using.
template<typename T>
T getRandomElement(const std::vector<T>& vec, std::mt19937& gen) {
    // A distribution to uniformly select an index from 0 to the vector's max index.
    std::uniform_int_distribution<> distrib(0, vec.size() - 1);
    return vec[distrib(gen)];
}

int main() {
    // --- High-Quality Random Number Setup ---
    // std::mt19937 is a powerful and widely-used random number generation engine.
    // We "seed" it with the current time to ensure we get a different sequence
    // of random numbers every time we run the generator. This makes our test data less repetitive.
    std::mt19937 random_engine(static_cast<unsigned int>(time(0)));

    // --- Configuration ---
    const long long numberOfLinesToGenerate = 100000; // Generate a significant number of lines.
    const std::string outputFilename = "sample.log";

    // --- Data Pools for Generating Realistic Log Entries ---
    // Using vectors to hold our sample data makes it easy to add more variety later.
    std::vector<std::string> ip_addresses = { "203.0.113.89", "198.51.100.2", "192.168.1.10", "10.0.0.5", "172.16.31.45", "10.10.10.10" };
    std::vector<std::string> user_ids = { "user_alpha", "user_beta", "quant_gamma", "trader_delta", "risk_epsilon", "admin_zeta" };
    std::vector<std::string> actions = { "LOGIN", "LOGOUT", "TRADE_EXECUTE", "DATA_QUERY", "ORDER_CANCEL", "FAILED_LOGIN" };
    std::vector<std::string> statuses = { "SUCCESS", "FAILURE", "PENDING" };
    std::vector<std::string> trade_symbols = { "AAPL", "GOOG", "MSFT", "AMZN", "TSLA", "NVDA" };

    // --- File Generation Logic ---
    // 'ofstream' stands for 'Output File Stream'. We use it for writing to files.
    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << outputFilename << std::endl;
        return 1;
    }

    long long startTimestamp = 1672531200; // A fixed start time (approx. Jan 1, 2023) for consistency.

    for (long long i = 0; i < numberOfLinesToGenerate; ++i) {
        // Increment timestamp by a random small amount to simulate time passing.
        std::uniform_int_distribution<> time_increment_dist(1, 5);
        startTimestamp += time_increment_dist(random_engine);

        // Get random components for the log line.
        std::string ip = getRandomElement(ip_addresses, random_engine);
        std::string user = getRandomElement(user_ids, random_engine);
        std::string action = getRandomElement(actions, random_engine);
        // Force the status to be 'FAILURE' if the action is a 'FAILED_LOGIN'.
        std::string status = (action == "FAILED_LOGIN") ? "FAILURE" : getRandomElement(statuses, random_engine);

        std::uniform_int_distribution<> latency_dist(5, 250); // latency in milliseconds
        int latency = latency_dist(random_engine);

        // --- Assembling the Log Line ---
        // Format: Timestamp|IP|UserID|Action|Status|Latency(ms)|Details
        outputFile << startTimestamp << "|"
            << ip << "|"
            << user << "|"
            << action << "|"
            << status << "|"
            << latency << "ms|";

        // Add context-specific details based on the action.
        if (action == "TRADE_EXECUTE") {
            std::uniform_int_distribution<> quantity_dist(10, 500);
            std::uniform_real_distribution<> price_dist(100.0, 5000.0);
            outputFile << "Symbol:" << getRandomElement(trade_symbols, random_engine)
                << ",Quantity:" << quantity_dist(random_engine)
                << ",Price:" << std::fixed << std::setprecision(2) << price_dist(random_engine);
        }
        else if (action == "FAILED_LOGIN") {
            outputFile << "ErrorCode:401_UNAUTHORIZED";
        }
        else {
            outputFile << "Details:N/A";
        }
        // End the line with a newline character.
        outputFile << "\n";
    }

    outputFile.close(); // Explicitly close the file.
    std::cout << "Successfully generated " << numberOfLinesToGenerate << " lines in '" << outputFilename << "'" << std::endl;

    return 0;
}

