/* Walks the record list appending the records passing the eligibility gate (kind, id < 900, group,
 * progress flags). */

/* Dispatch to Ov005_WalkRecordsAppendMatching with handler Ov005_IsMissionModeRowListed. */
extern unsigned short Ov005_WalkRecordsAppendMatching(int a, int b, int c, void *handler);
extern void Ov005_IsMissionModeRowListed(void);
int Ov005_AppendEligibleRecords(int param_1, int param_2, int param_3) {
    return Ov005_WalkRecordsAppendMatching(param_1, param_2, param_3, (void *)&Ov005_IsMissionModeRowListed);
}
