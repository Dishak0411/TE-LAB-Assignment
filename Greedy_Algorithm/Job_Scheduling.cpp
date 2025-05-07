#include <bits/stdc++.h>
using namespace std;

struct Job{
    char id;
    int deadline;
    int profit;
};

bool jobCampare(Job a, Job b){
    return a.profit > b.profit;
}

void jobScheduling(vector<Job> &jobs){
    sort(jobs.begin(), jobs.end(), jobCampare);

    int n = jobs.size();
    vector<bool> slots(n, false);
    vector<char>result(n);

    for(int i=0; i<n; i++){
        for(int j= min(n, jobs[i].deadline)-1; j>=0; j--){
            if(!slots[j]){
                slots[j] = true;
                result[j] = jobs[i].id;
                break;
            }
        }
    }

    cout << "Scheduled Jobs for Max Profit: ";
    for(int i=0; i<n; i++){
        if(slots[i]){
            cout << result[i] << " ";
        }
    }

}



int main(){
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;

    vector<Job> jobs(n);

    cout << "Enter job details (id, deadline, profit):\n";
    for(int i=0; i<n; i++){
        cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;
    }

    jobScheduling(jobs);
    

    return 0;
}
