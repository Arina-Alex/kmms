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
    while (str[total_len] != '\0') total_len++;
    
    if (digits_count == 0) {
		length = 1;
		numbers = new int[length];
		numbers[0] = 0;
		sign = 0;
		return;
	}

	int str_len = get_length(str);
	int start = 0;
	sign = 1;

	if (str[0] == '-') {
		sign = -1;
		start = 1;
		str_len += 1;
	} else if (str[0] == '+') {
		sign = 1;
		start = 1;
		str_len += 1;
	}
	
	while (start < str_len && str[start] == '0') {
		start++;
	}

	if (start == str_len) {
		length = 1;
		numbers = new int[length];
		numbers[0] = 0;
		sign = 0;
		return;
	}
	
	length = str_len - start;
	numbers = new int[length];
	
	for (int i = 0; i < length; i++) {
		char a = str[str_len - 1 - i]; 
		numbers[i] = a - '0';	
	}
	
	
	
	// int digits_count = get_length(str);  
    // int total_len = 0;
    // while (str[total_len] != '\0') {
	// 	total_len++;
	// }
    // if (digits_count == 0) {
	// 	length = 1;
	// 	numbers = new int[length];
	// 	numbers[0] = 0;
	// 	sign = 0;
	// 	return;
	// }

	// int start = 0;
	// sign = 1;

	// if (str[0] == '-') {
	// 	sign = -1;
	// 	start = 1;
	// } else if (str[0] == '+')
	// {
	// 	sign = 1;
	// 	start = 1;
	// }
	
    // while (start < total_len && str[start] == '0') {
    //     start++;
    // }

    // if (start == total_len) {
    //     length = 1;
    //     numbers = new int[length];
    //     numbers[0] = 0;
    //     sign = 0;
    //     return;
    // }

    // length = total_len - start;
	// numbers = new int[length];
    // for (int i = 0; i < length; i++) {
    //     char a = str[total_len - 1 - i]; 
    //     numbers[i] = a - '0';	
    // }
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

LongNumber LongNumber::operator -() const {
	LongNumber result(*this);
	if (result.sign != 0) {
		result.sign = -result.sign;
	}
	return result;
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
	if (sign != x.sign) {
		if (sign == 0) return x;
		if (x.sign == 0) return *this;

		if (sign > 0 && x.sign < 0) {
			return *this - (-x);
		} else {
            return x - (-*this); 
        }
	}

	if (sign == 0) return *this;

	LongNumber result = add_abs(*this, x);
	result.sign = sign;
	return result;
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
	int comp = compare_abs(x);

	if (sign != x.sign) {	
		if (sign > 0 && x.sign < 0) {
			LongNumber result = add_abs(*this, x);
			result.sign = 1;
			return result;
		} else if (sign < 0 && x.sign > 0) {
			LongNumber result = add_abs(*this, x);
			result.sign = -1;
			return result;
		}
	}
	if (x.sign == 0) return *this;
	if (sign == 0) return -x;
	
	if (comp > 0) {
		LongNumber result = sub_abs(*this, x);
		result.sign = sign;
		return result;
	} else if (comp == -1) {
		LongNumber result = sub_abs(x, *this);
		result.sign = -(x.sign);
		return result;
	} else {
		return LongNumber("0");
	}
}

bool LongNumber::is_negative() const noexcept {
    return sign == -1;
	
}

LongNumber LongNumber::add_abs (const LongNumber& a, const LongNumber& b) {
	int max_len = a.length;
	if (b.length > max_len) {
		max_len = b.length;
	}
	LongNumber result(max_len + 1, 1);

	int carry = 0;
	int num_a, num_b;

	for (int i = 0; i < max_len; i++) {
		if (i < a.length) {
			num_a = a.numbers[i];
		} else {
			num_a = 0;
		}
		 
		if (i < b.length) {
			num_b = b.numbers[i];
		} else {
			num_b = 0;
		}
		int sum = num_a + num_b + carry;
		result.numbers[i] = sum % 10;
		carry = sum / 10;
	}
	if (carry > 0) {
		result.numbers[max_len] = carry;
	} else {
		result.length = max_len;
	}
	return result;
}

LongNumber LongNumber::sub_abs (const LongNumber& a, const LongNumber& b) {
	LongNumber result(a.length, 1);
	
	int borrow = 0;
	int num_a, num_b;

	for (int i = 0; i < a.length; i++) {
		num_a = a.numbers[i];
		if (b.length > i) {
			num_b = b.numbers[i];
		} else {
			num_b = 0;
		}

		int diff = num_a - num_b - borrow;
		if (diff < 0) {
			diff += 10;
			borrow = 1;
		} else {
			borrow = 0;
		}

		result.numbers[i] = diff;
	}

	int real_length = a.length;
		for (int i = a.length - 1; i > 0; i--) {
			if (result.numbers[i] == 0) {
				real_length--;
			} else {
				break;
			}
		}
		
    if (real_length != a.length) {
        LongNumber normalized(real_length, 1);
        for (int i = 0; i < real_length; i++) {
            normalized.numbers[i] = result.numbers[i];
        }
        return normalized;
    }

	return result;

}

int LongNumber::compare_abs(const LongNumber& x) const {
	if (length > x.length) return 1;
	if (length < x.length) return -1;
	for (int i = length - 1; i >= 0; i--) {
		if (numbers[i] > x.numbers[i]) return 1;
		if (numbers[i] < x.numbers[i]) return -1;
	}
	return 0;
}

int LongNumber::get_length(const char* const str) const noexcept {
	if (!str) return 0;

	int i = 0;
	int len = 0;
	if (str[0] == '-' or str[0] == '+') {
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