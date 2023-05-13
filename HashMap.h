// ===================================================
// Templated HashMap implementation
// By Andre Lungu
// ===================================================

#ifndef HASHMAP_H
#define HASHMAP_H

// Actual HashMap Class
template<class K, class V, class HashFunction> class HashMap{
public:
	class HashMapNode{
		private:
			K key;
			V value;
			HashMapNode *next;
			HashMapNode *prev;
		public:
			friend class HashMap;
			friend class HashMapNode;
			HashMapNode(const K& k, const V& v) : key(k), value(v), next(nullptr), prev(nullptr){}
	};
	class HashMapIterator{
		public:
			friend class HashMap;
			const K& operator*() const{ return *ptr; }
			HashMapIterator(HashMap *h) : hs(h), ptr(nullptr), index(-1){} 
			HashMapIterator(const HashMapIterator& i) : hs(i.hs), ptr(i.ptr), index(i.index){}
			HashMapIterator(HashMap *h, HashMapNode* p, size_t i) : hs(h), ptr(p), index(i){}
			friend bool operator==(const HashMapIterator& h1, const HashMapIterator& h2);
			HashMapIterator& operator++(){
				// uf we stukk have stuff in this spot in the array
				if(ptr->next){
					ptr = ptr->next;
					return *this;
				}
				// else need to find next occupied table slot 
				while(index < hs->_nBuckets && !(hs->_table[index])){
					++index;
				}
				if(index == hs->_nBuckets) ptr = nullptr;
				return *this;
			}
			HashMapIterator operator++(int){
				HashMapIterator temp(this);
				this->operator++();
				return temp;
			}
			HashMapIterator& operator--(){
				if(ptr->prev){
					ptr = ptr->prev;
					return *this;
				}
				// decrementing end iterator: moving to last element in last bucket
				if(!ptr){

				}
				// moving to 
				while(index > 0 && !(hs->_table[index])){
					--index;
				}
				return *this;
			}
			HashMapIterator operator--(int){
				HashMapIterator temp(this);
				this->operator--();
				return temp;
			}
		private:
			HashMap* hs;
			HashMapNode* ptr;
			size_t index;
	};


private:
	HashMapNode** _table;
	// array size
	size_t _nBuckets;
	// actual number of elements
	size_t _size;
	HashFunction _hash; 
public:
	// Construction & Assignment
	HashMap();
	HashMap(size_t init_size);
	~HashMap() {this->delete_table();}
	HashMap(const HashMap& H){this->copy(H);}
	HashMap& operator=(const HashMap& H){this->delete_table(); this->copy(H); return *this;}

	// Element access
	HashMapNode& operator[](const K& key);
	HashMapIterator find(const K& key);

	// Iterator Operations
};
#endif