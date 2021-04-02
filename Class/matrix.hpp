#ifndef SJTU_MATRIX_HPP
#define SJTU_MATRIX_HPP

//An improve version of matrix

#include <cstddef>
#include <initializer_list>
#include <utility>
#include <iterator>
#include <iostream>

using std::size_t;
using std::endl;
using std::cout;

namespace sjtu {
    
    template<class T>
    class Matrix {
    private:
        // your private member variables here.
        T *matrix_storage = nullptr;
        size_t matrix_row = 0;
        size_t matrix_column = 0;
    
    public:
        //friend declaration
        
        friend class iterator;
        
        template<class T_, class U>
        friend auto operator*(const Matrix<T_> &mat, const U &x);
        
        template<class T_, class U>
        friend auto operator*(const U &x, const Matrix<T_> &mat);
        
        template<class U, class V>
        friend auto operator*(const Matrix<U> &a, const Matrix<V> &b);
        
        template<class U, class V>
        friend auto operator+(const Matrix<U> &a, const Matrix<V> &b);
        
        template<class U, class V>
        friend auto operator-(const Matrix<U> &a, const Matrix<V> &b);
        
        template<class U>
        friend std::ostream &operator<<(std::ostream &os, const Matrix<U> &matrix);
        
        template<class U>
        friend std::istream &operator>>(std::istream &is, Matrix<U> &matrix);
    
    
    public:
        Matrix() = default;
        
        Matrix(size_t n, size_t m, T _init = T()) {
            matrix_row = n;
            matrix_column = m;
            matrix_storage = new T[n * m];
            for (size_t i = 0; i < n * m; i++) {
                matrix_storage[i] = _init;
            }
        }
        
        explicit Matrix(std::pair<size_t, size_t> sz, T _init = T()) {
            matrix_row = sz.first;
            matrix_column = sz.second;
            matrix_storage = new T[sz.first * sz.second];
            for (size_t i = 0; i < sz.first * sz.second; i++) {
                matrix_storage[i] = _init;
            }
        }
        
        Matrix(const Matrix &o) {
            std::pair<size_t, size_t> sz = o.size();
            matrix_row = sz.first;
            matrix_column = sz.second;
            matrix_storage = new T[sz.first * sz.second];
            for (size_t i = 0; i < sz.first; i++) {
                for (size_t j = 0; j < sz.second; j++) {
                    matrix_storage[i * sz.second + j] = o(i, j);
                }
            }
        }
        
        template<class U>
        Matrix(const Matrix<U> &o) {
            std::pair<size_t, size_t> sz = o.size();
            matrix_row = sz.first;
            matrix_column = sz.second;
            matrix_storage = new T[sz.first * sz.second];
            for (size_t i = 0; i < sz.first; i++) {
                for (size_t j = 0; j < sz.second; j++) {
                    matrix_storage[i * sz.second + j] = o(i, j);
                }
            }
        }
        
        Matrix &operator=(const Matrix &o) {
            if(this==&o)return *this;
            std::pair<size_t, size_t> sz = o.size();
            matrix_row = sz.first;
            matrix_column = sz.second;
            for (size_t i = 0; i < sz.first; i++) {
                for (size_t j = 0; j < sz.second; j++) {
                    matrix_storage[i * sz.second + j] = o(i, j);
                }
            }
            return *this;
        }
        
        template<class U>
        Matrix &operator=(const Matrix<U> &o) {
            if(this==&o)return *this;
            std::pair<size_t, size_t> sz = o.size();
            matrix_row = sz.first;
            matrix_column = sz.second;
            for (size_t i = 0; i < sz.first; i++) {
                for (size_t j = 0; j < sz.second; j++) {
                    matrix_storage[i * sz.second + j] = o(i, j);
                }
            }
            return *this;
        }
        
        Matrix(Matrix &&o) noexcept {
            //use when "Matrix a(b);" or "Matrix a=b;"
            matrix_column = o.matrix_column;
            matrix_row = o.matrix_row;
            matrix_storage = o.matrix_storage;
            o.matrix_storage = nullptr;
        }
        
