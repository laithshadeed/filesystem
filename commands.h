void ls(const std::vector<std::string> & argv, Directory* &cwd)
{
   std::vector<std::string> dirList = argv;
   Node* handle = cwd;
   bool printDirName = dirList.size() > 1;
   if(dirList.empty()) {
      dirList.push_back(""); //getHandle will return a handle for the current if empty string provided
   }
   for(auto dirName: dirList) {
      if(printDirName) {
         std::cout << dirName << ":" << std::endl;
      }

      handle = cwd->getHandle(dirName);

      if(dirName == ".") {
         handle = cwd->getHandle(); //get the current node handle
      }

      if(dirName == "..") {
         handle = cwd->getParent()->getHandle();
      }

      if(!handle) {
         std::cout << "ls: cannot access " << dirName << ": No such file or directory" << std::endl;
         continue;
      }

      auto nodes = handle->getNodes();
      if(!nodes || nodes->empty()) {
         continue;
      }

      for(auto it = nodes->begin(); it != nodes->end(); it++) {
         std::cout << it->second->getName() << std::endl;
      }
   }
}

void cd(const std::vector<std::string> & argv, Directory* &cwd)
{
   std::string name = ".."; //initial assumption going up

   if(!argv.empty()) {
      name = argv[0];
   }


   if(name == ".") {
      return; //cd same directory
   }

   if(name == "..") {
      Directory* parent = cwd->getParent();
      if(!parent) {
         return; //Trying to cd above '/'
      }

      cwd = parent;
      return;
   }

   Node* handle = cwd->getHandle(name);
   if(!handle) {
      std::cout << "cd: " << name << ": No such file or directory" << std::endl;
      return;
   }

   //Check if the handle is directory then cd otherwise print error
   Directory* dir = dynamic_cast<Directory*>(handle);
   if(!dir) {
      //The user trying to cd file, return
      std::cout << "cd: " << name << ": Not a directory" << std::endl;
      return;
   }

   //cd to that dir
   cwd = dir;
}

void pwd(const std::vector<std::string> & argv, Directory* &cwd)
{
   std::cout << cwd->getFullPath() << std::endl;
}


void mkdir(const std::vector<std::string> & argv, Directory* &cwd)
{
   for(auto& name : argv) {
      if(name[0] == '-') {
         std::cout << "mkdir: options are not supported in this version" << std::endl;
         break;
      }

      if(name.find('/') != std::string::npos) {
         std::cout << "mkdir: Nested directory creation is not supported in this version" << std::endl;
         break;
      }

      //To add '.' & '..' inside Directory constructor later, then no need for this if-stmt
      if(name == "." || name == "..") {
         std::cout << "mkdir: cannot create directory `" << name << "`: File exist" << std::endl;
         continue;
      }

      Directory* dir = new Directory(name, cwd);
      if(!cwd->add(dir)) {
         std::cout << "mkdir: cannot create directory `" << name << "`: File exist" << std::endl;
         continue;
      }
   }
}

void rm(const std::vector<std::string> & argv, Directory* &cwd)
{
   std::cout << "Sorry, rm is not supported in this version" << std::endl;
}

void touch(const std::vector<std::string> & argv, Directory* &cwd)
{
   std::cout << "Sorry, touch is not supported in this version" << std::endl;
}

void echo(const std::vector<std::string> & argv, Directory* &cwd)
{
   std::cout << "Sorry, echo is not supported in this version" << std::endl;
}

void cat(const std::vector<std::string> & argv, Directory* &cwd)
{
   std::cout << "Sorry, cat is not supported in this version" << std::endl;
}


void ln(const std::vector<std::string> & argv, Directory* &cwd)
{
   std::cout << "Sorry, ln is not supported in this version" << std::endl;
}

typedef void(*funcionPointer)(const std::vector<std::string> & argv, Directory* &cwd);
typedef std::unordered_map<std::string, funcionPointer> functionMap;

//Mapping commands to their help menu
std::unordered_map<std::string, std::string> helpMap = {
   {"ls",      "Usage: ls [FILE]...\n"
               "List information about the FILEs (the current directory by default)."},
   {"cd",      "Usage: cd [Directory]\n"
               "Change the current working directory to a specific folder, if no arugment change to '..' by default"},
   {"pwd",     "Usage: pwd\n"
               "Write to standard output an absolute pathname of the current working directory"},
   {"mkdir",   "Usage: mkdir DIRECTORY...\n"
               "Create the DIRECTORY(ies), if they do not already exist."},
   {"rm",      "Usage: rm [OPTION]... FILE...\n"
               "Remove (unlink) the FILE(s).\n"
               "-r remove directories and their contents recursively"},
   {"touch",   "Usage: touch FILE...\n"
               "Update the access and modification times of each FILE to the current time.\n"
               "A FILE argument that does not exist is created empty"},
   {"echo",    "Usage: echo [STRING]...\n"
               "Echo the STRING(s) to standard output and can be piped to a file"},
   {"cat",     "Usage: cat [FILE]...\n"
               "Concatenate FILE(s)"},
   {"ln",      "Usage: ln TARGET LINK_NAME\n"
               "Create a link to TARGET with the name LINK_NAME"}
   ,
};


void help(const std::vector<std::string> & argv, Directory* &cwd)
{
   if(argv.size() != 1) {
      std::cout << "Invalid number of arguments" << std::endl;
      std::cout << "help <command>" << std::endl;
      return;
   }

   std::string arg = argv[0];

   if(helpMap.find(arg) == helpMap.end()) {
      std::cout << "No help entry for " << arg << std::endl;
      return;
   }

   std::cout << helpMap.at(arg) << std::endl;
   return;
}

//Mapping commands to their functions defined in commands.h
std::unordered_map<std::string, funcionPointer> supportedCommands = {
   {"ls", &ls},
   {"cd", &cd},
   {"pwd", &pwd},
   {"mkdir", &mkdir},
   {"rm", &rm},
   {"touch", &touch},
   {"echo", &echo},
   {"ln", &ln},
   {"cat", &cat},
   {"help", &help},
};
