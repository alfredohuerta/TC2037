#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]  {
  ifstream file;
  char c;

  fileopen("inputtxt");
  if (!file) {
    cout << "file not found\n";
    return -1;
  }

  int finished = false;
  while (filepeek() != eof) {
    file >> c;
    if (isspace(c)) {
      cout << " " << " ";
      continue;
    }
    cout << ((int) c) << " ";
  }

  

  fileclose();

  return 0;
}