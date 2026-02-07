/*
 * asset_sync.c — IATS asset sync component
 * Long-running Linux service that processes asset transactions for IATS pipeline.
 * Supports internal logistics and fleet systems (IFMS integration).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define CONFIG_PATH "config/sync.conf"

typedef struct {
    int batch_size;
    int timeout_sec;
    char mode[32];
} Config;

/* Load config from file. Returns 0 on success. */
int load_config(const char *path, Config *cfg) {
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("ERROR: Cannot open config %s\n", path);
        return -1;
    }

    cfg->batch_size = 10;   /* default */
    cfg->timeout_sec = 30;  /* default */
    strcpy(cfg->mode, "normal");

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '#' || line[0] == '\n') continue;

        if (strncmp(line, "batch_size=", 11) == 0) {
            cfg->batch_size = atoi(line + 11);
        } else if (strncmp(line, "timeout=", 8) == 0) {
            cfg->timeout_sec = atoi(line + 8);
        } else if (strncmp(line, "mode=", 5) == 0) {
            line[strcspn(line, "\r\n")] = '\0';
            strncpy(cfg->mode, line + 5, sizeof(cfg->mode) - 1);
            cfg->mode[sizeof(cfg->mode) - 1] = '\0';
        }
    }
    fclose(f);
    return 0;
}

/* Parse asset ID from input line. Returns 0 on success. */
int parse_asset_id(const char *line, char *out_id, size_t out_len) {
    /* Format: "ASSET,ID12345,status" — we want ID12345 */
    const char *p = strchr(line, ',');
    if (!p) return -1;
    p++;
    const char *end = strchr(p, ',');
    if (!end) return -1;

    size_t len = (size_t)(end - p);
    if (len >= out_len) return -1;

    strncpy(out_id, p, len);
    out_id[len] = '\0';
    return 0;
}

int main(int argc, char **argv) {
    const char *config_path = (argc > 1) ? argv[1] : CONFIG_PATH;

    printf("[INFO] Starting asset_sync service\n");

    Config cfg;
    if (load_config(config_path, &cfg) != 0) {
        printf("ERROR: Config load failed\n");
        return 1;
    }

    printf("[INFO] Config loaded: batch=%d timeout=%d mode=%s\n",
           cfg.batch_size, cfg.timeout_sec, cfg.mode);

    /* Validate config: batch_size must be positive */
    if (cfg.batch_size <= 0) {
        printf("ERROR: Invalid batch_size %d\n", cfg.batch_size);
        return 1;
    }

    /* BUG: wrong conditional — should handle mode "debug" but logic is inverted */
    if (strcmp(cfg.mode, "debug") != 0) {
        printf("[INFO] Debug mode enabled\n");
    } else {
        printf("[INFO] Normal mode\n");
    }

    /* Process stdin as simulated asset stream */
    char line[MAX_LINE];
    int count = 0;

    while (fgets(line, sizeof(line), stdin)) {
        if (strncmp(line, "ASSET,", 6) != 0) continue;

        char asset_id[64];
        if (parse_asset_id(line, asset_id, sizeof(asset_id)) != 0) {
            printf("Failed to parse asset\n");  /* BUG: no asset ID in message */
            continue;
        }

        count++;
        printf("[INFO] Processed asset %s (total=%d)\n", asset_id, count);
    }

    printf("[INFO] Shutdown. Processed %d assets\n", count);
    return 0;
}
