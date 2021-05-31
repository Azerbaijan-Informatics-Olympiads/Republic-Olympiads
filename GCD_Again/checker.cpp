#include <cstdio>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv) {

	FILE *fout = fopen(argv[3], "r");

	int a;
	fscanf(fout, "%d", &a);

	if (a<=100 && a>=1) {
		fprintf(stderr, "%d Checkmate!\n",a);
		printf("1.0\n");
	} else {
		fprintf(stderr, "%d Blunder!\n",a);
		printf("0.0\n");
	}

	return 0;

}
