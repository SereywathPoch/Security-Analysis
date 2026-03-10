// File: NetworkLog-Collector.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp_in = fopen("network.log", "r");  // Pretend this is a network log
    FILE *fp_out = fopen("collected_network.log", "w");

    if (!fp_in || !fp_out) {
        perror("File error");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp_in)) {
        // For simplicity, copy all lines
        fprintf(fp_out, "%s", line);
    }

    fclose(fp_in);
    fclose(fp_out);
    printf("Network logs collected into collected_network.log\n");
    return 0;
}