#pragma once

template <typename T>
struct Vector2 {
	// union allows for the same memory location to be accessed with different names
	union {
		struct {
			T x, y;
		};
		T arr[2];
	};

	// constructor that initializes x and y to provided values, or 0 if not provided
	Vector2(T x = 0, T y = 0) {
		this->x = x; this->y = y;
	};

	__forceinline Vector2<T> lerp(Vector2<T> target, float pct) {
		return Vector2<T>((this->x + (target.x - this->x) * pct), (this->y + (target.y - this->y) * pct));
	}

	Vector2<int> ToInt() {
		return Vector2<int>(x, y);
	}

	Vector2<float> toFloat() {
		return Vector2<float>(x, y);
	}
};