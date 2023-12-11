#include <iostream>
#include <filesystem>

using std::vector, std::string, std::cout, std::endl;

typedef std::filesystem::path path_t;
typedef vector<std::filesystem::path> vPath_t;

static void getDir(vPath_t &v, const path_t &p) {
	for (const auto &entry : std::filesystem::directory_iterator(p)) {
		v.push_back(entry.path().filename().string());
	}
}

static void printEntry(const path_t& s, const path_t& topS) {
	cout << "\033[31m" << s << "\033[33m" << " from: "
		<< topS << "\033[0m" << endl;
}

int main() {
    const path_t root = "...";
    vPath_t top;

    getDir(top, root);

    for (const auto& entry : top) {
        if ((!entry.string().contains("(") || !entry.string().contains(")")) && !entry.string().contains("#Download")) {
            printEntry(entry, entry);
            continue;
        }

        const path_t topPath = root / entry;
        vPath_t mid;
        getDir(mid, topPath);

        for (const auto& midEntry : mid) {
            if (!midEntry.string().contains("Season ")) {
                printEntry(midEntry, entry);
                break;
            }

            const path_t midPath = topPath / midEntry;
            vPath_t bot;
            getDir(bot, midPath);

            for (const auto& botEntry : bot) {
                if (botEntry == "Plex Versions") continue;

                if (!botEntry.string().starts_with(entry.string())) {
                    printEntry(botEntry, entry);
                    break;
                }
            }
        }
    }

    return 0;
}
