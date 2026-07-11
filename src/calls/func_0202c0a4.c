/* Return &elem[index] (0x14 stride) of the sub-table at *(data_0204c208+0x61c4),
 * or NULL when that table pointer is null or index is the 0xff sentinel. */
extern int data_0204c208;

void *func_0202c0a4(int index) {
    int invalid = 1;
    int base = *(int *)(data_0204c208 + 0x6000 + 0x1c4);
    if (base != 0 && index != 0xff) invalid = 0;
    if (invalid) return 0;
    return (void *)(base + index * 0x14);
}
