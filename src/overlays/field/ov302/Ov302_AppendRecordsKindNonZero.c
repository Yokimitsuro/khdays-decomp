/* Walks the record list appending the records whose kind byte (+0x23) is nonzero. Returns what
 * Ov302_ParseRecordListAppendMatches returns. */

extern int Ov302_ParseRecordListAppendMatches(void *a, void *b, void *c, void *cb);
extern void Ov302_RecordFilter_MissionModeEntry(void);

int Ov302_AppendRecordsKindNonZero(void *a, void *b, void *c) {
    return Ov302_ParseRecordListAppendMatches(a, b, c, Ov302_RecordFilter_MissionModeEntry);
}
