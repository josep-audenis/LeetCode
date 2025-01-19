// Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D elevation map, return the volume of water it can trap after raining.
// 
// - Example 1:
// Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
// Output: 4
// Explanation: After the rain, water is trapped between the blocks.
// We have two small ponds 1 and 3 units trapped.
// The total volume of water trapped is 4.
// 
// - Example 2:
// Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
// Output: 10
// 
// Constraints:
// · m == heightMap.length
// · n == heightMap[i].length
// · 1 <= m, n <= 200
// · 0 <= heightMap[i][j] <= 2 * 104

#define MAX 40000
const int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int isOutside(int i, int j, int maxR, int maxC) {
    return (i < 0 || j < 0 || i >= maxR || j >= maxC);
}

uint32_t pack(int h, int i, int j) {
    return ((uint32_t)h << 16) | (i << 8) | j;
}

typedef struct {
    uint32_t items[MAX];
    int size;
} Heap;

void push(Heap* heap, uint32_t value) {
    int i = heap->size++;
    while(i > 0 && (value >> 16) < (heap->items[(i - 1) / 2] >> 16)) {
        heap->items[i] = heap->items[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->items[i] = value;
}

uint32_t pop(Heap* heap) {
    uint32_t root = heap->items[0];
    uint32_t last = heap->items[--heap->size];

    int i = 0, child;
    for (; (child = 2 * i + 1) < heap->size; i = child) {
        if (child + 1 < heap->size && (heap->items[child] >> 16) > (heap->items[child + 1] >> 16))
            child++;
        if ((last >> 16) <= (heap->items[child] >> 16))
            break;
        heap->items[i] = heap->items[child];
    }

    heap->items[i] = last;
    return root;
}

int trapRainWater(int** heightMap, int heightMapSize, int* heightMapColSize) {
    int rows = heightMapSize;
    int cols = *heightMapColSize;

    Heap heap = {{0}, 0};
    bool visited[rows][cols];
    memset(visited, 0, sizeof(visited));

    int volume = 0;

    for (int i = 0; i < cols; i++) {
        push(&heap, pack(heightMap[0][i], 0, i));
        push(&heap, pack(heightMap[rows - 1][i], rows - 1, i));
        visited[0][i] = visited[rows - 1][i] = true;
    }

    for (int i = 0; i < rows; i++) {
        push(&heap, pack(heightMap[i][0], i, 0));
        push(&heap, pack(heightMap[i][cols - 1], i, cols - 1));
        visited[i][0] = visited[i][cols - 1] = true;
    }

    while (heap.size > 0) {
        uint32_t packed = pop(&heap);
        int h = packed >> 16;
        int i = (packed >> 8) & 255; 
        int j = packed & 255;

        for (int k = 0; k < 4; k++) {
            int ai = i + dirs[k][0];
            int aj = j + dirs[k][1];

            if (isOutside(ai, aj, rows, cols) || visited[ai][aj]) continue;

            visited[ai][aj] = true;

            int ah = heightMap[ai][aj];
            if (ah < h) volume += h - ah;

            push(&heap, pack(h > ah ? h : ah, ai, aj));
        }
    }

    return volume;
}

// Runtime: 10ms 
// Memory: 10.55MB
// Inspired by user alpindale