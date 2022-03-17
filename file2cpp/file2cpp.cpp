#include <cstdio>

int main(int argc, char **argv) {
	if (argc < 2) return 0;
	FILE *fr = fopen(argv[1], "rb");
	if (fr == 0) return 1;
	printf("BYTE data[] = {\n");
	printf("\t");
	int a = 0, c;
	while (!feof(fr))
	{
		c = fgetc(fr);
		if (c == 0xFFFFFFFF) break;
		printf("0x%.2X,", c);
		a++;
		if (a == 16)
		{
			printf("\n\t");
			a = 0;
		}
	}
	fclose(fr);
	printf("\n};");
    return 0;
}

