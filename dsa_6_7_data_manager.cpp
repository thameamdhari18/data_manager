#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <unordered_map>

using namespace std;

struct Record {
    int id;
    string data;
};

class DataStructureManager {
private:
    vector<Record> array;
    list<Record> linkedList;
    stack<Record> recordStack;
    queue<Record> recordQueue;
    unordered_map<int, Record> hashTable;

public:
    void insert_record(const Record& record) {
        array.push_back(record);
        linkedList.push_back(record);
        recordStack.push(record);
        recordQueue.push(record);
        hashTable[record.id] = record;
    }

    void delete_record(int record_id) {
        for (auto it = array.begin(); it != array.end(); ++it) {
            if (it->id == record_id) {
                array.erase(it);
                break;
            }
        }

        auto it = linkedList.begin();
        while (it != linkedList.end()) {
            if (it->id == record_id) {
                it = linkedList.erase(it);
            } else {
                ++it;
            }
        }

        stack<Record> tempStack;
        while (!recordStack.empty()) {
            if (recordStack.top().id != record_id) {
                tempStack.push(recordStack.top());
            }
            recordStack.pop();
        }
        while (!tempStack.empty()) {
            recordStack.push(tempStack.top());
            tempStack.pop();
        }

        queue<Record> tempQueue;
        while (!recordQueue.empty()) {
            if (recordQueue.front().id != record_id) {
                tempQueue.push(recordQueue.front());
            }
            recordQueue.pop();
        }
        recordQueue = tempQueue;

        hashTable.erase(record_id);
    }

    bool search_record(int record_id) {
        for (const auto& record : array) {
            if (record.id == record_id) return true;
        }

        for (const auto& record : linkedList) {
            if (record.id == record_id) return true;
        }

        stack<Record> tempStack = recordStack;
        while (!tempStack.empty()) {
            if (tempStack.top().id == record_id) return true;
            tempStack.pop();
        }

        queue<Record> tempQueue = recordQueue;
        while (!tempQueue.empty()) {
            if (tempQueue.front().id == record_id) return true;
            tempQueue.pop();
        }

        return hashTable.count(record_id) > 0;
    }

    Record retrieve_latest_record() {
        if (!recordStack.empty()) {
            return recordStack.top();
        } else {
            throw runtime_error("No records available");
        }
    }

    Record retrieve_oldest_record() {
        if (!recordQueue.empty()) {
            return recordQueue.front();
        } else {
            throw runtime_error("No records available");
        }
    }

    Record retrieve_record_by_key(int record_id) {
        auto it = hashTable.find(record_id);
        if (it != hashTable.end()) {
            return it->second;
        } else {
            throw runtime_error("Record not found");
        }
    }

    void display_records() {
        cout << "Records in array:\n";
        for (const auto& record : array) {
            cout << "ID=" << record.id << ", Data=" << record.data << endl;
        }

        cout << "\nRecords in linked list:\n";
        for (const auto& record : linkedList) {
            cout << "ID=" << record.id << ", Data=" << record.data << endl;
        }

        cout << "\nRecords in stack (top to bottom):\n";
        stack<Record> tempStack = recordStack;
        while (!tempStack.empty()) {
            cout << "ID=" << tempStack.top().id << ", Data=" << tempStack.top().data << endl;
            tempStack.pop();
        }

        cout << "\nRecords in queue (front to back):\n";
        queue<Record> tempQueue = recordQueue;
        while (!tempQueue.empty()) {
            cout << "ID=" << tempQueue.front().id << ", Data=" << tempQueue.front().data << endl;
            tempQueue.pop();
        }

        cout << "\nRecords in hash table:\n";
        for (const auto& [id, record] : hashTable) {
            cout << "ID=" << record.id << ", Data=" << record.data << endl;
        }
    }
};

int main() {
    DataStructureManager manager;
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Insert Record\n";
        cout << "2. Delete Record\n";
        cout << "3. Search Record\n";
        cout << "4. Retrieve Latest Record\n";
        cout << "5. Retrieve Oldest Record\n";
        cout << "6. Retrieve Record by Key\n";
        cout << "7. Display All Records\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        try {
            switch (choice) {
            case 1: {
                int id;
                string data;
                cout << "Enter record ID: ";
                cin >> id;
                cin.ignore(); 
                cout << "Enter record data: ";
                getline(cin, data);
                manager.insert_record({id, data});
                cout << "Record inserted.\n";
                break;
            }
            case 2: {
                int id;
                cout << "Enter record ID to delete: ";
                cin >> id;
                manager.delete_record(id);
                cout << "Record deleted.\n";
                break;
            }
            case 3: {
                int id;
                cout << "Enter record ID to search: ";
                cin >> id;
                bool found = manager.search_record(id);
                cout << "Record " << (found ? "found." : "not found.") << endl;
                break;
            }
            case 4: {
                Record record = manager.retrieve_latest_record();
                cout << "Latest record: ID=" << record.id << ", Data=" << record.data << endl;
                break;
            }
            case 5: {
                Record record = manager.retrieve_oldest_record();
                cout << "Oldest record: ID=" << record.id << ", Data=" << record.data << endl;
                break;
            }
            case 6: {
                int id;
                cout << "Enter record ID to retrieve: ";
                cin >> id;
                Record record = manager.retrieve_record_by_key(id);
                cout << "Record: ID=" << record.id << ", Data=" << record.data << endl;
                break;
            }
            case 7: {
                manager.display_records();
                break;
            }
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    } while (choice != 8);

    return 0;
}