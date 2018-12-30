
#ifndef SIMULATOR9492YN_MASTER_THREADER_H
#define SIMULATOR9492YN_MASTER_THREADER_H

#include <string>
#include <thread>
#include <mutex>

using namespace std;

/*
 * structure of variables that are needed
 * for read/write actions
 */
struct threadData {

    // sockets
    int serverSocket;
    int clientSocket;

    // frequency of reading
    int hz;

    // variable and it's value (updating simulator)
    string var;
    double value;

    // mutex for locking (set from Runner)
    mutex* mut;
};

class Threader {

private:

    threadData tData;

public:

    // getter
    threadData getThreader() const {
        return this->tData;
    }

    // setters
    void setServerSocket(int serverSocket) {
        this->tData.serverSocket = serverSocket;
    }

    void setClientSocket(int clientSocket) {
        this->tData.clientSocket = clientSocket;
    }

    void setServerHz(int hz) {
        this->tData.hz = hz;
    }

    void setMutex(mutex* m) {
        this->tData.mut = m;
    }

    void setVarString(const string& var) {
        this->tData.var = var;
    }

    void setValue(double value) {
        this->tData.value = value;
    }

    // static instance
    static Threader* getInstance(){
        static Threader* instance;
        if (instance == NULL) {
            instance = new Threader();
        }
        return instance;
    }


};

#endif //SIMULATOR9492YN_MASTER_THREADER_H
