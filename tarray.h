#pragma once

namespace Tmpl8 {

	template <typename T>
	class UniquePtr {
	public:
		T* ptr;

		UniquePtr(T* in) {
			ptr = in;
		}

		UniquePtr() : ptr(nullptr) {

		}

		UniquePtr(const UniquePtr& other) = delete;
		UniquePtr& operator=(const UniquePtr& other) = delete;

		UniquePtr& operator=(UniquePtr&& other) {
			if (this != &other) {
				if (ptr) delete ptr;
				ptr = other.ptr;
				other.ptr = nullptr;
			}
			return *this;
		}

		UniquePtr& operator=(T* other) {
			ptr = other;
			return *this;
		}

		UniquePtr(UniquePtr&& other) : ptr(other.ptr) {
			other.ptr = nullptr;
		}
		
		void Reset() {
			delete ptr;
			ptr = nullptr;
		}

		T& operator*() {
			return *ptr;
		}

		T* operator->() {
			return ptr;
		}

		~UniquePtr() {
			delete ptr;
		}
	};

	template <typename T>
	class Array {
	public:
		T* items;
		size_t length;

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

	 	virtual void Clear() {
			if (length > 0 && items != nullptr) {
				FREE64(items);
			}
			length = 0;
		}
	};

	template <typename T>
	class PtrArray : public Array<T*> {
	public:
		PtrArray() : Array() { }
		PtrArray(size_t length) : Array(length) { }
		PtrArray(size_t length, T** vals) : Array(length, vals) { }
		PtrArray(PtrArray& other) : Array(other) { }

		void Clear() override {
			if (length > 0 && items != nullptr) {
				delete[] items;
			}
			length = 0;
		}
	};

	using IntArray = Array<int>;
}
