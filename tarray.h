#pragma once

namespace Tmpl8 {

	template <typename T>
	class Array {
		T* items;
		size_t length;

	public:
		int counter = 1;
		Array() : items(nullptr), length(0) { }

		Array(size_t length) : length(length) {
			items = (T*)MALLOC64(length * sizeof(T)); 
		}
		
		Array(size_t length, T* vals) : length(length) {
			items = (T*)MALLOC64(length * sizeof(T));
			for (int i = 0; i < length; i++) {
				items[i] = vals[i];
			}
		}
		
		Array(Array& other) {
			items = other.items;
			length = other.length;
			counter = ++other.counter;
		}

		Array& operator=(Array& other) {
			if (this != &other) {
				items = other.items;
				length = other.length;
				counter = ++other.counter;
			}
			return *this;
		}
		
		~Array() {
			counter--;
			if (counter != 0) return;

			Clear();
		}

		T& operator[](size_t index) {
			return items[index];
		}

		const T& operator[](size_t index) const {
			return items[index];
		}

		inline T& At(size_t index) const {
			return items[index];
		}

		inline size_t GetLength() const {
			return length;
		}

		void Clear() {
			if (length > 0 && items != nullptr) {
				FREE64(items);
			}
			length = 0;
		}
	};

	using IntArray = Array<int>;
}
