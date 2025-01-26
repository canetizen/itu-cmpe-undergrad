/* Mustafa Can Caliskan
 * 150200097
 * BLG335E HW2 */

//Utility libraries
#include <iostream>
#include <vector>
#include <string> 
#include <chrono> //time mesaurement

//File operations
#include <fstream>
#include <sstream>

//Height calculation
#include <math.h> 

using namespace std;

//Utility functions
void write_pairs_to_csv(string, vector <pair<string, int>> &); //writes pair array to output file
void write_one_pair_to_csv(string, pair<string, int> &); //writes a single pair to output file
void read_pairs_from_csv(string, vector <pair<string, int>> &); //reads pairs from input file
size_t find(const std::string&, char); //finds a substring (in our code, we need it to find underscore)
void swap(pair<string, int>&, pair<string, int>&); //swaps pairs

//Heap functions
void max_heapify(vector<pair<string, int>>&, int, int, int);
void build_max_heap(vector<pair<string, int>>&, int);
void heapsort(vector<pair<string, int>>&, int);
void max_heap_insert(vector<pair<string, int>>&, string, int);
pair<string, int> heap_extract_max(vector<pair<string, int>>&);
void heap_increase_key(vector<pair<string, int>>&, int, int);
pair<string, int> heap_maximum(vector<pair<string, int>> &);
int dary_calculate_height(int, int);
pair<string, int> dary_extract_max(vector<pair<string, int>> &, int);
void dary_insert_element(vector<pair<string, int>> &, string, int, int);
void dary_increase_key(vector<pair<string, int>>&, int, int, int);

int main(int argc, char** argv) {

    if (argc < 4 || argc > 7) { //argument check
        cout << "Invalid arguments, program terminated." << endl;
        return 1;
    }

    vector <pair<string, int>> arr; //pair array to store cities

    read_pairs_from_csv(argv[1], arr); //reading pairs

    string* args = new string[argc]; //for converting char** to string[] (required for function name comparison)
    for (int i = 0; i < argc; ++i) {
        args[i] = argv[i];
    }


    /*
     * I assume that the necessary parameters are provided to the called functions according to their requirements. 
     * (The parameters i, d, k will be provided only for the functions that need them.) */

    //Parameter initialization
    int i = 0; 
    int d = 2; //default d is binary
    int k = 0; // 3434 of k_istanbul_3434 or k3434
    string city_name = ""; //istanbul of k_istanbul_3434

    string out_csv = args[3]; //name of the output file

    if (argc > 4) { //i,d,k flags
        for (int j = 4; j < argc; j++) {
            if (args[j].length() < 2) { //EX: only k
                cout << "Improper flag, program terminated." << endl;
                return 1;
            }
            switch(args[j][0]) {
                case 'i':
                    i = stoi(args[j].substr(1)) - 1; //Given indices start from 1 (1 corresponds to the root)
                    break;

                case 'd':
                     d = stoi(args[j].substr(1)); 
                    break;

                case 'k': {
                    size_t underscore_position = args[j].substr(2).find('_');
                    if (underscore_position != string::npos) {
                        city_name = args[j].substr(2, underscore_position);
                        k = stoi(args[j].substr(2).substr(underscore_position + 1));
                    } else { //If '_' is not found (k123)
                        k = stoi(args[j].substr(1));
                    }
                    break; 
                }

                default:
                    cout << "Unidentified flag, program terminated." << endl;
                    return 1;
            }
        }
    }

    pair<string, int> result_pair = make_pair("", -1); //to store some individual pairs such as height or extracted pair

    auto start_time = chrono::high_resolution_clock::now(); // Time measurement started
    if (args[2] == "max_heapify") {
        max_heapify(arr, arr.size(), i, d);

    } else if (args[2] == "build_max_heap") {
        build_max_heap(arr, d);

    } else if (args[2] == "heapsort") {
        heapsort(arr, d);

    } else if (args[2] == "max_heap_insert") {
        max_heap_insert(arr, city_name, k);

    } else if (args[2] == "heap_increase_key") {
        heap_increase_key(arr, i, k);

    } else if (args[2] == "dary_insert_element") {
        dary_insert_element(arr, city_name, k, d);

    } else if (args[2] == "dary_increase_key") {
        dary_increase_key(arr, i, k, d);

    } else if (args[2] == "heap_extract_max") {
        result_pair = heap_extract_max(arr);

    } else if (args[2] == "heap_maximum") {
        result_pair = heap_maximum(arr);

    } else if (args[2] == "dary_calculate_height") {
        int result_value = dary_calculate_height(arr.size(), d);
        result_pair = make_pair("Height: ", result_value);

    } else if (args[2] == "dary_extract_max") {
        result_pair = dary_extract_max(arr, d);

    } else {        
        cout << "Unidentified function, program terminated" << endl;
        return 1;
    }

    auto end_time = chrono::high_resolution_clock::now(); // Time measurement of end
    auto time_elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count(); // Time difference between end and start
    cout << "Time taken by "<< args[2] << " with given d = " << d << " and n = " << arr.size() << " is: " << time_elapsed << " ns." << endl;

    if (result_pair.first != "" && result_pair.second != -1) {
        write_one_pair_to_csv(out_csv, result_pair);
    } else {
        write_pairs_to_csv(out_csv, arr);
    }
    cout << "Operation completed successfully." << endl;
    return 0;
}

/* max_heap function is implemented to handle both binary and d-ary cases
 * Since the default value of d is 2, if the max_heap function is called without specifying the d parameter, it will be set to 2.*/
