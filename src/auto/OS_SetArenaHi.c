void OS_SetArenaHi(int i, int v) {
    *(int *)((i << 2) + 0x27ff000 + 0xdc4) = v;
}
