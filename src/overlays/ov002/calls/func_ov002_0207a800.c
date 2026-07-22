/* Set the list's shared mode byte at +0x7a and push the same mode into every row,
 * addressing each row's entry through its byte id at +0x10. The row count at
 * +0x50 is re-read on every iteration rather than cached -- that is the ROM. */
extern int func_ov002_02076468(int listId);
extern int func_ov002_02076a80(int list, int row);
extern void func_ov002_02076968(int entry, int mode);

void func_ov002_0207a800(int listId, int mode) {
    char *list = (char *)func_ov002_02076468(listId);
    int i = 0;

    list[0x7a] = (char)mode;

    while (i < *(unsigned short *)(list + 0x50)) {
        func_ov002_02076968(*(unsigned char *)(func_ov002_02076a80((int)list, i) + 0x10), mode);
        i++;
    }
}
