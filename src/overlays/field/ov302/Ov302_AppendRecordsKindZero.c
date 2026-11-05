/* Walks the record list appending the records whose kind byte (+0x23) is 0. Returns what
 * Ov302_ParseRecordListAppendMatches returns. */

extern int Ov302_ParseRecordListAppendMatches(void *a, void *b, void *c, void *cb);
extern void Ov302_RecordFilter_StoryRow(void);

int Ov302_AppendRecordsKindZero(void *a, void *b, void *c) {
    return Ov302_ParseRecordListAppendMatches(a, b, c, Ov302_RecordFilter_StoryRow);
}
