
#include <iostream>
#include <exception>
#include <utility>

class smart_array {
public:
    explicit smart_array(unsigned int capacity)
        : capacity_(capacity), size_(0) {
        if (capacity_ == 0) {
            throw std::invalid_argument("capacity must be greater than zero");
        }
        data_ = new int[capacity_]();
    }

    // Конструктор копирования: выделяем СВОЮ память и копируем содержимое
    smart_array(const smart_array& other)
        : capacity_(other.capacity_), size_(other.size_) {
        data_ = new int[capacity_];
        for (unsigned int i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    // Оператор присваивания: сначала освобождаем свою память,
    // затем копируем данные из другого объекта
    smart_array& operator=(const smart_array& other) {
        if (this == &other) {          // защита от самоприсваивания a = a
            return *this;
        }
        int* new_data = new int[other.capacity_];
        for (unsigned int i = 0; i < other.size_; ++i) {
            new_data[i] = other.data_[i];
        }
        delete[] data_;                // старый буфер больше не нужен
        data_ = new_data;
        capacity_ = other.capacity_;
        size_ = other.size_;
        return *this;
    }

    void add_element(int value) {
        if (size_ >= capacity_) {
            resize();
        }
        data_[size_++] = value;
    }

    int get_element(unsigned int index) const {
        if (index >= size_) {
            throw std::out_of_range("index out of range");
        }
        return data_[index];
    }

    ~smart_array() {
        delete[] data_;
    }

private:
    void resize() {
        unsigned int new_capacity = capacity_ * 2;
        int* new_data = new int[new_capacity]();
        for (unsigned int i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    int* data_;
    unsigned int capacity_;
    unsigned int size_;
};

int main() {
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);

        smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        arr = new_array;

        std::cout << arr.get_element(0) << std::endl; // 44
        std::cout << arr.get_element(1) << std::endl; // 34
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}