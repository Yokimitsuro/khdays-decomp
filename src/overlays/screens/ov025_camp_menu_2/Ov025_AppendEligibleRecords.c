/* Walks the record list appending the records passing the eligibility gate (kind, id < 900, group,
 * progress flags). */

extern unsigned short Ov025_WalkRecordsAppendMatching();
extern int Ov025_IsMissionModeRowListed();

int Ov025_AppendEligibleRecords(int arg0, int arg1, int arg2) {
    return Ov025_WalkRecordsAppendMatching(arg0, arg1, arg2, Ov025_IsMissionModeRowListed);
}
