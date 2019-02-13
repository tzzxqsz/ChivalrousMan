#pragma once
#ifndef __CHASH_MAP__H__
#define  __CHASH_MAP__H__
#include"cHas.h"
#include<algorithm>
#include<utility>
#include<list>
#include<vector>
#include<iterator>
using namespace std;

#define ErrorStr "hash_map��С����Ϊ0"

/*
const_chash_map_iterator
cHash_Map��const������
*/
template<typename  HashMap>
class const_chash_map_iterator :public iterator<bidirectional_iterator_tag, typename HashMap::value_type>
{
public:
	using value_type = typename HashMap::value_type;
	using list_iterator_type = typename HashMap::ListType::const_iterator;

	const_chash_map_iterator();

	/*
	const_chash_map_iterator(size_t bucket,list_iterator_type iterator,const HashMap* Map);
	���캯����ʼ��hashMapͰ������hashMap��������hashMap����ָ��
	@Param��
	size_t bucket��hashMapͰ����
	list_iterator_type iterator��hashMap������
	HashMap* Map��hashMap����ָ��
	*/
	const_chash_map_iterator(size_t bucket, list_iterator_type iterator, HashMap* hashMap);

	const value_type& operator*() const;

	const value_type* operator->() const;

	//ǰ++
	const_chash_map_iterator<HashMap>& operator++();
	//��++
	const_chash_map_iterator<HashMap> operator++(int);

	//ǰ--
	const_chash_map_iterator<HashMap>& operator--();
	//��--
	const_chash_map_iterator<HashMap> operator--(int);

	bool operator==(const const_chash_map_iterator<HashMap>& rhs) const;

	bool operator!=(const const_chash_map_iterator<HashMap>& rhs) const;

	~const_chash_map_iterator();
protected:
	//hashMapͰ����
	size_t m_bucketIndex;

	//hashMap������
	list_iterator_type m_listIterator;

	//hashMap����ָ��
	HashMap* m_hashMap;

	//++
	void increment();

	//--
	void decrement();
};

template<typename HashMap>
const_chash_map_iterator<HashMap>::const_chash_map_iterator() :
	m_bucketIndex(0), m_listIterator(list_iterator_type()), m_hashMap(nullptr)
{
}

template<typename HashMap>
inline const_chash_map_iterator<HashMap>::const_chash_map_iterator(size_t bucket, list_iterator_type iterator, HashMap * hashMap) :
	m_bucketIndex(bucket), m_listIterator(iterator), m_hashMap(hashMap)
{
}

template<typename HashMap>
inline const typename const_chash_map_iterator<HashMap>::value_type & const_chash_map_iterator<HashMap>::operator*() const
{
	return *m_listIterator;
}

template<typename HashMap>
inline const typename const_chash_map_iterator<HashMap>::value_type * const_chash_map_iterator<HashMap>::operator->() const
{
	return &(*m_listIterator);
}

template<typename HashMap>
inline const_chash_map_iterator<HashMap>& const_chash_map_iterator<HashMap>::operator++()
{
	increment();
	return *this;
}

template<typename HashMap>
inline const_chash_map_iterator<HashMap> const_chash_map_iterator<HashMap>::operator++(int)
{
	const_chash_map_iterator<HashMap>* temp = this;
	increemnt();
	return *temp;
}

template<typename HashMap>
inline const_chash_map_iterator<HashMap>& const_chash_map_iterator<HashMap>::operator--()
{
	decrement();
	return *this;
}

template<typename HashMap>
inline const_chash_map_iterator<HashMap> const_chash_map_iterator<HashMap>::operator--(int)
{
	const_chash_map_iterator<HashMap>* temp = this;
	decrement();
	return *temp;
}

