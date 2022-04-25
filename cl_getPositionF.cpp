#include "llvm/Support/CommandLine.h"
#include "string.h"
#include "fstream"


using namespace llvm;
using namespace std;
static cl::list<std::string> Files(cl::Positional, cl::OneOrMore);
static cl::list<std::string> Libraries("l", cl::ZeroOrMore);

int main(int argc, char**argv) {
  // ...
  std::vector<std::string>::iterator fileIt = Files.begin();
  std::vector<std::string>::iterator libIt  = Libraries.begin();
  unsigned libPos = 0, filePos = 0;
  while ( 1 ) {
    if ( libIt != Libraries.end() )
      libPos = Libraries.getPosition( libIt - Libraries.begin() );
    else
      libPos = 0;
    if ( fileIt != Files.end() )
      filePos = Files.getPosition( fileIt - Files.begin() );
    else
      filePos = 0;

    if ( filePos != 0 && (libPos == 0 || filePos < libPos) ) {
      // Source File Is next
      ++fileIt;
    }
    else if ( libPos != 0 && (filePos == 0 || libPos < filePos) ) {
      // Library is next
      ++libIt;
    }
    else
      break; // we're done with the list
  }
}
