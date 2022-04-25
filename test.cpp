#include "llvm/Support/CommandLine.h"
#include "string.h"
#include "fstream"
#include "iostream"

using namespace llvm;
using namespace std;

// cl::opt<string> OutputFilename("o", cl::desc("Specify output filename"), cl::value_desc("filename"));
// cl::opt<string> InputFilename(cl::Positional, cl::desc("<input file>"), cl::Required);

/* Boolean Arguments */
// cl::opt<bool> Force ("f", cl::desc("Enable binary output on terminals"));
// cl::opt<bool> Quiet ("quiet", cl::desc("Don't print informational messages"));
// cl::opt<bool> Quiet2("q", cl::desc("Don't print informational messages"), cl::Hidden);

/* Argument Aliases */
// cl::alias QuietA("q",cl::desc("Alias for -quiet"), cl::aliasopt(Quiet)); // 可以设置匿名，这样就只用查找quiet了，不用再查找一遍 q了。
// 设置匿名防止这样的语句出现：if (!Quiet && !Quiet2) printInformationalMessage(...);

/* Selecting an alternative from a set of possibilities */

// enum OptLevel {
//     g, O1, O2, O3
// };

// cl::opt<OptLevel> OptimizationLevel(cl::desc("Choose optimization level:"),
//     cl::values(
//         clEnumVal(g,"No optimizations, enable debugging"),
//         clEnumVal(O1, "ENable trivial optimizations"),
//         clEnumVal(O2,"Enable default optimizations"),
//         clEnumVal(O3, "Enable expensive optimizations")));
// 有时不想将g当作枚举类型，可以这样写：
/*
enum OptLevel {
    Debug, O1, O2, O3
};
cl::opt<OptLevel> OptimizationLevel(cl::desc("Choose optimization level:"),
    cl::values(
        clEnumValN(Debug,"g","No optimizations, enable debugging"),
        clEnumVal(O1, "ENable trivial optimizations"),
        clEnumVal(O2,"Enable default optimizations"),
        clEnumVal(O3, "Enable expensive optimizations")));

*/

/* Named Alternatives */
// enum DebugLev {
//     nodebug, quick, detailed
// };
// Enable Debug Options to be specified on the command line
// cl::opt<DebugLev> DebugLevel("debug_level", cl::desc("Set the debugging level:"),
//     cl::values(
//         clEnumValN(nodebug, "none", "disable debug information"),
//         clEnumVal(quick, "enable quick debug information"),
//         clEnumVal(detailed, "enable detailed debug information")
//     ));

/* Parsing alist of options */
// 有时可能某些选项需要出现多次，其顺序和出现次数很重要，这时就绪要cl::list了
// enum Opts {
//     // 'inline' is a c++ keyword, so name it 'inlining'
//     dce, instsimplify, inlining, strip
// };
/*
cl::list<Opts> OptimizationList(cl::desc("Available Optimizations:"),
    cl::values(
        clEnumVal(dce, "Dead Code Elimination"),
        clEnumVal(instsimplify, "Instruction Simplification"),
        clEnumValN(inlining, "inline", "Procedure Integration"),
        clEnumVal(strip, "Strip Symbols")
    ));
    */
// 上述值可以用标准vector获取

/* cl::list有如下使用场景：如果要链接多个.o文件，可以这样写*/
// cl::list<std::string> InputFilenames(cl::Positional, cl::desc("<Input files>"), cl::OneOrMore);

/* Collecting options as a set of flags */
/*
cl::bits<Opts> OptimizationBits(cl::desc("Available Optimizations:"),
    cl::values(
        clEnumVal(dce,"Dead Code Dlimination"),
        clEnumVal(instsimplify,"Instruction Simplification"),
        clEnumValN(inlining, "inline", "Procedure Integration"),
        clEnumVal(strip, "Strip Symbols")
    ));
*/
/* Grouping options into categories */
// 将选项按照类别分组
/*
cl::OptionCategory StageSelectionCat("Stage Selection Options",
                                     "These control which stages are run.");// 定义某种类别
cl::opt<bool> Preprocessor("E",cl::desc("Run preprocessor stage."),
                               cl::cat(StageSelectionCat));
cl::opt<bool> NoLink("c", cl::desc("Run all stages except linking."),
                          cl::cat(StageSelectionCat));
*/
/* Positional Arguments */
// cl::opt<string> Regex(cl::Positional, cl::desc("<regular expression>"), cl::Required);
// cl::opt<string> Filename(cl::Positional, cl::desc("<input file>"), cl::init("-"));

/* Determining absolute position with getPosition() */
static cl::list<std::string> Files(cl::Positional, cl::OneOrMore);
static cl::list<std::string> Libraries("l", cl::ZeroOrMore);

int main(int argc, char **argv)
{
    /* Adding freeform text to help output */
    // 在cl::parseCommandLineOptions的第三个参数上可添加自由格式的文本信息。
    cl::ParseCommandLineOptions(argc, argv, " CommandLine compiler example\n\n"
    " This program blah blah blah...\n");

    // std::ofstream Output(OutputFilename.c_str(), std::ofstream::out);

    // if(Output.good()){
    //     printf("hello CommandLine\n");
    // }

    // if (OptimizationLevel >= O2) {}
    /* 如果不想直接映射g，用第二种方法可以这样写：
    if(OptimizationLevel == Debug){}
    */
    /*
    for(unsigned i = 0; i != OptimizationList.size(); ++i){
        switch(OptimizationList[i]){

        }
     }
     */
    /* 如果使用cl::bits,要看某个位是否是可以这样用*/
    // if(OptimizationBits.isSet(instsimplify)){}
    // 也能直接获取raw bit
    // unsigned bits = OptimizationBits.getBits();

    std::vector<std::string>::iterator fileIt = Files.begin();
    std::vector<std::string>::iterator libIt = Libraries.begin();
    unsigned libPos = 0, filePos = 0;
    while (1)
    {
        if (libIt != Libraries.end())
            libPos = Libraries.getPosition(libIt - Libraries.begin());
        else
            libPos = 0;
        if (fileIt != Files.end())
            filePos = Files.getPosition(fileIt - Files.begin());
        else
            filePos = 0;

        if (filePos != 0 && (libPos == 0 || filePos < libPos))
        {
            // Source File Is next
            cout<<*fileIt<<endl;
            ++fileIt;
            
        }
        else if (libPos != 0 && (filePos == 0 || libPos < filePos))
        {
            // Library is next
            cout<<*libIt<<endl;
            ++libIt;
            
        }
        else
            break; // we're done with the list
    }
}