#pragma once
#include<string>

template<typename T>
class cHas
{
public:
	size_t operator() (const T&key) const;
};

template<typename T>
inline size_t cHas<T>::operator()(const T & key) const
{
	size_t bytes = sizeof(key);
	size_t res = 0;
	for (size_t i = 0; i < bytes; ++i)
	{
		unsigned char b = *((unsigned char*)&key + i);
		res += b;
	}
	return res;
}


template<>
class cHas<std::string>
{
public:
	size_t operator() (const std::string&key) const;
};

inline size_t cHas<std::string>::operator()(const std::string & key) const
{
	size_t res = 0;
	for (size_t i = 0; i < key.size(); ++i)
	{
		res += (unsigned char)key[i];
	}
	return res;
}