void max_heapify(vector<pair<string, int>>&arr, int n, int i, int d) { 
    int parent = i;

    //loop through childs
    for (int j = 1; j <= d; ++j) {
        int child = d * i + j;

        //If any child is greater than its parent, parent is updated.
        if (child < n && arr[child].second > arr[parent].second) {
            parent = child;
        }
    }

    //If parent is updated, swap old parent and the new one.
    if (parent != i) {
        swap(arr[i], arr[parent]);
        max_heapify(arr, n, parent, d);
    }
}

/* build_max_heap function is implemented to handle both binary and d-ary cases
 * Since the default value of d is 2, if the max_heap function is called without specifying the d parameter, it will be set to 2.*/
void build_max_heap(vector<pair<string, int>> &arr, int d) {
    //Iterate through each parent
    for (int i = (arr.size() / d) - 1; i >= 0; --i) {
        max_heapify(arr, arr.size(), i, d);
    }
}

void heapsort(vector<pair<string, int>> &arr, int d) {
    build_max_heap(arr, d);
    //Since the largest element of a max heap is always the first element, within a loop, we build the heap each time and heapify it without including the largest element by moving it to the end.
    for (int i = arr.size() - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        max_heapify(arr, i, 0, d);
    }
}

void max_heap_insert(vector<pair<string, int>> &arr, string first, int second) {
    build_max_heap(arr, 2);
    pair <string, int> new_city = make_pair(first, second);
    arr.push_back(new_city); //new pair is inserted
    int i = arr.size() - 1;
    while (i > 0 && arr[(i - 1) / 2].second < arr[i].second) { //heap has changed. Heapify is neccessary.
        swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

pair<string, int> heap_extract_max(vector<pair<string, int>> &arr) {
    if (arr.size() == 0) {
        cout << "Heap is empty, operation terminated." << endl;
        return make_pair("", -1);
    }
    build_max_heap(arr, 2);
    pair<string, int> deleted_city = arr[0]; //Max element (the first element of max heap) is deleted.
    arr.erase(arr.begin());

    max_heapify(arr, arr.size(), 0, 2); //Heapify is neccessary.

    return deleted_city;
}

void heap_increase_key(vector<pair<string, int>>& arr, int index, int key) {
    int size = arr.size();
    if (index >= size || index < 0) {
        cout << "Index out of the range, operation terminated." << endl;
        return;
    }

    if (key < arr[index].second) {
        cout << "Given key is smaller than current key, operation terminated." << endl;
        return;
    }

    build_max_heap(arr, 2);
    arr[index].second = key; //Key of given index has changed.

    while (index > 0 && arr[(index - 1) / 2].second < arr[index].second) { //heapify is neccessary.
        swap(arr[index], arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

pair<string, int> heap_maximum(vector<pair<string, int>> &arr) {
    if (arr.size() == 0) {
        cout << "Heap is empty, operation terminated." << endl;
        return make_pair("", -1);
    }
    build_max_heap(arr, 2);

    return arr[0];
}

int dary_calculate_height(int n, int d) {
    int height = ceil(log(n * d - n + 1) / log(d)) - 1;
    return height;
}

pair<string, int> dary_extract_max(vector<pair<string, int>> &arr, int d) {
    if (arr.size() == 0) {
        cout << "Heap is empty, operation terminated." << endl;
        return make_pair("", -1);
    }
    build_max_heap(arr, d); //first build a max heap
    pair<string, int> deleted_city = arr[0]; //the first element of max heap is the largest (max)
    arr.erase(arr.begin()); //first element is extracted

    max_heapify(arr, arr.size(), 0, d); //heapify the new root

    return deleted_city;
}

void dary_insert_element(vector<pair<string, int>> &arr, string first, int second, int d) {
    build_max_heap(arr, d); //first build a max heap
    pair <string, int> new_city = make_pair(first, second); //inserted element is created
    arr.push_back(new_city); //it is added to vector
    int i = arr.size() - 1;
    while (i > 0 && arr[(i - 1) / d].second < arr[i].second) { //heapify the arr after adding
        swap(arr[i], arr[(i - 1) / d]);
        i = (i - 1) / d;
    }
}

void dary_increase_key(vector<pair<string, int>>& arr, int index, int key, int d) {
    int size = arr.size();
    if (index >= size || index < 0) {
        cout << "Index out of the range, operation terminated." << endl;
        return;
    }

    if (key < arr[index].second) { //if the key is already larger
        cout << "Given key is smaller than current key, operation terminated." << endl;
        return;
    }

    build_max_heap(arr, d); //build a max heap first
    arr[index].second = key; //key change

    while (index > 0 && arr[(index - 1) / d].second < arr[index].second) { //after change operation, arr needs to heapify
        swap(arr[index], arr[(index - 1) / d]);
        index = (index - 1) / d;
    }
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
        file << arr[i].first << ";" << to_string(arr[i].second) << endl;
    }
    file << arr.back().first << ";" << to_string(arr.back().second); // For the last element, '\n' is undesirable.

    file.close();
}

void write_one_pair_to_csv(string file_name, pair<string, int> &pair) {
    ofstream file(file_name, ios::out); // opened in write mode
    if (!file.is_open()) {
        cout << file_name << " file error. Program terminated." << endl;
        exit(1);
    }
    file << pair.first << ";" << to_string(pair.second); // For the last element, '\n' is undesirable.

    file.close();
}

size_t find(const std::string& str, char character) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == character) {
            return i;
        }
    }
    return string::npos; //maximum possible value for the type size_t. It is used to indicating that character does not found
}

void swap(pair<string, int>&pair_1, std::pair<string, int>&pair_2) {
    pair<string, int> temp = pair_1;
    pair_1 = pair_2;
    pair_2 = temp;
}