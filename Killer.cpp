#include<iostream>
#include<sstream>
#include<string>

void killByName(std::string szExeName) {
    std::string command = "killall " + szExeName;
    system(command.c_str());
}

void killByID(std::string id) {
    std::string command = "kill " + id;
    system(command.c_str());
}

int main(int argc, char* argv[]) {
    char *var = getenv("PROC_TO_KILL");
    if (var != nullptr) {
        std::string var_(var);
        std::stringstream ss(var);
        while (ss.getline(var, var_.size(), ',')) {
            std::string str(var);
            killByName(str);
        }
    }
    if (argc == 2) {
        std::stringstream ss1(argv[1]);
        int id = 0;
        ss1 >> id;
        std::string str(argv[1]);
        if (id == 0) {
            killByName(str);
        } else {
            killByID(str);
        }
    }
    return 0;
}
