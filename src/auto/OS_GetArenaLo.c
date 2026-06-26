int OS_GetArenaLo(int idx) {
    return *(int *)((idx << 2) + 0x27ff000 + 0xda0);
}
