#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>



int timeToMinutes(const std::string& time) {
    int HH = std::stoi(time.substr(0, 2));
    int mm = std::stoi(time.substr(3, 2));
    return HH * 60 + mm;
}

std::pair<int, int> minutesToTime(int minutes) {
    int HH = minutes / 60;
    int mm = minutes % 60;
    return {HH, mm};
}

double simulateProbability(const std::string& start_time, const std::string& end_time, int target_dimension, int simulations = 100000) {
    int start_minutes = timeToMinutes(start_time);
    int end_minutes = timeToMinutes(end_time);

    if (end_minutes < start_minutes) {
        end_minutes += 24 * 60;
    }

    int count_target = 0;

    std::srand(std::time(0));

    for (int i = 0; i < simulations; ++i) {
        int random_minutes = std::rand() % (end_minutes - start_minutes) + start_minutes;
        auto [HH, mm] = minutesToTime(random_minutes % (24 * 60));
        if (Loptr(HH, mm) == target_dimension) {
            count_target++;
        }
    }

    return static_cast<double>(count_target) / simulations;
}

int main() {
    std::string start_time, end_time;
    int target_dimension;

   
    
    std::cin >> start_time;
    std::cin >> end_time;
    std::cin >> target_dimension;

    double probability = simulateProbability(start_time, end_time, target_dimension);
    std::cout << std::fixed << std::setprecision(2) << probability << std::endl;

    return 0;
}
