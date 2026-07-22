/* Accept the request and, when there is a live context and the transition has
 * finished, notify with 3 for a non-zero request and -1 for a zero one. Reports
 * whether the request was accepted at all. */
extern int func_ov002_0205d450(int req);
extern int func_ov002_020573a4(void);
extern void func_ov002_0205d96c(int code);

extern char *data_ov002_0207f614;

int func_ov002_02056d90(int req) {
    if (func_ov002_0205d450(req) == 0) {
        return 0;
    }

    if (data_ov002_0207f614 != 0 && func_ov002_020573a4() != 0) {
        func_ov002_0205d96c(req != 0 ? 3 : -1);
    }

    return 1;
}
