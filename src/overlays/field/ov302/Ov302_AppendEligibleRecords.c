/* Walks the record list appending the records passing the eligibility gate (kind, id < 900, group,
 * progress flags). Returns what Ov302_ParseRecordListAppendMatches returns. */

extern int Ov302_ParseRecordListAppendMatches(void *a, void *b, void *c, void *cb);
extern void Ov302_IsMissionModeRowListed(void);

int Ov302_AppendEligibleRecords(void *a, void *b, void *c) {
    return Ov302_ParseRecordListAppendMatches(a, b, c, Ov302_IsMissionModeRowListed);
}
