# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
	stack<T> values;
	stack<T> minimums;
public:
	StackExt() {};
	bool empty() const; 
	T& top();
	void pop();
	void push(const T& val);
	T& findMin();
};

//=============================================================================
// Exercise 3: StackExt class
//=============================================================================
//TODO
/**
     * Check if the stack is empty.
     *
     * @return True if the stack is empty, false otherwise.
*/
template <class T>
bool StackExt<T>::empty() const {
    return values.empty();
}

//TODO
/**
     * Get the element at the top of the stack.
     *
     * @return Reference to the element at the top of the stack.
*/
template <class T>
T& StackExt<T>::top() {
    return values.top();
}

//TODO
/**
     * Remove the element at the top of the stack.
*/
template <class T>
void StackExt<T>::pop() {
    if (!values.empty()) {
        if (values.top() == minimums.top()) {
            minimums.pop(); // Remove the corresponding minimum value
        }
        values.pop(); // Remove the top element
    }
}

//TODO
/**
     * Insert an element into the stack.
     *
     * @param val The value to be inserted.
*/
template <class T>
void StackExt<T>::push(const T& val) {
    values.push(val);
    if (minimums.empty() || val <= minimums.top()) {
        minimums.push(val); // Update minimums stack
    }
}

//TODO
/**
     * Get the value of the smallest element in the stack.
     *
     * @return Reference to the smallest element.
*/
template <class T>
T& StackExt<T>::findMin() {
    return minimums.top();
}
