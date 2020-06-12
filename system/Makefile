# Makefile for building RT system

build_all: clean build_data_provider build_data_processing build_data_archiver

build_data_provider:
	g++ data_provider.cpp pshm.h -o data_provider `pkg-config opencv --cflags --libs` -lrt -pthread

build_data_processing:
	g++ data_processing.cpp pshm.h -o data_processing `pkg-config opencv --cflags --libs` -lrt -pthread

build_data_archiver:
	g++ data_archiver.cpp pshm.h -o data_archiver `pkg-config opencv --cflags --libs` -lrt -pthread

clean:
	rm -f data_provider
	rm -f data_processing
	rm -f data_archiver