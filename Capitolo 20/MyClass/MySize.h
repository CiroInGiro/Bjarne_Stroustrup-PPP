#pragma once

template<typename T>
// requires T()
size_t MySize() {
	T* p = new T[2];
	T* p1 = &p[0];
	T* p2 = &p[1];
	size_t diff = &p2 - &p1;
	p2 = p1 = nullptr;
	delete[] p;
	return diff;
}
