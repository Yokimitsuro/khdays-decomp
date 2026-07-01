int func_ov026_0208e720(char *obj) {
    if (*(unsigned short *)(*(int *)obj + 2) != 0x15) {
        return 0;
    }
    *(int *)obj = 0;
    return 1;
}
