#include "directory.h"

Directory::Directory(std::string inName, Directory* inParent)
   : Node(inName, inParent)
{
   nodes = new HashTable();
}

bool Directory::remove(Node* node)
{
   return false;
}

bool Directory::add(Node* node)
{
   auto item = nodes->find(node->getName());
   if(item != nodes->end()) {
         //item already there
         return false;
   }

   nodes->insert(Directory::HashTablePair(node->getName(), node));
   return true;
}


long long Directory::getSize() const
{
   long long size = 0;

   for(auto it = nodes->begin(); it != nodes->end(); it++) {
      size += it->second->getSize();
   }

   return size;
}

int Directory::getNodesCount() const
{
   int count = 0;

   for(auto it = nodes->begin(); it != nodes->end(); it++) {
      count += it->second->getNodesCount();
   }

   return count;
}

Directory::HashTable* Directory::getNodes() const
{
   return nodes;
}

Node* Directory::getHandle(std::string inName)
{
   if(inName.empty()) {
		return this;
	}

   auto item = nodes->find(inName);
   if(item != nodes->end()) {
         return item->second;
   }

   return 0;
}
