#ifndef FILELIST_H
#define FILELIST_H

#include <list>

class BHFile;

class FileList : public std::list<BHFile* const> {
public:
  /*! \brief Constructs an empty FileList
   */
  FileList();

  /*! \brief Add a BHFile object to the FileList
   * \param f pointer to the BHFile to add
   * \sa addFile(const string& path)
   * 
   * Adds a pre-existing BHFile object to the FileList,
   * usually already filled with hash data.
   */
  void addFile(BHFile* f);

  /*! \brief Add a file by path to the FileList
   * \param path path to the file to add
   * \sa addFile(BHFile* f)
   * 
   * Adds a file by path to the FileList,
   * usually without hashdata available but to
   * be hashed by the Hasher.
   */
  void addFile(const string& path);

  /*! \brief Recursively add files
   * \param path path to the file/directory to add
   * \sa addFile(BHFile* f)
   * 
   * Add all files under addRecursive to the FileList
   * recursively. Creates a BHFile object for every
   * file including its fileSize.
   */
  void addRecursive(const string& path);
}

#endif //FILELIST_H