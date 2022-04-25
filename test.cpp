#include "llvm/Support/CommandLine.h"
#include "string.h"
#include "fstream"
#include "iostream"

using namespace llvm;
using namespace std;


cl::opt<string> Script(cl::Positional, cl::desc("<input script>"), cl::init("-"));
cl::list<string> Argv(cl::ConsumeAfter, cl::desc("<program arguments>..."));
cl::opt<bool> Trace("x", cl::desc("Enable trace output"));

int main(int argc, char **argv)
{
    /* Adding freeform text to help output */
    // 在cl::parseCommandLineOptions的第三个参数上可添加自由格式的文本信息。
    cl::ParseCommandLineOptions(argc, argv, " CommandLine compiler example\n\n"
    " This program blah blah blah...\n");
    return 0;
}