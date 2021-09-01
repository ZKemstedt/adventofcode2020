#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define DEBUG 0

#ifdef DEBUG
#include <string.h>
#endif

#define ROWLEN 32
#define BORDER 31

struct Lane {
    uint8_t id;
    uint8_t step_x;
    uint8_t step_y;
    uint8_t trees;
};

void print_lane(struct Lane *lane) {
    printf("Lane %d (right %d, down %d) encountered %d trees.\n",
        lane->id, lane->step_x, lane->step_y, lane->trees);
}

struct Lane Lane_init(uint8_t id, uint8_t step_x, uint8_t step_y,
                      uint8_t trees) {
    struct Lane lane = { id, step_x, step_y, trees };
    return lane;
}

int main() {
    FILE *file;
    uint32_t filesize;
    uint32_t total_trees = 1;
    char *map;

    file = fopen("day3\\input.txt", "rb");  // parent dir - windows
    if (file == NULL)
        file = fopen("input.txt", "rb");    // same dir
    if (file == NULL)
        file = fopen("day3/input.txt", "rb");// parent dir - *nix
    if (file == NULL) {
        fputs("File error", stderr);
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);
    filesize = ftell(file);
    rewind(file);

    map = malloc(filesize);
    if (map == NULL) {
        fclose(file);
        fputs("Memory error", stderr);
        exit(EXIT_FAILURE);
    }
    
    fread(map, 1, filesize+1, file);
    fclose(file);
    map[filesize] = '\0';

    struct Lane lanes[5] = {
        Lane_init(1, 1, 1, 0),
        Lane_init(2, 3, 1, 0),
        Lane_init(3, 5, 1, 0),
        Lane_init(4, 7, 1, 0),
        Lane_init(5, 1, 2, 0)
    };

    for (uint8_t i = 0; i < 5; i++) {
        uint32_t distance_traveled = 0;
        uint8_t pos_x = 0, step = 0;
        struct Lane *lane = &lanes[i];
        char *c = map;

        #ifdef DEBUG
        char *dbg_line_start;
        char dbg_line[32];
        uint8_t dbg_c_pos;
        #endif

        while (distance_traveled < filesize) {
            c += step;
            if (*c == '#')
                lane->trees++;

            if (DEBUG) {
                // print out the map and our position in it
                // note that for lane5, every 2nd row is skipped
                char *dbg_line_start = c - pos_x;
                memset(dbg_line, '\0', 32);
                strncpy(dbg_line, dbg_line_start, 32);

                dbg_c_pos = c - dbg_line_start;
                dbg_line[dbg_c_pos] = 'O';
                printf("%s", dbg_line);
            }

            step = lane->step_x + lane->step_y * ROWLEN;
            pos_x += lane->step_x;
            if (pos_x >= BORDER) {
                pos_x -= BORDER;
                step -= BORDER;
            }
            distance_traveled += step;
        }
        print_lane(lane);
        total_trees *= lane->trees;
    }

    printf("\n\tThe product of encountered trees of each lane is: %d\n\n", total_trees);

    free(map);
    exit(EXIT_SUCCESS);
}
