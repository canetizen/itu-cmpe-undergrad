/**
 * BLG 336E Project 3
 * Mustafa Can Caliskan
 * 150200097
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

// Extra Libraries
#include <iomanip>
#include <exception>
#include <unordered_map>
#include <map>
#include <cmath>

using namespace std;

// Struct to store time intervals with start and finish times
struct TimeIntervals {
    int startTime;
    int finishTime;
};

// Struct to store priority value
struct Priority {
    double priority;    
};

// Struct to store item details including priority, name, and price
struct Item {
    Priority value;
    string itemName;
    double price;   
};

// Struct to store schedule details including priority, time intervals, floor name, and room name
struct Schedule {
    Priority roomPriority;
    TimeIntervals interval;
    string floorName;
    string roomName;
};

// Function to sort schedules by their finish times
bool sortByFinishTime(const Schedule& a, const Schedule& b) {
    return a.interval.finishTime < b.interval.finishTime;
}

// Function to find the last non-conflicting schedule
int findLastNonConflictingSchedule(const vector<Schedule>& schedules, int currentIndex) {
    int low = 0, high = currentIndex - 1;

    while (low <= high) {
        int middle = (low + high) / 2;

        if (schedules[middle].interval.finishTime <= schedules[currentIndex].interval.startTime) {
            if (middle + 1 <= high && schedules[middle + 1].interval.finishTime <= schedules[currentIndex].interval.startTime) {
                low = middle + 1;
            } else {
                return middle;
            }
        } else {
            high = middle - 1;
        }
    }

    return -1;
}

/**
 * Function to find the optimal set of non-overlapping schedules that maximizes the total priority.
 * @param schedules A vector of Schedule structs.
 * @return A vector of Schedule structs representing the optimal set.
 */
vector<Schedule> weighted_interval_scheduling(vector<Schedule> schedules) {
    vector<Schedule> optimalSchedules;
    sort(schedules.begin(), schedules.end(), sortByFinishTime); // Sort schedules based on finish time

    int scheduleCount = schedules.size();
    vector<int> maxPriority(scheduleCount, 0); // DP array to keep track of max priority values
    vector<int> lastSelectedIndex(scheduleCount, -1); // Array to store indices for schedule reconstruction

    maxPriority[0] = schedules[0].roomPriority.priority;
    lastSelectedIndex[0] = 0;

    // Loop through each schedule
    for (int i = 1; i < scheduleCount; ++i) {
        int currentProfit = schedules[i].roomPriority.priority;
        int lastNonConflictIndex = findLastNonConflictingSchedule(schedules, i); // Find last non-conflicting schedule

        // Add the profit of the last non-conflicting schedule if it exists
        if (lastNonConflictIndex != -1) {
            currentProfit += maxPriority[lastNonConflictIndex];
        }

        // Compare to decide whether to include the current schedule
        if (currentProfit > maxPriority[i - 1]) {
            maxPriority[i] = currentProfit;
            lastSelectedIndex[i] = i;
        } else {
            maxPriority[i] = maxPriority[i - 1];
            lastSelectedIndex[i] = lastSelectedIndex[i - 1];
        }
    }

    // Reconstruct the optimal schedule list
    int index = lastSelectedIndex[scheduleCount - 1];
    while (index != -1) {
        optimalSchedules.push_back(schedules[index]);
        index = findLastNonConflictingSchedule(schedules, index);
        if (index != -1) {
            index = lastSelectedIndex[index];
        }
    }

    // Reverse the optimal schedules to maintain correct order
    reverse(optimalSchedules.begin(), optimalSchedules.end());
    return optimalSchedules;
}

/**
 * Function to solve the knapsack problem, selecting items that maximize the total priority without exceeding the budget.
 * @param items A vector of Item structs.
 * @param budget The maximum allowable budget.
 * @return A vector of Item structs representing the selected items.
 */
vector<Item> knapsack(const vector<Item>& items, int budget) {
    int itemCount = items.size();
    vector<vector<double>> maxValue(itemCount + 1, vector<double>(budget + 1, 0.0)); // 2D array to track max values
    vector<vector<bool>> includeItem(itemCount + 1, vector<bool>(budget + 1, false)); // 2D array to track selected items

    // Iterate over each item
    for (int i = 1; i <= itemCount; ++i) {
        // Iterate over each possible budget value
        for (int currentBudget = 0; currentBudget <= budget; ++currentBudget) {
            // Check if the current item's price is within the current budget
            if (items[i - 1].price <= currentBudget) {
                double potentialValue = items[i - 1].value.priority + maxValue[i - 1][currentBudget - static_cast<int>(items[i - 1].price)];
                // If including the item increases the value, update the maxValue and mark the item as included
                if (potentialValue > maxValue[i - 1][currentBudget]) {
                    maxValue[i][currentBudget] = potentialValue;
                    includeItem[i][currentBudget] = true;
                } else {
                    maxValue[i][currentBudget] = maxValue[i - 1][currentBudget];
                }
            } else {
                maxValue[i][currentBudget] = maxValue[i - 1][currentBudget];
            }
        }
    }

    vector<Item> result; // Vector to store the selected items
    int remainingBudget = budget;
    for (int i = itemCount; i > 0 && remainingBudget > 0; --i) {
        // If the item is marked as included, add it to the result and reduce the remaining budget
        if (includeItem[i][remainingBudget]) {
            result.push_back(items[i - 1]);
            remainingBudget -= static_cast<int>(items[i - 1].price);
        }
    }
    return result;
}

