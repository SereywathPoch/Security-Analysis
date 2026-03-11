// File: LLP(Low-LevelPreprocessing).c
#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp = fopen("sample.eml", "r");
    FILE *out = fopen("filtered.eml", "w");

    if (!fp || !out) return 1;

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "http") != NULL) {
            fputs(line, out); // keep lines with links
        }
    }

    fclose(fp);
    fclose(out);
    printf("Filtered links saved to filtered.eml\n");
    return 0;
}