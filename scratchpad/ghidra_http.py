"""Direct HTTP bridge to Ghidra on 8089, the documented fallback when the MCP
tools are unavailable."""
import sys
import json
import http.client
import urllib.parse


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


def get(endpoint, params=None, timeout=120):
    query = "?" + urllib.parse.urlencode(params) if params else ""
    c = http.client.HTTPConnection("127.0.0.1", 8089, timeout=timeout)
    c.request("GET", "/" + endpoint + query)
    r = c.getresponse()
    out = r.read().decode("utf-8", "replace")
    c.close()
    return out.strip()


if __name__ == "__main__":
    what = sys.argv[1]
    if what == "decompile":
        print(get("decompile_function", {"address": sys.argv[2]}))
    elif what == "disasm":
        print(get("disassemble_function", {"address": sys.argv[2]}))
    elif what == "sig":
        print(get("get_function_signature", {"address": sys.argv[2]}))
    elif what == "struct":
        print(get("get_struct_layout", {"struct_name": sys.argv[2]}))
    elif what == "script":
        print(post("run_ghidra_script", {"script_name": sys.argv[2]}))
    elif what == "save":
        print(post("save_program", {}))
    else:
        print(get(what, dict(a.split("=", 1) for a in sys.argv[2:])))
