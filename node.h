/*
For this question, I’d like you to build an OOP representation of a filesystem.
Think about what objects, methods and attributes to use as well as how they relate.
As a bonus, think about how you would add symlinks or hardlinks. I’d like you to implement this in an OO language such as C++ or Java.
*/

#ifndef _NODE_H_
#define _NODE_H_

#include <string>
#include <unordered_map>

class Directory;

class Node
{
   protected:
      typedef std::unordered_map<std::string, Node*> HashTable;
      typedef std::pair<std::string, Node*> HashTablePair;

      Directory* parent;

      std::string name;
      std::string owner;
      int ownerID;
      std::string group;
      int groupID;

      long long size;
      long creationTime;
      long updateTime;
      long accessTime;
      short permission;

   public:
      Node(const std::string & inName, Directory* inParent);

      /** Write operations **/
      bool remove(); //It will remove the current node (if empty) from its parent
      virtual bool remove(Node* node); //It will remove the passed node from this object
      virtual bool add(Node* node);

      /** Read operations **/
      Directory* getParent() const;
      std::string getFullPath() const;
      virtual long long getSize() const;
      virtual int getNodesCount() const; //Recursive call to all childs nodes
      virtual std::string getContents() const;
      virtual HashTable* getNodes() const;
      virtual Node* getHandle(); //If node is link it will return the linked node
      virtual Node* getHandle(std::string inName); //If node is directory it will the node with the specificed name

      //Setters
      void setName(const std::string & inName);
      void setOwner(std::string inOwner);
      void setOwnerID(int inOwnerID);
      void setGroup(std::string inGroup);
      void setGroupID(int inGroupID);
      void setCreationTime(long inCreationTime);
      void setUpdateTime(long inUpdateTime);
      void setAccessTime(long inAccessTime);
      void setPermission(short iPermission);

      //Getters
      std::string getName() const;
      std::string getOwner() const;
      int getOwnerID() const;
      std::string getGroup() const;
      int getGroupID() const;
      long getCreationTime() const;
      long getUpdateTime() const;
      long getAccessTime() const;
      short getPermission() const;
};

#endif /* _NODE_H_ */
