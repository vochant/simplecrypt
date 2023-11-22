#ifndef __LIB_CRYPT
#define __LIB_CRYPT

#define CURRENT_VERSION 0

#include <bits/stdc++.h>
using namespace std;

mt19937 rnd;

void Init() {
	rnd.seed(random_device{}());
}

class Mask0 {
private:
	unsigned char conv[256], dconv[256];
public:
	Mask0() {
		bool vis[258];
		memset(vis, 0, sizeof(vis));
		int nex, cnt, cur;
		for (int i = 0; i < 256; i++) {
			nex = rnd() % (256 - i);
			cnt = 0;
			cur = 0;
			while (cnt <= nex) {
				if (!vis[cur]) {
					cnt++;
				}
				cur++;
			}
			conv[i] = cur - 1;
			vis[cur - 1] = true;
		}
		for (int i = 0; i < 256; i++) {
			dconv[conv[i]] = i;
		}
	}
	Mask0(FILE *s) {
		for (int i = 0; i < 256; i++) {
			conv[i] = getc(s);
		}
		for (int i = 0; i < 256; i++) {
			dconv[conv[i]] = i;
		}
	}
	void output_mask(FILE* out) {
		for (int i = 0; i < 256; i++) {
			putc(conv[i], out);
		}
	}
	void stream_encode(long long content_length, FILE* in, FILE* out) {
		unsigned char ch, xorbase = 0;
		for (long long i = 0; i < content_length; i++) {
			ch = getc(in);
			xorbase ^= ch;
			putc(conv[xorbase], out);
		}
	}
	void stream_decode(long long content_length, FILE* in, FILE* out) {
		unsigned char ch, prev = conv[0];
		for (long long i = 0; i < content_length; i++) {
			ch = getc(in);
			putc(dconv[prev] ^ dconv[ch], out);
			prev = ch;
		}
	}
};

long long gfsize(const char *fn) {
	if (!fn) {
		return -1;
	}
	FILE *fp = NULL;
	long long res;
	errno_t err0 = fopen_s(&fp, fn, "rb");
	if (err0 != 0) {
		printf("Failed when opening file \"%s\", code %d.\n", fn, err0);
		return -1;
	}
	int err1 = _fseeki64(fp, 0, SEEK_END);
	if (err1 != 0) {
		printf("Failed when moving cursor in file \"%s\" (SEEK_END), code %d.\n", fn, err1);
		return -1;
	}
	res = _ftelli64(fp);
	int err2 = _fseeki64(fp, 0, SEEK_SET);
	if (err2 != 0) {
		printf("Failed when moving cursor in file \"%s\" (SEEK_SET), code %d.\n", fn, err1);
		return -1;
	}
	fclose(fp);
	return res;
}

#endif