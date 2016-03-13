#include "node.h"
#include "directory.h"

Node::Node(const std::string & inName, Directory* inParent)
{
	name = inName;
	parent = inParent;
}

/** Write Operations **/

bool Node::remove()
{
	//Just remove this node from its parent
	if(!parent) {
		return true;
	}

	return parent->remove(this);
}

bool Node::remove(Node* node)
{
	return false; //Could be replaced by exception that said "You should override to use this method"
}

bool Node::	add(Node* node)
{
	return false; //Could be replaced by exception that said "You should override to use this method"
}

/** Read Operations **/
Directory* Node::getParent() const
{
	return parent;
}

std::string Node::getFullPath() const
{
	if(!parent) {
		return name;
	}
	
	std::string parentPath = parent->getFullPath();
	
	if(parentPath == "/") {
		return parentPath + name;
	}
	
	return parentPath + '/' + name;
}

long long Node::getSize() const
{
	return size;
}

int Node::getNodesCount() const
{
	return 1; //Default behaviour of 1 file
}

Node* Node::getHandle()
{
	return this;
}

Node* Node::getHandle(std::string inName)
{
	if(inName.empty() || name == inName) {
		return this;
	}
	
	return 0;
}

Node::HashTable* Node::getNodes() const
{
	return 0;
}

std::string Node::getContents() const
{
	return getName();
}


//Setters
void Node::setName(const std::string & inName)
{
	name = inName;
}

void Node::setOwner(std::string inOwner)
{
   owner = inOwner;
}

void Node::setOwnerID(int inOwnerID)
{
   ownerID = inOwnerID;
}

void Node::setGroup(std::string inGroup)
{
   group = inGroup;
}

void Node::setGroupID(int inGroupID)
{
   groupID = inGroupID;
}

void Node::setCreationTime(long inCreationTime)
{
   creationTime = inCreationTime;
}

void Node::setUpdateTime(long inUpdateTime)
{
   updateTime = inUpdateTime;
}

void Node::setAccessTime(long inAccessTime)
{
   accessTime = inAccessTime;
}

void Node::setPermission(short inPermission)
{
   permission = inPermission;
}

//Getters
std::string Node::getName() const
{
	return name;
}

std::string Node::getOwner() const
{
   return owner;
}

int Node::getOwnerID() const
{
   return ownerID;
}

std::string Node::getGroup() const
{
   return group;
}

int Node::getGroupID() const
{
   return groupID;
}

long Node::getCreationTime() const
{
   return creationTime;
}

long Node::getUpdateTime() const
{
   return updateTime;
}

long Node::getAccessTime() const
{
   return accessTime;
}

short Node::getPermission() const
{
   return permission;
}
