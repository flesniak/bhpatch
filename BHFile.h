#ifndef BHFILE_H
#define BHFILE_H

#include <string>
#include <vector>

class BHFile {
public:
  BHFile(const std::string& path = std::string());

  string getPath() const;
  void setPath(const string& fileName);

  uint64_t getSize() const;
  void setSize(uint64_t size);

  const std::vector<char[16]>& getHashes() const;
  void setHashes(const std::vector<char[16]>& hashData);
  void appendHash(char[16] hash);

private:
  std::vector<char[16]> p_hashes;
  string p_path;
  uint64_t p_size;
}

#endif //BHFILE_H