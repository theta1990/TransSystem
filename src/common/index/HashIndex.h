/*
 * HashIndex.h
 *
 *  Created on: Dec 10, 2014
 *      Author: volt
 */

#ifndef HASHINDEX_H_
#define HASHINDEX_H_
#include "../../common.h"
#include "BitLock.h"
namespace expdb {

template <typename T>
struct Hash
{
	uint64_t operator() (const T &v){
		return v.hash();
	}
};

template <typename T>
struct Hash<T*>
{
	uint64_t operator() (T *v){
		return v ? v ->hash() : 0;
	}
};

template <typename T>
struct Hash<const T*>
{
	uint64_t operator() (const T *v){
		return v ? v->hash() : 0;
	}
};

template <typename T>
struct Equal
{
	bool operator() (const T &a, const T &b) const{

		return a == b;
	}
};

template <typename T>
struct Equal<T*>
{
	bool operator() (const T* &a, const T* &b) const{

		return a && b && *a == *b;
	}
};



template<typename KEY, typename VALUE>
class TableIterator;

template<typename KEY, typename VALUE>
class HashIndex {

public:
	typedef Hash<KEY> HashFunc;
	typedef Equal<KEY> EqualFunc;

	struct Hnode{
		KEY 	k;
		VALUE 	v;
		Hnode	*nxt;
	};

	/**
	 * 这个类还不是线程安全的，在读取的过程中没有对hash桶加锁。
	 * 果然迭代器做起来非常的困难。
	 */
	class TableIterator
	{

	public:
		TableIterator(const HashIndex<KEY, VALUE> *mainTable) : m_idx(0), m_curNode(NULL), m_table(mainTable) {

		}

		int32_t open() {

			int32_t ret = SUCCESS;

			if( NULL == m_table ) ret = ERROR;

			m_idx = 0;
			m_curNode = NULL;

			return ret;
		}

		int32_t next(VALUE &v) {

			int32_t ret = SUCCESS;

			if( NULL != m_curNode && NULL != m_curNode->nxt ) {

				m_curNode = m_curNode->nxt;
			}else {

				m_curNode = NULL;
				//find a non-null slot in the hash buckets array.
				/**
				 * 在这里加上对bucket的并发访问控制，保证能够顺利的获得下一个节点
				 */
				for(; m_idx < m_table->m_size && NULL == m_table->m_table[m_idx]; ++m_idx);

				if( m_idx < m_table->m_size ) {
					m_curNode = m_table->m_table[m_idx++];
					m_curNode = m_curNode->nxt;
				}
			}

			if( m_curNode == NULL ) {
				ret = END;
			}else {
				v = m_curNode->v;
			}
			return ret;
		}

		int32_t close() {

			m_curNode = NULL;
			m_table = NULL;
			m_idx = 0;
			return SUCCESS;
		}

	private:

		uint64_t 	m_idx;		//now visit
		const Hnode *m_curNode;
		const HashIndex<KEY, VALUE>	*m_table;
	};

public:
	HashIndex();

	int32_t init(uint64_t size);
	virtual ~HashIndex();

	int32_t insert(const KEY &key, VALUE value);
	int32_t find(const KEY &key, VALUE &value);
	int32_t remove(const KEY &key);

	TableIterator begin() const {

		return TableIterator(this);
	}

	void destroy();


