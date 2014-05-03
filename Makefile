main_server:./src/*.cpp -I./include 
	g++ -g -o $@ $< -lpthread