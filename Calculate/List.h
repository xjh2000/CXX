#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
//
// Created by haoge on 2021/6/16.
//

#ifndef START_LIST_H
#define START_LIST_H


#include "ListNode.h" //�����б��ڵ���

template<typename T>
class List { //�б�ģ����
    using ListNodePosi = ListNode<T> *;
    using Rank = int;
private:
    int _size; // ��ģ
    ListNodePosi header; // ͷ�ڱ�
    ListNodePosi trailer; //β�ڱ�

protected:
    void init(); //�б�����ʱ�ĳ�ʼ��
//    int clear(); //������нڵ�

    int copyNodes(ListNodePosi, int); //�����б�����λ��p���n��
//    ListNodePosi merge ( ListNodePosi, int, List<T> &, ListNodePosi, int ); //�鲢
//    void mergeSort ( ListNodePosi &, int ); //�Դ�p��ʼ������n���ڵ�鲢����
//    void selectionSort ( ListNodePosi, int ); //�Դ�p��ʼ������n���ڵ�ѡ������
//    void insertionSort ( ListNodePosi, int ); //�Դ�p��ʼ������n���ڵ��������
//    void radixSort(ListNodePosi, int); //�Դ�p��ʼ������n���ڵ��������

public:
    // ���캯��
    List() { init(); } //Ĭ�� NOLINT(cppcoreguidelines-pro-type-member-init)
    // O(n)-O(n)
    List(const List<T> &l) { // NOLINT(cppcoreguidelines-pro-type-member-init)
        this->copyNodes(l.first(), l._size);
    }

    List(const List<T> &L, Rank r, int n); //�����б�L���Ե�r�����n��
    List(ListNodePosi p, int n); //�����б�����λ��p���n��
//    // ��������
//    ~List(); //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
//    // ֻ�����ʽӿ�
//    Rank size() const { return _size; } //��ģ
//    bool empty() const { return _size <= 0; } //�п�

    // O(n)-O(1)
    ListNodePosi operator[](Rank r) const; //���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
    // O(1)-O(1)
    ListNodePosi first() const { return header->succ; } //�׽ڵ�λ��
    // O(1)-O(1)
    ListNodePosi last() const { return trailer->pred; } //ĩ�ڵ�λ��
//    bool valid ( ListNodePosi p ) //�ж�λ��p�Ƿ����Ϸ�
//    { return p && ( trailer != p ) && ( header != p ); } //��ͷ��β�ڵ��ͬ��NULL
    // O(n)-O(1)
    ListNodePosi find(T const &e) const //�����б�����
    { return find(e, _size, trailer); }

    // O(n)-O(1)
    ListNodePosi find(T const &e, int n, ListNodePosi p) const; //�����������
//    ListNodePosi search ( T const& e ) const //�����б�����
//    { return search ( e, _size, trailer ); }
//    ListNodePosi search ( T const& e, int n, ListNodePosi p ) const; //�����������
//    ListNodePosi selectMax ( ListNodePosi p, int n ); //��p����n-1�������ѡ�������
//    ListNodePosi selectMax() { return selectMax ( header->succ, _size ); } //���������
//    // ��д���ʽӿ�

    // O(1)-O(1)
    ListNodePosi insertAsFirst(T const &e); //��e�����׽ڵ����
    // O(1)-O(1)
    ListNodePosi insertAsLast(T const &e); //��e����ĩ�ڵ����
    // O(1)-O(1)
    ListNodePosi insert(ListNodePosi p, T const &e); //��e����p�ĺ�̲���
    // O(1)-O(1)
    ListNodePosi insert(T const &e, ListNodePosi p); //��e����p��ǰ������
    T remove ( ListNodePosi p ); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
//    void merge ( List<T> & L ) { merge ( header->succ, _size, L, L.header->succ, L._size ); } //ȫ�б��鲢
//    void sort ( ListNodePosi p, int n ); //�б���������
//    void sort() { sort ( first(), _size ); } //�б���������
//    int deduplicate(); //����ȥ��
//    int uniquify(); //����ȥ��
//    void reverse(); //ǰ���ã�ϰ�⣩
//    // ����
//    void traverse ( void (* ) ( T& ) ); //����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ�
//    template <typename VST> //������
//    void traverse ( VST& ); //����������ʵʩvisit�������������󣬿�ȫ�����޸ģ�
};

template<typename T>
void List<T>::init() {
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->pred = nullptr;
    header->succ = trailer;
    trailer->pred = header;
    trailer->succ = nullptr;
    _size = 0;
}

template<typename T>
typename List<T>::ListNodePosi List<T>::operator[](Rank r) const {
    ListNodePosi tp = first();
    while (r-- > 0) tp = tp->succ;
    return tp;
}

template<typename T>
typename List<T>::ListNodePosi List<T>::find(const T &e, int n, List::ListNodePosi p) const {
    while (n-- > 0)if ((p = p->pred)->data == e)return p;
    return nullptr;
}

template<typename T>
typename List<T>::ListNodePosi List<T>::insertAsFirst(const T &e) {
    _size++;
    return header->insertAsSucc(e);
}

template<typename T>
typename List<T>::ListNodePosi List<T>::insertAsLast(const T &e) {
    _size++;
    return trailer->insertAsPred(e);
}

template<typename T>
typename List<T>::ListNodePosi List<T>::insert(List::ListNodePosi p, const T &e) {
    _size++;
    return p->insertAsSucc(e);
}

template<typename T>
typename List<T>::ListNodePosi List<T>::insert(const T &e, List::ListNodePosi p) {
    _size++;
    return p->insertAsPred(e);
}

template<typename T>
int List<T>::copyNodes(List::ListNodePosi p, int n) {
    init();
    while (n--) {
        insertAsFirst(p->data);
        p = p->succ;
    }
}

template<typename T>
List<T>::List(const List<T> &L, Rank r, int n) {
    this->copyNodes(L[r], n);
}

template<typename T>
List<T>::List(List::ListNodePosi p, int n) {
    this->copyNodes(p, n);
}

template<typename T>
T List<T>::remove(List::ListNodePosi p) {
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    return e;
}

//List


#endif //START_LIST_H

//#pragma clang diagnostic pop