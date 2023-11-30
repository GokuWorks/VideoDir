#include <iostream>
#include <filesystem>

using std::vector, std::string, std::cout, std::endl;

typedef vector<string> vStr_t;

static void getDir(vStr_t &v, const string &p) {
	for (const auto &entry : std::filesystem::directory_iterator(p)) {
		v.push_back(entry.path().filename().string());
	}
}

static void printEntry(const string& s, const string& topS) {
	cout << "\033[31m" << s << "\033[33m" << " from: "
		<< topS << "\033[0m" << endl;
}

int main() {
	const string ROOT = "Y:/Media/Anime";
	vStr_t top;

	getDir(top, ROOT);

	for (const auto& entry : top) {
		string topS(entry.data());

		if ((!entry.contains("(") || !entry.contains(")")) && !entry.contains("#Download")) {
			printEntry(entry, topS);
			continue;
		}
	}

	return 0;
}