#include <gtest/gtest.h>

#include "vector.hpp"

using mal::Vector;

TEST(VectorTest, ConstructorAndSize) {
    Vector<int> v;
    EXPECT_EQ(v.get_size(), 0);
}

TEST(VectorTest, PushBack) {
	Vector<int> v;
	v.push_back(10);
	v.push_back(25);
	v.push_back(70);

	EXPECT_EQ(v.get_size(), 3) << "Ошибка при push_back int";
	EXPECT_TRUE(v.has_item(25)) << "Ошибка при push_back int";
	EXPECT_FALSE(v.has_item(40)) << "Ошибка при push_back int";

    Vector<double> v_double;
    v_double.push_back(3.14);
    v_double.push_back(2.718);

    EXPECT_EQ(v_double[0], 3.14) << "Ошибка при push_back double";
    EXPECT_EQ(v_double[1], 2.718) << "Ошибка при push_back double";
    
    Vector<std::string> v_string;
    v_string.push_back("Hello");
    v_string.push_back("World");

    EXPECT_EQ(v_string[0], "Hello") << "Ошибка при push_back string";
    EXPECT_EQ(v_string[1], "World") << "Ошибка при push_back string";
}

TEST(VectorTest, Insert) {
    Vector<int> v;
    v.push_back(25);
    v.push_back(70);
    
    bool result = v.insert(0, 10);
    
    EXPECT_TRUE(result) << "Ошибка при insert int beginning";
    EXPECT_EQ(v.get_size(), 3) << "Ошибка при insert int beginning";
    EXPECT_EQ(v[0], 10) << "Ошибка при insert int beginning";
    EXPECT_EQ(v[1], 25) << "Ошибка при insert int beginning";
    
    bool result_2 = v.insert(1, 20);
    
    EXPECT_TRUE(result_2) << "Ошибка при insert int middle";
    EXPECT_EQ(v.get_size(), 4) << "Ошибка при insert int middle";
    EXPECT_EQ(v[0], 10) << "Ошибка при insert int middle";
    EXPECT_EQ(v[1], 20) << "Ошибка при insert int middle";
    EXPECT_EQ(v[2], 25) << "Ошибка при insert int middle";
    
    bool result_3 = v.insert(3, 30);
    
    EXPECT_TRUE(result_3) << "Ошибка при insert int end";
    EXPECT_EQ(v.get_size(), 5) << "Ошибка при insert int end";
    EXPECT_EQ(v[2], 25) << "Ошибка при insert int end";
	EXPECT_EQ(v[3], 30) << "Ошибка при insert int end";
	EXPECT_EQ(v[4], 70) << "Ошибка при insert int end";

    bool result_4 = v.insert(6, 80);
    EXPECT_FALSE(result_4);
    EXPECT_EQ(v.get_size(), 5);  
    
}

TEST(VectorTest, HasItem) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(25);
    
    EXPECT_TRUE(v.has_item(25)) << "Ошибка при has_item int";
    EXPECT_FALSE(v.has_item(30)) << "Ошибка при has_item int";
}

TEST(VectorTest, RemoveFirst) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(25);
    v.push_back(70);
    v.push_back(25);
    v.push_back(40);
    
    bool result = v.remove_first(25);
    
    EXPECT_TRUE(result) << "Ошибка при remove_first int";
    EXPECT_EQ(v.get_size(), 4) << "Ошибка при remove_first int";
    EXPECT_EQ(v[0], 10) << "Ошибка при remove_first int";
    EXPECT_EQ(v[1], 70) << "Ошибка при remove_first int";
    EXPECT_EQ(v[2], 25) << "Ошибка при remove_first int";
    EXPECT_EQ(v[3], 40) << "Ошибка при remove_first int";
    
    bool result_2 = v.remove_first(38); 
    
    EXPECT_FALSE(result_2) << "Ошибка при remove_first int not exist";
    EXPECT_EQ(v.get_size(), 4) << "Ошибка при remove_first int not exist";
    EXPECT_EQ(v[0], 10) << "Ошибка при remove_first int not exist";
    EXPECT_EQ(v[1], 70) << "Ошибка при remove_first int not exist";
    EXPECT_EQ(v[2], 25) << "Ошибка при remove_first int not exist";
    EXPECT_EQ(v[3], 40) << "Ошибка при remove_first int not exist";
}

TEST(VectorTest, RemoveFirstEmptyVector) {
    Vector<int> v;
    
    bool result = v.remove_first(10);
    
    EXPECT_FALSE(result) << "Ошибка при remove_first int empty";
    EXPECT_EQ(v.get_size(), 0) << "Ошибка при remove_first int empty";
}

TEST(VectorTest, Capacity) {
    Vector<int> v;
    
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
    
    EXPECT_EQ(v.get_size(), 10) << "Ошибка при capacity больше начального";
    
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(v[i], i) << "Ошибка при capacity больше начального";
    }
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
