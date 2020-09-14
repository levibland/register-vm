#include "RVMDebugger.h"

int main(int argc, char *argv[])
{
	if (argc < 1) {
		std::cout << "Usage RVMDebugger.exe [FILE]" << std::endl;
	}
	std::string file = (argv[1]);
	RVMDebugger debugger(file);
	debugger.debug();
	return 0;
}
