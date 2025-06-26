#include <fstream>

class PageManager {
	std::fstream fileStream;
public:
	explicit PageManager(const char filename[]) {
	}
	~PageManager() = default;
};