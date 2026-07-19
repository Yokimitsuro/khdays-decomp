typedef struct { unsigned short low : 8; unsigned short high : 8; } NodeFlags;

/* True when none of the four live sub-nodes already holds this id. */
int func_ov253_020cceb0(char *obj, int id) {
    int i;
    int **table = *(int ***)(obj + 0x458);
    for (i = 0; i < 4; i++) {
        char *e = (char *)table[i];
        if ((((NodeFlags *)(e + 0x60))->low & 1) != 0) {
            if (*(int *)(e + 0x3bc) == id) {
                return 0;
            }
        }
    }
    return 1;
}