template<typename HashMap>
inline bool const_chash_map_iterator<HashMap>::operator==(const const_chash_map_iterator<HashMap>& rhs) const
{
	if (m_bucketIndex == rhs.m_bucketIndex&&m_listIterator == rhs.m_listIterator&&m_hashMap == rhs.m_hashMap)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename HashMap>
inline bool const_chash_map_iterator<HashMap>::operator!=(const const_chash_map_iterator<HashMap>& rhs) const
{
	return !(*this == rhs);
}

template<typename HashMap>
inline const_chash_map_iterator<HashMap>::~const_chash_map_iterator()
{

}

template<typename HashMap>
inline void const_chash_map_iterator<HashMap>::increment()
{
	++m_listIterator;
	auto& buckets = m_hashMap->m_Buckets;
	if (m_listIterator == std::end(buckets[m_bucketIndex]))
	{
		for (size_t i = m_bucketIndex+1; i < buckets.size(); ++i)
		{
			if (!buckets[i].empty())
			{
				m_bucketIndex = i;
				m_listIterator = begin(buckets[m_bucketIndex]);
				return;
			}
		}
		m_bucketIndex = buckets.size() - 1;
		m_listIterator = end(buckets[m_bucketIndex]);
	}
}

template<typename HashMap>
inline void const_chash_map_iterator<HashMap>::decrement()
{
	auto& buckets = m_hashMap->m_Buckets;
	if (m_listIterator != begin(buckets[m_bucketIndex]))
	{
		--m_listIterator;
		return;
	}
	else
	{
		for (int i = m_bucketIndex - 1; i >= 0; --i)
		{
			if (!buckets[i].empty())
			{
				m_bucketIndex = i;
				m_listIterator = std::end(buckets[m_bucketIndex]);
					--m_listIterator;
				return;
			}
		}
		m_bucketIndex = 0;
		m_listIterator = std::begin(buckets[m_bucketIndex]);
	}
}

/*
chash_map_iterator
cHash_Map����ͨ������
*/
template<typename HashMap>
class chash_map_iterator :public const_chash_map_iterator<HashMap>
{
public:
	template<typename Key, typename T, typename Compare = equal_to<Key>, typename Hash = cHas<Key>>
	friend class cHash_Map;

	chash_map_iterator();

	/*
	const_chash_map_iterator(size_t bucket,list_iterator_type iterator,const HashMap* Map);
	���캯����ʼ��hashMapͰ������hashMap��������hashMap����ָ��
	@Param��
	size_t bucket��hashMapͰ����
	list_iterator_type iterator��hashMap������
	HashMap* Map��hashMap����ָ��
	*/
	chash_map_iterator(size_t bucket, list_iterator_type iterator,HashMap* hashMap);

	value_type& operator*();

	value_type* operator->();

	//ǰ++
	chash_map_iterator<HashMap>& operator++();
	//��++
	chash_map_iterator<HashMap> operator++(int);

	//ǰ--
	const_chash_map_iterator<HashMap>& operator--();
	//��--
	const_chash_map_iterator<HashMap> operator--(int);

	~chash_map_iterator();
};

template<typename HashMap>
inline chash_map_iterator<HashMap>::chash_map_iterator() :
	const_chash_map_iterator<HashMap>()
{
}

template<typename HashMap>
inline chash_map_iterator<HashMap>::chash_map_iterator(size_t bucket, list_iterator_type iterator,HashMap * hashMap) :
	const_chash_map_iterator<HashMap>(bucket, iterator, hashMap)
{
}

template<typename HashMap>
inline typename chash_map_iterator<HashMap>::value_type & chash_map_iterator<HashMap>::operator*()
{
	return const_cast<value_type&>(*(this->m_listIterator));
}

template<typename HashMap>
inline typename chash_map_iterator<HashMap>::value_type * chash_map_iterator<HashMap>::operator->()
{
	return const_cast<value_type*>(&(*(this->m_listIterator)));
}

template<typename HashMap>
inline chash_map_iterator<HashMap>& chash_map_iterator<HashMap>::operator++()
{
	increment();
	return *this;
}

template<typename HashMap>
inline chash_map_iterator<HashMap> chash_map_iterator<HashMap>::operator++(int)
{
	const_chash_map_iterator<HashMap>* temp = this;
	increemnt();
	return *temp;
}

template<typename HashMap>
inline const_chash_map_iterator<HashMap>& chash_map_iterator<HashMap>::operator--()
{
	decrement();
	return *this;
}

template<typename HashMap>
inline const_chash_map_iterator<HashMap> chash_map_iterator<HashMap>::operator--(int)
{
	const_chash_map_iterator<HashMap>* temp = this;
	decrement();
	return *temp;
}

template<typename HashMap>
inline chash_map_iterator<HashMap>::~chash_map_iterator()
{

}

/*
chash_map_reverse_iterator
���������
*/
template<typename HashMap>
class chash_map_reverse_iterator:public chash_map_iterator<HashMap>
{
public:
	chash_map_reverse_iterator();

	/*
	const_chash_map_iterator(size_t bucket,list_iterator_type iterator,const HashMap* Map);
	���캯����ʼ��hashMapͰ������hashMap��������hashMap����ָ��
	@Param��
	size_t bucket��hashMapͰ����
	list_iterator_type iterator��hashMap������
	HashMap* Map��hashMap����ָ��
	*/
	chash_map_reverse_iterator(size_t bucket, list_iterator_type iterator, HashMap* hashMap);

	value_type& operator*();

	value_type* operator->();

	//ǰ++
	chash_map_reverse_iterator<HashMap>& operator++();
	//��++
	chash_map_reverse_iterator<HashMap> operator++(int);

	//ǰ--
	chash_map_reverse_iterator<HashMap>& operator--();
	//��--
	chash_map_reverse_iterator<HashMap> operator--(int);

	~chash_map_reverse_iterator();
};

template<typename HashMap>
inline chash_map_reverse_iterator<HashMap>::chash_map_reverse_iterator():
	chash_map_iterator<HashMap>()
{
}

template<typename HashMap>
inline chash_map_reverse_iterator<HashMap>::chash_map_reverse_iterator(size_t bucket, list_iterator_type iterator, HashMap * hashMap):
	chash_map_iterator<HashMap>(bucket,iterator,hashMap)
{
}

template<typename HashMap>
inline typename chash_map_reverse_iterator<HashMap>::value_type & chash_map_reverse_iterator<HashMap>::operator*()
{
	return const_cast<value_type&>(*(this->m_listIterator));
}

template<typename HashMap>
inline typename chash_map_reverse_iterator<HashMap>::value_type * chash_map_reverse_iterator<HashMap>::operator->()
{
	return const_cast<value_type*>(&(*this->m_listIterator));
}

template<typename HashMap>
inline chash_map_reverse_iterator<HashMap>& chash_map_reverse_iterator<HashMap>::operator++()
{
	decrement();
	return *this;
}

template<typename HashMap>
inline chash_map_reverse_iterator<HashMap> chash_map_reverse_iterator<HashMap>::operator++(int)
{
	chash_map_reverse_iterator<HashMap> *temp = this;
	decrement();
	return *temp;
}

template<typename HashMap>
inline chash_map_reverse_iterator<HashMap>& chash_map_reverse_iterator<HashMap>::operator--()
{
	increment();
	*this;
}

template<typename HashMap>
inline chash_map_reverse_iterator<HashMap> chash_map_reverse_iterator<HashMap>::operator--(int)
{
	chash_map_reverse_iterator<HashMap>* temp = this;
	increment();
	return *temp;
}

template<typename HashMap>
inline chash_map_reverse_iterator<HashMap>::~chash_map_reverse_iterator()
{
}


/*
cHash_map
*/
template<typename Key,typename T,typename Compare=equal_to<Key>,typename Hash=cHas<Key>>
class cHash_Map
{
public:
	//****************************��׼���ͱ���*************************//
	using key_type = Key;
	using mapped_type = T;
	using value_type = pair<Key, T>;
	using reference = pair<Key, T>&;
	using const_reference = const pair<Key, T>&;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using hash_map_type = cHash_Map<Key, T, Compare, Hash>;
	//****************************************************************//

public:
	//*******************������*********************//
	friend class  const_chash_map_iterator<hash_map_type>;
	friend class chash_map_iterator<hash_map_type>;
	friend class chash_map_reverse_iterator<hash_map_type>;

	using reverse_iterator = chash_map_reverse_iterator<hash_map_type>;
	using iterator = chash_map_iterator<hash_map_type>;
	using const_iterator = const_chash_map_iterator<hash_map_type>;
	//*********************************************//
public:
	/*
	cHash_Map(const Compare& comp=Compare(),const size_t& numBuckets=101,const Hash& hash=Hash());
	���캯������ʼ��hash_map��ֵ�ȽϺ�������С��hash����
	@Param:
		Compare comp��hash_map��ֵ�ȽϺ���
		size_t numBuckets��hash_map��hashֵ��Χ
		Hash hash��hash���������ڵõ�hash��ֵ
	*/
	explicit cHash_Map(const Compare& comp=Compare(),const size_t& numBuckets=101,const Hash& hash=Hash());

	/*
	insert(const value_type& value);
	��hash_map�в����ֵ��
	@Param��
		value_type value����Ҫ����ļ�ֵ��
	@return value_type*��
		nullptr������ʧ�ܻ�ǰ����ļ�ֵ���Ѿ�����
		validValue����ǰ����ļ�ֵ��ָ��
	*/
	value_type* insert(const value_type& value);

	/*
	find(const Key& key);
	����Keyֵ����hash_map�еļ�ֵ��
	@Param��
		Key key����ֵ
	*/
	value_type* find(const Key& key);
	const value_type* find(const Key& key) const;

	/*
	erase(const Key& key);
	����Keyֵɾ��hash_map�еļ�ֵ��
	@Param��
		Key key��hash_map��ֵ
	@return value_type:
		��ɾ���ļ�ֵ��
	*/
	value_type erase(const Key& key);

	/*
	operator[] (const Key& key);
	���ռ�ֵȡ����Ӧ��mappedֵ
	@Param��
		Key key����ֵ
	*/
	T& operator[] (const Key& key);

	/*
	size()
	��ȡhash_map��С
	@return size_type��
		size
	*/
	size_type size() const;

	/*
	bucketCapacity()
	��ȡhash_map�����б����
	@return
		hash_map�����б����
	*/
	size_type bucketCapacity() const;

	/*
	rebucketCapacity();
	���·�������
	@Param��
		size_t capacity�����·��������
	*/
	void rebucketCapacity(size_type capacity);

	/*
	empty()
	�ж��Ƿ�Ϊ��
	@return bool��
		true����
		false����
	*/
	bool empty() const;

	void clear();

	iterator begin();

	iterator end();

	const_iterator cbegin() const;

	const_iterator cend() const;

	reverse_iterator rbegin();

	reverse_iterator rend();

	const reverse_iterator crbegin() const;

	const reverse_iterator crend() const;

	bool operator==(const hash_map_type& other);

	virtual ~cHash_Map();
private:
	using ListType = list<value_type>;

	/*
	findElement(const Key& key,size_t& hashKey);
	����ָ����ֵ�ļ�ֵ�ԣ�������hashKeyֵ
	@Param��
		Key key:��ֵ
		size_t& hashKey�������ɵ�hashKeyֵ
	@return��
		���ҵ��ļ�ֵ�Ե�����
	*/
	typename ListType::iterator findElement(const Key& key, size_t& hashKey);

	vector<ListType> m_Buckets;
	size_t m_size;
	Compare m_comp;
	Hash m_hash;
	size_t m_bucketCapacity;
};

template<typename Key, typename T, typename Compare, typename Hash>
inline cHash_Map<Key, T, Compare, Hash>::cHash_Map(const Compare & comp, const size_t & numBuckets, const Hash & hash)
{
	if (numBuckets == 0) {
		throw invalid_argument(ErrorStr);
	}
	m_Buckets.resize(numBuckets);
	m_bucketCapacity = numBuckets;
	m_comp = comp;
	m_hash = hash;
	m_size = 0;
}

template<typename Key, typename T, typename Compare, typename Hash>
inline  typename cHash_Map<Key, T, Compare, Hash>::value_type* cHash_Map<Key, T, Compare, Hash>::insert(const value_type & value)
{
	size_t hashKey = 0;
	auto it = findElement(value.first, hashKey);
	if (it == std::end(m_Buckets[hashKey]))
	{
		m_Buckets[hashKey].push_back(value);
		++m_size;
	}
	else
	{
		return nullptr;
	}
}

template<typename Key, typename T, typename Compare, typename Hash>
inline typename cHash_Map<Key, T, Compare, Hash>::value_type * cHash_Map<Key, T, Compare, Hash>::find(const Key & key)
{
	size_t hashKey = 0;
	auto it=findElement(key, hashKey);
	if (it != std::end(m_Buckets[hashKey]))
	{
		return &(*it);
	}
	else
	{
		return nullptr;
	}
}

template<typename Key, typename T, typename Compare, typename Hash>
inline const typename cHash_Map<Key, T, Compare, Hash>::value_type * cHash_Map<Key, T, Compare, Hash>::find(const Key & key) const
{
	return const_cast<cHash_Map<Key, T, Compare, Hash>*>(this)->find(key);
}

template<typename Key, typename T, typename Compare, typename Hash>
inline typename cHash_Map<Key, T, Compare, Hash>::value_type cHash_Map<Key, T, Compare, Hash>::erase(const Key & key)
{
	size_t hashKey = 0;
	auto it = findElement(key, hashKey);
	if (it != end(m_Buckets[hashKey]))
	{
		value_type temp;
		temp = *it;
		m_Buckets[hashKey].erase(it);
		--m_size;
		return temp;
	}
	else
	{
		return value_type();
	}
}

template<typename Key, typename T, typename Compare, typename Hash>
inline T & cHash_Map<Key, T, Compare, Hash>::operator[](const Key & key)
{
	size_t hashKey = 0;
	auto it = findElement(key, hashKey);
	if (it == std::end(m_Buckets[hashKey]))
	{
		return insert(value_type(key, mapped_type()))->second;
	}
	else
	{
		return it->second;
	}
}

template<typename Key, typename T, typename Compare, typename Hash>
inline typename cHash_Map<Key, T, Compare, Hash>::size_type cHash_Map<Key, T, Compare, Hash>::size() const
{
	return m_size;
}

template<typename Key, typename T, typename Compare, typename Hash>
inline typename cHash_Map<Key, T, Compare, Hash>::size_type cHash_Map<Key, T, Compare, Hash>::bucketCapacity() const
{
	return m_bucketCapacity;
}

template<typename Key, typename T, typename Compare, typename Hash>
inline void cHash_Map<Key, T, Compare, Hash>::rebucketCapacity(size_type capacity)
{
	m_Buckets.clear();
	m_Buckets.resize(capacity);
}

template<typename Key, typename T, typename Compare, typename Hash>
inline bool cHash_Map<Key, T, Compare, Hash>::empty() const
{
	return m_size == 0;
}

template<typename Key, typename T, typename Compare, typename Hash>
inline void cHash_Map<Key, T, Compare, Hash>::clear()
{
	m_Buckets.clear();
}

template<typename Key, typename T, typename Compare, typename Hash>
inline  typename cHash_Map<Key, T, Compare, Hash>::iterator cHash_Map<Key, T, Compare, Hash>::begin()
{
	if (m_size== 0)
	{
		return end();
	}
	for (size_t i = 0; i < m_Buckets.size(); ++i)
	{
		if (!m_Buckets[i].empty())
		{
			return chash_map_iterator<hash_map_type>(i, std::begin(m_Buckets[i]), this);
		}
	}
	return end();
}

template<typename Key, typename T, typename Compare, typename Hash>
inline typename cHash_Map<Key, T, Compare, Hash>::iterator cHash_Map<Key, T, Compare, Hash>::end()
{
	return  chash_map_iterator<hash_map_type>(m_Buckets.size() - 1, std::end(m_Buckets[m_Buckets.size() - 1]), this);
}

template<typename Key, typename T, typename Compare, typename Hash>
inline typename cHash_Map<Key, T, Compare, Hash>::const_iterator cHash_Map<Key, T, Compare, Hash>::cbegin() const
{
	return const_cast<hash_map_type*>(this)->begin();
}

template<typename Key, typename T, typename Compare, typename Hash>
inline typename cHash_Map<Key, T, Compare, Hash>::const_iterator cHash_Map<Key, T, Compare, Hash>::cend() const
{
	return const_cast<hash_map_type*>(this)->end();
}

template<typename Key, typename T, typename Compare, typename Hash>
inline typename cHash_Map<Key, T, Compare, Hash>::reverse_iterator cHash_Map<Key, T, Compare, Hash>::rbegin()
{
	if (m_size == 0)
	{
		return rend();
	}
	for (size_t i = m_Buckets.size() - 1; i >= 0; --i)
	{
		if (!m_Buckets[i].empty())
		{
			auto iter = std::end(m_Buckets[i]);
			return chash_map_reverse_iterator<hash_map_type>(i, --iter, this);
		}
	}
	return rend();
}

template<typename Key, typename T, typename Compare, typename Hash>
inline typename cHash_Map<Key, T, Compare, Hash>::reverse_iterator cHash_Map<Key, T, Compare, Hash>::rend()
{
	return chash_map_reverse_iterator<hash_map_type>(0, std::begin(m_Buckets[0]), this);
}

template<typename Key, typename T, typename Compare, typename Hash>
inline const typename cHash_Map<Key, T, Compare, Hash>::reverse_iterator cHash_Map<Key, T, Compare, Hash>::crbegin() const
{
	return rbegin();
}

template<typename Key, typename T, typename Compare, typename Hash>
inline const typename cHash_Map<Key, T, Compare, Hash>::reverse_iterator cHash_Map<Key, T, Compare, Hash>::crend() const
{
	return rend();
}

template<typename Key, typename T, typename Compare, typename Hash>
inline bool cHash_Map<Key, T, Compare, Hash>::operator==(const hash_map_type & other)
{
	if (this->size() != other.size() || this->bucketCapacity() != other.bucketCapacity())
	{
		return  false;
	}
	for (int i = 0; i < m_Buckets.size(); ++i)
	{
		if (m_Buckets[i].size() != other, m_Buckets[i].size())
		{
			return false;
		}
		else if (m_Buckets[i] != other.m_Buckets[i])
		{
			return false;
		}
	}
	return true;
}

template<typename Key, typename T, typename Compare, typename Hash>
inline cHash_Map<Key, T, Compare, Hash>::~cHash_Map()
{

}

template<typename Key, typename T, typename Compare, typename Hash>
inline typename cHash_Map<Key, T, Compare, Hash>::ListType::iterator cHash_Map<Key, T, Compare, Hash>::findElement(const Key & key, size_t& hashKey)
{
	hashKey = m_hash(key) % m_Buckets.size();
	for (auto it = std::begin(m_Buckets[hashKey]); it != std::end(m_Buckets[hashKey]); ++it)
	{
		if (m_comp(it->first, key))
		{
			return it;
		}
	}
	return std::end(m_Buckets[hashKey]);
}

#endif // !__CHASH_MAP__H__