/* Whether every flag of the offset-table row set for `key` is raised: the table is loaded, the
 * rows (0x14 apart, count in the set's +2) whose flag (+8 id plus nine) is clear are counted,
 * the count is reported through e700 (kind 1) and the table released; 1 when none is missing. */
typedef signed char s8;
typedef short s16;

extern void func_ov002_0206e0f0(int nWhich);
extern char *func_ov002_0206e144(int nKey);
extern int func_02023588(int nFlag);
extern void func_ov002_0206e700(int a, int count);
extern void func_ov002_0206e184(void);

int func_ov069_020b8320(int key)
{
    int missing;
    char *rows;
    int i;
    char *row;

    missing = 0;
    func_ov002_0206e0f0(0);
    rows = func_ov002_0206e144(key);
    if (rows != 0) {
        i = 0;
        if (*(s8 *)(rows + 2) > 0) {
            row = rows;
            do {
                if (func_02023588(*(s16 *)(row + 8) + 9) == 0) {
                    missing++;
                }
                i++;
                row += 0x14;
            } while (i < *(s8 *)(rows + 2));
        }
    }
    func_ov002_0206e700(1, missing);
    func_ov002_0206e184();
    if (missing == 0) {
        return 1;
    }
    return 0;
}
