#include <iostream>

class BusStopSimulation {
private:
    // �������� const double �� static const double �� ��������� �� �������� �� ������ �����
    static const double averageArrivalTimePassengers;
    static const double averageArrivalTimeBuses;

    // ��� ������� (������ �� �)
    bool isEndStop;

    // ʳ������ ���� � ���������
    int busCapacity;

    // ���� �� ������� �� ��� ������� �������
    int passengersCount;
    double arrivalTimesPassengers[200];

public:
    // �����������
    BusStopSimulation(bool isEnd, int capacity)
        : isEndStop(isEnd), busCapacity(capacity), passengersCount(0) {}

    // ����� ��� ��������� ���������� �������
    void printResults() const {
        std::cout << "Simulation results:" << std::endl;
        std::cout << "Average time between passenger arrivals: " << averageArrivalTimePassengers << " minutes" << std::endl;
        std::cout << "Average time between bus arrivals: " << averageArrivalTimeBuses << " minutes" << std::endl;
        std::cout << "Is it an end stop? " << (isEndStop ? "Yes" : "No") << std::endl;
        std::cout << "Bus capacity: " << busCapacity << " seats" << std::endl;
        std::cout << "Passenger count: " << passengersCount << std::endl;

        if (passengersCount > 0) {
            std::cout << "Arrival times for passengers: ";
            for (int i = 0; i < passengersCount; ++i) {
                std::cout << arrivalTimesPassengers[i] << " ";
            }
            std::cout << "minutes" << std::endl;
        }
    }

    // ����� ��� ���������� �������
    void simulate(int simulationTime) {
        double currentTime = 0.0;
        double busArrivalTime = 0.0;

        while (currentTime < simulationTime) {
            // �������� ��� ������� ������ ��������
            double passengerArrivalTime = currentTime + averageArrivalTimePassengers;

            // ���� �� ������ ������� � ��������� �������, ��������� ����� ��������
            if (currentTime >= busArrivalTime && isEndStop) {
                int passengersToLeave = std::min(busCapacity, passengersCount);
                std::cout << "Bus arrived. Passengers leaving: " << passengersToLeave << std::endl;
                passengersCount -= passengersToLeave;
            }

            // ���� ����� ������� ������� �� ������� ���������, ������ ����
            if (passengerArrivalTime < busArrivalTime || !isEndStop) {
                arrivalTimesPassengers[passengersCount++] = passengerArrivalTime;
                std::cout << "New passenger arrived at time: " << passengerArrivalTime << std::endl;
            }

            // ���������� ��� �������� �������� ���������
            busArrivalTime = currentTime + averageArrivalTimeBuses;

            // �������� ����������� ��� �������� ���������
            std::cout << "Bus scheduled to arrive at time: " << busArrivalTime << std::endl;

            // �������� ������ � ���
            currentTime = std::min(passengerArrivalTime, busArrivalTime);
        }
    }
};

// ��������� ������� ��� static const double
const double BusStopSimulation::averageArrivalTimePassengers = 8.0; // ������� ��� �� �������� �������� (��)
const double BusStopSimulation::averageArrivalTimeBuses = 20.0; // ������� ��� �� �������� ��������� (��)

int main() {
    // ������ ��������� ��� �������
    bool isEndStop = true; // �� � ������� �������
    int busCapacity = 20; // ������� ���� � ���������
    int simulationTime = 300; // ��������� ������� (��)

    // ��������� ��'��� ������� �� ��������� ���������
    BusStopSimulation simulation(isEndStop, busCapacity);
    simulation.simulate(simulationTime);

    // �������� ���������� �������
    simulation.printResults();

    return 0;
}
