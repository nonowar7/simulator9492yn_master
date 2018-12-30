

#include "TableManager.h"

// reading paths from file to hash map
int TableManager::getAddressesFromFile() {

    ifstream file;
    file.open("addresses.txt");
    if (file.bad()) {
        cout << "file problem" << endl;
        return -1;
    }

    string address;
    int index=0;

    // adding the paths to orderToPath map
    while (file >> address) {
        this->orderToPath[index] = address;
        index++;
    }

    file.close();
    return 0;
}

// binding variable to a path
void TableManager::bindStringToPath(const string& var, const string& path) {

    // locking access to the map
    Threader* threader = Threader::getInstance();
    threader->getThreader().mut->lock();

    //  enter var and path to stringToPath map
    this->stringToPath[var] = path;

    // enter vae's value to stringToValue map
    this->stringToValue[var] = this->pathToValue[path];

    // add another var to vector of the known path
    vector<string> temp = this->pathTostring[path];
    temp.push_back(var);
    this->pathTostring[path] = temp;

    // unlocking access
    threader->getThreader().mut->unlock();

}

// checking if a variable exists in stringToValue map
bool TableManager::isVarInTable(const string& varName) {

    Threader* threader = Threader::getInstance();
    threader->getThreader().mut->lock();

    bool ans = false;
    if (this->stringToValue.count(varName) > 0) {
        ans = true;
    }

    threader->getThreader().mut->unlock();

    return ans;
}

// checking if a variable is local or bind to path
bool TableManager::isVarBindToAddress(const string& varName){

    Threader* threader = Threader::getInstance();
    threader->getThreader().mut->lock();
    bool ans =  (bool)stringToPath.count(varName);
    threader->getThreader().mut->unlock();

    return ans;
}

// pulling a variables path from map
string TableManager::getVarAddress(const string& varName){

    Threader* threader = Threader::getInstance();
    threader->getThreader().mut->lock();

    string address = stringToPath[varName];

    threader->getThreader().mut->unlock();

    return address;
}

/*
 * taking the first 23 values from a string (separated
 * by commas) and passing them for update
 */

string TableManager::cut23Values(string str) {

    TableManager* tableManager = TableManager::getInstance();
    string temp;

    // 23 values are ended with /n
    while (str.at(0) != ENTER) {

        temp += str.at(0);
        str = str.substr(1, str.size() - 1);
    }

    str = str.substr(1, str.size() - 1);

    tableManager->updateTheTables(temp);

    return str;
}

/*
 * separating the values from each other and inserting
 * them by order to the maps.
 */
void TableManager::updateTheTables(string values) {

    Threader* threader = Threader::getInstance();
    string value;
    int index =0 ;

    while (index < SET_VALUES) {
        bool checkValues = values.empty();
        // values are separated by commas
        if (!checkValues && values.at(0) != ',') {
            value += values.at(0);
        } else {

            threader->getThreader().mut->lock();

            // inserting values to pathToValue map
            double number = stod(value);
            string path = this->orderToPath[index];
            this->pathToValue[path] = number;

            // inserting values to other binded variables
            // via path
            vector<string> v = (this->pathTostring[path]);
            vector<string>:: iterator itr;
            for( itr = v.begin(); itr != v.end(); itr++) {
                this->stringToValue[*itr] = number;
            }

            threader->getThreader().mut->unlock();

            index++;
            value="";
        }

        if (!checkValues) {
            values = values.substr(1, values.size() - 1);
        }

    }
}

// pulling variable's value
double TableManager::getVarValue(const string& var) {
    Threader* threader = Threader::getInstance();
    threader->getThreader().mut->lock();

    double value = this->stringToValue[var];

    threader->getThreader().mut->unlock();

    return value;
}

// updating variable's value in stringToValue map
void TableManager::updateLocalVar(const string& var, double value) {

    Threader* threader = Threader::getInstance();
    threader->getThreader().mut->lock();
    this->stringToValue[var] = value;
    threader->getThreader().mut->unlock();

}

void TableManager::updateClientData(const string& var, double num) {

    Threader* threader = Threader::getInstance();
    threader->getThreader().mut->lock();

    // pulling variable's path
    string path = this->stringToPath[var];

    // sending the new var's info to the simulator
    threader->setVarString(var);
    threader->setValue(num);
    informSimulator(path);

    // sending info on other binded vars only if the
    // vector contains more than 1 var
    vector<string> v = (this->pathTostring[path]);
    if (v.size() > 1) {
        vector<string>:: iterator itr;
        for( itr = v.begin(); itr != v.end(); itr++) {
            this->stringToValue[*itr] = num;
        }
    }

    threader->getThreader().mut->unlock();

}

/*
 * passing the variable's that has been updated
 * to the simulator (informing is made immediately
 * after variable is updated
 */
void TableManager::informSimulator(const string& path) {

    Threader* threader = Threader::getInstance();
    // creating information pattern
    string line = "set " + path + " " + to_string(threader->getThreader().value) + string("\r\n");

    // writing to simulator
    ssize_t writeValue = write(threader->getThreader().clientSocket,line.c_str(), line.length());

    if (writeValue < 0) {
        throw "problem while writing to simulator";
    }

}