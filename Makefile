main: src/main.cpp src/Node.cpp src/Search.cpp
	g++ -o main src/main.cpp src/Node.cpp src/Search.cpp src/Node_15.cpp -std=c++11

clean:
	rm main