#include <gtest/gtest.h>

#include "super_puper_long_numbers.hpp"

TEST(SuperPuperLongNumberTest, Equal) {
    mal::LongNumber num1("123");
    mal::LongNumber num2("123");
    mal::LongNumber num3("456");
    mal::LongNumber num4("-123");
    mal::LongNumber num5("-123");
	mal::LongNumber num6("124");
	mal::LongNumber num7("12");

    EXPECT_TRUE(num1 == num2) << "Одинаковые положительные числа должны быть равны";
    
    EXPECT_FALSE(num1 == num3) << "Разные числа не должны быть равны";
    
    EXPECT_FALSE(num1 == num4) << "Числа с разными знаками не должны быть равны";
    
    EXPECT_TRUE(num4 == num5) << "Одинаковые отрицательные числа должны быть равны";

	EXPECT_FALSE(num1 == num6) << "Разные числа не должны быть равны";
    
	EXPECT_FALSE(num1 == num7) << "Числа разной длины не должны быть равны";
}

TEST(SuperPuperLongNumberTest, NotEqual) {
    mal::LongNumber num1("123");
    mal::LongNumber num2("123");
    mal::LongNumber num3("456");
    mal::LongNumber num4("-123");
	mal::LongNumber num5("124");
	mal::LongNumber num6("45");

    
    EXPECT_FALSE(num1 != num2) << "Одинаковые числа должны давать false для !=";

    EXPECT_TRUE(num1 != num3) << "Разные числа должны давать true для !=";

    EXPECT_TRUE(num1 != num4) << "Одинаковые числа с разными знаками должны давать true для !=";

	EXPECT_TRUE(num1 != num5) << "Разные числа должны давать true для !=";

	EXPECT_TRUE(num1 != num6) << "Числа разной длины не должны быть равны";
}

TEST(SuperPuperLongNumberTest, Greater) {
    mal::LongNumber num1("3457");
    mal::LongNumber num2("3456");
    mal::LongNumber num3("-3456");
    mal::LongNumber num4("456");
    mal::LongNumber num5("3457");
    mal::LongNumber num6("-3451");
    mal::LongNumber num7("-3457");
    mal::LongNumber num8("-456");

    EXPECT_TRUE(num1 > num2) << "Положительное число должно быть больше другого положительного (одна длина)";
    
    EXPECT_FALSE(num2 > num1) << "Меньшее положительное не должно быть больше большего";
    
    EXPECT_TRUE(num1 > num3) << "Положительное число должно быть больше отрицательного (равные по модулю)";
    
    EXPECT_FALSE(num4 > num5) << "Число с меньшей длиной не должно быть больше числа с большей длиной";
    
    EXPECT_TRUE(num6 > num7) << "Отрицательное число должно быть больше другого отрицательного (ближе к нулю)";
    
    EXPECT_TRUE(num8 > num7) << "Отрицательное число с меньшей длиной должно быть больше отрицательного с большей длиной";
    
    EXPECT_FALSE(num2 > num2) << "Число не должно быть больше самого себя";
}

TEST(SuperPuperLongNumberTest, Less) {
    mal::LongNumber num1("3456");
    mal::LongNumber num2("3457");
    mal::LongNumber num3("-3456");
    mal::LongNumber num4("-3459");
    mal::LongNumber num5("-3456");
    mal::LongNumber num6("-456");
    mal::LongNumber num7("-3457");
    mal::LongNumber num8("123");

    EXPECT_TRUE(num1 < num2) << "Меньшее положительное должно быть меньше большего (одна длина)";
    
    EXPECT_FALSE(num2 < num1) << "Большее положительное не должно быть меньше меньшего";
    
    EXPECT_FALSE(num1 < num3) << "Положительное число не должно быть меньше отрицательного";
    
    EXPECT_TRUE(num4 < num5) << "Отрицательное число должно быть меньше другого отрицательного (дальше от нуля)";
    
    EXPECT_FALSE(num6 < num7) << "Отрицательное число с меньшей длиной не должно быть меньше отрицательного с большей длиной";
    
    EXPECT_TRUE(num3 < num8) << "Отрицательное число должно быть меньше положительного";
    
    EXPECT_FALSE(num1 < num1) << "Число не должно быть меньше самого себя";
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}