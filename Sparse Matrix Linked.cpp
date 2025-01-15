#include <iostream>
#include <limits>
using namespace std;

// Node structure for the Linked List
class Node {
public:
    int row, col, value;
    Node* next;

    Node(int r, int c, int val) : row(r), col(c), value(val), next(nullptr) {}
};

// SparseMatrix class definition
class SparseMatrix {
private:
    Node* head; // Pointer to the head of the linked list

public:
    SparseMatrix() : head(nullptr) {}

    // Function to add a new element to the matrix
    void addElement(int row, int col, int value) {
        if (value == 0) {
            cout << "Zero values are not stored in the sparse matrix.\n";
            return;
        }
        Node* newNode = new Node(row, col, value);
        if (!head) {
            head = newNode; // Initialize head if list is empty
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next; // Traverse to the end of the list
            }
            temp->next = newNode; // Add the new node at the end
        }
    }

    // Function to print the matrix in its full form
    void printMatrix(int rows, int cols) {
        Node* temp = head;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (temp && temp->row == i && temp->col == j) {
                    cout << temp->value << " ";
                    temp = temp->next; // Move to the next node
                } else {
                    cout << "0 "; // Print zero for empty positions
                }
            }
            cout << endl;
        }
    }

    // Function to find the value at a given position in the matrix
    int getValue(int row, int col) {
        Node* temp = head;
        while (temp) {
            if (temp->row == row && temp->col == col) {
                return temp->value;
            }
            temp = temp->next; // Continue searching
        }
        return 0; // Return zero if no value is found
    }

    // Destructor to release allocated memory
    ~SparseMatrix() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    int rows, cols, numElements;

    // Input for matrix dimensions
    cout << "Enter the number of rows: ";
    while (!(cin >> rows) || rows <= 0) {
        cout << "Invalid input. Please enter a positive integer for rows: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter the number of columns: ";
    while (!(cin >> cols) || cols <= 0) {
        cout << "Invalid input. Please enter a positive integer for columns: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    SparseMatrix matrix;

    // Input for non-zero elements
    cout << "Enter the number of non-zero elements: ";
    while (!(cin >> numElements) || numElements < 0) {
        cout << "Invalid input. Please enter a non-negative integer for the number of elements: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter each non-zero element in the format (row column value):\n";
    for (int i = 0; i < numElements; i++) {
        int r, c, val;
        cout << "Element " << i + 1 << ": ";
        cin >> r >> c >> val;

        // Validate input indices
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            cout << "Invalid row or column index. Please enter valid indices within matrix dimensions.\n";
            i--; // Retry the input for the current element
            continue;
        }

        matrix.addElement(r, c, val);
    }

    // Display the sparse matrix
    cout << "\nThe Sparse Matrix is:\n";
    matrix.printMatrix(rows, cols);

    // Search functionality
    int searchRow, searchCol;
    cout << "\nEnter the row and column to search for an element: ";
    cin >> searchRow >> searchCol;

    if (searchRow >= 0 && searchRow < rows && searchCol >= 0 && searchCol < cols) {
        int value = matrix.getValue(searchRow, searchCol);
        cout << "Value at (" << searchRow << ", " << searchCol << "): " << value << endl;
    } else {
        cout << "Invalid indices for search. They must be within matrix dimensions.\n";
    }

    return 0;
}
