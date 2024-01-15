#include <iostream>
#include <queue>
#include <string>
#include <ctime>

#pragma warning(disable : 4996)

class PrintRequest {
public:
    std::string user;
    int priority;

    PrintRequest(const std::string& u, int p) : user(u), priority(p) {}
};

class PrintStatistics {
public:
    std::string user;
    time_t printTime;

    PrintStatistics(const std::string& u, time_t t) : user(u), printTime(t) {}
};

// Corrected comparator for priority_queue
struct ComparePriority {
    bool operator()(const PrintRequest& left, const PrintRequest& right) const {
        return left.priority > right.priority;
    }
};

class PrinterQueue {
private:
    std::priority_queue<PrintRequest, std::vector<PrintRequest>, ComparePriority> printQueue;
    std::queue<PrintStatistics> printStats;

public:
    void enqueuePrintRequest(const std::string& user, int priority) {
        PrintRequest request(user, priority);
        printQueue.push(request);
        std::cout << "Print request from " << user << " with priority " << priority << " enqueued.\n";
    }

    void processPrintRequests() {
        while (!printQueue.empty()) {
            PrintRequest currentRequest = printQueue.top();
            printQueue.pop();

            // Simulating the printing process
            std::cout << "Printing for " << currentRequest.user << " with priority " << currentRequest.priority << "...\n";

            // Recording print statistics
            PrintStatistics stats(currentRequest.user, std::time(nullptr));
            printStats.push(stats);
        }
    }

    void printStatistics() {
        std::cout << "\nPrint Statistics:\n";
        while (!printStats.empty()) {
            PrintStatistics stats = printStats.front();
            printStats.pop();

            std::cout << "User: " << stats.user << ", Print Time: " << std::ctime(&stats.printTime);
        }
    }
};

int main() {
    PrinterQueue printer;

    // Enqueue print requests with different priorities
    printer.enqueuePrintRequest("User1", 2);
    printer.enqueuePrintRequest("User2", 1);
    printer.enqueuePrintRequest("User3", 3);

    // Process print requests
    printer.processPrintRequests();

    // Print statistics
    printer.printStatistics();

    return 0;
}
