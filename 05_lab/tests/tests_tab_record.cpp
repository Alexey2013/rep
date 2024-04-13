#include "TabRecord.h"
#include <gtest.h>
const int key = 0;

//TEST(TabRecord, can_create_TabRecord) {
//	string* data = new string("test");
//	ASSERT_NO_THROW(TabRecord<int, string> tr(key, data));
//}

TEST(TabRecord, can_get_key) {
	string* data = new string("test");
	TabRecord<int, string> tr(key, data);
	EXPECT_EQ(key, tr.GetKey());
}

TEST(TabRecord, can_get_data1) {
	string* data = new string("test");
	TabRecord<int, string> tr(key, data);
	EXPECT_EQ(data, tr.GetData());
}

TEST(TabRecord, can_get_data2) {
	string* data = new string("test");
	TabRecord<int, string> tr(key, data);
	EXPECT_EQ("test", *tr.GetData());
}

TEST(TabRecord, null_data_pointer_returns_null) {
	TabRecord<int, string> tr(key, nullptr);
	EXPECT_EQ(nullptr, tr.GetData());
}

TEST(TabRecord, copied_record_have_equal_key) {
	string* data = new string("test");
	TabRecord<int, string> tr1(key, data);
	TabRecord<int, string> tr2(tr1);
	EXPECT_EQ(tr1.GetKey(), tr2.GetKey());
}

TEST(TabRecord, copied_record_have_equal_data) {
	string* data = new string("test");
	TabRecord<int, string> tr1(key, data);
	TabRecord<int, string> tr2(tr1);
	EXPECT_EQ(tr1.GetData(), tr2.GetData());
}

TEST(TabRecord, different_records_not_equal) {
	string* data = new string("test");
	TabRecord<int, string> tr1(key, data);
	TabRecord<int, string> tr2(key+1, data);
	EXPECT_NE(tr1.GetKey(), tr2.GetKey());
}
