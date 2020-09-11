#include "rvm.h"

int main(int argc, char* argv[])
{
    if (argc <= 1) {
        std::cout << "Usage: Unix, RVM <file>, Windows RVM.exe <file>" << std::endl;
        return 0;
    }

    RVM vm(argv[1]);

        // return the vm's exit code
        return vm.Run();
}