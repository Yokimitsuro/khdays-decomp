/* Update the scroll position: scale the row by 0x4d and divide by the viewport
 * height at +0xcc, then store the pair at +0x34/+0x38 and relayout -- but only
 * when it actually changed. func_02020400 is the signed divide helper; the
 * QUOTIENT is the low half of its return. */
extern long long func_02020400(int a, int b);
extern void func_ov002_02058898(void);

extern char *data_ov002_0207f618;

void func_ov002_02059730(int row, int offset) {
    char *ctx = data_ov002_0207f618;
    int scaled;

    if (ctx == 0) {
        return;
    }

    scaled = (int)func_02020400(offset * 0x4d, *(unsigned short *)(ctx + 0xcc));

    if (*(int *)(ctx + 0x34) == row && *(unsigned short *)(ctx + 0x38) == scaled) {
        return;
    }

    *(int *)(ctx + 0x34) = row;
    *(short *)(ctx + 0x38) = (short)scaled;
    func_ov002_02058898();
}
