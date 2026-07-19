"""audit_struct_sync.py -- structs declared in the C tree that Ghidra does not have.

The struct rule says: when you decode a layout, create the Ghidra type IN THE SAME
BATCH.  Within hours of writing that rule I typed three functions' C and skipped
the Ghidra half on all three.  That is the same failure the naming debt had, and
it has the same fix: stop relying on discipline and COUNT it.

A struct is "real" only when both halves exist:
  - in the .c, because that is what makes the match and what the port reads;
  - in Ghidra, because that is what makes every OTHER function touching the
    object readable.

This lists the named structs declared in non-stub .c files and flags the ones with
no Ghidra type of that name.  Run it at the end of a session, like
audit_unnamed.py.

    python tools/audit_struct_sync.py          # needs the Ghidra bridge on :8089
    python tools/audit_struct_sync.py --list   # every declaration, not just a count
"""
import json, os, re, sys, urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BRIDGE = 'http://127.0.0.1:8089'
# throwaway names: a per-file scratch shape, not a claim about a real object
GENERIC = {'A', 'B', 'C', 'D', 'E', 'S', 'T', 'X', 'Obj', 'Sub', 'Inner', 'Elem',
           'Foo', 'bf', 'hw60', 'b8', 'b1', 'w3', 'v3', 'blk11', 'row8', 'Mid',
           'Outer', 'Block', 'vec', 'vec3'}
# `}\s*NAME;` also matches the close of an if/loop followed by a bare statement,
# which is how `break` and `return` showed up as "structs" on the first run.
KEYWORDS = {'break', 'return', 'continue', 'goto', 'else', 'do', 'while', 'if'}
DECL = re.compile(r'\bstruct\s+([A-Za-z_]\w*)\s*\{|\}\s*([A-Za-z_]\w*)\s*;')


def strip_comments(t):
    t = re.sub(r'/\*.*?\*/', ' ', t, flags=re.S)
    return re.sub(r'//[^\n]*', ' ', t)


def c_structs():
    """name -> set of files declaring it (typedef'd or tagged)."""
    out = {}
    for base in ('src', 'libs'):
        for dp, dn, fn in os.walk(os.path.join(ROOT, base)):
            dn[:] = [d for d in dn if d != 'asm_stubs']
            for f in fn:
                if not f.endswith('.c'):
                    continue
                p = os.path.join(dp, f)
                try:
                    t = strip_comments(open(p, errors='replace').read())
                except OSError:
                    continue
                for m in re.finditer(r'\bstruct\s+([A-Za-z_]\w*)\s*\{', t):
                    out.setdefault(m.group(1), set()).add(p)
                for m in re.finditer(r'\}\s*([A-Za-z_]\w*)\s*;', t):
                    if m.group(1) in KEYWORDS:
                        continue
                    out.setdefault(m.group(1), set()).add(p)
    return out


def ghidra_types():
    try:
        req = urllib.request.Request(BRIDGE + '/list_data_types?limit=2000')
        raw = urllib.request.urlopen(req, timeout=20).read().decode('utf-8', 'replace')
    except Exception as e:
        print('!! Ghidra bridge unreachable (%s) -- cannot check the Ghidra half.' % e)
        print('   Start it, or check by hand with mcp__ghidra__get_struct_layout.')
        return None
    return set(re.findall(r'[A-Za-z_]\w*', raw))


if __name__ == '__main__':
    cs = c_structs()
    interesting = {n: f for n, f in cs.items() if n not in GENERIC and len(n) > 3}
    gt = ghidra_types()
    print('named structs declared in the C tree: %d (of %d, ignoring scratch names)'
          % (len(interesting), len(cs)))
    if gt is None:
        sys.exit(1)
    missing = sorted((len(f), n, f) for n, f in interesting.items() if n not in gt)
    print('WITHOUT a Ghidra type of the same name: %d' % len(missing))
    print()
    for cnt, n, files in sorted(missing, reverse=True):
        print('  %-28s %d file(s)' % (n, cnt))
        if '--list' in sys.argv:
            for p in sorted(files):
                print('      %s' % os.path.relpath(p, ROOT).replace(os.sep, '/'))
