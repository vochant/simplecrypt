#include "codec.hpp"

string fnproc(string fn) {
	string ret = "", tmp = "";
	int len = fn.length();
	for (int i = 0; i < len; i++) {
		if (fn[i] == '.') {
			ret += tmp;
			tmp = ".";
		} else {
			tmp += fn[i];
		}
	}
	if (ret == "") {
		ret = tmp;
	}
	ret += ".llar";
	return ret;
}

string getext(string fn) {
	string res = "";
	int len = fn.length();
	for (int i = 0; i < len; i++) {
		if (fn[i] == '.') {
			res = "";
		} else {
			res += fn[i];
		}
	}
	return res;
}

int main(int argc, char *argv[]) {
	Init();
	if (argc == 1) {
		return 0;
	}
	if (argc == 2) {
		if (getext(argv[1]) == "llar") {
			DecodeArchive darch(argv[1]);
			if (darch.Error()) {
				return -1;
			}
			darch.GetInformations();
			darch.ExtractAll();
			return darch.Error();
		} else {
			EncodeArchive earch(fnproc(argv[1]));
			if (earch.Error()) {
				return 1;
			}
			earch.AddFile(argv[1]);
			if(earch.Error()) {
				return 1;
			}
			earch.ConstructFile();
			return earch.Error();
		}
	}
	EncodeArchive earch("out.llar");
	if (earch.Error()) {
		return 1;
	}
	for (int i = 1; i < argc; i++) {
		earch.AddFile(argv[i]);
		if(earch.Error()) {
			return 1;
		}
	}
	earch.ConstructFile();
	return earch.Error();
}