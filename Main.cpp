#include <iostream>

class BusStopSimulation {
private:
    // Замінюємо const double на static const double та визначаємо їх значення за межами класу
    static const double averageArrivalTimePassengers;
    static const double averageArrivalTimeBuses;

    // Тип зупинки (кінцева чи ні)
    bool isEndStop;

    // Кількість місць у маршрутці
    int busCapacity;

    // Люди на зупинці та час їхнього приходу
    int passengersCount;
    double arrivalTimesPassengers[200];

public:
    // Конструктор
    BusStopSimulation(bool isEnd, int capacity)
        : isEndStop(isEnd), busCapacity(capacity), passengersCount(0) {}

    // Метод для виведення результатів імітації
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

    // Метод для проведення імітації
    void simulate(int simulationTime) {
        double currentTime = 0.0;
        double busArrivalTime = 0.0;

        while (currentTime < simulationTime) {
            // Генеруємо час приходу нового пасажира
            double passengerArrivalTime = currentTime + averageArrivalTimePassengers;

            // Якщо це кінцева зупинка і маршрутка приїхала, симулюємо виход пасажирів
            if (currentTime >= busArrivalTime && isEndStop) {
                int passengersToLeave = std::min(busCapacity, passengersCount);
                std::cout << "Bus arrived. Passengers leaving: " << passengersToLeave << std::endl;
                passengersCount -= passengersToLeave;
            }

            // Якщо новий пасажир прийшов до приходу маршрутки, додаємо його
            if (passengerArrivalTime < busArrivalTime || !isEndStop) {
                arrivalTimesPassengers[passengersCount++] = passengerArrivalTime;
                std::cout << "New passenger arrived at time: " << passengerArrivalTime << std::endl;
            }

            // Обчислюємо час прибуття наступної маршрутки
            busArrivalTime = currentTime + averageArrivalTimeBuses;

            // Виводимо повідомлення про прибуття маршрутки
            std::cout << "Bus scheduled to arrive at time: " << busArrivalTime << std::endl;

            // Рухаємось вперед у часі
            currentTime = std::min(passengerArrivalTime, busArrivalTime);
        }
    }
};

// Означення значень для static const double
const double BusStopSimulation::averageArrivalTimePassengers = 8.0; // середній час між приходом пасажирів (хв)
const double BusStopSimulation::averageArrivalTimeBuses = 20.0; // середній час між приходом маршруток (хв)

int main() {
    // Задаємо параметри для імітації
    bool isEndStop = true; // чи є зупинка кінцевою
    int busCapacity = 20; // кількість місць у маршрутці
    int simulationTime = 300; // тривалість імітації (хв)

    // Створюємо об'єкт імітації та запускаємо симуляцію
    BusStopSimulation simulation(isEndStop, busCapacity);
    simulation.simulate(simulationTime);

    // Виводимо результати імітації
    simulation.printResults();

    return 0;
}
