#include<iostream>
#include <cstdlib>

std::string kill_path = "../../Killer/cmake-build-debug/Killer";

void printProcesses() {
  std::cout << "\n///////////////////////////////////\n";
  system("ps -e");
  std::cout << "\n///////////////////////////////////\n\n";
}

void kill(std::string str) {
  system((kill_path + " " + str).c_str());
}

  int main() {
  printProcesses();
  if (setenv("PROC_TO_KILL", "Telegram,firefox", 0) == -1) {
      std::cout << "Error in creating of env var!\n\n";
  }
      kill("");
      std::cout << "Telegram,firefox were killed\n\n";
  unsetenv("PROC_TO_KILL");
  printProcesses();

  std::string name_or_id;
  std::cout << "Enter id of process\n";
  std::cin >> name_or_id;
  kill(name_or_id);
  printProcesses();

  std::cout << "Enter name of process\n";
  std::cin >> name_or_id;
  kill(name_or_id);
  printProcesses();

  return 0;
}