        Matrix &operator=(Matrix &&o) noexcept {
            //use when "Matrix a; a=b;"
            matrix_column = o.matrix_column;
            matrix_row = o.matrix_row;
            delete[] matrix_storage;
            matrix_storage = o.matrix_storage;
            o.matrix_storage = nullptr;
            return *this;
        }
        
        ~Matrix() {
            if (matrix_storage != nullptr) {
                delete[] matrix_storage;
            }
            matrix_storage = nullptr;
        }
        
        Matrix(std::initializer_list<std::initializer_list<T>> il) {
            size_t il_row_size = il.size();
            size_t il_column_size = (*il.begin()).size();
            matrix_column = il_column_size;
            matrix_row = il_row_size;
            matrix_storage = new T[matrix_row * matrix_column];
            size_t i = 0;
            for (auto iter_row = il.begin(); iter_row != il.end(); iter_row++) {
                if ((*iter_row).size() != il_column_size) {
                    delete[] matrix_storage;
                    throw std::invalid_argument("INITIALIZER_LIST DOESN'T FORM A RECTANGLE!");
                }
                size_t j = 0;
                for (auto iter_column = (*iter_row).begin(); iter_column != (*iter_row).end(); iter_column++) {
                    matrix_storage[i * matrix_column + j] = *iter_column;
                    j++;
                }
                i++;
            }
        }
    
    public:
        size_t rowLength() const {
            return matrix_row;
        }
        
        size_t columnLength() const {
            return matrix_column;
        }
        
        void resize(size_t _n, size_t _m, T _init = T()) {
            if (_n * _m == matrix_row * matrix_column) {
                matrix_row = _n;
                matrix_column = _m;
            }
            else {
                size_t new_size = _n * _m, old_size = matrix_column * matrix_row;
                matrix_row = _n;
                matrix_column = _m;
                T *temp = new T[new_size];
                for (size_t i = 0; i < new_size; i++) {
                    temp[i] = (i < old_size ? matrix_storage[i] : _init);
                }
                delete[] matrix_storage;
                matrix_storage = temp;
            }
        }
        
        void resize(std::pair<size_t, size_t> sz, T _init = T()) {
            if (sz.first * sz.second == matrix_row * matrix_column) {
                matrix_row = sz.first;
                matrix_column = sz.second;
            }
            else {
                size_t new_size = sz.first * sz.second, old_size = matrix_column * matrix_row;
                matrix_row = sz.first;
                matrix_column = sz.second;
                T *temp = new T[new_size];
                for (size_t i = 0; i < new_size; i++) {
                    temp[i] = (i < old_size ? matrix_storage[i] : _init);
                }
                delete[] matrix_storage;
                matrix_storage = temp;
            }
        }
        
        std::pair<size_t, size_t> size() const {
            std::pair<size_t, size_t> temp;
            temp.first = matrix_row;
            temp.second = matrix_column;
            return temp;
        };
        
        void clear() {
            matrix_row = 0;
            matrix_column = 0;
            if (matrix_storage != nullptr) {
                delete[] matrix_storage;
                matrix_storage = nullptr;
            }
            else throw std::invalid_argument("THE MATRIX HAS BEEN CLEARED!");
        }
    
    public:
        const T &operator()(size_t i, size_t j) const {
            //right value
            if (i >= matrix_row || j >= matrix_column || i < 0 || j < 0)throw std::invalid_argument("WRONG POSITION!");
            return matrix_storage[i * matrix_column + j];
        }
        
        T &operator()(size_t i, size_t j) {
            //left value
            if (i >= matrix_row || j >= matrix_column || i < 0 || j < 0)throw std::invalid_argument("WRONG POSITION!");
            return matrix_storage[i * matrix_column + j];
        }
        
        Matrix<T> row(size_t i) const {
            if (i >= matrix_row || i < 0)throw std::invalid_argument("WRONG POSITION!");
            Matrix<T> temp(1, matrix_column);
            for (size_t j = 0; j < matrix_column; j++) {
                temp.matrix_storage[j] = matrix_storage[i * matrix_column + j];
            }
            return temp;
        }
        
