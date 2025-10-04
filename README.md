# High-Performance Log File Analyzer
## 1. Overview

This is a high-performance C++ application designed to parse, analyze, and extract key metrics from large server log files. The project is tailored to analyze logs from a custom simulated log file currently a custom financial trading log file, providing insights relevant to system performance, user activity, and potential cybersecurity threats.

This project serves as a practical demonstration of modern C++ skills, including efficient file I/O, string manipulation, and the use of optimal data structures for data aggregation.
## 2. Features

- High-Speed, Memory-Efficient Parsing: Reads and processes large log files (millions of lines) efficiently without loading the entire file into memory.

- Structured Analysis: Generates a summary report with relevant key metrics.

- Scalable Architecture: Built with a modular design to easily accommodate new analysis metrics in the future.

- Self-Contained Testing: Includes a dedicated utility to generate realistic test log data.
## 3. Log Format
The analyzer is designed to parse log files with the following | (pipe) delimited format:

Timestamp|IP_Address|UserID|Action|Status|Latency|Details

- Timestamp: UNIX epoch time.
- IP_Address: The source IP of the request.
- UserID: The identifier of the user performing the action.
- Action: The type of action (e.g., LOGIN, TRADE_EXECUTE, DATA_QUERY).
- Status: The result of the action (e.g., SUCCESS, FAILURE, PENDING).
- Latency: The time taken for the operation to complete, in milliseconds.
- Details: Context-specific information (e.g., trade details, error codes).

Sample Log Line:

1672531213|198.51.100.2|trader_delta|TRADE_EXECUTE|SUCCESS|89ms|Symbol:AAPL,Quantity:100,Price:150.75

## 4. How to Compile and Run
This project is built using standard C++. It can be compiled with any modern C++17 compliant compiler (like GCC, Clang, or MSVC in Visual Studio).
Using Visual Studio:
1. Clone the Repository: Download or clone this project to your local machine.
2. Create Solution: Open Visual Studio and create a new empty solution.
3. Add Projects:
   - Add a new "Console App" project to the solution named LogGenerator. Copy the code from log_generator.cpp into its main file.
   - Add a second "Console App" project named LogAnalyzer. Copy the code from main.cpp into its main file.
4. Generate the Log File:
   - Right-click the LogGenerator project in the Solution Explorer and select "Set as Startup Project".
   - Press F5 or Ctrl + F5 to build and run it. This will create the sample.log file in your project's output directory.
5. Run the Analyzer:
   - Right-click the LogAnalyzer project and select "Set as Startup Project".
   - CRITICAL: You must provide the log file name as a command-line argument.
     - Right-click the LogAnalyzer project again -> Properties.
     - Navigate to the Debugging tab.
     - In the Command Arguments field, type sample.log.
   - Press F5 or Ctrl + F5 to build and run the analyzer.
