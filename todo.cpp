#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Task {
    string name;
    string priority;
    bool completed;
};

vector<Task> tasks;

void loadTasks() {
    ifstream file("tasks.txt");
    string name, priority, status;

    while (getline(file, name)) {
        if (name.empty())
            continue;

        getline(file, priority);
        getline(file, status);

        tasks.push_back({name, priority, status == "1"});
    }

    file.close();
}

void saveTasks() {
    ofstream file("tasks.txt");

    for (auto &task : tasks) {
        file << task.name << endl;
        file << task.priority << endl;
        file << (task.completed ? "1" : "0") << endl;
    }

    file.close();
}

void addTask() {
    string name;
    string priority;

    cin.ignore();
cout<<"enter task keyword to search:";
    getline(cin, name);
cout << "Enter priority (High/Medium/Low): ";
cin >> priority;

if (priority != "High" && priority != "Medium" && priority != "Low") {
    cout << "Invalid priority.\n";
    return;
}

tasks.push_back({name, priority, false});
    
    saveTasks();

    cout << "Task added successfully.\n";
}

void viewTasks() {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    cout << "\n===== TASKS =====\n";

    for (int i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". "
             << tasks[i].name
             << " | Priority: " << tasks[i].priority
             << " | Status: "
             << (tasks[i].completed ? "Completed" : "Pending")
             << endl;
    }
}

void deleteTask() {
    int number;

    viewTasks();

    if (tasks.empty())
        return;

    cout << "Enter task number to delete: ";
    cin >> number;

    if (number < 1 || number > tasks.size()) {
        cout << "Invalid task number.\n";
        return;
    }

    tasks.erase(tasks.begin() + number - 1);
    saveTasks();

    cout << "Task deleted successfully.\n";
}

void markCompleted() {
    int number;

    viewTasks();

    if (tasks.empty())
        return;

    cout << "Enter task number to mark completed: ";
    cin >> number;

    if (number < 1 || number > tasks.size()) {
        cout << "Invalid task number.\n";
        return;
    }

    tasks[number - 1].completed = true;
    saveTasks();

    cout << "Task marked as completed.\n";
}

void searchTasks() {
    string keyword;
    bool found = false;

    cin.ignore();
    cout << "Enter keyword: ";
    getline(cin, keyword);

    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].name.find(keyword) != string::npos) {
            cout << i + 1 << ". "
                 << tasks[i].name
                 << " | Priority: " << tasks[i].priority

                 << " | Status: "
                 << (tasks[i].completed ? "Completed" : "Pending")

                 << endl;


            found = true;
        }
    }


    if (!found)
        cout << "No matching tasks found.\n";
}


void showHighPriorityTasks() {
    bool found = false;

    cout << "\n===== HIGH PRIORITY TASKS =====\n";


    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].priority == "High") {

            cout << i + 1 << ". "
                 << tasks[i].name
                 << " | Status: "
                 << (tasks[i].completed ? "Completed" : "Pending")

                 << endl;


            found = true;

        }
    }

    if (!found)
        cout << "No high priority tasks found.\n";

}

int main() {
    loadTasks();

    int choice;

    while (true) {


cout << "\n===== TO-DO LIST MANAGER =====\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Delete Task\n";
        cout << "4. Mark Completed\n";
        cout << "5. Search Tasks\n";
        cout << "6. Show High Priority Tasks\n";
        cout << "7. Exit\n";
cout << "8. Save and Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                addTask();
                break;

            case 2:
                viewTasks();
                break;

            case 3:
                deleteTask();
                break;

            case 4:
                markCompleted();
                break;

            case 5:
                searchTasks();
                break;

            case 6:
                showHighPriorityTasks();
                break;

            case 7:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice.\n";
        }
    }
}
