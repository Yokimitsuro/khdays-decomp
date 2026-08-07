# Semantic Ghidra gate

## Required mutation protocol

1. Inspect function decompilation and disassembly.
2. Confirm the correct address space and ARM/THUMB mode.
3. Apply names, prototype and types through an ASCII Jython script in `~/ghidra_scripts/`.
4. Run with `run_ghidra_script`; never use `run_script_inline`.
5. Save with a separate `save_program` call.
6. Read every mutation back by address.
7. Record concrete output in the semantic receipt.

Bridge fallback:

```python
import http.client, json, urllib.parse

def post(endpoint, payload, timeout=600):
    c = http.client.HTTPConnection("127.0.0.1", 8089, timeout=timeout)
    body = json.dumps(payload).encode()
    c.request("POST", "/" + endpoint, body=body,
              headers={"Content-Type": "application/json",
                       "Content-Length": str(len(body))})
    r = c.getresponse()
    out = r.read().decode("utf-8", "replace")
    c.close()
    return r.status, out

def get(endpoint, params=None, timeout=60):
    query = "?" + urllib.parse.urlencode(params) if params else ""
    c = http.client.HTTPConnection("127.0.0.1", 8089, timeout=timeout)
    c.request("GET", "/" + endpoint + query)
    r = c.getresponse()
    out = r.read().decode("utf-8", "replace")
    c.close()
    return out.strip()

post("run_ghidra_script", {"script_name": "NameAndTypeFoo.py"})
post("save_program", {})
print(get("get_function_by_address",
          {"address": "arm9_ov002::020679d4"}))
```

Use the overlay-qualified address. An unqualified lookup can return a false “not found”.

## Struct decision

Every function must record one of:

- `created`: new semantic type created in Ghidra;
- `extended`: existing type gained verified fields;
- `reused`: existing type already represented every decoded access and was applied;
- `no_new_layout`: the function revealed no new object layout, with an explicit explanation.

For globals loaded through literal pools, apply `T *` or `T **` to the pool slot according to the
real pointer depth. Overlay `.bss` can use a separate address space.

## Receipt commands

Replace the example evidence with real read-back output. Do not mark a field from intention alone.

```bash
python .claude/hooks/khdays_control.py semantic-mark ghidra_inspected true
python .claude/hooks/khdays_control.py semantic-mark semantic_name "Game_ActionInitObject"
python .claude/hooks/khdays_control.py semantic-mark function_rename_readback true
python .claude/hooks/khdays_control.py semantic-mark function_rename_evidence \
  "get_function_by_address returned Game_ActionInitObject"

python .claude/hooks/khdays_control.py semantic-mark parameters_reviewed true
python .claude/hooks/khdays_control.py semantic-mark parameters_evidence \
  "state: GameState *, cmd: const s16 *; read back from Ghidra"

python .claude/hooks/khdays_control.py semantic-mark locals_reviewed true
python .claude/hooks/khdays_control.py semantic-mark locals_evidence \
  "entry and payload renamed; remaining compiler temporaries explicitly reviewed"

python .claude/hooks/khdays_control.py semantic-mark prototype_readback true
python .claude/hooks/khdays_control.py semantic-mark prototype_evidence \
  "void Game_ActionInitObject(GameState *state, const s16 *cmd)"

python .claude/hooks/khdays_control.py semantic-mark layout_decision extended
python .claude/hooks/khdays_control.py semantic-mark layout_evidence \
  "Extended GameState with actionScratch at verified offset 0x578"

python .claude/hooks/khdays_control.py semantic-mark types_applied_readback true
python .claude/hooks/khdays_control.py semantic-mark types_evidence \
  "state parameter and literal-pool slot decompile through GameState fields"

python .claude/hooks/khdays_control.py semantic-mark transactions_closed true
python .claude/hooks/khdays_control.py semantic-mark transactions_evidence \
  "no open transaction after CloseTxAndSave/read-back"

python .claude/hooks/khdays_control.py semantic-mark program_saved_readback true
python .claude/hooks/khdays_control.py semantic-mark save_evidence \
  "save_program succeeded; VerifySaved reported isChanged=false"

python .claude/hooks/khdays_control.py semantic-mark audit_unnamed_no_new_debt true
python .claude/hooks/khdays_control.py semantic-mark audit_unnamed_evidence \
  "active function absent from new unnamed debt"

python .claude/hooks/khdays_control.py semantic-mark audit_struct_sync_no_new_debt true
python .claude/hooks/khdays_control.py semantic-mark audit_struct_sync_evidence \
  "all active-function C layouts represented by Ghidra types"
```

Then run:

```bash
python .claude/hooks/khdays_control.py semantic-check
```
