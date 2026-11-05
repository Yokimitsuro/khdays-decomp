/* Walks the record list appending the records passing the eligibility gate (kind, id < 900, group,
 * progress flags). */

/* Dispatch to Ov009_WalkRecordsAppendMatching with handler Ov009_IsMissionModeRowListed. */
extern unsigned short Ov009_WalkRecordsAppendMatching(int a, int b, int c, void *handler);
extern void Ov009_IsMissionModeRowListed(void);
int Ov009_AppendEligibleRecords(int param_1, int param_2, int param_3) {
    return Ov009_WalkRecordsAppendMatching(param_1, param_2, param_3, (void *)&Ov009_IsMissionModeRowListed);
}
