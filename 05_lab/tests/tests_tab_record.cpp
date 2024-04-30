#include "TabRecord.h"
#include <gtest.h>

TEST(TabRecord, can_get_key) {
	string* data = new string("test");
	TabRecord<int, string> tr(1, data);
	EXPECT_EQ(1, tr.GetKey());
}

TEST(TabRecord, can_get_data1) {
	string* data = new string("test");
	TabRecord<int, string> tr(1, data);
	EXPECT_EQ(*data, *tr.GetData()); 
}

TEST(TabRecord, can_get_data2) {
	string* data = new string("test");
	TabRecord<int, string> tr(1, data);
	EXPECT_EQ("test", *tr.GetData()); 
}

TEST(TabRecord, copied_record_have_equal_key) {
	string* data = new string("test");
	TabRecord<int, string> tr1(1, data);
	TabRecord<int, string> tr2(tr1);
	EXPECT_EQ(tr1.GetKey(), tr2.GetKey());
}

TEST(TabRecord, copied_record_have_equal_data) {
	string* data = new string("test");
	TabRecord<int, string> tr1(1, data);
	TabRecord<int, string> tr2(tr1);
	EXPECT_EQ(*tr1.GetData(), *tr2.GetData());
}

TEST(TabRecord, different_records_not_equal) {
	string* data = new string("test");
	TabRecord<int, string> tr1(1, data);
	TabRecord<int, string> tr2(2, data);
	EXPECT_NE(tr1, tr2);
}

TEST(TabRecord, assignment_works_correctly) {
	string* data = new string("test");
	TabRecord<int, string> tr1(1, data);
	TabRecord<int, string> tr2(2, data);
	tr2 = tr1;
	EXPECT_EQ(tr1, tr2);
}
