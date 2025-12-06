#include <bits/stdc++.h>
using namespace std;

void loadBalancing(vector<int> jobs, int m) {
    //  descending order of jobs 
    sort(jobs.rbegin(), jobs.rend());

    // Priority queue to store (current_load, machine_id) - min heap
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    // Initialise with 0 load
    for (int i = 1; i <= m; i++) {
        pq.push({0, i});
    }

    // Store jobs assigned to each machine
    vector<vector<int>> assignment(m+1);

    // Assign jobs
    for (int job : jobs) {
        auto [load, machine] = pq.top();
        pq.pop();

        // Assign job to machine
        assignment[machine].push_back(job);

        // Update machine load
        load += job;
        pq.push({load, machine});
    }

    // Print results
    int maxLoad = 0;
    cout << "Job Assignment to Machines:\n";
    for (int i = 1; i <= m; i++) {
        int total = 0;
        cout << "M" << i << " -> { ";
        for (int job : assignment[i]) {
            cout << job << " ";
            total += job;
        }
        cout << "}  Load = " << total << "\n";
        maxLoad = max(maxLoad, total);
    }

    cout << "Maximum Load (Makespan) = " << maxLoad << "\n";
}

int main() {
    vector<int> jobs = {6, 4, 3, 2, 2, 2};
    int m = 3; // number of machines

    loadBalancing(jobs, m);
    return 0;
}
