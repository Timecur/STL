#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <assert.h>

using namespace std;

inline void SafeRelease(char* s){
	if (s != nullptr)
	{
		delete[]s;
		s = nullptr;
	}
}

class MyString{
public:
	typedef char* Iterator;

public:
	MyString::MyString(const char* str = "")
	{
		if (nullptr == str){
			assert(false);
			return;
		}

		_size = myStrlen(str);
		_capacity = _size;
		_str = new char[_capacity + 1];
		myStrcpy(_str, str);
	}
	MyString::MyString(const MyString& str)
		:_str(new char[str._capacity + 1])
		, _size(str._size)
		, _capacity(str._capacity)
	{
		myStrcpy(_str, str._str);
	}
	MyString& operator=(const MyString& str);
	MyString& operator+(const MyString& str);
	MyString::~MyString()
	{
		if (nullptr != _str){
			delete[] _str;
			_str = nullptr;
		}

	}
	Iterator Begin();
	Iterator End();

	void Push_back(char c);
	void Pop_back();
	void Append(size_t n, char c);
	void Append(const char* str);

	MyString& operator+=(char c);
	MyString& operator+=(const char* str);
	void Clear();
	void Swap(MyString& str);
	const char* C_str()const;
	size_t Size()const;
	size_t Capacity()const;
	bool Empty()const;
	void Resize(size_t newSize, char c = char());
	void Reserve(size_t newCapacity);

	char& operator[](size_t index);
	const char& operator[](size_t index)const;
	bool operator<(const MyString& s);
	bool operator<=(const MyString& s);
	bool operator>(const MyString& s);
	bool operator>=(const MyString& s);
	bool operator==(const MyString& s);
	bool operator!=(const MyString& s);
	
	size_t Find(const char c, size_t pos = 0) const;
	// 返回子串s在string中第一次出现的位置
	size_t Find(const char* s, size_t pos = 0) const;
	// 截取string从pos位置开始的n个字符
	MyString SubStr(size_t pos, size_t n);
	// 在pos位置上插入字符c/字符串str，并返回该字符的位置
	MyString& Insert(size_t pos, char c);
	MyString& Insert(size_t pos, const char* str);
	// 删除pos位置上的元素，并返回该元素的下一个位置
	MyString& Erase(size_t pos, size_t len);
private:
	friend ostream& operator<<(ostream& o, MyString& str);
	friend istream& operator >> (istream& is, MyString& ss);
	friend int IndexKMP(const char* S, const char* T);
	friend void GetNext(string T, int* next);

private:
	int myStrlen(const char* str);
	char* myStrcpy(char* dest, const char* src);

private:
	char* _str;
	size_t _capacity;
	size_t _size;

};
