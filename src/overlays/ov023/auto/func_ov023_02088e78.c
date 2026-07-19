/* Latches the value into both scroll slots and, unless the node is already flagged, pushes it to
 * the node and marks it dirty. */
void func_ov023_02088e78(char *obj, int value) {
    char *p = obj + 0x1000;
    int *node;
    *(int *)(p + 0xa34) = value;
    *(int *)(p + 0xa30) = value;
    node = *(int **)(p + 0x5e0);
    if ((*node & 0x20) == 0) {
        *(short *)((char *)node + 0x80) = (short)value;
        *(unsigned short *)((char *)node + 4) |= 0x20;
    }
}
