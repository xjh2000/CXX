#pragma clang diagnostic push

//
// Created by 93462 on 2021/5/16.
//

#ifndef START_VECTOR_H
#define START_VECTOR_H

using namespace std;
using Rank = int;          //秩
#define DEFAULT_CAPACITY 3 //默认的初始容量（实际应用中可设置为更大）

#include <vector>
#include <iostream>
#include <new>
#include "until.h"

template<typename T>
class Vector { //向量模板类
protected:
    Rank _size;
    int _capacity;
    T *_elem; //规模、容量、数据区
    // O(n)-O(n)
    void copyFrom(T const *A, Rank lo, Rank hi); //复制数组区间A[lo, hi)
    // O(1)-O(1) - share create space
    void expand(); //空间不足时扩容
    // O(1)-O(1) - share delete space
    void shrink(); //装填因子过小时压缩

public:
    // O(n)-O(1)
    bool bubble(Rank lo, Rank hi); //扫描交换
    // O(n*n)-O(1)-O(n/2)
    void bubbleSort(Rank lo, Rank hi); //起泡排序算法
    //    Rank maxItem ( Rank lo, Rank hi ); //选取最大元素
    //    void selectionSort ( Rank lo, Rank hi ); //选择排序算法
    // O(n)-O(n)
    void merge(Rank lo, Rank mi, Rank hi); //归并算法
    // O(n*log(n))-O(n)
    void mergeSort(Rank lo, Rank hi); //归并排序算法
    //    void heapSort ( Rank lo, Rank hi ); //堆排序（稍后结合完全堆讲解）
    //    Rank partition ( Rank lo, Rank hi ); //轴点构造算法
    //    void quickSort ( Rank lo, Rank hi ); //快速排序算法
    //    void shellSort ( Rank lo, Rank hi ); //希尔排序算法

    explicit Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //容量为c、规模为s、所有元素初始为v
    {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    } //s<=c NOLINT(bugprone-suspicious-semicolon)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"

    // O(n)-O(n)
    Vector(T const *A, Rank n) { copyFrom(A, 0, n); } //数组整体复制
    // O(n)-O(n)
    Vector(T const *A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //区间
    // O(n)-O(n)
    Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V._size); } //向量整体复制
    // O(n)-O(n)
    Vector(Vector<T> const &V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //区间
#pragma clang diagnostic pop

    // 析构函数
    ~Vector() { delete[] _elem; } //释放内部空间
    void test();

    void print();

    // 只读访问接口
    Rank size() const { return _size; }   //规模
    bool empty() const { return !_size; } //判空
    // O(n)-O(1)
    int disordered() const;

    // O(n)-O(1)
    // return : -1--error
    Rank find(T const &e) const { return find(e, 0, _size); } //无序向量整体查找
    // O(n)-O(1)
    // return : -1--error
    Rank find(T const &e, Rank lo, Rank hi) const; //无序向量区间查找

//    Rank search(T const &e) const //有序向量整体查找
//    { return (0 >= _size) ? -1 : search(e, 0, _size); }

    Rank search(T const &e, Rank lo, Rank hi) const; //有序向量区间查找
    // 可写访问接口
    T &operator[](Rank r); //重载下标操作符，可以类似于数组形式引用各元素

    //    const T& operator[] ( Rank r ) const; //仅限于做右值的重载版本

    // O(n)-O(n)
    Vector<T> &operator=(Vector<T> const &); //重载赋值操作符，以便直接克隆向量
    // O(n)-O(1)
    T remove(Rank r); //删除秩为r的元素
    // O(n)-O(1)
    // note: 0<=lo<hi<=_size
    int remove(Rank lo, Rank hi); //删除秩在区间[lo, hi)之内的元素

    // O(n)-O(1)
    Rank insert(Rank r, T const &e); //插入元素
    // O(n)-O(1)
    Rank insert(T const &e) { return insert(_size, e); } //默认作为末元素插入

    //    void sort(Rank lo, Rank hi); //对[lo, hi)排序
    //    void sort() { sort ( 0, _size ); } //整体排序
    // O(n)-O(1)
    void unsort(Rank lo, Rank hi); //对[lo, hi)置乱
    // O(n)-O(1)
    void unsort() { unsort(0, _size); } //整体置乱
    // O(log(n))-O(1)-O(1.5log(n)) - binarySearch
    Rank binSearch(const T &e, Rank lo, Rank hi) const;

    // O(log(n))-O(1)-O(log(n)) - binarySearch1
    Rank binSearch1(const T &e, Rank lo, Rank hi) const;

    // O(log(n))-O(1)-O(1.44log(n)) - fibSearch
    Rank fibSearch(const T &e, Rank lo, Rank hi) const;

    // O(n*n)-O(1)
    int deduplicate(); //无序去重
    // O(n*n)-O(1)
    int uniquify(); //有序去重
    // 遍历

    // O(n)-O(1)
    void traverse(void (*)(T &)); //遍历（使用函数指针，只读或局部性修改）
    // O(n)-O(1)
    template<typename VST>
    void traverse(VST &); //遍历（使用函数对象，可全局性修改）
};

template<typename T>
void Vector<T>::copyFrom(const T *A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi)
        _elem[_size++] = A[lo++];
}

template<typename T>
Vector<T> &Vector<T>::operator=(Vector<T> const &v) {
    if (&v == this)
        return *this;
    if (_elem)
        delete[] _elem;
    copyFrom(v._elem, 0, v._size);
    return *this;
}

