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
    bool search(T x);

   private:
    int change_length(int old_length, int new_length);
};

template <typename T>
Array<T>::Array(int l) : number(0) {
    length = l;
    array = new T[length];
}

template <typename T>
~Array<T>::Array(int n) {
    number = 0;
    delete[] array;
}

template <typename T>
bool Array<T>::search(T x) {
    for (int i = 0; i < number; ++i) {
        if (x == array[i]) {
            return true;
        }
    }
    return false;
}

template <typename T>
int Array<T>::push(T x) {
    if (search(x)) {
        return -1;
    }
    if (number >= length) {
        change_length(length, length * 2);
    } else if (number * 3 <= length) {
        change_length(length, lenght / 2);
    }
    Array[++number] = x;
}

template <typename T>
int Array<T>::remove(T x) {
    if (!search(x)) {
    }
}

#endif  // ARRAY_H__