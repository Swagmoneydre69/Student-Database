// ===================================================
// Templated HashMap implementation
// By Andre Lungu
// ===================================================

#ifndef HASHMAP_H
#define HASHMAP_H
#include <list>
#include <utility>

// Actual HashMap Class
template<class K, class V, class HashFunction> class HashMap{
public:
	class HashMapIterator{
		public:
			typedef std::list<std::pair<K,V>>::iterator iterator_t;
			friend class HashMap;
			// CONSTRUCTORS
			HashMapIterator(HashMap *h, size_t i) : hs(h), index(i){
				itr = h->_table[i].begin();
			}
			HashMapIterator(const HashMapIterator& i) : hs(i.hs), itr(i.itr), index(i.index){}
			HashMapIterator(HashMap *h, iterator_t t, size_t i) : hs(h), itr(t), index(i){}

			// OPERATORS
			const std::pair<K,V>& operator*() const{ return *itr; }
			friend bool operator==(const HashMapIterator& h1, const HashMapIterator& h2);
			friend bool operator!=(const HashMapIterator& h1, const HashMapIterator& h2);
			/* Prefix increment */
			HashMapIterator& operator++(){     
				if(++itr != hs->_table[index].end()) return *this;
				do{ 
					++index; 
				}while(hs->_table[index].size() == 0 && index < hs->_nBuckets);
				if(index != hs->_nBuckets){
					itr = hs->_table[index].begin();
				}
				else{
					itr = hs->_table[hs->_nBuckets].end();
				}
				return *this;
			}     
			/* Postfix increment */
			HashMapIterator operator++(int){
				HashMapIterator temp(*this);
				this->operator++();
				return temp;
			}   
			/* Prefix decrement */
			HashMapIterator& operator--(){
				// decrementing end iterator
				if(itr != hs->_table[index].begin()){
					--itr;
					return *this;
				}
				do{
					--index;
				} while(index >= 0 && hs->_table[index].empty());
				itr = hs->_table[index].begin();
				while(itr != hs->_table[index].end()){
					++itr;
				}
				--itr;
				return *this;
			} 
			/* Postfix decrement */   
			HashMapIterator operator--(int){
				HashMapIterator temp(*this);
				this->operator--();
				return temp;
			}   
		private:
			HashMap* hs;
			iterator_t itr;
			size_t index;
	};

// =========================================================================================
	// Actual HashMap implementation 
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
	size_t hash
public:
	// Construction & Assignment
	HashMap() : _table(nullptr), _nBuckets(0), _size(0){}
	HashMap(size_t init_size) : _nBuckets(init_size), _size(0){
		_table = new std::list<std::pair<K,V>>[init_size];
		for(int i = 0; i < init_size; ++i){
			_table[i] = std::list<std::pair<K,V>>();
		}
	}
	~HashMap() {delete _table;}
	HashMap(const HashMap& H) : _table(nullptr), _nBuckets(H._nBuckets), _size(H._size){this->copy(H);}
	HashMap& operator=(const HashMap& H){delete _table; this->copy(H); return *this;}

	// Element access/insertion/modification
	V& operator[](const K& key);
	HashMapIterator find(const K& key) const;
	size_t bucket(const K& key) const;
	std::pair<HashMapIterator, bool> insert(const K& key);
	bool erase(const K& key);

	// Iterators
	HashMapIterator begin() const;
	HashMapIterator end() const{return HashMapIterator(this,_table[_nBuckets-1].end(),-1);}
};

// ======================================
// MEMBER FUNCTION IMPLEMENTATIONS
// ======================================
template<class K, class V, class HashFunction>
void HashMap::copy(const HashMap& H){
	_table = new std::list<std::pair<K,V>>[H._nBuckets];
	for(size_t i = 0; i < H._nBuckets; ++i){
		_table[i] = std::list<std::pair<K,V>>(H._table[i]);
	}
}

template<class K, class V, class HashFunction>
V& HashMap::operator[](const K& key){
	size_t index = bucket(key);
	HashMapIterator itr(this, index);
	while(itr.itr != _table[index].end() && itr->first != key){
		++itr;
	}
	if(itr.itr == _table[index].end()){
		_table[index].push_back(std::make_pair(key, V()));
	}
	return _table[index].back().second;
}

template<class K, class V, class HashFunction>
HashMapIterator HashMap::find(const K& key) const{
	size_t index = bucket(key);
	HashMapIterator itr(this, index);
	while(itr.itr != _table[index].end() && itr->first != key){
		++itr;
	}
	if(itr.itr == _table[index].end()) return this->end();
	return itr;
}

template<class K, class V, class HashFunction>
size_t HashMap::bucket(const K& key) const{
	return _hash(key) % _nBuckets;
}

template<class K, class V, class HashFunction>
bool operator==(const HashMapIterator& h1, const HashMapIterator& h2){
	return (h1.index == h2.index && h1.itr->first == h2.itr->first
			&& h1.itr->second == h2.itr->second && h1.hs == h2.hs);
}

template<class K, class V, class HashFunction>
bool operator!=(const HashMapIterator& h1, const HashMapIterator& h2){
	return !(h1 == h2);
}

template<class K, class V, class HashFunction>
std::pair<HashMapIterator, bool> insert(const K& key){
	size_t index = _hash(key);
	HashMapIterator itr(this, index);
	while(itr != _table[index].end() && itr->first != key) ++itr;
	if(itr == _table[index].end()){
		_table[index].push_back(std::make_pair(key, V()));
		return std::make_pair(HashMapIterator(this, --(_table[index].end()), index), true);
	}
	return std::make_pair(itr, false);
}

template<class K, class V, class HashFunction>
HashMapIterator HashMap::begin() const{
	int i = 0;
	while(_table[i].empty() && i < _nBuckets) ++i;
	return HashMapIterator(this,_table[i].begin(),i);
}

#endif