/* func_ov023_02083b7c -- store a two-word pair into slot `idx` of the ov023 slot table.
 * Slots are 0x30 bytes apart in the scene object (data_ov023_0208a784[1]) and the pair lands at
 * +0x18/+0x1c. Written as a struct copy on purpose: two separate member assignments make mwcc
 * load the second word first. */
extern int data_ov023_0208a784;

typedef struct { int a, b; } Pair;

void func_ov023_02083b7c(int idx, Pair *src) {
    char *slot = (char *)(*(int *)((char *)&data_ov023_0208a784 + 4) + idx * 0x30);
    *(Pair *)(slot + 0x18) = *src;
}
