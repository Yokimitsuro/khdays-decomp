int func_ov022_020b0ac8(int arg0) {
    if (*(int *)(arg0 + 0x474) >= 0 &&
        *(int *)(arg0 + 0x474) + 1 >= *(int *)(*(int *)(arg0 + 0x468) + 0x14)) {
        if (*(int *)(*(int *)(arg0 + 0x470) + 4) == 0)
            return *(int *)(*(int *)(arg0 + 0x470) + 8);
        return *(int *)(*(int *)(arg0 + 0x46c) + 4);
    }
    return *(int *)(*(int *)(arg0 + 0x470) + 4);
}
