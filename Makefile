all: test.cpp share.cpp
	g++ -fPIC -g -lpthread -shared share.cpp -o libshared.so
	g++ -ldl -ltbb_debug -ltbbmalloc_debug -ltbbmalloc_proxy -g test.cpp
