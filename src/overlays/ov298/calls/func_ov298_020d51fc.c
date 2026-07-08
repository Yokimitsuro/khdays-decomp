struct bf { unsigned b : 8; };

extern void func_ov298_020d4124(void *node);

void func_ov298_020d51fc(int *node) {
    int *state = (int *)node[1];

    func_ov298_020d4124(node);

    if (*(unsigned char *)(state[1] + 0xad) != 0) return;

    state[0x24] = 0;
    ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b &= ~1;
    *(unsigned char *)(*state + 0x1c7) = 4;
}
