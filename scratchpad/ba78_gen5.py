import os

TYPES = """typedef struct {
    int x;
    int y;
    int z;
} Ov002Vec3;

typedef struct {
    Ov002Vec3 vecIn;
    int nField0c;
    char pad0010[0x24];
    Ov002Vec3 vecOut;
    int nValue;
} Ov002PoseEntry;

extern char *data_ov002_0207fa00;

"""

SIG = "void func_ov002_0206ba78(Ov002Vec3 *src, int value) {\n"
OUTER = """    char *base = data_ov002_0207fa00 + 0x8bcc;
    Ov002PoseEntry *entry;
    int off = 0;
    int i = 0;

    do {
"""
VALUE = """        if (value == -1) {
            entry->nValue = entry->nField0c;
        } else {
            entry->nValue = value;
        }
        i++;
        off += 0x44;
    } while (i < 4);
}
"""
IFELSE = """        if (src == 0) {
            from = &entry->vecIn;
        } else {
            from = src;
        }
"""

B = {}

# g1: a second entry-typed pointer, copied from entry, used as the copy destination
B["g1_entryalias"] = OUTER + """        Ov002Vec3 *from;
        Ov002PoseEntry *dst;

        entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
""" + IFELSE + """        dst = entry;
        dst->vecOut = *from;
""" + VALUE

# g2: alias assigned before the if/else
B["g2_aliasbefore"] = OUTER + """        Ov002Vec3 *from;
        Ov002PoseEntry *dst;

        entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        dst = entry;
""" + IFELSE + """        dst->vecOut = *from;
""" + VALUE

# g3: alias declared before from
B["g3_aliasdeclfirst"] = OUTER + """        Ov002PoseEntry *dst;
        Ov002Vec3 *from;

        entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        dst = entry;
""" + IFELSE + """        dst->vecOut = *from;
""" + VALUE

# g4: destination local assigned after the if/else, addressed as a member
B["g4_dstafter"] = OUTER + """        Ov002Vec3 *from;
        Ov002Vec3 *dst;

        entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
""" + IFELSE + """        dst = &entry->vecOut;
        *dst = *from;
""" + VALUE

# g5: alias is a char cursor, copy through a cast
B["g5_charalias"] = OUTER + """        Ov002Vec3 *from;
        char *dst;

        entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        dst = (char *)entry;
""" + IFELSE + """        *(Ov002Vec3 *)(dst + 0x34) = *from;
""" + VALUE

# g6: alias is a char cursor assigned after the if/else
B["g6_charaliasafter"] = OUTER + """        Ov002Vec3 *from;
        char *dst;

        entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
""" + IFELSE + """        dst = (char *)entry;
        *(Ov002Vec3 *)(dst + 0x34) = *from;
""" + VALUE

# g7: alias points at vecIn, destination reached by the struct offset
B["g7_vecinalias"] = OUTER + """        Ov002Vec3 *from;
        Ov002Vec3 *dst;

        entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
""" + IFELSE + """        dst = &entry->vecIn;
        *(Ov002Vec3 *)((char *)dst + 0x34) = *from;
""" + VALUE

# g8: entry aliased, both the copy and the value writes go through the alias
B["g8_aliasall"] = OUTER + """        Ov002Vec3 *from;
        Ov002PoseEntry *dst;

        entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        dst = entry;
""" + IFELSE + """        dst->vecOut = *from;
""" + VALUE

# g9: alias declared inner, entry inner too
B["g9_bothinner"] = """    char *base = data_ov002_0207fa00 + 0x8bcc;
    int off = 0;
    int i = 0;

    do {
        Ov002PoseEntry *entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
        Ov002Vec3 *from;
        Ov002PoseEntry *dst;

""" + IFELSE + """        dst = entry;
        dst->vecOut = *from;
""" + VALUE

# g10: alias inner, entry outer, alias declared after from, assigned last
B["g10_aliaslast"] = OUTER + """        Ov002Vec3 *from;
        Ov002PoseEntry *dst;

        entry = (Ov002PoseEntry *)(*(char **)(base + 4) + off);
""" + IFELSE + """        dst = entry;
        dst->vecOut = *from;
""" + VALUE

out = os.path.join("build", "try", "ba78")
for name, body in B.items():
    with open(os.path.join(out, name + ".c"), "w") as f:
        f.write(TYPES + SIG + body)
print("wrote %d" % len(B))
