#include "codec.hpp"

void About() {
	puts("Mirekintoc's LLAR CLI v1.0.0");
	puts("Designed for LLAR v1.0");
	puts("LLAR (MOS-0001) is a definition, not a project.");
	puts("Join the MOS (Mirekintoc Open Standards)!");
	puts("Copyright(C) 2009-2023 Mirekintoc Void.");
	puts("Copyright(C) 2019-2023 Minphtis Development.");
	puts("Under MIT License.");
}

void Help() {
	puts("Usage:");
	puts("llarm <archive> [d|e] <optional: files>\n");
	puts("Use \'d\' to decode a file.");
	puts("If you used <optional: files>, than it will");
	puts("do not extract all files, but decode files");
	puts("mentioned. You can use it for not only once.\n");
	puts("Use \'e\' to encode a file.");
	puts("If you do not used <optional: files>, than it");
	puts("will be an empty archive. Just contain something");
	puts("in it!\n");
	puts("\"llarm -h|--help\" will show help.");
	puts("\"llarm -a|--about\" will show about.");
}

int main(int argc, char *argv[]) {
	Init();
	if (argc == 1) {
		About();
		putchar('\n');
		Help();
		return 0;
	}
	if (argc == 2) {
		string argv_1 = argv[1];
		if (argv_1 == "-h" || argv_1 == "--help") {
			Help();
			return 0;
		}
		if (argv_1 == "-a" || argv_1 == "--about") {
			About();
			return 0;
		}
		puts("Unknown usage!\n");
		Help();
		return 1;
	}
	string f = argv[1], opt = argv[2];
	if (opt == "d") {
		DecodeArchive darch(f);
		if (darch.Error()) {
			return 1;
		}
		darch.GetInformations();
		if (argc > 3) {
			for (int i = 3; i < argc; i++) {
				darch.ExtractEach(argv[i]);
				if (darch.Error()) {
					return 1;
				}
			}
		} else {
			darch.ExtractAll();
		}
		return darch.Error();
	}
	if (opt == "e") {
		EncodeArchive earch(f);
		if (earch.Error()) {
			return 1;
		}
		for (int i = 3; i < argc; i++) {
			earch.AddFile(argv[i]);
			if(earch.Error()) {
				return 1;
			}
		}
		earch.ConstructFile();
		return earch.Error();
	}
	puts("Unknown operation!");
	Help();
	return 1;
}