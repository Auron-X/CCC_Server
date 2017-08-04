CFLAGS = -I/usr/local/cuda/include -I/usr/include/hdf5/serial -I/opt/caffe/include -I/opt/caffe/build/include -I/usr/local/include/opencv -I/usr/local/include
LIBS = -L/usr/local/lib -lpthread
	
server:
	g++ $(CFLAGS) server.cpp -o server $(LIBS)