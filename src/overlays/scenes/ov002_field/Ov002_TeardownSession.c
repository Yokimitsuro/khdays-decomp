/* Tear down the ov002 session at data_ov002_0207f99c: run the pre-teardown pass,
 * destroy the object whose handle is at +0, free every object on the list at
 * +8 (taking each successor before freeing), then drop the pointer. */
extern int data_ov002_0207f99c;

extern void Ov002_FreeCueTable(void);
extern void VeneerTo_Obj_Destroy(int handle);
extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern void NNSi_FndFreeFromDefaultHeap(void *p);

void Ov002_TeardownSession(void) {
    void **node;
    char *self = *(char **)&data_ov002_0207f99c;

    Ov002_FreeCueTable();
    VeneerTo_Obj_Destroy(*(int *)self);

    node = (void **)NNS_FndGetNextListObject(self + 8, 0);
    while (node != 0) {
        void **next = (void **)NNS_FndGetNextListObject(self + 8, node);

        if (node != 0) {
            NNSi_FndFreeFromDefaultHeap(node);
        }
        node = next;
    }

    *(int *)&data_ov002_0207f99c = 0;
}
