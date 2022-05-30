#include <iostream>
#include<unistd.h>

int main() {
    std::string procs[]{"../../procP/cmake-build-debug/procP",
                        "../../procA/cmake-build-debug/procA",
                        "../../procM/cmake-build-debug/procM",
                        "../../procS/cmake-build-debug/procS"};
    std::cout << "Enter 5 numbers:\n";
    int pid, p[3];
    for (int i = 0; i < 3; i++) {
        if (pipe(p) < 0)
            exit(1);
        pid = fork();
        if (!pid){
            if (dup2(p[1], 1) < 0) exit(1);
            system(procs[i].c_str());
        }
         if (dup2(p[0], 0) < 0) exit(1);
    }
    system(procs[3].c_str());
    return 0;
}