/**
 * Function to round a number to one decimal place.
 * @param number The number to be rounded.
 * @return The rounded number.
 */
double customRound(double number) {
    double decimalPart = number - floor(number);
    double roundedDecimal = round(decimalPart * 10) / 10;
    if (roundedDecimal >= 0.5) {
        return ceil(number * 10) / 10;
    } else {
        return floor(number * 10) / 10;
    }
}

/**
 * Function to read items from a file and store them in a vector.
 * @param path The path to the directory containing the items file.
 * @return A vector of Item structs.
 */
vector<Item> readItems(const string& path) {
    try {
        ifstream itemFile(path + "/items.txt");
        if (!itemFile.is_open()) {
            throw runtime_error("Failed to open items file.");
        }

        vector<Item> items;
        string line;
        getline(itemFile, line); // Assuming first line is header
        while (getline(itemFile, line)) {
            stringstream ss(line);
            string itemName;
            double price;
            double value;
            ss >> itemName >> price >> value;
            items.push_back({{value}, itemName, price});
        }
        return items;
    } catch(const exception& e) {
        cerr << "Exception caught in readItems: " << e.what() << endl;
        throw;
    }
}

/**
 * Function to read priority map from a file and store it in an unordered map.
 * @param path The path to the directory containing the priority file.
 * @return An unordered map with room names as keys and priority values as values.
 */
unordered_map<string, int> readPriorityMap(const string& path) {
    try {
        ifstream priorityFile(path + "/priority.txt");
        if (!priorityFile.is_open()) {
            throw runtime_error("Failed to open priority file.");
        }

        unordered_map<string, int> priorityMap;
        string line;
        getline(priorityFile, line); // Assuming first line is header
        while (getline(priorityFile, line)) {
            stringstream ss(line);
            string floorName, roomNo;
            int priority;
            ss >> floorName >> roomNo >> priority;
            priorityMap[floorName + " " + roomNo] = priority; // Combine floorName and roomNo as key
        }
        return priorityMap;
    } catch(const exception& e) {
        cerr << "Exception caught in readPriorityMap: " << e.what() << endl;
        throw;
    }
}

/**
 * Function to read floor schedules from a file and store them in a map.
 * @param path The path to the directory containing the room time intervals file.
 * @param priorityMap An unordered map containing priority values for rooms.
 * @return A map with floor names as keys and vectors of Schedule structs as values.
 */
map<string, vector<Schedule>> readFloorSchedules(const string& path, const unordered_map<string, int>& priorityMap) {
    try {
        ifstream roomFile(path + "/room_time_intervals.txt");
        if (!roomFile.is_open()) {
            throw runtime_error("Failed to open room time intervals file.");
        }

        map<string, vector<Schedule>> floorSchedules;
        string line;
        getline(roomFile, line); // Assuming first line is header
        while (getline(roomFile, line)) {
            stringstream ss(line);
            string floorName, roomNo, start, end;
            ss >> floorName >> roomNo >> start >> end;
            Schedule sch;
            sch.floorName = floorName;
            sch.roomName = roomNo;
            sch.interval.startTime = stoi(start.substr(0, start.find(':'))) * 60 + stoi(start.substr(start.find(':') + 1)); // Convert start time to minutes
            sch.interval.finishTime = stoi(end.substr(0, end.find(':'))) * 60 + stoi(end.substr(end.find(':') + 1)); // Convert end time to minutes
            sch.roomPriority.priority = priorityMap.at(floorName + " " + roomNo); // Using .at() for bounds checking
            floorSchedules[floorName].push_back(sch);
        }
        return floorSchedules;
    } catch(const exception& e) {
        cerr << "Exception caught in readFloorSchedules: " << e.what() << endl;
        throw;
    }
}

int main(int argc, char *argv[]) {
    try {
        string case_no = argv[1];
        string case_name = "case_" + case_no;
        string path = "./inputs/" + case_name;

        int total_budget = 200000;

        auto items = readItems(path);
        auto priorityMap = readPriorityMap(path);
        auto floorSchedules = readFloorSchedules(path, priorityMap);

        cout << "Best Schedule for Each Floor\n";
        for (auto& floor: floorSchedules) {
            auto& schedules = floor.second;
            vector<Schedule> optimalSchedules = weighted_interval_scheduling(schedules);
            int totalPriority = 0;
            for (const auto& sched: optimalSchedules) {
                totalPriority += sched.roomPriority.priority;
            }
            cout << floor.first << " --> Priority Gain: " << totalPriority << endl;
            for (const auto& sched: optimalSchedules) {
                cout << floor.first << "\t" << sched.roomName << "\t"
                    << setw(2) << setfill('0') << sched.interval.startTime / 60 << ":" 
                    << setw(2) << setfill('0') << sched.interval.startTime % 60 << "\t"
                    << setw(2) << setfill('0') << sched.interval.finishTime / 60 << ":" 
                    << setw(2) << setfill('0') << sched.interval.finishTime % 60 
                << endl;
            }
            cout << endl;
        }

        vector<Item> selectedItems = knapsack(items, total_budget);
        cout << "\nBest Use of Budget\n";
        cout << "Total Value --> ";
        double totalValue = 0.0;
        for (const auto& item: selectedItems) {
            totalValue += item.value.priority;
        }
        cout << fixed << setprecision(1) << customRound(totalValue) << endl << endl;
        for (const auto& item: selectedItems) {
            cout << item.itemName << endl;
        }
    } catch(const exception& e) {
        cerr << "Exception caught in main: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}