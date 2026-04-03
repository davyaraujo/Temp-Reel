CXX = arm-linux-g++ -Wall -Wextra
PTHREAD_FLAGS = -lpthread
BIN_DIR = bin

# Create bin directory if it doesn't exist
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# TP1
tp1: $(BIN_DIR)
	$(CXX) TP1/tp1.cpp TP1/Chrono.cpp TP1/timespec.cpp -o $(BIN_DIR)/tp1

# TP2 exercises
tp2a: $(BIN_DIR)
	$(CXX) TP2/tp2a.cpp -o $(BIN_DIR)/tp2a -lrt

tp2b: $(BIN_DIR)
	$(CXX) TP2/tp2b.cpp -o $(BIN_DIR)/tp2b -lrt

tp2c: $(BIN_DIR)
	$(CXX) TP1/Chrono.cpp TP1/timespec.cpp TP2/tp2c.cpp -o $(BIN_DIR)/tp2c -lrt

tp2de: $(BIN_DIR)
	$(CXX) TP1/Chrono.cpp TP1/timespec.cpp TP2/tp2d-e.cpp -o $(BIN_DIR)/tp2de -lrt

tp3c: $(BIN_DIR)
	$(CXX) TP3/Mutex.cpp TP3/thread.cpp TP1/Chrono.cpp TP1/timespec.cpp TP3/TD3-c.cpp $(PTHREAD_FLAGS) -o $(BIN_DIR)/tp3c -lpthread

tp3d: $(BIN_DIR)
	$(CXX) TP3/TD3-d.cpp TP3/Mutex.cpp TP3/thread.cpp TP3/semaphore.cpp  TP1/Chrono.cpp TP1/timespec.cpp TP3/monitor.cpp $(PTHREAD_FLAGS) -o $(BIN_DIR)/tp3d -lpthread

tp3e: $(BIN_DIR)
	$(CXX) TP3/TD3-e.cpp TP3/Mutex.cpp TP3/thread.cpp TP3/semaphore.cpp TP1/Chrono.cpp TP1/timespec.cpp TP3/monitor.cpp $(PTHREAD_FLAGS) -o $(BIN_DIR)/tp3e -lpthread -lrt

tp4: $(BIN_DIR)
	$(CXX) TP1/Chrono.cpp TP1/timespec.cpp TP3/TD4.cpp TP3/Mutex.cpp TP3/thread.cpp TP3/semaphore.cpp TP3/monitor.cpp $(PTHREAD_FLAGS) -o $(BIN_DIR)/tp4 -lpthread

# Clean
clean:
	@rm -rf $(BIN_DIR)
	@echo "Cleaned!"

.PHONY: tp1 tp2a tp2b tp2c tp2de tp3c tp3d tp3e tp4 clean