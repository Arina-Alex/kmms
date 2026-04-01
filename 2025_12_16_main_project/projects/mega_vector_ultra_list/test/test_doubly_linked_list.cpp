#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

using mal::DoublyLinkedList;

TEST(DoublyLinkedListTest, Constructor) {
    DoublyLinkedList<int> list;
    EXPECT_EQ(list.get_size(), 0);
}

TEST(DoublyLinkedListTest, HasItem) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(25);
	
    EXPECT_TRUE(list.has_item(10)) << "Ошибка при has_item int";
    EXPECT_TRUE(list.has_item(25)) << "Ошибка при has_item int";
    EXPECT_FALSE(list.has_item(40)) << "Ошибка при has_item int";
}

TEST(DoublyLinkedListTest, PushBack) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(25);
    list.push_back(40);
    
    EXPECT_EQ(list.get_size(), 3) << "Ошибка при push_back int";
    EXPECT_TRUE(list.has_item(25)) << "Ошибка при push_back int";
    EXPECT_FALSE(list.has_item(38)) << "Ошибка при push_back int";
}

TEST(DoublyLinkedListTest, RemoveFirst) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(25);
    list.push_back(40);
	list.push_back(25);
 
    EXPECT_TRUE(list.remove_first(25)) << "Ошибка при remove_first int middle";
    EXPECT_EQ(list.get_size(), 3) << "Ошибка при remove_first int middle";
    EXPECT_TRUE(list.has_item(25)) << "Ошибка при remove_first int middle"; 
    
    EXPECT_TRUE(list.remove_first(10)) << "Ошибка при remove_first int beginning";
    EXPECT_EQ(list.get_size(), 2) << "Ошибка при remove_first int beginning";
    EXPECT_FALSE(list.has_item(10)) << "Ошибка при remove_first int beginning";
    
    EXPECT_TRUE(list.remove_first(25)) << "Ошибка при remove_first int end";
    EXPECT_EQ(list.get_size(), 1) << "Ошибка при remove_first int end";
    
    EXPECT_TRUE(list.remove_first(40)) << "Ошибка при remove_first int один элемент";
    EXPECT_EQ(list.get_size(), 0) << "Ошибка при remove_first int один элемент";
    
    EXPECT_FALSE(list.remove_first(100)) << "Ошибка при remove_first int пустой список";
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
