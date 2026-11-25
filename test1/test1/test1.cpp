#include <iostream>
#include <exception>

class smart_array {
public:
    // Конструктор: выделяем память под нужное количество элементов
    explicit smart_array(unsigned int capacity)
        : capacity_(capacity), size_(0) {
        if (capacity_ == 0) {
            throw std::invalid_argument("capacity must be greater than zero");
        }
        data_ = new int[capacity_]();
    }

    // Запрещаем копирование: два объекта не должны владеть одной памятью
    smart_array(const smart_array&) = delete;
    smart_array& operator=(const smart_array&) = delete;

    // Добавление элемента. Если массив заполнен — расширяем его
    void add_element(int value) {
        if (size_ >= capacity_) {
            resize();
        }
        data_[size_++] = value;
    }

    // Получение элемента по индексу с проверкой границ
    int get_element(unsigned int index) const {
        if (index >= size_) {
            throw std::out_of_range("index out of range");
        }
        return data_[index];
    }

    // Деструктор: освобождаем память (RAII)
    ~smart_array() {
        delete[] data_;
    }

private:
    // Перевыделение памяти с запасом
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
        arr.add_element(14);
        arr.add_element(15);
        std::cout << arr.get_element(1) << std::endl; // выведет 4
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}