        Matrix<T> column(size_t i) const {
            if (i >= matrix_column || i < 0)throw std::invalid_argument("WRONG POSITION!");
            Matrix<T> temp(matrix_row, 1);
            for (size_t j = 0; j < matrix_row; j++) {
                temp.matrix_storage[j] = matrix_storage[j * matrix_column + i];
            }
            return temp;
        }
    
    
    public:
        template<class U>
        bool operator==(const Matrix<U> &o) const {
            std::pair<size_t, size_t> sz = o.size();
            if (sz.second == matrix_column && sz.first == matrix_row) {
                for (size_t i = 0; i < matrix_row; i++) {
                    for (size_t j = 0; j < matrix_column; j++) {
                        if (o(i, j) != matrix_storage[i * matrix_column + j])
                            return false;
                    }
                }
                return true;
            }
            else return false;
        }
        
        template<class U>
        bool operator!=(const Matrix<U> &o) const {
            std::pair<size_t, size_t> sz = o.size();
            if (sz.second == matrix_column && sz.first == matrix_row) {
                for (size_t i = 0; i < matrix_row; i++) {
                    for (size_t j = 0; j < matrix_column; j++) {
                        if (o(i, j) != matrix_storage[i * matrix_column + j])
                            return true;
                    }
                }
                return false;
            }
            else return true;
        }
        
        Matrix operator-() const {
            Matrix temp = *this;
            for (size_t i = 0; i < matrix_row; i++) {
                for (size_t j = 0; j < matrix_column; j++) {
                    temp.matrix_storage[i * matrix_column + j] *= -1;
                }
            }
            return temp;
        }
        
        template<class U>
        Matrix &operator+=(const Matrix<U> &o) {
            if (matrix_row != o.matrix_row || matrix_column != o.matrix_column)throw std::invalid_argument("MATRIX'S SHAPE IS DIFFERENT!");
            for (size_t i = 0; i < matrix_row; i++) {
                for (size_t j = 0; j < matrix_column; j++) {
                    matrix_storage[i * matrix_column + j] += o(i, j);
                }
            }
            return *this;
        }
        
        template<class U>
        Matrix &operator-=(const Matrix<U> &o) {
            if (matrix_row != o.matrix_row || matrix_column != o.matrix_column)throw std::invalid_argument("MATRIX'S SHAPE IS DIFFERENT!");
            for (size_t i = 0; i < matrix_row; i++) {
                for (size_t j = 0; j < matrix_column; j++) {
                    matrix_storage[i * matrix_column + j] -= o(i, j);
                }
            }
            return *this;
            
        }
        
        template<class U>
        Matrix &operator*=(const U &x) {
            for (size_t i = 0; i < matrix_row; i++) {
                for (size_t j = 0; j < matrix_column; j++) {
                    matrix_storage[i * matrix_column + j] *= x;
                }
            }
            return *this;
        }
        
        Matrix tran() const {
            Matrix temp(matrix_column, matrix_row);
            for (size_t i = 0; i < matrix_column; i++) {
                for (size_t j = 0; j < matrix_row; j++) {
                    temp.matrix_storage[i * matrix_row + j] = (*this)(j, i);
                }
            }
            return temp;
        }
    
    public: // iterator
        
        class iterator {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            using size_type = size_t;
            using difference_type = std::ptrdiff_t;//signed integer
            
            iterator() = default;
            
            iterator(const iterator &) = default;
            
            iterator &operator=(const iterator &) = default;
        
        
        private:
            Matrix<T> *matrix_ptr = nullptr;
            
            size_t iter_row = 0;
            size_t iter_column = 0;
            size_t iter_position = 0;
            
            size_t iter_border_left = 0;
            size_t iter_border_right = 0;
            size_t iter_border_up = 0;
            size_t iter_border_down = 0;
            size_t border_distance_lr = iter_border_right - iter_border_left + 1;
            size_t border_distance_ud = iter_border_down - iter_border_up + 1;
        
        
        public:
            //friend declaration
            friend iterator Matrix::begin();
            
            friend iterator Matrix::end();
            
            friend std::pair<iterator, iterator> Matrix::subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r);
        
        
        public:
            difference_type operator-(const iterator &o) {
                difference_type temp = iter_position - o.iter_position;
                return temp;
            }
            
