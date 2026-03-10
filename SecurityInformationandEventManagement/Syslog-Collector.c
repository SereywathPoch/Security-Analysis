// File: Syslog-Collector.c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("/var/log/auth.log", "r");
    FILE *out = fopen("collected_logs.log", "w");
    if (!fp || !out) return 1;

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        fprintf(out, "%s", buffer);
    }

    fclose(fp);
    fclose(out);
    printf("Logs collected to collected_logs.log\n");
    return 0;
}