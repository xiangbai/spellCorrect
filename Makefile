server:./src/MutexLock.cpp ./src/Condition.cpp ./src/Thread.cpp ./src/WorkThread.cpp ./src/ThreadPool.cpp ./src/Server.cpp ./src/main_server.cpp  
	g++ -g -o $@ $< -lpthread -I./include