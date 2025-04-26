#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct NODE
{
    int key;
    NODE *p_next;
    NODE(int data) : key(data), p_next(nullptr) {}
};

struct Queue
{
    NODE *head;
    NODE *tail;
    int size;
    Queue() : head(nullptr), tail(nullptr), size(0) {}
};

bool isEmpty(const Queue &q)
{
    return q.head == nullptr;
}

Queue *initializeQueue()
{
    return new Queue();
}

int dequeue(Queue *&q)
{
    if (isEmpty(*q))
    {
        return -1;
    }
    NODE *temp = q->head;
    int popped_key = temp->key;
    q->head = q->head->p_next;
    if (q->head == nullptr)
    {
        q->tail = nullptr;
    }
    delete temp;
    q->size--;
    return popped_key;
}

void enqueue(Queue *&q, int key)
{
    NODE *new_node = new NODE(key);
    if (q->tail != nullptr)
    {
        q->tail->p_next = new_node;
    }
    else
    {
        q->head = new_node;
    }
    q->tail = new_node;
    q->size++;
}

int size(const Queue &q)
{
    return q.size;
}

void cleanupQueue(Queue *&q)
{
    if (q == nullptr)
    {
        return;
    }
    while (!isEmpty(*q))
    {
        dequeue(q);
    }
    delete q;
    q = nullptr;
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");

    if (!input_file.is_open())
    {
        cout << "Cant open file.";
        return -1;
    }
    if (!output_file.is_open())
    {
        cout << "Cant open file.";
        return -1;
    }

    string line;
    Queue *queue = nullptr;
    string currentState = "";
    while (getline(input_file, line))
    {
        stringstream ss(line);
        string line_process;
        ss >> line_process;
        if (line_process == "init")
        {
            if (queue)
                cleanupQueue(queue);
            queue = initializeQueue();
            currentState = "";
            output_file << "EMPTY" << endl;
        }
        else if (line_process == "enqueue")
        {
            int val;
            ss >> val;
            enqueue(queue, val);
            currentState = to_string(val) + (currentState.empty() ? "" : " " + currentState);
            output_file << currentState << endl;
        }
        else if (line_process == "dequeue")
        {
            if (!isEmpty(*queue))
            {
                dequeue(queue);
                size_t pos = currentState.find(' ');
                if (pos != string::npos)
                {
                    currentState = currentState.substr(pos + 1);
                }
                else
                {
                    currentState = "";
                }
            }
            output_file << (currentState.empty() ? "EMPTY" : currentState) << endl;
        }
    }

    cleanupQueue(queue);
    input_file.close();
    output_file.close();

    return 0;
}
