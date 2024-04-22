#ifndef _SORT_H
#define _SORT_H
#include <algorithm>

template<typename T>
void simple_sort(T* a, size_t n) {
	for (size_t i = 0; i < n - 1; i++) {
		for (size_t j = i + 1; j < n; j++) {
			if (a[i] > a[j]) {
				std::swap(a[i], a[j]);
			}
		}
	}
}

template<typename T>
void choose_sort(T* a, size_t n) {
	for (size_t i = 0; i < n - 1; i++) {
		T min = a[i];
		size_t min_index = i;
		for (size_t j = i + 1; j < n; j++) {
			if (a[j] < min) {
				min = a[j];
				min_index = j;
			}
		}
		a[min_index] = a[i];
		a[i] = min;
	}
}

template<typename T>
void insertion_sort(T* a, size_t n) {
	for (size_t i = 1; i < n; i++) {
		T curr = a[i];
		size_t j = i - 1;

		while (j >= 0 && a[j] > curr) {
			a[j + 1] = a[j];
			j--;
		}

		a[j + 1] = curr;
	}
}

template<typename T>
void Bubble_sort(T* a, size_t n) {
	for (size_t i = 0; i < n - 1; i++) { 
		for (size_t j = 0; j < n - i - 1; j++) { 
			if (a[j + 1] < a[j]) {
				std::swap(a[j], a[j + 1]);
			}
		}
	}
}

template<typename T>
void merge(T* a, size_t left, size_t middle, size_t right) {
	size_t n1 = middle - left + 1;
	size_t n2 = right - middle;

	T* L = new T[n1];
	T* R = new T[n2];

	for (size_t i = 0; i < n1; i++)
		L[i] = a[left + i];
	for (size_t i = 0; i < n2; i++)
		R[i] = a[middle + 1 + i];

	size_t i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j])
			a[k++] = L[i++];
		else
			a[k++] = R[j++];
	}

	while (i < n1) a[k++] = L[i++];
	while (j < n2) a[k++] = R[j++];

}

template<typename T>
void merge_sort(T* a, size_t left, size_t right) {
	if (left < right) {
		size_t middle = left + (right - left) / 2;
		merge_sort(a, left, middle);
		merge_sort(a, middle + 1, right);
		merge(a, left, middle, right);
	}
}

template<typename T>
void QuickSort(T* a, size_t n) {
	if (n <= 1) return;
	size_t i = 0, j = n - 1;
	T pivot = a[n / 2]; 
	while (i <= j) {
		while (a[i] < pivot) i++; 
		while (a[j] > pivot) j--;
		if (i <= j) {
			std::swap(a[i], a[j]); 
			i++;
			j--;
		}
	}
	if (j > 0) QuickSort(a, j + 1); 
	if (i < n) QuickSort(a + i, n - i); 
}

template<typename T>
void CountingSort(T* a, size_t n) {
	if (n <= 1)return;
	T min_val = *std::min_element(a, a + n);
	T max_val = *std::max_element(a, a + n);
	size_t range = max_val - min_val + 1;
	size_t* count = new size_t[range]();

	for (size_t i = 0; i < n; ++i) {
		++count[a[i] - min_val];
	}
	size_t index = 0;
	for (size_t i = 0; i < range; ++i) {
		for (size_t j = 0; j < count[i]; ++j) {
			a[index++] = static_cast<T>(i + min_val);
		}
	}
}

#endif 