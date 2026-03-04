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


TEST(SuperPuperLongNumberTest, Addition) {
    mal::LongNumber num1("123");
    mal::LongNumber num2("456");
    mal::LongNumber num3("999");
    mal::LongNumber num4("1");
	mal::LongNumber num5("500");
	mal::LongNumber num6("-300");
    mal::LongNumber num7("-500");

    mal::LongNumber result1 = "579";
    EXPECT_TRUE(num1 + num2 == result1) << "Ошибка при сложении без переноса";
    
    mal::LongNumber result2 = "1000";
    EXPECT_TRUE(num3 + num4 == result2) << "Ошибка при сложении с переносом";
    
    mal::LongNumber result3 = "200";
    EXPECT_TRUE(num5 + num6 == result3) << "Ошибка при сложении со вторым отрицательным числом (вычитание)";

    mal::LongNumber result4 = "200";
    EXPECT_TRUE(num6 + num5 == result4) << "Ошибка при сложении с первым отрицательным числом (вычитание)";

    mal::LongNumber result5 = "-800";
    EXPECT_TRUE(num6 + num7 == result5) << "Ошибка при сложении двух отрицительных";
}

TEST(SuperPuperLongNumberTest, Subtration) {
    mal::LongNumber num1("123");
    mal::LongNumber num2("456");
    mal::LongNumber num3("1000");
    mal::LongNumber num4("1");
	mal::LongNumber num5("500");
    mal::LongNumber num6("500");
	mal::LongNumber num7("-300");
    mal::LongNumber num8("-500");
    mal::LongNumber num9("-500");

    mal::LongNumber result1 = "333";
    EXPECT_TRUE(num2 - num1 == result1) << "Ошибка при вычитании без заимствования";
    
    mal::LongNumber result2 = "999";
    EXPECT_TRUE(num3 - num4 == result2) << "Ошибка при вычитании с заимствованием";
    
    mal::LongNumber result3 = "-333";
    EXPECT_TRUE(num1 - num2 == result3) << "Ошибка при вычитании чисел одинаковой длины с отрицательным результатом";

    mal::LongNumber result4 = "0";
    EXPECT_TRUE(num5 - num6 == result4) << "Ошибка при вычитании одинаковых положительных чисел";

    mal::LongNumber result5 = "0";
    EXPECT_TRUE(num8 - num9 == result5) << "Ошибка при вычитании одинаковых отрицательных чисел";

    mal::LongNumber result6 = "800";
    EXPECT_TRUE(num6 - num7 == result6) << "Ошибка при вычитании со вторым отрицательным числом (сложение)";

    mal::LongNumber result7 = "-800";
    EXPECT_TRUE(num7 - num6 == result7) << "Ошибка при вычитании со первым отрицательным числом";

    mal::LongNumber result8 = "200";
    EXPECT_TRUE(num7 - num8 == result8) << "Ошибка при вычитании двух отрицательных a>b";
    
    mal::LongNumber result9 = "-200";
    EXPECT_TRUE(num8 - num7 == result9) << "Ошибка при вычитании двух отрицательных a<b";

    mal::LongNumber result10 = "-999";
    EXPECT_TRUE(num4 - num3 == result10) << "Ошибка при вычитании чисел разной длины с отрицательным результатом";
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


