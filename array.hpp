#ifndef ARRAY_H__
#define ARRAY_H__

template <typename T>
class Array {
   public:
    int number;

   private:
    T* array;
    int length;

   public:
    Array(int l = 1);
    ~Array();
    int push(T x);
    int remove(T x);
    int search(T x);
    T operator[](int i) { return array[i]; }

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
    if (search(x) > 0) {
        return -1;
    }
    if (number >= length) {
        change_length(length, length * 2);
    } else if (number * 4 <= length) {
        change_length(length, length / 2);
    }
    array[++number] = x;
    return 1;
}

template <typename T>
int Array<T>::remove(T x) {
    int index = search(x);
    if (index < 0) {
        return -1;
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

#endif  // ARRAY_H__