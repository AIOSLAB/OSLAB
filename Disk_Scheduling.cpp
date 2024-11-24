#include<bits/stdc++.h> // Includes all standard libraries in C++, such as iostream, vector, algorithm, etc.
using namespace std;    // Allows usage of standard library objects without explicitly prefixing "std::".

#define MAX 100         // Defines a constant MAX with value 100 for array size constraints.

// Function to implement Shortest Seek Time First (SSTF) disk scheduling algorithm.
void sstf(int request[], int n, int head){

    cout<<"SSTF: ";    // Print the algorithm's name for clarity in output.
    bool processed[MAX] = {false}; // Array to track which requests have been processed.
    int current_head = head;       // Initialize the current head position.

    // Loop to process all requests one by one.
    for(int j=0; j<n; j++){
        int min_dist = INT_MAX;   // Initialize the minimum distance to a large value.
        int next_index = -1;      // Variable to store the index of the closest request.

        // Find the closest unprocessed request.
        for(int i=0; i<n; i++){
            if(!processed[i]){   // Check if the request has not been processed.
                int dist = abs(current_head - request[i]); // Calculate distance from the current head.
                if(dist < min_dist){  // Update minimum distance and next index if closer request is found.
                    min_dist = dist;
                    next_index = i;
                }
            }
        }

        if(next_index == -1){    // Break if no valid requests are left.
            break;
        }

        processed[next_index] = true;  // Mark the request as processed.
        current_head = request[next_index]; // Move head to the processed request.
        cout << current_head << " ";  // Output the processed request.
    }
    cout << endl;   // Print a newline after processing all requests.
}

// Function to implement SCAN disk scheduling algorithm.
void scan(int request[], int n, int head, int disk_size){
    cout << "SCAN: ";    // Print the algorithm's name for clarity in output.
    vector<int> request_sorted(n+1); // Create a vector to include all requests and the head position.
    request_sorted[0] = head;  // Include the head position in the list.

    for(int i=0; i<n; i++){    // Copy the requests to the vector.
        request_sorted[i+1] = request[i];
    }

    n++;   // Increment the total number of requests to account for the head position.
    sort(request_sorted.begin(), request_sorted.end()); // Sort all requests including the head position.

    int posi_head = -1;   // Variable to store the index of the head position in the sorted list.
    for(int i=0; i<n; i++){ // Find the index of the head position.
        if(request_sorted[i] == head){
            posi_head = i;
            break;
        }
    }

    // Move rightwards from the head position to the end of the disk.
    for(int i=posi_head; i<n; i++){
        cout << request_sorted[i] << " ";
    }
    cout << disk_size - 1 << " "; // Include the end of the disk.

    // Move leftwards from the head position to the start of the disk.
    for(int i=posi_head-1; i>=0; i--){
        cout << request_sorted[i] << " ";
    }
    cout << endl;   // Print a newline after processing all requests.
}

// Function to implement C-LOOK disk scheduling algorithm.
void clook(int request[], int n, int head){
    vector<int> request_sorted(n); // Create a vector to store sorted requests.
    for(int i=0; i<n; i++){        // Copy the requests into the vector.
        request_sorted[i] = request[i];
    }
    sort(request_sorted.begin(), request_sorted.end()); // Sort the requests.

    int posi_head = -1;   // Variable to find the index of the first request greater than the head.
    for(int i=0; i<n; i++){
        if(request_sorted[i] >= head){ // Find the position where head fits.
            posi_head = i;
            break;
        }
    }

    cout << "C-LOOK: ";   // Print the algorithm's name for clarity in output.

    // Process requests from the head to the end of the disk.
    for(int i=posi_head; i<n; i++){
        cout << request_sorted[i] << " ";
    }
    // Process requests from the start to just before the head's position.
    for(int i=posi_head-1; i>=0; i--){
        cout << request_sorted[i] << " ";
    }
    cout << endl;   // Print a newline after processing all requests.
}

// Main function: Entry point of the program.
int main(){
    int n, disk_size, head;   // Variables for the number of requests, disk size, and head position.
    cout << "Enter number of requests: ";  // Prompt for the number of requests.
    cin >> n;   // Read the number of requests.
    cout << "\nEnter disk size: ";         // Prompt for disk size.
    cin >> disk_size;   // Read the disk size.
    cout << "\n Enter initial head position: "; // Prompt for initial head position.
    cin >> head;   // Read the head position.

    int request[MAX];  // Array to store the disk requests.

    cout << "Enter " << n << " requests: (Space separated): " << endl; // Prompt to enter the requests.
    for(int i=0; i<n; i++){   // Read all requests into the array.
        cin >> request[i];
    }

    sstf(request, n, head);       // Call SSTF algorithm.
    scan(request, n, head, disk_size); // Call SCAN algorithm.
    clook(request, n, head);      // Call C-LOOK algorithm.

    return 0;   // Exit the program successfully.
}

/*
Sample Input/Output:
Enter number of requests: 8
Enter disk size: 200
Enter initial head position: 50
Enter 8 requests: (Space separated):
98 183 41 122 14 124 65 67
*/
