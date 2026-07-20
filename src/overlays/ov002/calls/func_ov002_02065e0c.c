/* Tear down the ov002 session at data_ov002_0207f99c: run the pre-teardown pass,
 * close the wireless key-sharing handle at +0, free every object on the list at
 * +8 (taking each successor before freeing), then drop the pointer. */
extern int data_ov002_0207f99c;

extern void func_ov002_02067028(void);
extern void WM_EndKeySharing_0x02023ad0(int handle);
extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern void NNSi_FndFreeFromDefaultHeap(void *p);

void func_ov002_02065e0c(void) {
    void **node;
    char *self = *(char **)&data_ov002_0207f99c;

    func_ov002_02067028();
    WM_EndKeySharing_0x02023ad0(*(int *)self);

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
