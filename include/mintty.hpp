#include <cstdint>
#include <string>
#include <unistd.h>
#include <vector>

class Shell {
public:
  void run();

  Shell();
  ~Shell() = default;

private:
  int lastStatus = 0;
  bool readLine(std::string &line);
  std::vector<std::string> tokenize(const std::string &line);
  int execute(const std::vector<std::string> &tokens);
};