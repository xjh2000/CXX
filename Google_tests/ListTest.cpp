#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

//
// Created by haoge on 2021/6/16.
//

#include <gtest/gtest.h>
#include "List.h"
#include "Vector.h"

class ListTest : public testing::Test {
};

TEST_F(ListTest, base) {
    List<int> list;
    list.insertAsFirst(10);
    list.insertAsLast(11);
    List<int> list1{list};
    List<int> list2(list1, 1, 1);
    ASSERT_EQ(10, list.find(10)->data);
    list.remove(list.find(10));
    ASSERT_EQ(nullptr, list.find(10));
    ASSERT_EQ(10, list1.find(10)->data);
    ASSERT_EQ(10, list2.find(10)->data);
    ASSERT_EQ(11, list.find(11)->data);
    ASSERT_EQ(11, list1.find(11)->data);
}

TEST_F(ListTest, test) {
    List<int> list;
    list.insertAsFirst(10);
    list.insertAsLast(10);
    list.traverse(&printT<int>);
    list.deduplicate();
    list.insertAsLast(10);
    list.uniquify();
    ASSERT_EQ(1, list.getSize());
}

TEST_F(ListTest, search) {
    List<int> list;
    list.insertAsFirst(10);
    list.insertAsLast(11);
    ASSERT_EQ(11, list.search(11)->data);
}

TEST_F(ListTest, insertionSort) {
    List<int> list;
    list.insertAsFirst(11);
    list.insertAsLast(10);
    list.insertAsLast(8);
    list.insertAsLast(9);
    list.sort();
    ASSERT_EQ(11, list[list.size() - 1]->data);

}

TEST_F(ListTest, selectionSort) {
    List<int> list;
    list.insertAsFirst(11);
    list.insertAsLast(10);
    list.insertAsLast(8);
    list.insertAsLast(9);
    list.selectionSort(list.first(), list.size());
    ASSERT_EQ(11, list[list.size() - 1]->data);

}