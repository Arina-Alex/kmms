#include "super_puper_long_numbers.hpp"

using mal::LongNumber;
		
LongNumber::LongNumber() {
	length = 1;
	sign = 0;
	numbers = new int[length];
	numbers[0] = 0;
}

LongNumber::LongNumber(int length, int sign) : length(length), sign(sign) {
	numbers = new int[length];
	for (int i = 0; i < length; i++){
		numbers[i] = 0;
	}
}

LongNumber::LongNumber(const char* const str) {
	int digits_count = get_length(str);  
    int total_len = 0;
    while (str[total_len] != '\0') {
		total_len++;
	}
    if (digits_count == 0) {
		length = 1;
		numbers = new int[length];
		numbers[0] = 0;
		sign = 0;
		return;
	}

	int start = 0;
	sign = 1;

	if (str[0] == '-') {
		sign = -1;
		start = 1;
	} else if (str[0] == '+')
	{
		sign = 1;
		start = 1;
	}
	
    while (start < total_len && str[start] == '0') {
        start++;
    }

    if (start == total_len) {
        length = 1;
        numbers = new int[length];
        numbers[0] = 0;
        sign = 0;
        return;
    }
    length = total_len - start;
	numbers = new int[length];
    for (int i = 0; i < length; i++) {
        char a = str[total_len - 1 - i]; 
        numbers[i] = a - '0';	
    }
}

LongNumber::LongNumber(const LongNumber& x) {
	length = x.length;
	sign = x.sign;
	numbers = new int[length];
	for (int i = 0; i < length; i++) {
		numbers[i] = x.numbers[i];
	}
}

 LongNumber::LongNumber(LongNumber&& x) {
 	length = x.length;
	sign = x.sign;
	numbers = x.numbers;
	x.numbers = nullptr;
}

LongNumber::~LongNumber() {
	delete[] numbers;
}

LongNumber& LongNumber::operator = (const char* const str) {
	int str_length = get_length(str);
	int start = 0;
	if (str[0] == '-') {
		sign = -1;
		length = str_length - 1;
		start = 1;
	} else {
		sign = 1;
		length = str_length;
	}

	delete[] numbers;
	numbers = new int[length];

	for (int i = 0; i < length; i++) {
		numbers[i] = str[str_length + start - 1 - i] - '0';
	}
	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if (this != &x) {
		delete[] numbers;
	
		length = x.length;
		sign = x.sign;
		numbers = new int[length];

		for (int i = 0; i < length; i++) {
			numbers[i] = x.numbers[i];
		}
	}
	return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	if (&x != this) {
		delete[] numbers;
		length = x.length;
		sign = x.sign;
		numbers = x.numbers;
		x.numbers = nullptr;
	}
	return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
	if (sign != x.sign) return false;
	if (length != x.length) return false;

	for (int i = 0; i < length; i++) {
		if (numbers[i] != x.numbers[i]) return false;
	}
	return true;
}

bool LongNumber::operator != (const LongNumber& x) const {
	return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
	if (sign > x.sign) {
		return true;
	} else if (sign < x.sign) {
		return false;
	} else if (sign == 0) return false;

	if (length > x.length) {
		return (sign > 0);
	} else if (length < x.length) {
		return (sign < 0);
	} else {
		for (int i = length - 1; i >= 0; i--) {
        	if (numbers[i] > x.numbers[i]) return (sign > 0);
        	if (numbers[i] < x.numbers[i]) return (sign < 0);
        }
	}
	return false;
}

bool LongNumber::operator < (const LongNumber& x) const {
	return x > *this;
}

int LongNumber::get_length(const char* const str) const noexcept {
	if (!str) return 0;

	int i = 0;
	int len = 0;
	if (str[0]=='-' or str[0]=='+') {
		i = 1;
	}
	while (str[i] >= '0' && str[i] <= '9') {
		len ++;
		i++;
	}
	return len;
}

namespace mal {
  std::ostream& operator << (std::ostream &os, const LongNumber& x) {
    if (x.sign == -1) os << '-';  
	for (int i = x.length - 1; i >= 0; i--){
            os << x.numbers[i];
        }
        return os;
    }
}