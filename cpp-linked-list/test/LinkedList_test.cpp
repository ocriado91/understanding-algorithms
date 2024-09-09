#include "gtest/gtest.h"
#include "../src/LinkedList.hpp"

TEST(LinkedListTest, OneSizeTest) {
    ListNode* list = new ListNode(1);
    ASSERT_EQ(list->size(), 0);
}

TEST(LinkedListTest, SizeTest) {
    ListNode* list = new ListNode(1);
    list->append(2);
    list->append(3);

    ASSERT_EQ(list->size(), 2);
}

TEST(LinkedListTest, InsertTest) {
    ListNode* list = new ListNode(1);
    list->append(2);
    list->append(3);

    list->insert(10, 1);

    ASSERT_EQ(list->size(), 3);
    ASSERT_EQ(list->toString(), "[1;10;2;3]");
}

TEST(LinkedListTest, RemoveTest) {
    ListNode* list = new ListNode(1);
    list->append(2);
    list->append(3);

    list->remove(1);

    ASSERT_EQ(list->size(), 1);
    ASSERT_EQ(list->toString(), "[1;3]");
}

TEST(LinkedListTest, MergeTest) {
    std::vector<int> list1_data{1, 3, 5};
    std::vector<int> list2_data{2, 4, 6};

    ListNode* list1 = vector2ListNode(list1_data);
    ListNode* list2 = vector2ListNode(list2_data);

    ListNode* mergedList = mergeTwoList(list1, list2);

    ASSERT_EQ(mergedList->size(), 5);
    ASSERT_EQ(mergedList->toString(), "[1;2;3;4;5;6]");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}