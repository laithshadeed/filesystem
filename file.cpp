#include "file.h"

File::File(std::string inName, Directory* inParent, int inSize )
   : Node( inName, inParent )
{
   size = inSize;
}

std::string File::getContents() const
{
   return contents;
}

void File::setContents(std::string inContents)
{
   contents = inContents;
}
