#ifndef SIMULATOR9492YN_MASTER_RUNNER_H
#define SIMULATOR9492YN_MASTER_RUNNER_H

#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "TableManager.h"
#include "ShuntingYard.h"

using namespace std;

/*
 * running the program from a file (running lexer and
 * then parser via lines commited).
 */
class Runner {

    // mutex variable for the program
   mutex mu;

public:

    /*
     * running lexer and parser with line data
     */
    void runTheProgram(const string& line, Lexer* lexer, Parser* parser) {
        lexer->setLine(line);
        parser->setLine(lexer->lexicalAnalysis());
        parser->parserAnalysis();
    }

    /*
     * program initialization
     */
    void run(int argc, char* argv[]) {

        // download addresses from file
        TableManager *tableManager = TableManager::getInstance();
        int paths = tableManager->getAddressesFromFile();
        if (paths < 0) {
            cout << "problem with paths" << endl;
            return;
        }

        // set mutex variable
        Threader *threader = Threader::getInstance();
        threader->setMutex(&mu);

        // set lexer and parser objects
        Lexer lexer;
        Parser parser;
        string line;

        /*
         * verifying validation of input and reading it,
         * then calling 'run the program' ot
         */
        if (argc > 1) {
            string fileName = argv[1];
            ifstream file(fileName);
            if (file.is_open()) {
                while (getline(file, line)) {
                    runTheProgram(line, &lexer, &parser);
                }
                file.close();
            }
        } else {
            return;
        }

        // closing sockets
        close(threader->getThreader().serverSocket);
        close(threader->getThreader().clientSocket);
    }
};

#endif