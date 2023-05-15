// ===================================================
// Templated HashMap implementation
// By Andre Lungu
// ===================================================

#ifndef HASHMAP_H
#define HASHMAP_H
#include <list>
#include <utility>
#include <cstddef>
#include <iostream>

// Actual HashMap Class
template<class K, class V, class HashFunction> class HashMap{
public:
// =========================================================================================
	// Actual HashMap implementation 
	// Construction & Assignment
	HashMap() : _table(nullptr), _nBuckets(0), _size(0){}
	HashMap(int init_size) : _nBuckets(init_size), _size(0){
		_table = new std::list<std::pair<K,V>>[init_size];
		for(int i = 0; i < init_size; ++i){
			_table[i] = std::list<std::pair<K,V>>();
		}
	}
	~HashMap() {delete[] _table;}
	HashMap(const HashMap& H) : _table(nullptr), _nBuckets(H._nBuckets), _size(H._size){this->copy(H);}
	HashMap& operator=(const HashMap& H){delete _table; this->copy(H); return *this;}

	// Element access/insertion/modification
	V& operator[](const K& key);
	bool find(const K& key) const;
	size_t bucket(const K& key) const;
	bool insert(const K& key);
	bool erase(const K& key);
	void print_table() const;

	// Iterators
	/*HashMapIterator begin() const;
	HashMapIterator end() const{return HashMapIterator(this,_table[_nBuckets-1].end(),-1);}*/
private:
	// REPRESENTATION
	// dynamically allocated array of lists of pairs
	std::list<std::pair<K,V>>* _table;
	// array size
	size_t _nBuckets;
	// actual number of elements
	size_t _size;
	HashFunction _hash; 

	// PRIVATE MEMBER FUNCTIONS
	void copy(const HashMap& H);
	void resize(size_t new_size);
	
};

// ======================================
// MEMBER FUNCTION IMPLEMENTATIONS
// ======================================
template<class K, class V, class HashFunction>
void HashMap<K,V,HashFunction>::copy(const HashMap& H){
	_table = new std::list<std::pair<K,V>>[H._nBuckets];
	for(size_t i = 0; i < H._nBuckets; ++i){
		_table[i] = std::list<std::pair<K,V>>(H._table[i]);
	}
}

template<class K, class V, class HashFunction>
V& HashMap<K,V,HashFunction>::operator[](const K& key){
	size_t index = bucket(key);
	typename std::list<std::pair<K,V>>::iterator itr = _table[index].begin();
	while(itr != _table[index].end() && itr->first != key){
		++itr;
	}
	if(itr == _table[index].end()){
		_table[index].push_back(std::make_pair(key, V()));
		++_size;
		itr = --(_table[index].end());
	}
	return itr->second;
}

template<class K, class V, class HashFunction>
bool HashMap<K,V,HashFunction>::find(const K& key) const{
	size_t index = bucket(key);
	typename std::list<std::pair<K,V>>::iterator itr = _table[index].begin();
	while(itr != _table[index].end() && itr->first != key){
		++itr;
	}
	if(itr == _table[index].end()) return false;
	return true;
}

template<class K, class V, class HashFunction>
size_t HashMap<K,V,HashFunction>::bucket(const K& key) const{
	return _hash(key) % _nBuckets;
}


template<class K, class V, class HashFunction>
bool HashMap<K,V,HashFunction>::insert(const K& key){
	size_t index = _hash(key);
	typename std::list<std::pair<K,V>>::iterator itr = _table[index].begin();
	while(itr != _table[index].end() && itr->first != key) ++itr;
	if(itr == _table[index].end()){
		_table[index].push_back(std::make_pair(key, V()));
		++_size;
		return true;
	}
	return false;
}

template<class K, class V, class HashFunction>
void HashMap<K,V,HashFunction>::print_table() const{
	for(size_t i = 0; i < _nBuckets; ++i){
		std::cout<<"["<< i <<"]: ";
		for(typename std::list<std::pair<K,V>>::iterator itr = _table[i].begin(); itr != _table[i].end(); ++itr){
			std::cout << "( "<< itr->first << ", "<<itr->second<< " ) ";
		}
		std::cout << "\n";
	}
}
#endif