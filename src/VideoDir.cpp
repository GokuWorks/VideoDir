#include <iostream>
#include <filesystem>

using std::vector, std::string;

typedef vector<string> vStr_t;

static void getDir(vStr_t &v, const string &p) {
	for (const auto &entry : std::filesystem::directory_iterator(p)) {
		v.push_back(entry.path().filename().string());
	}
}

int main() {
	const string ROOT = "Y:/Media/Anime";
	vStr_t top;

	return 0;
}