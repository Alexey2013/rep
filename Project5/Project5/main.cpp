#include  "header.h"
#include <iostream>
using namespace std;

int main() {
	string path = get_path();
	group group(path);
	group.menu(path);
	return 0;
}