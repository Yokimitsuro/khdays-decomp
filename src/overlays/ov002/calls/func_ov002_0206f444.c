/* Instantiate the overlay's root object with a single construction parameter and
 * keep its handle. Both globals are reached by ADDRESS, not by value -- the
 * class descriptor is the object itself, and the handle slot is written in
 * place. */
extern int func_02023930(void *classDesc, int *params);

extern int data_ov002_0207f024;
extern char data_ov002_0207f028[];

void func_ov002_0206f444(int param) {
    int params[1];

    params[0] = param;
    data_ov002_0207f024 = func_02023930(data_ov002_0207f028, params);
}
