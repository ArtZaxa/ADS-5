// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int InitialSize>
class TStack {
private:
    T* arr;
    int capacity;
    int topIndex;

    void resize(int newCapacity) {
        if (newCapacity <= capacity) {
            return;
        }

        T* temp = new T[newCapacity];
        for (int i = 0; i <= topIndex; ++i) {
            temp[i] = arr[i];
        }

        delete[] arr;
        arr = temp;
        capacity = newCapacity;
    }

public:
    TStack()
        : capacity(InitialSize > 0 ? InitialSize : 1),
          topIndex(-1) {
        arr = new T[capacity];
    }

    TStack(const TStack& other)
        : capacity(other.capacity),
          topIndex(other.topIndex) {
        arr = new T[capacity];
        for (int i = 0; i <= topIndex; ++i) {
            arr[i] = other.arr[i];
        }
    }

    TStack& operator=(const TStack& other) {
        if (this != &other) {
            T* temp = new T[other.capacity];
            for (int i = 0; i <= other.topIndex; ++i) {
                temp[i] = other.arr[i];
            }

            delete[] arr;
            arr = temp;
            capacity = other.capacity;
            topIndex = other.topIndex;
        }
        return *this;
    }

    ~TStack() {
        delete[] arr;
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == capacity - 1;
    }

    T get() const {
        if (isEmpty()) {
            return T();
        }
        return arr[topIndex];
    }

    void pop() {
        if (!isEmpty()) {
            --topIndex;
        }
    }

    void push(const T& item) {
        if (isFull()) {
            resize(capacity * 2);
        }
        arr[++topIndex] = item;
    }
};

#endif  // INCLUDE_TSTACK_H_
