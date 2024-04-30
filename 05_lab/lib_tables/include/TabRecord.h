#ifndef _TAB_RECORD_H
#define _TAB_RECORD_H
#include <iostream>
using namespace std;

template <class TKey, class TData>
class TabRecord {
protected:
	TKey key;
	TData* data;
public:
	TabRecord(const TKey& _key, TData* _data);
	TabRecord(const TabRecord<TKey, TData>& record);
	~TabRecord();
	TKey GetKey() const;
	TData* GetData() const;
	const TabRecord<TKey, TData>& operator=(const TabRecord<TKey, TData>& record);
	bool operator==(const TabRecord<TKey, TData>& record) const;
	bool operator!=(const TabRecord<TKey, TData>& record) const;
};

template <class TKey, class TData>
TabRecord<TKey, TData>::TabRecord(const TKey& _key, TData* _data) : key(_key) {
	data = new TData(*_data);
}

template <class TKey, class TData>
TabRecord<TKey, TData>::TabRecord(const TabRecord<TKey, TData>& record) : key(record.key) {
	data = new TData(*record.data);
}

template <class TKey, class TData>
TKey TabRecord<TKey, TData>::GetKey() const {
	return key;
}

template <class TKey, class TData>
TData* TabRecord<TKey, TData>::GetData() const {
	return data;
}

template<typename TKey, typename TData>
const TabRecord<TKey, TData>& TabRecord<TKey, TData>::operator=(const TabRecord& record) {
	if (this == &record) {
		return *this;
	}
	key = record.key;
	data = new TData(*record.data);
	return *this;
}

template<typename TKey, typename TData>
bool TabRecord<TKey, TData>::operator==(const TabRecord<TKey, TData>& record) const {
	return (key == record.GetKey() && *data == *record.GetData());
}

template<typename TKey, typename TData>
bool TabRecord<TKey, TData>::operator!=(const TabRecord<TKey, TData>& record) const{
	return !(*this == record);
}

template<typename TKey, typename TData>
TabRecord<TKey, TData>::~TabRecord() {
	delete data;
}

#endif 