template<typename T>
void Vector<T>::expand() {
    if (_size < _capacity)
        return;
    if (_capacity < DEFAULT_CAPACITY)
        _capacity = DEFAULT_CAPACITY;
    T *oleElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; ++i) {
        _elem[i] = oleElem[i];
    }
    delete[] oleElem;
}

template<typename T>
void Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1)
        return;
    if (_size << 2 > _capacity)
        return;
    T *oleElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; ++i) {
        _elem[i] = oleElem[i];
    }
    delete[] oleElem;
}

template<typename T>
void Vector<T>::test() {
    this->_size = 3;
    this->expand();
    this->_size = 1;
    this->shrink();
}

template<typename T>
T &Vector<T>::operator[](Rank r) {
    return _elem[r];
}

template<typename T>
void Vector<T>::print() {
    for (int i = 0; i < _size; ++i)
        std::cout << _elem[i] << '\t';
    std::cout << '\n';
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    srand((unsigned int) time(nullptr)); // NOLINT(cert-msc51-cpp)
    T *V = _elem + lo;
    for (Rank i = hi - lo; i > 0; i--)
        swap(V[i - 1], V[rand() % i]); // NOLINT(cert-msc50-cpp)
}

template<typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const {
    while ((lo < hi--) && (_elem[hi] != e));
    return hi;
}

template<typename T>
Rank Vector<T>::insert(Rank r, const T &e) {
    expand();
    for (int i = _size; i > r; i--)
        _elem[i] = _elem[i - 1];
    _elem[r] = e;
    _size++;
    return r;
}

template<typename T>
T Vector<T>::remove(Rank r) {
    T re = _elem[r];
    remove(r, r + 1);
    return re;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
    if (lo >= hi)
        return 0;
    for (; hi < _size; _elem[lo++] = _elem[hi++]);
    _size = lo;
    shrink();
    return hi - lo;
}

template<typename T>
int Vector<T>::deduplicate() {
    int oldSize = _size;
    int i = 1;
    while (i < _size) {
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
    }
    return oldSize - _size;
}

template<typename T>
int Vector<T>::uniquify() {
    int i = 1, j = 0;
    for (; i < _size; i++) {
        if (_elem[i] != _elem[j])
            _elem[++j] = _elem[i];
    }
    _size = ++j;
    shrink();
    return i - j;
}
// int oldSize = _size;
// int i = 1;
// while (i < _size)
// {
//     (_elem[i-1]!= _elem[i]) ? i++ : remove(i);
// }
// return oldSize - _size;

template<typename T>
void Vector<T>::traverse(void (*visitor)(T &)) {
    for (int i = 0; i < _size; ++i)
        visitor(_elem[i]);
}

template<typename T>
template<typename VST>
void Vector<T>::traverse(VST &visitor) {
    for (int i = 0; i < _size; ++i)
        visitor(_elem[i]);
}

template<typename T>
int Vector<T>::disordered() const {
    int n = 0;
    for (int i = 1; i < _size; ++i)
        if (_elem[i - 1] > _elem[i])
            n++;
    return n;
}

template<typename T>
Rank Vector<T>::search(const T &e, Rank lo, Rank hi) const {
    return binSearch(e, lo, hi);
}


template<typename T>
Rank Vector<T>::binSearch(const T &e, Rank lo, Rank hi) const {
    while (lo <= hi) {
        Rank mid = (lo + hi) >> 1;
        if (e < _elem[mid]) hi = mid;
        else if (_elem[mid] < e) lo = mid + 1;
        else return mid;
    }
    return -1;
}

template<typename T>
Rank Vector<T>::binSearch1(const T &e, Rank lo, Rank hi) const {
    while (lo < hi) {
        Rank mid = (lo + hi) >> 1;
        if (_elem[mid] < e) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return _elem[lo] == e ? lo : -1;
}


template<typename T>
Rank Vector<T>::fibSearch(const T &e, Rank lo, Rank hi) const {
    Fib fib(hi - lo);
    while (lo < hi) {
        Rank mi = lo + fib.get();
        if (_elem[mi] < e) {
            lo = mi + 1;
        } else if (e < _elem[mi]) {
            hi = mi;
        } else {
            return mi;
        }
        fib.prev();
    }
    return -1;
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
    bool status = true;
    for (; lo < hi; lo++) {
        if (_elem[lo] > _elem[lo + 1]) {
            swap(_elem[lo], _elem[lo + 1]);
            status = false;
        }
    }
    return status;
}

template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
    while (!bubble(lo, hi--));
}

template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if (hi - lo < 2)
        return;
    Rank mi = (lo + hi) / 2;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T *A = _elem + lo;
    int lb = mi - lo;
    T *B = new T[lb];
    for (Rank i = 0; i < lb; B[i] = A[i], i++);
    int lc = hi - mi;
    T *C = _elem + mi;
    for (int a = 0, b = 0, c = 0; (b < lb) || (c < lc);) {
        if ((b < lb) && (c >= lc || B[b] <= C[c])) A[a++] = B[b++];
        if ((c < lc) && (b >= lb || B[b] > C[c])) A[a++] = C[c++];
    }
    delete[] B;
}

//Vector

// tool function

template<typename T>
static bool lt(T *a, T *b) { return lt(*a, *b); }

template<typename T>
static bool lt(T &a, T &b) { return a < b; }

template<typename T>
static bool eq(T *a, T *b) { return eq(*a, *b); }

template<typename T>
static bool eq(T &a, T &b) { return a == b; }

template<typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi) {
    while (lo < hi) {
        Rank mi = (lo + hi) >> 1;
        if (e < A[mi]) hi = mi;
        else if (A[mi] < e) lo = mi + 1;
        else return mi;
    }
    return -1;
}

#endif //START_VECTOR_H
