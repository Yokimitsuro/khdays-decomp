/* Walks the record list appending the records passing the eligibility gate (kind, id < 900, group,
 * progress flags). */

/* Dispatch to Ov004_WalkRecordsAppendMatching with handler Ov004_IsMissionModeRowListed. */
extern unsigned short Ov004_WalkRecordsAppendMatching(int a, int b, int c, void *handler);
extern void Ov004_IsMissionModeRowListed(void);
int Ov004_AppendEligibleRecords(int param_1, int param_2, int param_3) {
    return Ov004_WalkRecordsAppendMatching(param_1, param_2, param_3, (void *)&Ov004_IsMissionModeRowListed);
}
