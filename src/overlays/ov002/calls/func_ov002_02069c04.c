/*
 * Ov002_SetStateRecordStage - set the three stage/status bytes at +5/+6/+7 of the state
 * record at root-context + 0x8c94 to 0, 1, 2. Leaf helper chained from
 * Ov002_InitStateRecord (func_ov002_02069c24) at the end of that record's reset.
 *
 * THUMB leaf (bx lr).
 */

extern int data_ov002_0207fa00;

void func_ov002_02069c04(void)
{
    char *rec = (char *)(data_ov002_0207fa00 + 0x8c94);

    rec[5] = 0;
    rec[6] = 1;
    rec[7] = 2;
}
