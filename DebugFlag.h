// DebugFlag.h - Get access to the '-debug' command line option
//

// DebugFlag - This boolean is set to true if the '-debug' command line option
// is specified.  This should probably not be referenced directly, instead, use
// the DEBUG macro below.
//
extern bool DebugFlag;

// DEBUG macro - This macro should be used by code to emit debug information.
// In the '-debug' option is specified on the command line, and if this is a
// debug build, then the code specified as the option to the macro will be
// executed.  Otherwise it will not be.
#ifdef NDEBUG
#define LLVM_DEBUG(X)
#else
#define LLVM_DEBUG(X) do { if (DebugFlag) { X; } } while (0)
#endif