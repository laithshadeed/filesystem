#ifndef _FILE_H_
#define _FILE_H_

#include "node.h"

class File : public Node
{
   public:
      File(std::string name, Directory* parent, int size);

      /** Read operation **/
      std::string getContents() const;

      /** Write operation **/
      void setContents(std::string inContents);
   private:
      std::string contents;
};

#endif /* _FILE_H_ */
