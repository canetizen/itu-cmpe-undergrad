/**
 * BLG 336E - Analysis of Algorithms II
 * Assignment 1
 * Mustafa Can Caliskan
 * 150200097
*/
* * * * * * * * * * * * * */

#include <iostream>         
#include <vector>
#include <fstream>
#include <sstream>       
#include <stack>
#include <queue>
#include <chrono>       // For time measurement

#include <limits.h> // For INT_MIN


using namespace std;
using namespace std::chrono;

/**
 * Inserts given new pair into destination vector in sorted manner.
 * 
 * @param vec The map represented as a 2D vector of integers.
 * @param new_pair The pair that is added into map.
 */
void insert_sorted(vector<pair<int, int>> &vec, const pair<int, int> &new_pair) {
    if (vec.empty()) {
        vec.push_back(new_pair);
        return;
    }

    for (auto iter = vec.begin(); iter != vec.end(); iter++) {
        if ((new_pair.first > iter->first) || (new_pair.first == iter->first && new_pair.second < iter->second)) {
            vec.insert(iter, new_pair);
            return;
        }
    }
    vec.push_back(new_pair);
}

/**
 * Perform Depth-First Search (DFS) traversal on a map.
 * 
 * @param map The map represented as a 2D vector of integers.
 * @param row The starting row index for the DFS traversal.
 * @param col The starting column index for the DFS traversal.
 * @param resource The resource value to search for during the traversal.
 * @return The size of the colony found during the DFS traversal.
 */
int dfs(vector<vector<int>>& map, int row, int col, int resource) {
    int total_count = 0;
    int row_size = map.size();
    int col_size = map[0].size();

// Since the map is circular, in order to constrain the row and column within the boundaries, a modulo operation is applied.
    int limit_row = (row + row_size) % row_size; 
    int limit_col = (col + col_size) % col_size;

// Base condition.
    if (map[limit_row][limit_col] != resource) {
        return 0;
    }

    map[limit_row][limit_col] = INT_MIN; // Assigned to indicate prior visitation.

    total_count += 1 + dfs(map, limit_row + 1, limit_col, resource) 
                + dfs(map, limit_row - 1, limit_col, resource) 
                + dfs(map, limit_row, limit_col + 1, resource)
                + dfs(map, limit_row, limit_col - 1, resource);

    return total_count;
}


/**
 * Perform Breadth-First Search (BFS) traversal on a map.
 * 
 * @param map The map represented as a 2D vector of integers.
 * @param row The starting row index for the BFS traversal.
 * @param col The starting column index for the BFS traversal.
 * @param resource The resource value to search for during the traversal.
 * @return The size of the colony found during the BFS traversal.
 */
int bfs(vector<vector<int>>& map, int row, int col, int resource) {
    queue<pair<int, int>> bfs_queue;

    int total_count = 0;
    int row_size = map.size();
    int col_size = map[0].size();

    bfs_queue.push(make_pair(row, col));

    map[row][col] = INT_MIN; // Assigned to indicate prior visitation.

    int neighbor_directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    while (!bfs_queue.empty()) {
        int row = bfs_queue.front().first;
        int col = bfs_queue.front().second;

        bfs_queue.pop();
        total_count++;

        for (int i = 0; i < 4; i++) {
            int neighbor_row = neighbor_directions[i][0];
            int neighbor_col = neighbor_directions[i][1];

            int limit_row = (neighbor_row + row + row_size) % row_size;
            int limit_col = (neighbor_col + col + col_size) % col_size;

            if (map[limit_row][limit_col] == resource) {
                map[limit_row][limit_col] = INT_MIN;
                bfs_queue.push(make_pair(limit_row, limit_col));
            }
        }
    }
    return total_count;
}

/**
 * Finds the top-k largest colonies in a given map.
 *
 * @param map The map represented as a 2D vector of integers.
 * @param useDFS A boolean flag indicating whether to use Depth-First Search (DFS) or Breadth-First Search (BFS) algorithm.
 * @param k The number of top colonies to find.
 * @return A vector of pairs representing the size and resource type of the top-k largest colonies.
 */
vector<pair<int, int>> top_k_largest_colonies(vector<vector<int>>& map, bool useDFS, unsigned int k) {

    auto start = high_resolution_clock::now();      // Start measuring time

    int region = 0;
    vector<pair<int, int>> result_vector;
    
    for (unsigned int i = 0; i < map.size(); i++) {
        for (unsigned int j = 0; j < map[0].size(); j++) {
            int resource = map[i][j];
            if (resource != INT_MIN) {
                if (useDFS) {
                    region = dfs(map, i, j, resource);
                } else {
                    region = bfs(map, i, j, resource);
                }
                insert_sorted(result_vector, make_pair(region, resource));
            }
        }
    }

    auto stop = high_resolution_clock::now();                       // Stop measuring time
    auto duration = duration_cast<nanoseconds>(stop - start);       // Calculate the duration
    cout << "Time taken: " << duration.count() << " nanoseconds" << endl;

    // To retain the first k elements of the result vector.
    if (k < result_vector.size()) {
        result_vector.resize(k);
    }

    return result_vector;
}

// Main function
int main(int argc, char* argv[]) {

    // Check the command line arguments
    if (argc != 4) {

        // It should be: <1 or 0> <k> <filename.txt>
        cerr << "Usage: " << argv[0] << " <1 or 0> <k> <filename.txt>" << endl;
        return 1;
    }

    // Get the arguments
    bool useDFS = (atoi(argv[1]) == 1);
    int k = atoi(argv[2]);

    // Read the map from the text file
    string filename = argv[3];
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    vector<vector<int>> sector_map;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        vector<int> row;
        int num;
        while (iss >> num) {
            row.push_back(num);
        }
        sector_map.push_back(row);
    }
    file.close();   

    // Find the largest colony
    vector<pair<int, int>> result = top_k_largest_colonies(sector_map, useDFS, k);

    // Print the result
    cout << "Algorithm: " << (useDFS ? "DFS" : "BFS") << endl;
    cout << "Map: " << filename << endl;

    // If no colonies are found
    if (result.empty()) {
        cout << "No colonies found." << endl;
        return 0;
    }

    // Print the top-k colonies
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "Colony " << i + 1 << ": Size = " << result[i].first << ", Resource Type = " << result[i].second << endl;
    }

    return 0;
}