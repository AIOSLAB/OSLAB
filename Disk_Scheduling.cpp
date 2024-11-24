#include<bits/stdc++.h>
using namespace std;

#define MAX 100

void sstf(int request[], int n, int head){

    cout<<"SSTF: ";
    bool processed[MAX] = {false};
    int current_head = head;

    for(int j=0; j<n; j++){
        int min_dist = INT_MAX;
        int next_index = -1;
        for(int i=0; i<n; i++){
            if(!processed[i]){
                int dist = abs(current_head-request[i]);
                if(dist < min_dist){
                    min_dist = dist;
                    next_index = i;
                }
            }
        }

        if(next_index == -1){
            break;
        }

        processed[next_index] = true;
        current_head = request[next_index];
        cout << current_head<<" ";
    }
    cout<<endl;
}

void scan(int request[], int n, int head, int disk_size){
    cout<<"SCAN: ";
    vector<int> request_sorted(n+1); //to include head
    request_sorted[0] = head;

    for(int i=0; i<n; i++){
        request_sorted[i+1] = request[i];
    }

    n++;
    sort(request_sorted.begin(), request_sorted.end());
    
    int posi_head=-1;
    for(int i=0; i<n; i++){
        if(request_sorted[i] == head){
            posi_head = i;
            break;
        }
    }

    for(int i=posi_head; i<n; i++){
        cout<<request_sorted[i]<<" ";
    }
    cout<<disk_size-1<<" ";
    for(int i=posi_head-1; i>=0; i--){
        cout<<request_sorted[i]<<" ";
    }
    cout<<endl;
}

void clook(int request[], int n, int head){
    vector<int> request_sorted(n);
    for(int i=0; i<n; i++){
        request_sorted[i] = request[i];
    }
    sort(request_sorted.begin(), request_sorted.end());

    int posi_head = -1;
    for(int i=0; i<n; i++){ //to find first req greater than head
        if(request_sorted[i] >= head){
            posi_head = i;
            break;
        }
    }

    cout<<"C-LOOK: ";
    for(int i=posi_head; i<n; i++){
        cout<<request_sorted[i]<<" ";
    }
    for(int i=posi_head-1; i>=0; i--){
        cout<<request_sorted[i]<<" ";
    }
    cout<<endl;
}

int main(){
    int n,disk_size,head;
    cout<<"Enter number of requests: ";
    cin >> n;
    cout<<"\nEnter disk size: ";
    cin >> disk_size;
    cout<<"\n Enter initial head position: ";
    cin >> head;

    int request[MAX];

    cout<<"Enter "<<n<<" requests: (Space separated): "<<endl;
    for(int i=0; i<n; i++){
        cin>>request[i];
    }

    sstf(request,n,head);
    scan(request,n,head,disk_size);
    clook(request,n,head);

    return 0;
}

/*
Enter number of requests: 8
Enter disk size: 200
Enter initial head position: 50
Enter 8 requests: (Space separated):
98 183 41 122 14 124 65 67
*/