	friend class TableIterator;
private:
	Hnode**		m_table;
	BitLock 	m_bitLock;
	uint64_t 	m_size;
	HashFunc 	m_hash_func;
	EqualFunc 	m_equal_func;
};

/**
 * Hash索引的迭代器，访问完整的hash表。
 */


template<typename KEY, typename VALUE>
HashIndex<KEY, VALUE>::HashIndex() :
		m_table(NULL), m_bitLock(), m_size(0) {

}

template<typename KEY, typename VALUE>
int32_t HashIndex<KEY, VALUE>::init(uint64_t size) {

	m_size = size;
	m_table = (Hnode **)malloc(m_size * sizeof(Hnode*));
	m_bitLock.init(m_size);
	memset(m_table, 0, m_size * sizeof(Hnode*));

	return SUCCESS;
}

template<typename KEY, typename VALUE>
HashIndex<KEY, VALUE>::~HashIndex() {

	destroy();
}

template<typename KEY, typename VALUE>
int32_t HashIndex<KEY, VALUE>::insert(const KEY& key, VALUE value) {

	int ret = SUCCESS;
	uint64_t hk = m_hash_func(key);

	if (m_size < 0 || m_table == NULL) {

		ret = expdb::ERROR;
		VOLT_ERROR("hash index array not inited");
	} else {

		hk &= (m_size - 1);
		BitLockGuard(m_bitLock, hk);
		if (m_table[hk] == NULL) { //bucket is empty

			Hnode *newnode = (Hnode *)malloc(sizeof(Hnode));
			m_table[hk] = (Hnode*)malloc(sizeof(Hnode));

			newnode->k = key;
			newnode->v = value;
			newnode->nxt = NULL;
			m_table[hk]->nxt = newnode;
		} else {

			Hnode *nxt = m_table[hk]->nxt;
			Hnode *prev = m_table[hk];

			while (nxt != NULL) {

				if( m_equal_func(key, nxt->k) ){

					ret = DUPKEY;
					break;
				}else {

					prev = nxt;
					nxt = nxt->nxt;
				}
			}
			if (expdb::DUPKEY != ret) {	//does not confilct with existing one
				Hnode *newnode = (Hnode *)malloc(sizeof(Hnode));

				newnode->k = key;		//copy
				newnode->v = value;	//copy
				newnode->nxt = nxt;
				prev->nxt = newnode;
			}
		}
	}
	return ret;
}

template<typename KEY, typename VALUE>
int32_t HashIndex<KEY, VALUE>::find(const KEY& key, VALUE& value) {

	int ret = SUCCESS;
	uint64_t hk = m_hash_func(key);
	if (m_size < 0 || m_table == NULL) {

		ret = ERROR;
		VOLT_ERROR("hash table not inited");
	} else {

		hk &= (m_size - 1);
		BitLockGuard(m_bitLock, hk);

		if (m_table[hk] == NULL) { //bucket is empty

			ret = NOTFOUND;
		} else {

			Hnode *nxt = m_table[hk]->nxt;

			while (nxt != NULL) {

				if( m_equal_func(key, nxt->k) ){

					value = (nxt->v);
					ret = SUCCESS;
					break;
				}else {

					nxt = nxt->nxt;
				}
			}

			if (nxt == NULL)
				ret = NOTFOUND;
		}
	}
	return ret;
}

template<typename KEY, typename VALUE>
int32_t HashIndex<KEY, VALUE>::remove(const KEY& key) {

	int ret = SUCCESS;
	uint64_t hk = m_hash_func(key);
	if (m_size < 0 || m_table == NULL) {

		ret = ERROR;
		VOLT_ERROR("hash table not inited");
	} else {

		hk &= (m_size - 1);
		BitLockGuard(m_bitLock, hk);

		if (m_table[hk] == NULL) { //bucket is empty

			ret = NOTFOUND;
		} else {

			Hnode *nxt = m_table[hk]->nxt;
			Hnode *prev = m_table[hk];

			while (nxt != NULL) {

				if (m_equal_func(key, nxt->k)) {

					ret = SUCCESS;
					prev->nxt = nxt->nxt;
					free(nxt);
					break;
				} else {

					prev = nxt;
					nxt = nxt->nxt;
				}
			}

			if (nxt == NULL)
				ret = NOTFOUND;
		}
	}
	return ret;
}

template<typename KEY, typename VALUE>
void HashIndex<KEY, VALUE>::destroy() {

	if (m_size > 0 && m_table != NULL) {
		Hnode *now = NULL, *nxt = NULL;
		for (int i = 0; i < m_size; ++i) {
			BitLockGuard(m_bitLock, i);
			now = m_table[i];
			while (now != NULL) {

				nxt = now->nxt;
				free(now);
				now = nxt;
			}
		}
	}
	m_bitLock.destroy();
	m_size = 0;
	free(m_table);
	m_table = NULL;
}

} /* namespace expdb */

#endif /* HASHINDEX_H_ */