            iterator &operator+=(difference_type offset) {
                difference_type d_row = offset / (border_distance_lr);
                difference_type d_column = offset - d_row * (border_distance_lr);
                if (d_column + iter_column > iter_border_right) {
                    d_row++;
                    d_column -= border_distance_lr;
                }
                if (iter_row + d_row > iter_border_down)throw std::invalid_argument("OUT OF THE MATRIX!!");
                iter_row += d_row;
                iter_column += d_column;
                iter_position = iter_row * (matrix_ptr->matrix_column) + iter_column;
                return *this;
            }
            
            iterator operator+(difference_type offset) const {
                iterator temp = *this;
                difference_type d_row = offset / (border_distance_lr);
                difference_type d_column = offset - d_row * (border_distance_lr);
                if (d_column + iter_column > iter_border_right) {
                    d_row++;
                    d_column -= border_distance_lr;
                }
                if (temp.iter_row + d_row > iter_border_down)throw std::invalid_argument("OUT OF THE MATRIX!!");
                temp.iter_row += d_row;
                temp.iter_column += d_column;
                temp.iter_position = temp.iter_row * (matrix_ptr->matrix_column) + temp.iter_column;
                return temp;
            }
            
            iterator &operator-=(difference_type offset) {
                if ((offset % border_distance_lr) <= iter_column - iter_border_left) {
                    //not switch to new line
                    if (iter_row < iter_border_up + (offset / border_distance_lr))throw std::invalid_argument("OUT OF THE MATRIX!!");
                    iter_row -= (offset / border_distance_lr);
                    iter_column -= offset;
                    iter_position = iter_row * (matrix_ptr->matrix_column) + iter_column;
                    return *this;
                }
                else {
                    //switch to new line
                    if (iter_row < 1 + iter_border_up + (offset / border_distance_lr))throw std::invalid_argument("OUT OF THE MATRIX!!");
                    iter_row -= (1 + offset / border_distance_lr);
                    iter_column += (border_distance_lr - offset);
                    iter_position = iter_row * (matrix_ptr->matrix_column) + iter_column;
                    return *this;
                }
            }
            
            iterator operator-(difference_type offset) const {
                iterator temp = *this;
                if ((offset % border_distance_lr) <= iter_column - iter_border_left) {
                    //not switch to new line
                    if (iter_row < iter_border_up + (offset / border_distance_lr))throw std::invalid_argument("OUT OF THE MATRIX!!");
                    temp.iter_row -= (offset / border_distance_lr);
                    temp.iter_column -= offset;
                    temp.iter_position = temp.iter_row * (matrix_ptr->matrix_column) + temp.iter_column;
                    return temp;
                }
                else {
                    //switch to new line
                    if (iter_row < 1 + iter_border_up + (offset / border_distance_lr))throw std::invalid_argument("OUT OF THE MATRIX!!");
                    temp.iter_row -= (1 + offset / border_distance_lr);
                    temp.iter_column += (border_distance_lr - offset);
                    temp.iter_position = temp.iter_row * (matrix_ptr->matrix_column) + temp.iter_column;
                    return temp;
                }
            }
            
            iterator &operator++() {
                //++iter;  return added iter;
                (*this) += 1;
                return *this;
            }
            
            iterator operator++(int) {
                //iter++;  return original iter
                iterator tmp = *this;
                (*this) += 1;
                return tmp;
            }
            
            iterator &operator--() {
                //--iter;
                (*this) -= 1;
                return *this;
            }
            
            iterator operator--(int) {
                //iter--;
                iterator tmp = *this;
                (*this) -= 1;
                return tmp;
            }
            
            reference operator*() const {
                T &temp = (*matrix_ptr)(iter_row, iter_column);
                return temp;
            }
            
            pointer operator->() const {
                T *temp = &((*matrix_ptr)(iter_row, iter_column));
                return temp;
            }
            
            bool operator==(const iterator &o) const {
                if (matrix_ptr != o.matrix_ptr)return false;
                else {
                    if (iter_position != o.iter_position)return false;
                    else {
                        if (iter_border_up != o.iter_border_up || iter_border_down != o.iter_border_down || iter_border_left != o.iter_border_left || iter_border_right != o.iter_border_right) {
                            return false;
                        }
                        else return true;
                    }
                }
            }
            
