#ifndef HASHER_H
#define HASHER_H

#include "FileList.h"

class Hasher {
public:
  Hasher(FileList* files, int blockSize);
  void hash();
  void verify();
  int getBlockSize() const;

private:
  int p_blockSize;
}

#endif //HASHER_H