all: partition
partition:
	g++ -o partition partition.cpp
clean:
	rm -f partition