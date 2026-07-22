/* Scene entry: publish the slot-4 descriptor, build the scene registry object
 * from its class template and park it in data_ov002_0207fa20 -- the registry the
 * ov002 accessor family reaches through ((int *)&data_ov002_0207fa20)[1].
 * Reports 1 = entered. */
extern void func_02020aa8(int index, int value);
extern int func_02023930(const void *cls, int a);

extern char data_ov002_0207f484[];
extern char data_ov002_0207f454[];
extern int data_ov002_0207fa20;

int func_ov002_020763c8(void) {
    func_02020aa8(4, (int)data_ov002_0207f484);
    data_ov002_0207fa20 = func_02023930(data_ov002_0207f454, 0);
    return 1;
}
