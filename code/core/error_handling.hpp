#include <exception>
#include <string>

static class AlreadyDead : public std::exception
{
      private:
	std::string message = "Tried to kill already dead entity of type";
	std::string type_name = "";
	int index;

      public:
	AlreadyDead() {}

	// Override what() method, marked
	// noexcept for modern C++
	const char *what() const noexcept { return message.c_str(); }
};
