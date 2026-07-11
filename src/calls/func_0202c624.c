/* Per-tick update for entity[index] (0x184 stride at data_0204c208+0xc4):
 * when state bits 0x18 are both set, snapshot the 3-word vector at +0xb4 into
 * +0x168 and run func_0202df34; then, gated by state bit 8 and flag bit 0x20,
 * advance via func_0202aa9c. */
extern int data_0204c208;
extern void func_0202df34(void *);
extern void func_0202aa9c(void *);

struct V3 { int a, b, c; };

void func_0202c624(int index) {
    unsigned char *entity = (unsigned char *)(data_0204c208 + 0xc4 + 0x184 * index);
    if ((entity[8] & 0x18) == 0x18) {
        *(struct V3 *)(entity + 0x168) = *(struct V3 *)(entity + 0xb4);
        func_0202df34(entity + 0x168);
    }
    if ((entity[8] & 8) == 0) return;
    if (*(int *)(entity + 0xc) & 0x20) return;
    func_0202aa9c(entity + 0x10);
}
