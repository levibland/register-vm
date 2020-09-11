#include "rvmassembler.h"

int main(int argc, char* argv[])
{
	if (argc <= 1) {
		std::cout << "Usage: rasm <file>(UNIX), rasm.exe <file>(Windows)" << std::endl;
		return 0;
	}
	RVMAssembler assembler;
	std::string input = argv[1];
	std::string output = input.substr(0, input.find_last_of('.')) + ".rexe";
	AssemblerReturnValues ret = assembler.assembleToFile(input, output);
	switch (ret) {
	case AssemblerReturnValues::Success:
		std::cout << "File successfully assembled to: " << output << std::endl;
		break;
	case AssemblerReturnValues::IOError:
		std::cout << "There was an error while reading/writing a file on disk" << std::endl;
		break;
	case AssemblerReturnValues::MemoryAllocationError:
		std::cout << "Failed to dynamically allocate memory" << std::endl;
		break;
	case AssemblerReturnValues::AssemblerError:
		std::cout << "The input file could not be compiled" << std::endl;
		break;
	default:
		std::cout << "Received unknown error: " << ret << std::endl;
	}
	return ret;
}