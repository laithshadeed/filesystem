#ifndef _DIRECTORY_H_
#define _DIRECOTRY_H_

#include <vector>
#include <algorithm>
#include <utility>
#include "node.h"

class Directory : public Node
{
   public:
      Directory(std::string inName, Directory* inParent);

      /** Write operations **/
      bool remove(Node* node);
      bool add(Node* node);

      /** Read operations **/
      long long getSize() const;
      int getNodesCount() const;
      HashTable* getNodes() const;
      using Node::getHandle;
      Node* getHandle(std::string inName);

   private:
      HashTable* nodes;
};

#endif /* _DIRECTORY_H_ */
