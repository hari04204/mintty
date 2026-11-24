#include <string>
#include <unistd.h>
#include <vector>

class Shell {
public:
  void run();

  Shell();
  ~Shell() = default;

private:
  bool readLine(std::string& line);
  std::vector<std::string> tokenize(std::string& line);
  void execute();
};