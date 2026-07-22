/* Queue a graphics command and record it: enqueue, then allocate a 0x14-byte
 * record whose first word is the override from the fifth argument when there is
 * one and the third argument otherwise, and append it to the menu root's list at
 * +0xb0. */
extern void GFXi_EnqueueCommand(int a, int b, int c, int d);
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void MI_CpuFill8(void *dst, unsigned char value, unsigned int size);
extern void NNS_FndAppendListObject(void *list, void *object);

extern char *data_ov002_0207f60c;

void func_ov002_02053d28(int a, int b, int c, int d, int override) {
    void *record;

    GFXi_EnqueueCommand(a, b, c, d);

    record = NNSi_FndAllocFromDefaultExpHeap(0x14);
    MI_CpuFill8(record, 0, 0x14);

    if (override != 0) {
        c = override;
    }
    *(int *)record = c;

    NNS_FndAppendListObject(data_ov002_0207f60c + 0xb0, record);
}
