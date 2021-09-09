#ifndef ARRAY_H__
#define ARRAY_H__

template <typename T>
class Array {
   public:
    int number;
    T* array;
    int length;

   public:
    Array(int l = 1);
    ~Array();
    int push(T x);
    int remove(T x);
    int search(T x);
    bool empty() { return number <= 0; }
    T pop() { return array[--number]; }
    T top() const { return array[number - 1]; }

    Array<T>& operator=(const Array<T>& a);
    T operator[](int i) const { return array[i]; }
    bool operator==(const Array<T>& a) { return *array == *a.array; }
    bool operator!=(const Array<T>& a) { return *array != *a.array; }
    bool operator>(const Array<T>& a) { return *array > *a.array; }
    bool operator<(const Array<T>& a) { return *array < *a.array; }
    bool operator>=(const Array<T>& a) { return *array >= *a.array; }
    bool operator<=(const Array<T>& a) { return *array <= *a.array; }

   private:
    int change_length(int old_length, int new_length);
};

template <typename T>
Array<T>::Array(int l) : number(0) {
    length = l;
    array = new T[length];
}

template <typename T>
Array<T>::~Array() {
    number = 0;
    delete[] array;
    array = nullptr;
}

template <typename T>
int Array<T>::search(T x) {
    for (int i = 0; i < number; ++i) {
        if (x == array[i]) {
            return i;
        }
    }
    return -1;
}

template <typename T>
int Array<T>::push(T x) {
    if (search(x) >= 0) {
        return -1;
    }
    if (number >= length) {
        change_length(length, length * 2);
    }
    array[number++] = x;
    return 1;
}

template <typename T>
int Array<T>::remove(T x) {
    int index = search(x);
    if (index < 0) {
        return -1;
    }
    if (number <= 0) {
        return 0;
    }
    if (number * 4 <= length) {
        change_length(length, length / 2);
    }
    if (index + 1 != number) {
        for (int i = index; i < number; ++i) {
            array[i] = array[i + 1];
        }
    }
    --number;
    return 1;
}

template <typename T>
int Array<T>::change_length(int old_length, int new_length) {
    length = new_length;
    T* temp = new T[length];
    for (int i = 0; i < number; ++i) {
        temp[i] = array[i];
    }
    delete[] array;
    array = temp;
    return length;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& a) {
    if (length < a.length) {
        change_length(length, a.length);
    }
    for (int i = 0; i < a.number; ++i) {
        push(a[i]);
    }
    return *this;
}

#endif  // ARRAY_H__