            bool operator!=(const iterator &o) const {
                if (*this == o)return false;
                else return true;
            }
        };
        
        iterator begin() {
            iterator begin_iter;
            begin_iter.matrix_ptr = &(*this);
            begin_iter.iter_row = 0;
            begin_iter.iter_column = 0;
            begin_iter.iter_position = 0;
            begin_iter.iter_border_left = 0;
            begin_iter.iter_border_right = matrix_column - 1;
            begin_iter.iter_border_up = 0;
            begin_iter.iter_border_down = matrix_row - 1;
            begin_iter.border_distance_lr = begin_iter.iter_border_right - begin_iter.iter_border_left + 1;
            begin_iter.border_distance_ud = begin_iter.iter_border_down - begin_iter.iter_border_up + 1;
            return begin_iter;
        }
        
        iterator end() {
            iterator end_iter;
            end_iter.matrix_ptr = &(*this);
            end_iter.iter_row = matrix_row - 1;
            end_iter.iter_column = matrix_column - 1;
            end_iter.iter_position = (matrix_row - 1) * (matrix_column - 1);
            end_iter.iter_border_left = 0;
            end_iter.iter_border_right = matrix_column - 1;
            end_iter.iter_border_up = 0;
            end_iter.iter_border_down = matrix_row - 1;
            end_iter.border_distance_lr = end_iter.iter_border_right - end_iter.iter_border_left + 1;
            end_iter.border_distance_ud = end_iter.iter_border_down - end_iter.iter_border_up + 1;
            return end_iter;
        }
        
        std::pair<iterator, iterator> subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r) {
            iterator iter_sub_begin, iter_sub_end;
            
            iter_sub_begin.matrix_ptr = &(*this);
            iter_sub_begin.iter_row = l.first;
            iter_sub_begin.iter_column = l.second;
            iter_sub_begin.iter_position = l.first * (matrix_column) + l.second;
            iter_sub_begin.iter_border_left = l.second;
            iter_sub_begin.iter_border_right = r.second;
            iter_sub_begin.iter_border_up = l.first;
            iter_sub_begin.iter_border_down = r.first;
            iter_sub_begin.border_distance_lr = iter_sub_begin.iter_border_right - iter_sub_begin.iter_border_left + 1;
            iter_sub_begin.border_distance_ud = iter_sub_begin.iter_border_down - iter_sub_begin.iter_border_up + 1;
            
            iter_sub_end.matrix_ptr = &(*this);
            iter_sub_end.iter_row = r.first;
            iter_sub_end.iter_column = r.second;
            iter_sub_end.iter_position = r.first * (matrix_column) + r.second;
            iter_sub_end.iter_border_left = l.second;
            iter_sub_end.iter_border_right = r.second;
            iter_sub_end.iter_border_up = l.first;
            iter_sub_end.iter_border_down = r.first;
            iter_sub_end.border_distance_lr = iter_sub_end.iter_border_right - iter_sub_end.iter_border_left + 1;
            iter_sub_end.border_distance_ud = iter_sub_end.iter_border_down - iter_sub_end.iter_border_up + 1;
            
            std::pair<iterator, iterator> temp;
            temp.first = iter_sub_begin;
            temp.second = iter_sub_end;
            return temp;
        }
    };
    
}


namespace sjtu {
    
    template<class T, class U>
    auto operator*(const Matrix<T> &mat, const U &x) {
        T t;
        U u;
        Matrix<decltype(t * u)> temp(mat.matrix_row, mat.matrix_column);
        for (size_t i = 0; i < mat.matrix_row; i++) {
            for (size_t j = 0; j < mat.matrix_column; j++) {
                temp.matrix_storage[i * mat.matrix_column + j] = x * mat.matrix_storage[i * mat.matrix_column + j];
            }
        }
        return temp;
    }
    
