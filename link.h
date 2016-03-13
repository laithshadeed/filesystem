#ifndef _LINK_H_
#define _LINK_H_

#include "node.h"

class Link : public Node
{
   public:
      Link(std::string inName, Directory* inParent, Node* inLink);
      Node* getHandle();
   private:
      Node* link;
};

#endif /* _LINK_H_ */
