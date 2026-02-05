#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* next;

    Node(int v) {
        value = v;
        next = NULL;
    }
};

class MyQueue {
    int arr[100];
    int start, end;

public:
    MyQueue() {
        start = end = -1;
    }

    bool empty() {
        return start == -1;
    }

    void push(int x) {
        if (end == 99) return;
        if (start == -1) start = 0;
        arr[++end] = x;
    }

    int pop() {
        int x = arr[start];
        if (start == end)
            start = end = -1;
        else
            start++;
        return x;
    }
};

class Graph {
    int totalUsers;
    Node** list;
    bool* visited;

public:
    Graph(int n) {
        totalUsers = n;
        list = new Node*[totalUsers];
        visited = new bool[totalUsers];

        for (int i = 0; i < totalUsers; i++) {
            list[i] = NULL;
            visited[i] = false;
        }
    }

    void addFriendship(int u, int v) {
        Node* temp1 = new Node(v);
        temp1->next = list[u];
        list[u] = temp1;

        Node* temp2 = new Node(u);
        temp2->next = list[v];
        list[v] = temp2;
    }

    void clearVisited() {
        for (int i = 0; i < totalUsers; i++)
            visited[i] = false;
    }

    void showBFSCommunities() {
        clearVisited();
        MyQueue q;

        cout << "\n--- Communities Detected Using BFS ---\n";

        int group = 1;

        for (int i = 0; i < totalUsers; i++) {
            if (visited[i] == false) {
                cout << "Community " << group++ << ": ";

                visited[i] = true;
                q.push(i);

                while (!q.empty()) {
                    int currentUser = q.pop();
                    cout << currentUser << " ";

                    Node* ptr = list[currentUser];

                    while (ptr != NULL) {
                        int friendUser = ptr->value;

                        if (visited[friendUser] == false) {
                            visited[friendUser] = true;
                            q.push(friendUser);
                        }

                        ptr = ptr->next;
                    }
                }
                cout << endl;
            }
        }
    }

    void dfsHelper(int user) {
        visited[user] = true;
        cout << user << " ";

        Node* ptr = list[user];

        while (ptr != NULL) {
            int friendUser = ptr->value;

            if (visited[friendUser] == false)
                dfsHelper(friendUser);

            ptr = ptr->next;
        }
    }

    void showDFSCommunities() {
        clearVisited();

        cout << "\n--- Communities Detected Using DFS ---\n";

        int group = 1;

        for (int i = 0; i < totalUsers; i++) {
            if (visited[i] == false) {
                cout << "Community " << group++ << ": ";
                dfsHelper(i);
                cout << endl;
            }
        }
    }
};

int main() {
    int users, edges;

    cout << "Enter total number of users: ";
    cin >> users;

    Graph g(users);

    cout << "Enter number of friendships: ";
    cin >> edges;

    cout << "Enter friendship pairs (u v):\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        g.addFriendship(u, v);
    }

    int choice;
    cout << "\nPress 1 for BFS Communities";
    cout << "\nPress 2 for DFS Communities\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1)
        g.showBFSCommunities();
    else if (choice == 2)
        g.showDFSCommunities();
    else
        cout << "Invalid option!\n";

    return 0;
}
