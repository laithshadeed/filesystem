#include <string>
#include <vector>
#include <unordered_map>
#include <iterator>
#include <sstream>
#include <iostream>
#include "directory.h"
#include "file.h"
#include "commands.h"

//Split command line into spaces
void tokenize(const std::string &line, std::vector<std::string> &tokens);

//Apply the parsed command to its mapped function in commands.h
void apply (const functionMap & supportedCommands, const std::string & command,
   const std::vector<std::string> & argv, Directory* &cwd);

void printWelcomeMessage();

int main()
{
   //Initialize a root directory of /
   Directory* root = new Directory("/", 0);
   Directory* cwd = root; //The current working directory used accross the application

   //Input variables
   std::string line;
   std::vector<std::string> argv;

   printWelcomeMessage();

   //The main application loop responsible to handle user inputs
   while(std::getline(std::cin, line)) {
      //Parse the input line into arguments, split by space, we don't support double/single quotes or char escaping
      tokenize(line, argv);

      if(argv.empty()) {
         std::cout << "Please provide some input" << std::endl;
         std::cout << "$ ";
         continue;
      }

      //Extract the command
      std::string command = argv[0];

      //Handle special commands: exit
      if(command == "exit") {
         break;
      }

      if(supportedCommands.find(command) == supportedCommands.end()) {
         std::cout << "Invalid command." << std::endl;
         std::cout << "$ ";
         continue;
      }

      argv.erase(argv.begin()); //Remove the command name from the argument vector
      apply(supportedCommands,command, argv, cwd);
      argv.erase(argv.begin(), argv.end()); //Clean the old argument vector after each input
      std::cout << "$ ";
   }
}

void tokenize(const std::string &line, std::vector<std::string> &tokens)
{
   std::istringstream stream(line);
   std::copy(std::istream_iterator<std::string>(stream),
             std::istream_iterator<std::string>(),
             std::back_inserter<std::vector<std::string>>(tokens)
            );
}


void apply (const functionMap & supportedCommands, const std::string & command,
   const std::vector<std::string> & argv, Directory* &cwd)
{
   (*supportedCommands.at(command))(argv, cwd);
}

void printWelcomeMessage()
{
   //Generate a string commands list dynamically for their map
   std::string listOfCommands = "";
   for(auto it = helpMap.begin(); it != helpMap.end(); it++) {
       listOfCommands += it->first + ",";
   }
   listOfCommands = listOfCommands.substr(0, listOfCommands.size() - 1); //strip the last comma

   //Print the weclome messages
   std::cout << "Welcome to the simple in-memory filesystem." << std::endl;
   std::cout << "List of commands: " << listOfCommands << "." << std::endl;
   std::cout << "For help type: help <command>" << std::endl;
   std::cout << "To exit type: exit" << std::endl;
   std::cout << "$ ";
}
