#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0 // flip it.

#define ROWLEN 32
#define BORDER 31

struct Lane {
    int id;
    int step_x;
    int step_y;
    int trees;
};

void print_lane(struct Lane *lane) {
    printf("Lane %d (right %d, down %d) encountered %d trees.\n",
        lane->id, lane->step_x, lane->step_y, lane->trees);
}

struct Lane init_lane(int id, int step_x, int step_y) {
    struct Lane lane = { id, step_x, step_y };
    return lane;
}

int main() {
    FILE *file;
    char *map;
    long filesize;
    long total_trees = 1;

    // bruh
    file = fopen("day3\\input.txt", "rb");
    if (file == NULL) {
        file = fopen("input.txt", "rb");
        if (file == NULL) {
            file = fopen("day3/input.txt", "rb");
            if (file == NULL) {
                fputs("File error", stderr);
                exit(EXIT_FAILURE);
            }
        }
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
        init_lane(1, 1, 1),
        init_lane(2, 3, 1),
        init_lane(3, 5, 1),
        init_lane(4, 7, 1),
        init_lane(5, 1, 2)
    };

    for (int i = 0; i < 5; i++) {
        struct Lane *lane = &lanes[i];
        char *c = map;
        int distance, pos_x = 0;
        long traveled = 0;

        #ifdef DEBUG
        char *dbg_line_start;
        char dbg_line[32];
        int dbg_c_pos;
        #endif
        
        do {
            if (DEBUG) {
                // print out the map and our position in it
                // note that for lane5, every 2nd row is skipped
                dbg_line_start = c - pos_x;
                memset(dbg_line, '\0', 32);
                strncpy(dbg_line, dbg_line_start, 32);

                dbg_c_pos = c - dbg_line_start;
                dbg_line[dbg_c_pos] = 'O';
                printf("%s", dbg_line);
            }

            if (*c == '#')
                lane->trees++;

            distance = lane->step_x;   // walk x
            pos_x += lane->step_x;
            if (BORDER <= pos_x) {      // adjust for border
                pos_x -= BORDER;
                distance -= BORDER;
            }
            distance += lane->step_y * ROWLEN; // walk y
            traveled += distance;
            if (traveled > filesize) // don't run outside of memory
                break;

        } while (*(c += distance));

        print_lane(lane);
        total_trees *= lane->trees;
    }

    printf("\n\tThe product of encountered trees of each lane is: %ld\n\n", total_trees);

    free(map);
    exit(EXIT_SUCCESS);
}
