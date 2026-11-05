/* Walks the record list appending the records of kind 4 with id (+2) 10. Returns what
 * Ov302_ParseRecordListAppendMatches returns. */

extern int Ov302_ParseRecordListAppendMatches(void *a, void *b, void *c, void *cb);
extern void Ov302_RecordFilter_TutorialRow(void);

int Ov302_AppendRecordsKind4Id10(void *a, void *b, void *c) {
    return Ov302_ParseRecordListAppendMatches(a, b, c, Ov302_RecordFilter_TutorialRow);
}
