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

struct Stack
{
    NODE *top;
    int size;
    Stack() : top(nullptr), size(0) {}
};

bool isEmpty(const Stack &s)
{
    return s.top == nullptr;
}

Stack *initializeStack()
{
    return new Stack();
}

int pop(Stack *&s)
{
    if (isEmpty(*s))
        return -1;
    NODE *temp = s->top;
    int popped_key = temp->key;
    s->top = s->top->p_next;
    delete temp;
    s->size--;
    return popped_key;
}

void push(Stack *&s, int key)
{
    NODE *new_node = new NODE(key);
    new_node->p_next = s->top;
    s->top = new_node;
    s->size++;
}

int size(const Stack *s)
{
    return s->size;
}
void cleanupStack(Stack *&s)
{
    if (s)
    {
        while (!isEmpty(*s))
        {
            pop(s);
        }
        delete s;
        s = nullptr;
    }
}

int main()
{
    ifstream input_file("input.txt");
    ofstream output_file("output.txt");
    if (!input_file.is_open())
    {
        cout << "Can't open input file.\n";
        return -1;
    }
    if (!output_file.is_open())
    {
        cout << "Can't open output file.\n";
        return -1;
    }

    string line;
    Stack *stack = nullptr;
    string currentState = "";

    while (getline(input_file, line))
    {
        stringstream ss(line);
        string line_process;
        ss >> line_process;

        if (line_process == "init")
        {
            if (stack)
                cleanupStack(stack);
            stack = initializeStack();
            currentState = "";
            output_file << "EMPTY" << endl;
        }
        else if (line_process == "push")
        {
            int val;
            ss >> val;
            push(stack, val);
            currentState = (currentState.empty() ? "" : currentState + " ") + to_string(val);
            output_file << currentState << endl;
        }
        else if (line_process == "pop")
        {
            if (!isEmpty(*stack))
            {
                pop(stack);
                size_t pos = currentState.rfind(' ');
                if (pos != string::npos)
                    currentState = currentState.substr(0, pos);
                else
                    currentState = "";
            }

            output_file << (currentState.empty() ? "EMPTY" : currentState) << endl;
        }
    }

    cleanupStack(stack);
    input_file.close();
    output_file.close();

    return 0;
}
