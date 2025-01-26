/* Mustafa Can Caliskan
 * 150200097
 * BLG335E HW1 */

#include <vector> //vector
#include <string>
#include <iostream> //cout
#include <fstream> //file operations
#include <sstream> //file operations
#include <chrono> //measure time

using namespace std;

void quick_sort(vector<pair<string, int>>&, int, int, char, int, bool v);
int partition(vector<pair<string, int>>&, int, int, char, bool v); // Partition function for quicksort
void insertion_sort(vector<pair<string, int>>&, int, int); // Regular insertion sort
int generate_median_of_random_indices(int, int); // Generates 3 numbers and returns median of them.
void read_pairs_from_csv(string, vector<pair<string, int>>&); // Reads pairs from given CSV file
void write_pairs_to_csv(string, vector <pair<string, int>> &); // Writes pairs to given CSV file
void write_log_file(vector <pair<string, int>> &, int, int, int); //Logs
void swap_pairs(pair<string, int>&, std::pair<string, int>&); // Swaps given pairs

int main(int argc, char** argv) { // Arguments respectively: QuickSort (executable itself), input.csv, pivot_strategy, threshold k, output.csv, verbose (if any)
    vector<pair<string, int>> arr;
    
    srand(static_cast<unsigned int>(time(nullptr)));

    remove("log.txt"); //to delete previous log.txt if any (since log.txt file is opened in append mode, it is constantly overwritten.)

    read_pairs_from_csv(argv[1], arr); // input.csv sent as parameter

    auto start_time = chrono::high_resolution_clock::now(); // Time measurement started
    
    bool verbose = false;

    if ((argc == 6) && (argv[5][0] == 'v')) { // Verbose check
        verbose = true;
    } else if ((argc < 5 || argc > 6) || (argc == 6 && argv[5][0] != 'v')) {
        cout << "Error: Either missing, extra or wrong arguments. Try again." << endl;
        exit(1);
    }

    quick_sort(arr, 0, arr.size() - 1, argv[2][0], stoi(argv[3]), verbose); // pivot_strategy and threshold sent as parameter
    
    auto end_time = chrono::high_resolution_clock::now(); // Time measurement end
    auto time_elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count(); // Time difference between end and start
    cout << "Time taken by QuickSort with pivot strategy '" << argv[2] << "' and threshold " << argv[3] << ": " << to_string(time_elapsed) << " ns." << endl;
    
    write_pairs_to_csv(argv[4], arr);

    return 0;
}

//Based on homework description, I assumed that "naive approach" contains ALL pivot strategies. (non-hybrid <=> only quicksort)
int partition(vector <pair<string, int>> &arr, int start_index, int end_index, char pivoting_strategy, bool v) {
    switch (pivoting_strategy) { 
        case 'l': 
            break;
        case 'r': // Random approach
            swap_pairs(arr[(start_index + rand() % (end_index - start_index + 1))], arr[end_index]); break;
        case 'm': // Median approach
            swap_pairs(arr[generate_median_of_random_indices(start_index, end_index)], arr[end_index]); break;
        default:
            cout << pivoting_strategy << " is an unidentified strategy. Program terminated." << endl;
            exit(1);
    } // Pivot selected and swapped with the last element of array between given indices.
    
    pair<string, int> pivot_pair = arr[end_index]; 

    int current_index = start_index - 1;
    for (int j = start_index; j <= end_index; j++) {
        if(arr[j].second < pivot_pair.second) {
            current_index++;
            swap_pairs(arr[current_index], arr[j]);
        }
    }

    swap_pairs(arr[current_index + 1], arr[end_index]);

    if (v) { // Logging after swapping
        write_log_file(arr, start_index, end_index, current_index + 1);
    }
    
    return (current_index + 1); // current_index + 1 is the actual index of our pivot.
}

// Based on homework description, I assumed that when k is 1, only quick_sort works with given pivoting_strategy.
void quick_sort(vector <pair<string, int>> &arr, int start_index, int end_index, char pivoting_strategy, int k, bool v) {
    if (end_index - start_index + 1 > k) {
        int pivot_index = partition(arr, start_index, end_index, pivoting_strategy, v);
        quick_sort(arr, start_index, pivot_index - 1, pivoting_strategy, k, v);
        quick_sort(arr, pivot_index + 1, end_index, pivoting_strategy, k, v);
    } else {
        insertion_sort(arr, start_index, end_index);
    }
}

void insertion_sort(vector <pair<string, int>> &arr, int start_index, int end_index) {
    int j, key;
    for (int i = start_index + 1; i <= end_index; i++) {
        key = arr[i].second;
        j = i - 1;
 
        while ((j >= 0) && (arr[j].second > key)) {
            swap_pairs(arr[j + 1], arr[j]);
            j--;
        }
        arr[j + 1].second = key;
    }
}

int generate_median_of_random_indices(int start_index, int end_index) {
    int n1, n2, n3;

    n1 = start_index + rand() % (end_index - start_index + 1);
    n2 = start_index + rand() % (end_index - start_index + 1);
    n3 = start_index + rand() % (end_index - start_index + 1);

    if ((n1 >= n2 && n2 >= n3) || (n1 <= n2 && n2 <= n3))
        return n2;
    else if ((n2 >= n1 && n1 >= n3) || (n2 <= n1 && n1 <= n3))
        return n1;
    else
        return n3;
}

void read_pairs_from_csv(string csv_name, vector <pair<string, int>> &arr) {
    ifstream file(csv_name);
    if (!file.is_open()) {
        cout << "File not found. Program terminated." << endl;
        exit(1);
    }

    int pop;
    string city, line;
    while (getline(file, line)) {
        stringstream lineStream(line);
        getline(lineStream, city, ';');
        lineStream >> pop;
        arr.push_back(make_pair(city, pop));
    }

    file.close();
}

void write_pairs_to_csv(string file_name, vector <pair<string, int>> &arr) {
    ofstream file(file_name, ios::out); // opened in write mode
    if (!file.is_open()) {
        cout << file_name << " file error. Program terminated." << endl;
        exit(1);
    }
    for (unsigned int i = 0; i < arr.size() - 1; i++) {
        file << arr[i].first << ";" << to_string(arr[i].second) << "\n";
    }
    file << arr.back().first << ";" << to_string(arr.back().second); // For the last element, '\n' is undesirable.
    file.close();
}

void write_log_file(vector <pair<string, int>> &arr, int start_index, int end_index, int current_index) {
    ofstream file("log.txt", ios::app); // opened in append mode
    if (!file.is_open()) {
        cout << "log.txt file error. Program terminated." << endl;
        exit(1);
    }
    file << "Pivot: " << to_string(arr[current_index].second) << " Array: [";
    for (int i = start_index; i < end_index; i++) {
        file << to_string(arr[i].second) << ", ";
    }
    file << to_string(arr[end_index].second) << "]\n"; // For the last element, ',' is undesirable.
    file.close();
}

void swap_pairs(pair<string, int> &ptr1, pair<string, int> &ptr2) {
    pair<string, int> temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;
}