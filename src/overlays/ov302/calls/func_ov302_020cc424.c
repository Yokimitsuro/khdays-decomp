extern void *func_ov302_020cbf64(int rec, void *sub);
extern void NNS_FndAppendListObject(void *list, void *obj);

/* Scan the count-prefixed candidate array `param_2` for the best entry whose
 * level window brackets `param_3` (or that starts above it), preferring the
 * lowest window start; if one is found, instantiate it via func_ov302_020cbf64
 * and append to the list at param_1+0x18. Returns 1 if an entry was appended. */
int func_ov302_020cc424(int param_1, unsigned short *param_2, unsigned int param_3, unsigned int param_4) {
    int i;
    int ret;
    unsigned short *best;
    unsigned short *bestsub;
    int count;

    ret = 0;
    bestsub = 0;
    best = 0;
    i = 0;
    count = *param_2++;
    if (count > 0) {
        do {
            unsigned int v = param_2[3];
            if (((v <= param_3 + 1 && param_3 + 1 <= param_2[4]) || param_3 < v) &&
                (best == 0 || v < best[3])) {
                bestsub = param_2 + 0x18;
                best = param_2;
            }
            param_4 = *param_2;
            i = i + 1;
            param_2 = (unsigned short *)((char *)param_2 + param_4);
        } while (i < count);
    }
    if (best != 0) {
        void *rec = func_ov302_020cbf64((int)best, bestsub);
        NNS_FndAppendListObject((void *)(param_1 + 0x18), rec);
        ret = 1;
    }
    return ret;
}
