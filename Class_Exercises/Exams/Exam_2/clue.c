#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 35

typedef struct {
    int value;
    char route[35];
} NodeInfo;


int parseLine(char *line, NodeInfo nodes[]) {
    int count = 0;

    char *token = strtok(line, " ");

    while (token != NULL) {
        int value;
        char route[35];

        // Extract
        sscanf(token, "(%d,%[^)])", &value, route);

        nodes[count].value = value;
        strcpy(nodes[count].route, route);

        count++;
        token = strtok(NULL, " ");
    }

    return count;
}

int main() {
    char line[200] = "(16,) (10,L) (15,LR) (9,LLR)";
    NodeInfo nodes[MAXN];

    int n = parseLine(line, nodes);

    for (int i = 0; i < n; i++) {
        printf("%d -> %s\n", nodes[i].value, nodes[i].route);
    }

    return 0;
}