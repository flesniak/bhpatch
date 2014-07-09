#include <unistd.h>
#include <string>
#include <exception>

#include "Logger.h"

using namespace std;

void usage() {
  LOG(logInfo) << "Usage: bhpatch <-a|b|c|d> [-q|v] <-f foo.bhashes> <-p foo.bhpatch>";
  LOG(logInfo) << "  -a : apply foo.bhpatch";
  LOG(logInfo) << "  -b : hash files to create foo.bhashes";
  LOG(logInfo) << "  -c : create foo.bhashes using foo.bhpatch";
  LOG(logInfo) << "  -d : display contents";
  LOG(logInfo) << "  -f : bhashes file to use";
  LOG(logInfo) << "  -p : patch file to use (only for modes apply/create)";
  LOG(logInfo) << "  -q : be more quiet";
  LOG(logInfo) << "  -v : be more verbose";
}

int main(int argc, char** argv) {
  Logger::facility() = new LoggerFacilityConsole();
  Logger::logLevel() = logDebug;

  enum operation_t { none, display, hash, create, apply } operation = none;

  string hashFilePath;
  string patchFilePath;

  int opt = 0;
  opterr = 0; //we print error messages ourselves
  while( (opt = getopt(argc, argv, "abcdf:p:hqv")) != -1 ) {
    switch( opt ) {
      case 'a' : LOG(logDebug) << "Option -a detected"; //apply patch
                 if( operation != none ) {
                   LOG(logError) << "You may only specify one operation";
                   return 1;
                 } else
                   operation = apply;
                 break;
      case 'b' : LOG(logDebug) << "Option -b detected"; //hash files
                 if( operation != none ) {
                   LOG(logError) << "You may only specify one operation";
                   return 1;
                 } else
                   operation = hash;
                 break;
      case 'c' : LOG(logDebug) << "Option -c detected"; //create patch
                 if( operation != none ) {
                   LOG(logError) << "You may only specify one operation";
                   return 1;
                 } else
                   operation = create;
                 break;
      case 'd' : LOG(logDebug) << "Option -d detected"; //display contents of file
                 if( operation != none ) {
                   LOG(logError) << "You may only specify one operation";
                   return 1;
                 } else
                   operation = display;
                 break;
      case 'f' : LOG(logDebug) << "Option -f detected"; //specify hash file
                 if( !hashFilePath.empty() ) {
                   LOG(logError) << "Multiple bhashes files specified";
                   return 1;
                 } else
                   //TODO read hashFilePath
                 break;
      case 'p' : LOG(logDebug) << "Option -p detected"; //specify patch file
                 if( !patchFilePath.empty() ) {
                   LOG(logError) << "Multiple bhpatch files specified";
                   return 1;
                 } else
                   //TODO read patchFilePath
                 break;
      case 'q' : LOG(logDebug) << "Option -q detected"; //quiet mode
                 if( Logger::logLevel() != logError )
                   Logger::logLevel() = (logLevel_t)((unsigned char)Logger::logLevel()-1);
                 break;
      case 'v' : LOG(logDebug) << "Option -v detected"; //verbose mode
                 if( Logger::logLevel() != logDebug )
                   Logger::logLevel() = (logLevel_t)((unsigned char)Logger::logLevel()+1);
                 break;
      case '?' : if( isprint(optopt) )
                   LOG(logError) << "Unknown option -" << (char)optopt;
                 else
                   LOG(logError) << "Unknown option character " << std::hex << optopt;
                 usage();
                 return 1;
                 break;
      default :  return 255;
    }
  }

  for( int index = optind; index < argc; index++ )
    LOG(logDebug) << "Non-option argument " << argv[index];

  if( optind+1 != argc ) {
    LOG(logError) << "No path given";
    usage();
    return 1;
  }
  string filePath(argv[optind]);

  switch( operation ) {
    case apply :
      break;
    case create :
      break;
    case display :
      break;
    case hash :
      try {
        ConfigFile cf;
        cf.getFileList()->addRecursively(filePath);
        Hasher h(cf.getFileList());
        h.hash();
        cf.saveConfigFile(hashFilePath);
      } catch(exception& e) {
        LOG(logError) << "An error occured during hashing:" << e.what();
      }
      break;
    default:
      LOG(logError) << "BUG: invalid operation mode";
  }

  return 0;
}
