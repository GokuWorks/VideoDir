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

	for (const auto& entry : top) { //Maybe make as function for this. Nested path building may be an issue.
		string topS(entry.data());

		if ((!entry.contains("(") || !entry.contains(")")) && !entry.contains("#Download")) {//TODO: better comparisons
			printEntry(entry, topS);
			continue;
		}

		string topP = ROOT + "/" + entry;
		vStr_t mid;
		getDir(mid, topP);

		for (const auto& entry : mid) {
			if (!entry.contains("Season ")) {
				printEntry(entry, topS);
				break;
			}

			string midP = topP + "/" + entry;
			vStr_t bot;
			getDir(bot, midP);

			for (const auto& entry : bot) {
				if (entry == "Plex Versions") { continue; }

				if (!entry.contains(topS)) {
					printEntry(entry, topS);
					break;
				}
			}
		}
	}

	return 0;
}