    template<class T, class U>
    auto operator*(const U &x, const Matrix<T> &mat) {
        T t;
        U u;
        Matrix<decltype(t * u)> temp(mat.matrix_row, mat.matrix_column);
        for (size_t i = 0; i < mat.matrix_row; i++) {
            for (size_t j = 0; j < mat.matrix_column; j++) {
                temp.matrix_storage[i * mat.matrix_column + j] = x * mat.matrix_storage[i * mat.matrix_column + j];
            }
        }
        return temp;
    }
    
    template<class U, class V>
    auto operator*(const Matrix<U> &a, const Matrix<V> &b) {
        if (a.matrix_column != b.matrix_row)throw std::invalid_argument("MATRIX CAN'T BE MULTIPLE DUE TO ITS SHAPE!");
        
        //todo use this!!
        //typedef decltype(U()*V()) T;
        
        U u;
        V v;
        size_t new_row = a.matrix_row, new_column = b.matrix_column, _mid = a.matrix_column;
        Matrix<decltype(u * v)> temp(new_row, new_column);
        for (size_t i = 0; i < new_row; i++) {
            for (size_t j = 0; j < new_column; j++) {
                decltype(u * v) temp_sum = 0;
                for (size_t k = 0; k < _mid; k++) {
                    //a i row * b j column
                    temp_sum += (a.matrix_storage[i * _mid + k] * b.matrix_storage[k * new_column + j]);
                }
                temp.matrix_storage[i * new_column + j] = temp_sum;
            }
        }
        return temp;
    }
    
    template<class U, class V>
    auto operator+(const Matrix<U> &a, const Matrix<V> &b) {
        if (a.matrix_row != b.matrix_row || a.matrix_column != b.matrix_column)throw std::invalid_argument("MATRIX'S SHAPE IS DIFFERENT!");
        U u;
        V v;
        Matrix<decltype(u + v)> temp(a.matrix_row, a.matrix_column);
        for (size_t i = 0; i < a.matrix_row; i++) {
            for (size_t j = 0; j < a.matrix_column; j++) {
                size_t position = i * a.matrix_column + j;
                temp.matrix_storage[position] = a.matrix_storage[position] + b.matrix_storage[position];
            }
        }
        return temp;
    }
    
    template<class U, class V>
    auto operator-(const Matrix<U> &a, const Matrix<V> &b) {
        if (a.matrix_row != b.matrix_row || a.matrix_column != b.matrix_column)throw std::invalid_argument("MATRIX'S SHAPE IS DIFFERENT!");
        U u;
        V v;
        Matrix<decltype(u - v)> temp(a.matrix_row, a.matrix_column);
        for (size_t i = 0; i < a.matrix_row; i++) {
            for (size_t j = 0; j < a.matrix_column; j++) {
                size_t position = i * a.matrix_column + j;
                temp.matrix_storage[position] = a.matrix_storage[position] - b.matrix_storage[position];
            }
        }
        return temp;
    }
    
    template<class U>
    std::ostream &operator<<(std::ostream &os, const Matrix<U> &matrix) {
        for (int j = 0; j < 2*matrix.matrix_column-1; j++)os<<"-";
        os<<endl;
        for (int i = 0; i < matrix.matrix_row; i++) {
            for (int j = 0; j < matrix.matrix_column; j++) {
                os << matrix(i, j) << " ";
            }
            os << std::endl;
        }
        for (int j = 0; j < 2*matrix.matrix_column-1; j++)os<<"-";
        //os<<endl;
        return os;
    }
    
    template<class U>
    std::istream &operator>>(std::istream &is, Matrix<U> &matrix) {
        std::cout << "Input matrix row: ";
        is >> matrix.matrix_row;
        std::cout << "Input matrix column: ";
        is >> matrix.matrix_column;
        std::cout << "Input matrix:";
        std::cout << std::endl;
        delete[] matrix.matrix_storage;
        matrix.matrix_storage = new U[matrix.matrix_row * matrix.matrix_column];
        for (int i = 0; i < matrix.matrix_row; i++) {
            for (int j = 0; j < matrix.matrix_column; j++) {
                is >> matrix.matrix_storage[i * matrix.matrix_column + j];
            }
        }
        return is;
    }
    
}

#endif //SJTU_MATRIX_HPP

