#include "link.h"

Link::Link(std::string inName, Directory* inParent, Node* inLink)
   : Node(inName, inParent)
{
   link = inLink;
}
Node* Link::getHandle()
{
   return link;
}
