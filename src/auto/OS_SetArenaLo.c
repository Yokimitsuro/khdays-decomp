void OS_SetArenaLo(int i, int v) {
    *(int *)(0x27ff000 + (i << 2) + 0xda0) = v;
}
