#include <iostream>
#include "Program.h"

int main(int argc, char* argv[]) {
    {
        Program p = Program();

        p.e->Run();
    }

    cout << "Destructed everything successfully :)";
    return 0;
}
