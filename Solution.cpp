#include <bits/stdc++.h>
using namespace std;

class PageView {
public:
    string timestamp;
    string pageId;
    string customerId;

    PageView(const string& ts, const string& pid, const string& cid)
        : timestamp(ts), pageId(pid), customerId(cid) {}

    static PageView fromLogEntry(const string& logEntry) {
        istringstream iss(logEntry);
        string ts, pid, cid;
        getline(iss, ts, ',');
        getline(iss, pid, ',');
        getline(iss, cid, ',');
        return PageView(ts, pid, cid);
    }

    string toString() const {
        return timestamp + "," + pageId + "," + customerId;
    }
};

void createSampleLogFile(const string& filename, const vector<PageView>& pageViews) {
    ofstream file(filename);
    for (const auto& pageView : pageViews) {
        file << pageView.toString() << endl;
    }
}

map<string, set<string>> readDataFromFile(const string& filename) {
    map<string, set<string>> data;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        PageView pageView = PageView::fromLogEntry(line);
        data[pageView.customerId].insert(pageView.pageId);
    }

    return data;
}

int main() {
    // Create sample data for day1 and day2 logs
    createSampleLogFile("day1.log", {
        PageView("2024-08-18T10:00:00", "PageA", "Customer1"),
        PageView("2024-08-18T10:05:00", "PageB", "Customer1"),
        PageView("2024-08-18T10:10:00", "PageA", "Customer2"),
        PageView("2024-08-18T10:15:00", "PageC", "Customer3")
    });

    createSampleLogFile("day2.log", {
        PageView("2024-08-19T10:00:00", "PageB", "Customer1"),
        PageView("2024-08-19T10:05:00", "PageA", "Customer1"),
        PageView("2024-08-19T10:10:00", "PageA", "Customer3"),
        PageView("2024-08-19T10:15:00", "PageB", "Customer3"),
        PageView("2024-08-19T10:20:00", "PageD", "Customer4")
    });

    map<string, set<string>> dataFromDay1 = readDataFromFile("day1.log");
    set<string> loyalCustomersToReturn;

    ifstream file2("day2.log");
    string line;
    while (getline(file2, line)) {
        PageView pageViewFromDay2 = PageView::fromLogEntry(line);
        string customerId = pageViewFromDay2.customerId;

        if (dataFromDay1.find(customerId) != dataFromDay1.end()) {

            set<string>& pagesFromDay1 = dataFromDay1[customerId];
            string pageFromDay2 = pageViewFromDay2.pageId;

            if (pagesFromDay1.size() >= 2 || pagesFromDay1.find(pageFromDay2) == pagesFromDay1.end()) {
                loyalCustomersToReturn.insert(customerId);
                
                dataFromDay1.erase(customerId);
            }
        }
    }

    // Output loyal customers
    cout << "Loyal Customers: ";
    for (const auto& customer : loyalCustomersToReturn) {
        cout << customer << " ";
    }
    cout << endl;

    return 0;
}