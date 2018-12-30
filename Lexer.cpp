#include "Lexer.h"
#include <regex>

/**
 * The function separateOperations get string line,
 * And add spaces between operators: !,<,>,=.
 * It returns the new fixed line.
 */
string Lexer::separateOperations() {
    int i =0;
    string fixedLine;
    // Pass on every character in the line
    while (i < line.length()){
        // If the character is an operator
        if(line[i] =='=' || line[i] =='!' || line[i] =='<' || line[i] =='>'){
            fixedLine=fixedLine + " " + line[i] + " ";
        } else {
            fixedLine = fixedLine + line[i];
        }
        // Move to the next character
        i++;
    }
    // Return the fixed line
    return fixedLine;
}

/**
 * The function checkMatch check if the regex pattern match the string.
 * Return true if the pattern exist in the string and false otherwise.
 */
bool checkMatch (regex regexPattern, string str){
    smatch match;
    regex_search(str,match,regexPattern);
    // If there is a match return true
    if(!match.empty()){
        return true;
    }
    return false;
}

/**
 * The function checkUniqueCharacters - checks the first and the last character in the word.
 * If one of them is a unique character it update the boolean pointers head and back.
 * When the pointers gets false, it means that the word need to join to the next or the previous token,
 * Depends on the pointer that got the false.
 */
void checkUniqueCharacters(string word,bool* head,bool* back){
    string str;
    regex regOperator ("[-*/+]");
    regex leftBracket ("[(]");
    regex rightBracket ("[)]");
    bool matchingAnswer;
    char start = word[0];
    char end = word[word.length()-1];
    // Push the first character in the word
    str.push_back(start);
    matchingAnswer = checkMatch(leftBracket, str);
    // If the first character is: ( - left bracket it need to join to the next token
    if(matchingAnswer) {
        *head = true;
        *back = false;
        return;
    }
    matchingAnswer = checkMatch(rightBracket, str);
    // If the first character is: ) - right bracket it dosn't need to join to the next token
    if(matchingAnswer) {
        *head = false;
    } else{
        // If the first character is an operator it need to join to the previous token
        matchingAnswer = checkMatch(regOperator,str);
        if(matchingAnswer){
            *head = false;
        } else {
            *head = true;
        }
    }
    // Pop the first character in the word
    str.pop_back();
    // Push the last character in the word
    str.push_back(end);
    // If the last character is: ( left bracket, it need to join to the next token
    matchingAnswer = checkMatch(leftBracket,str);
    if(matchingAnswer){
        *back = false;
        return;
    }
    // If the last character is: ) right bracket, it need to join to the previous token only
    matchingAnswer = checkMatch(rightBracket,str);
    if(matchingAnswer){
        *head = false;
        *back = true;
        return;
    }
    // If the last character is operation, it need to join to the next token
    matchingAnswer = checkMatch(regOperator,str);
    if(matchingAnswer) {
        *back = false;
        return;
    } else {
        *back = true;
    }
}

/**
 * The function lexicalAnalysis take the data member line,
 * And split in to vector words.
 */
vector<string> Lexer::lexicalAnalysis() {
    vector<string> commands;
    // Add spaces before and after operators
    string str = separateOperations();
    string buffer;
    regex whiteSpace ("[^\n\t ]+");
    smatch match;
    bool flag = false;
    bool front;
    bool back;
    // Separate every word in the line
    while (regex_search(str,match,whiteSpace)){
        // Put the first word in the buffer
        buffer = match.str((0));
        // remove the word from the line
        str = match.suffix().str();
        // send the word to the unique characters function
        checkUniqueCharacters(buffer,&front,&back);
        if(flag && commands.size()>0){
            // get the last word from the vector
            string temp = commands.back();
            // bind it with the last word
            temp = temp+buffer;
            // pop the old word
            commands.pop_back();
            // push the new word into the vector
            commands.push_back(temp);
        } else{
            if(front){
                // push the word into the vector
                commands.push_back(buffer);
            } else {
                if(commands.size()>1 && !checkMatch(regex("[<=>]"),commands[commands.size()-1])){
                    // get the last word from the vector
                    string temp = commands.back();
                    // bind it with the last word
                    temp = temp+buffer;
                    // pop the old word
                    commands.pop_back();
                    // push the new word into the vector
                    commands.push_back(temp);
                } else{
                    // push the word into the vector
                    commands.push_back(buffer);
                }
            }
        }
        // initial the flag
        if(!back){
            flag = true;
        } else{
            flag = false;
        }
    }
    // return the vector with the words
    return commands;
}
