#ifndef CONFIGFILE_H
#define CONFIGFILE_H

class FileList;

class ConfigFile {
public:
  /*! \brief Constructs the ConfigFile object
   * 
   * Creates an empty FileList ready to use when hashing
   * new files or to load an existing config file to verify.
   */
  ConfigFile();

  /*! \brief Load a configuration file
   * \param config path of the configuration file to use
   * 
   * Tries load a configuration file and create a FileList
   * containing all BHFiles described in the config file
   */
  void loadConfigFile(const string& config);

  /*! \brief Save a configuration file
   * \param config path of the configuration file to use
   * 
   * Tries to save the internal FileList to disk.
   */
  void saveConfigFile(const string& config);

  FileList* getFileList();

private:
  FileList* p_fileList;
}

#endif //CONFIGFILE_H