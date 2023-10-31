#ifndef _TSTACK_H
#define _TSTACK_H

template <typename T>
class TStack {
private:
	int maxSize;
	int top;
	T* elems;
public:
	TStack(int _maxSize = 10);
	TStack(const TStack<T>& s);
	~TStack();
	void Pop();
	T Top() const;
	void Push(const T& e);
	bool IsEmpty(void) const;
	bool IsFull(void) const ;
};

template <typename T>
TStack<T>::TStack(int _maxSize) {
	if (_maxSize <= 0) throw "maxSize must be bigger than 0.";
	maxSize = _maxSize;
	top = -1;
	elems = new T[maxSize];
}

template <typename T>
TStack<T>::TStack(const TStack<T>& s) {
	maxSize = s.maxSize;
	top = s.top;
	elems = new T[maxSize];
	for (int i = 0; i <= top; i++)
		elems[i] = s.elems[i];
}

template <typename T>
TStack<T>::~TStack() {
	delete[] elems;
}

template <typename T>
bool TStack<T>::IsFull(void) const  {
	return (top == maxSize - 1);
}

template <typename T>
bool TStack<T>::IsEmpty(void) const  {
	return (top == -1);
}

template <typename T>
T TStack<T>::Top() const {
	if (IsEmpty()) throw "Stack is empty.";
	return elems[top];
}

template <typename T>
void TStack<T>::Push(const T& e) {
	if (IsFull()) throw "Stack is full.";
	elems[++top] = e;
}

template <typename T>
void TStack<T>::Pop() {
	if (IsEmpty()) throw "Stack is empty.";
	top--;
}

#endif 