#include "MyString.h"

	

	

	/*
	MyString::MyString& operator=(const MyString& s)
	{
		if (this != &s)
		{
			char* pStr = new char[str._capacity + 1];
			strcpy(pStr, s._str);
			delete[] _str;
			_str = pStr;
			_size = str._size;
			_capacity = str._capacity;
		}
		return *this;
	}
	*/
	
	MyString& MyString::operator=(const MyString& str){
		if (this != &str){
			MyString str_tmp(str);
			swap(_str, str_tmp._str);
			
			_size = str._size;
			_capacity = str._capacity;
		}

		return *this;
	}

	MyString& MyString::operator+(const MyString& str){
		assert(nullptr != _str && nullptr != str._str);

		int size = myStrlen(_str) + myStrlen(str._str) + 1;
		char* res = new char[size];
		memset(res, '\0', size);
		char* pres = res;
		
		char* ret = _str;
		const char* tmp = str._str;
		
		while (*ret != '\0'){
			*pres = *ret;
			pres++;
			ret++;
		}
		while (*tmp != '\0'){
			*pres = *tmp;
			pres++;
			tmp++;
		}

		delete[] _str;
		_str = nullptr;
		_str = new char[size];
		if (nullptr != res)
			myStrcpy(_str, res);
		
		delete[] res;
		res = nullptr;

		return *this;
	}

	

	MyString::Iterator MyString::Begin(){
		return _str;
	}

	MyString::Iterator MyString::End(){
		return _str + _size;
	}

	void MyString::Push_back(char c){
		if (_size == _capacity)
			Reserve(_capacity * 2);
		
		_str[_size++] = c;
		_str[_size] = '\0';
	}

	void MyString::Pop_back(){
		assert(_size > 0);
		_str[_size] = '\0';
	}

	void MyString::Append(size_t n, char c){
		for (size_t i = 0; i < n; ++i)
			Push_back(c);
	}

	void MyString::Append(const char* str){
		assert(nullptr != str);
		for (int i = 0; i < myStrlen(str); ++i){
			Push_back(str[i]);
		}
	}

	MyString& MyString::operator+=(char c){
		Push_back(c);
		return *this;
	}

	MyString& MyString::operator+=(const char* str){
		assert(nullptr != str);
		Append(str);
		return *this;
	}

	void MyString::Clear(){
		_size = 0;
		_str[_size] = '\0';
	}

	void MyString::Swap(MyString& str){
		swap(_str, str._str);
		swap(_size, str._size);
		swap(_capacity, str._capacity);
	}

	const char* MyString::C_str()const{
		return _str;
	}

	size_t MyString::Size()const{
		return _size;
	}

	size_t MyString::Capacity()const{
		return _capacity;
	}

	bool MyString::Empty()const{
		return 0 == _size;
	}

	void MyString::Resize(size_t newSize, char c){
		if (newSize > _size){
			if (newSize > _capacity){
				Reserve(newSize);
			}
			memset(_str + _size, c, newSize - _size);
		}
		_size = newSize;
		_str[newSize] = '\0';
	}

	void MyString::Reserve(size_t newCapacity){
		if (_capacity < newCapacity){
			char* str = new char[newCapacity+1];
			myStrcpy(str, _str);
	
			delete _str;
			_str = str;
			_capacity = newCapacity;
		}
	}

	char& MyString::operator[](size_t index){
		assert(index < _size);
		return _str[index];
	}

	const char& MyString::operator[](size_t index)const{
		assert(index < _size);
		return _str[index];
	}

	bool MyString::operator<(const MyString& s){
		char* sret = _str;
		char* stmp = s._str;

		while ('\0' != *sret++ && '\0' != *stmp++){
			if (*sret > *stmp)
				return false;
			else if (*sret < *stmp)
				return true;
		}
		return _size < s._size;
	}
	
	bool MyString::operator<=(const MyString& s){
		char* sret = _str;
		char* stmp = s._str;

		while ('\0' != *sret++ && '\0' != *stmp++){
			if (*sret > *stmp)
				return false;
			else if (*sret < *stmp)
				return true;
		}
		return _size <= s._size;
	}
	
	bool MyString::operator>(const MyString& s){
		char* sret = _str;
		char* stmp = s._str;

		while ('\0' != *sret++ && '\0' != *stmp++){
			if (*sret < *stmp)
				return false;
			else if (*sret > *stmp)
				return true;
		}
		return _size > s._size;
	}

	bool MyString::operator>=(const MyString& s){
		char* sret = _str;
		char* stmp = s._str;

		while ('\0' != *sret++ && '\0' != *stmp++){
			if (*sret < *stmp)
				return false;
			else if (*sret > *stmp)
				return true;
		}
		return _size >= s._size;
	}

	bool MyString::operator==(const MyString& s){
		char* sret = _str;
		char* stmp = s._str;

		while ('\0' != *sret++ && '\0' != *stmp++){
			if (*sret != *stmp)
				return false;
		}
		return _size == s._size;
	}

	bool MyString::operator!=(const MyString& s){
		return !(*this == s);
	}

	size_t MyString::Find(const char c, size_t pos) const{
		assert(pos >= 0);
		for (int i = pos; i < _size; ++i)
			if (c == _str[i])
				return i+1; // 因为下标从0开始
		return -1;
	}

	size_t MyString::Find(const char* s, size_t pos) const{
		assert(pos >= 0);
		return IndexKMP(_str + pos, s);
	}

	void GetNext(string T, int* next)
	{
		int i = 0, j = -1;
		next[0] = -1;

		// 前缀是固定的，后继是相对的
		while (i < T.size()){
			if (-1 == j || T[i] == T[j]){
				if (T[++i] != T[++j]){
					next[i] = next[j];
				}
				else{
					next[i] = j;
				}
			}
			else{
				j = next[j];
			}
		}
	}

	int IndexKMP(const char* S,const char* T)
	{
		int i = 0;
		int j = 0;
		int s_len = strlen(S);
		int t_len = strlen(T);
		int *next = new int[t_len + 1];

		GetNext(T, next);

		while (i < s_len && j < t_len){
			if (-1 == j || S[i] == T[j]){
				++i;
				++j;
			}
			else{
				j = next[j];
			}
		}

		delete[] next;
		if (j == t_len){
			return i - t_len;
		}
		else{
			return 0;
		}
	}

	MyString MyString::SubStr(size_t pos, size_t n){
		MyString str;
		for (int i = pos; i < _size && i < n; ++i){
			str.Push_back(_str[i]);
		}
		return str;
	}

	MyString& MyString::Insert(size_t pos, char c){
		assert(pos <= _size);
			
		char* str = new char[_size+1];
		myStrcpy(str, _str);

		if (_size + 1 > _capacity)
			Reserve(_size + 1);

		_str[pos] = c;
		_str[pos+1] = '\0';
		strcat(_str, str+pos);

		SafeRelease(str);
		return *this;
	}

	MyString& MyString::Insert(size_t pos, const char* str){
		assert(pos <= _size);
		char* str1 = new char[pos + 1];
		strncpy_s(str1,pos+1, _str, pos);
		
		char* str2 = new char[_size - pos + 1];
		strncpy_s(str2, _size-pos+1, _str + pos, _size-pos);

		if (_size + myStrlen(str) > _capacity)
			Reserve(_size + myStrlen(str)+1);

		myStrcpy(_str, str1);
		
		/*
		     这里不能直接用Append,因为此对象的size依然是原字符串长度,所以是在size后追加字符串。
			 此处是每次更新size来解决
	    */
		_size = myStrlen(_str);
		this->Append(str);
		
		//_size = myStrlen(_str);
		this->Append(str2);
		
		SafeRelease(str1);
		SafeRelease(str2);
		_size += myStrlen(str);

		return *this;
	}

	MyString& MyString::Erase(size_t pos, size_t len){
		assert(pos <= _size);

		char* str = new char[_size+1];

		if (pos + len < _size){
			myStrcpy(str, _str + pos + len-1);
			
		}
		_str[pos - 1] = '\0';
		strcat(_str, str);
		_size = myStrlen(_str);

		SafeRelease(str);
		return *this;
	}


	ostream& operator<<(ostream& o, MyString& str){
			if (nullptr == str._str)
				return o;
			return o << str._str;
	}

	istream& operator >> (istream& is, MyString& ss) // 输入时请勿包含空格
	{
		ss.Clear();
		is >> ss._str;

		ss._size = static_cast<unsigned>(strlen(ss._str));

		return is;
	}

	int MyString::myStrlen(const char* str){
		const char* ret = str;
		while (*ret != '\0'){
			ret++;
		}
		return ret - str;
	}

	char* MyString::myStrcpy(char* dest, const char* src){
		assert(dest != nullptr && src != nullptr);
		char* ret = dest;
		const char* tmp = src;
		while (*tmp != '\0')
		{
			*ret = *tmp;
			ret++;
			tmp++;
		}
		*ret = '\0';
		return dest;
	}
