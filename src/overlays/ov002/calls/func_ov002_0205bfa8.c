/*
 * func_ov002_0205bfa8 - refresh a 4-entry table of active elements (ARM).
 *
 * Walks the four stride-0x10 records starting at data_ov002_0207f620 + 0x440; for each record whose
 * type word (+0) is 3, recomputes its cached value (+8) by calling func_ov002_0205a598(0, record+0xc).
 * The loop index is declared before the record pointer so it claims the lower register the ROM uses.
 */
extern int data_ov002_0207f620;
extern int func_ov002_0205a598(int a, int b);

void func_ov002_0205bfa8(void)
{
    int base = *(int *)&data_ov002_0207f620;
    int i;
    char *entry = (char *)(base + 0x440);
    for (i = 0; i < 4; i++) {
        if (*(unsigned short *)entry == 3) {
            *(int *)(entry + 8) = func_ov002_0205a598(0, *(unsigned short *)(entry + 0xc));
        }
        entry += 0x10;
    }
}
