
#ifndef SIMULATOR9492YN_MASTER_TABLEMANAGER_H
#define SIMULATOR9492YN_MASTER_TABLEMANAGER_H

#include <unordered_map>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <chrono>
#include <unistd.h>
#include <sys/socket.h>
#include <thread>
#include <mutex>
#include <vector>
#include "Threader.h"
#include "Expression.h"

#define ENTER 10
#define MILLI_IN_SECONDS 1000
#define BUFFER_SIZE 1024
#define SET_VALUES 23

using namespace std::chrono_literals;
using namespace std;

/*
 * responsibility - handling all the information
 * and data in the program via hash maps
 */
class TableManager {

    unordered_map<string, double> pathToValue;
    unordered_map<int, string> orderToPath;

    // main tables
    unordered_map<string, double> stringToValue;
    unordered_map<string, string> stringToPath;
    unordered_map<string, vector<string>> pathTostring;

public:

    // static instance
    static TableManager* getInstance(){
        static TableManager* instance;
        if (instance == NULL) {
            instance = new TableManager();
        }
        return instance;
    }

    // explanations in cpp file
    int getAddressesFromFile() ;
    void bindStringToPath(const string& var, const string& path);
    bool isVarInTable(const string& varName) ;
    bool isVarBindToAddress(const string& varName);
    string getVarAddress(const string& varName);
    string cut23Values(string str) ;
    void updateTheTables(string values) ;
    double getVarValue(const string& var);
    void updateLocalVar(const string& var, double value) ;
    void updateClientData(const string& var, double num) ;
    void informSimulator(const string& path) ;


    // getter
    unordered_map<string,double> getStringToValueMap() const {
        return this->stringToValue;
    }

    /*
     * function is called from OpenDataServer -
     * opened when we create the first reading socket.
     * this function reads data from the simulator once,
     * then sends it to TableManager.
     */
    static void* firstReadFromSimulator(void* t) {

        TableManager* tableManager = TableManager::getInstance();

        // creating buffer for reading
        char buffer[BUFFER_SIZE];
        bzero(buffer,BUFFER_SIZE);

        // reading data
        ssize_t readValue = read(((Threader *) t)->getThreader().serverSocket, buffer, BUFFER_SIZE);

        // checking data received properly
        if (readValue < 0) {
            throw exception();
        }

        // sending data to TableManager proccess.
        string str = string(buffer);
        str = tableManager->cut23Values(str);
    }

    /*
    * function is called from OpenDataServer -
    * opened when we create the second reading socket.
    * this function reads data from the simulator as long as
    * the program runs.
    */
    static void* generalReadFromSimulator(void* t) {

        TableManager* tableManager = TableManager::getInstance();
        char buffer[BUFFER_SIZE];
        bzero(buffer,BUFFER_SIZE);

        ssize_t readValue = 0;

        // considering frequency of reading
        double timeRound = (double)MILLI_IN_SECONDS/((Threader *) t)->getThreader().hz;
        string str1;

        /*
         * reading from simulator as long as the data is received
         * without error ("infinite loop").
         */
        while (readValue!=-1) {

            // measuring initial time of action
            auto currentTime = chrono::steady_clock::now();

            // reading data to buffer
            readValue = read(((Threader *)t)->getThreader().serverSocket, buffer, BUFFER_SIZE);

            // sending data for update
            if (!str1.empty()) {
                str1 += string(buffer);
                str1 = tableManager->cut23Values(str1);
            } else {
                str1 = string(buffer);
                str1 = tableManager->cut23Values(str1);
            }

            // clearing buffer
            bzero(buffer, BUFFER_SIZE);

            // measuring current time in respect of initial time
            auto endTime = chrono::steady_clock::now();
            double timeUsed = chrono::duration_cast<chrono::milliseconds>(endTime-currentTime).count();
            double remained = timeRound-timeUsed;

            // sleeping if needed (if a ten'th of a second is not passed)
            if (remained > 0) {
                this_thread::sleep_for(std::chrono::milliseconds((int)remained));
            }
        }

        cout << "simulator done sending / problem while reading from simulator" << endl;

    }




};

#endif //SIMULATOR9492YN_MASTER_TABLEMANAGER_H
