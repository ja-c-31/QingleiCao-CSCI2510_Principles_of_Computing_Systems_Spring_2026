#include <stdio.h>
#include <stdlib.h>

#define NUM_PROCS 15
#define NUM_RES 15
#define MAX_EDGES 256


static int waiting[NUM_PROCS][NUM_RES];

static int held_by[NUM_RES];

typedef struct {
    int from_type;  /* 0 = process, 1 = resource */
    int from_id;
    int to_type;    /* 0 = process, 1 = resource */
    int to_id;
} Edge;

static Edge path[MAX_EDGES];
static int path_len = 0;

static void init_graph(void) {
    for (int p = 0; p < NUM_PROCS; p++) {
        for (int r = 0; r < NUM_RES; r++) {
            waiting[p][r] = 0;
        }
    }

    for (int r = 0; r < NUM_RES; r++) {
        held_by[r] = -1;
    }
}

static int valid_ids(int process, int resource) {
    return process >= 0 && process < NUM_PROCS && resource >= 0 && resource < NUM_RES;
}

static void push_edge(int from_type, int from_id, int to_type, int to_id) {
    if (path_len < MAX_EDGES) {
        path[path_len].from_type = from_type;
        path[path_len].from_id = from_id;
        path[path_len].to_type = to_type;
        path[path_len].to_id = to_id;
        path_len++;
    }
}

static void pop_edge(void) {
    if (path_len > 0) {
        path_len--;
    }
}

static void print_edge(const Edge *edge) {
    if (edge->from_type == 0) {
        printf("PROCESS %d -> ", edge->from_id);
    } else {
        printf("RESOURCE %d -> ", edge->from_id);
    }

    if (edge->to_type == 0) {
        printf("PROCESS %d\n", edge->to_id);
    } else {
        printf("RESOURCE %d\n", edge->to_id);
    }
}

static void print_cycle(void) {

    for (int i = path_len - 1; i >= 0; i--) {
        print_edge(&path[i]);
    }
}

static int search_process(int start_process, int current_process, int visited[NUM_PROCS]);

static int search_resource(int start_process, int current_resource, int visited[NUM_PROCS]) {
    int owner = held_by[current_resource];

    if (owner == -1) {
        return 0;
    }

    push_edge(1, current_resource, 0, owner);

    if (owner == start_process) {
        return 1;
    }

    if (search_process(start_process, owner, visited)) {
        return 1;
    }

    pop_edge();
    return 0;
}

static int search_process(int start_process, int current_process, int visited[NUM_PROCS]) {
    if (visited[current_process]) {
        return 0;
    }

    visited[current_process] = 1;

    for (int r = 0; r < NUM_RES; r++) {
        if (waiting[current_process][r]) {
            push_edge(0, current_process, 1, r);

            if (search_resource(start_process, r, visited)) {
                return 1;
            }

            pop_edge();
        }
    }

    return 0;
}

static int start_search(int start_process) {
    int visited[NUM_PROCS];

    for (int p = 0; p < NUM_PROCS; p++) {
        visited[p] = 0;
    }

    path_len = 0;
    return search_process(start_process, start_process, visited);
}

static void acquire_resource(int process, int resource) {
    if (!valid_ids(process, resource)) {
        return;
    }

    if (held_by[resource] == -1) {
        held_by[resource] = process;
    } else {
        waiting[process][resource] = 1;
    }
}

/*
 * Returns the process that receives the released resource, or -1 if nobody does.
 */
static int release_resource(int process, int resource) {
    if (!valid_ids(process, resource)) {
        return -1;
    }

    if (held_by[resource] != process) {
        return -1;
    }

    held_by[resource] = -1;

    for (int p = 0; p < NUM_PROCS; p++) {
        if (waiting[p][resource]) {
            waiting[p][resource] = 0;
            held_by[resource] = p;
            return p;
        }
    }

    return -1;
}

int main(void) {
    int process;
    int resource;
    char action;

    init_graph();

    while (scanf(" %d %c %d", &process, &action, &resource) == 3) {
        if (!valid_ids(process, resource)) {
            continue;
        }

        if (action == 'a') {
            acquire_resource(process, resource);

            if (start_search(process)) {
                printf("DEADLOCK DETECTED\n");
                print_cycle();
                printf("-1\n");
                return -1;
            }
        } else if (action == 'r') {
            int new_owner = release_resource(process, resource);

            if (new_owner != -1 && start_search(new_owner)) {
                printf("DEADLOCK DETECTED\n");
                print_cycle();
                printf("-1\n");
                return -1;
            }
        }
    }

    printf("NO DEADLOCK\n");
    printf("0\n");
    return 0;
}
