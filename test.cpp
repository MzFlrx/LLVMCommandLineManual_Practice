#include "llvm/Support/CommandLine.h"
#include "string.h"
#include "fstream"
#include "iostream"

using namespace llvm;
using namespace std;



bool DebugFlag;
static cl::opt<bool, true>
Debug("debug", cl::desc("Enable debug output"), cl::Hidden, cl::location(DebugFlag));
/**在上面的示例中，我们将“true”指定为 cl::opt 模板的第二个参数，表示模板不应该维护值本身的副本。  除此之外，我们指定 cl::location 属性，以便自动设置 DebugFlag。
 */




int main(int argc, char **argv)
{
    cl::extrahelp("\nADDITIONAL HELP:\n\n This is the extra help\n");
    /* Adding freeform text to help output */
    // 在cl::parseCommandLineOptions的第三个参数上可添加自由格式的文本信息。
    cl::ParseCommandLineOptions(argc, argv, " CommandLine compiler example\n\n"
    " This program blah blah blah...\n");




    return 0;
}