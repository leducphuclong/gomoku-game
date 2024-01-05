#include <bits/stdc++.h>

//g++ loadleaders.cpp -o loadleaders && ./loadleaders     

using namespace std;

#define nln '\n'

struct leader {
    string id, username, result, date;
    double time;
};

struct CompareLeader {
    // Comparison function for the priority queue
    bool operator()(const leader& lhs, const leader& rhs) const {
        if (lhs.result == "WIN" && rhs.result == "WIN") {
            // If both results are "WIN", prioritize lower time
            return lhs.time > rhs.time;
        } else if (lhs.result == "WIN" && rhs.result == "LOSE") {
            // If lhs is "WIN" and rhs is "LOSE", lhs is better
            return false;
        } else if (lhs.result == "LOSE" && rhs.result == "WIN") {
            // If lhs is "LOSE" and rhs is "WIN", rhs is better
            return true;
        } else {
            // If both results are "LOSE", prioritize higher time
            return lhs.time < rhs.time;
        }
    }
};


int main() {
    ifstream inFile("./x/Match.txt");
    vector<leader> leaders;
    leader tmp;
    while (getline(inFile, tmp.id)) {
        getline(inFile, tmp.username);
        getline(inFile, tmp.result);
        getline(inFile, tmp.date);
        inFile >> tmp.time;
        inFile.ignore();
        leaders.push_back(tmp);
    }
    inFile.close();

    ofstream outFile("leaders.txt");
    priority_queue<leader, vector<leader>, CompareLeader> pq;
    map<string, bool> exist;
    for (auto v : leaders)
        if (!exist[v.username] && pq.size() < 10) {
            pq.push(v);
            exist[v.username] = true;
        }
    while (!pq.empty()) {
        auto ld = pq.top();
        outFile << ld.username << nln << ld.result << nln << ld.date;
        outFile << nln  << ld.time << nln;
        pq.pop();
    }
        
    outFile.close();

    return 0;
}

