# include <iostream>
# include <stack>

using namespace std;

template<class T>
class StackExt {
private:
	stack<T> mainStack;
	stack<T> minStack;
public:
	StackExt() {
	}
	;
	bool empty() const;
	T& top();
	void pop();
	void push(const T& val);
	T& findMin();
};

template<class T>
bool StackExt<T>::empty() const {
	return mainStack.empty();
}

template<class T>
T& StackExt<T>::top() {
	return mainStack.top();
}

template<class T>
void StackExt<T>::pop() {
	if (mainStack.top() == minStack.top())
		minStack.pop();

	mainStack.pop();
}

template<class T>
void StackExt<T>::push(const T& val) {
	mainStack.push(val);

	if (minStack.empty() || val == minStack.top() || val < minStack.top())
		minStack.push(val);
}

template<class T>
T& StackExt<T>::findMin() {

	return minStack.top();
}
