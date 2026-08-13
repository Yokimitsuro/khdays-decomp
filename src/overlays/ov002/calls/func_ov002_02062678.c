/* Append one option's entries to the caller's list, optionally after the shared defaults.
 *
 * The record comes from the table at 0x1b4 of the scene context, selected by index. The defaults
 * are a fixed halfword table passed by address, and they only go in when the caller asks. The
 * limit is handed to both appends unchanged.
 *
 * The context is bound before the guard, not inside it, which is what the original does.
 */

extern char *data_ov002_0207f62c[];
extern short data_ov002_0207ed1c[];
extern void func_ov002_02062608(short *out, short *source, int limit);
extern short *func_ov002_02052844(char *table, unsigned int index);

void func_ov002_02062678(short *out, unsigned int index, int withDefaults, int limit) {
    char *ctx = data_ov002_0207f62c[1];

    if (withDefaults != 0) {
        func_ov002_02062608(out, data_ov002_0207ed1c, limit);
    }
    func_ov002_02062608(out, func_ov002_02052844(ctx + 0x1b4, index), limit);
}
