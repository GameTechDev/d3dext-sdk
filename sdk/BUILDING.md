# Building the static library from source

The SDK ships prebuilt static libraries in `sdk/lib`, and linking those is the normal way to
use it. The loader sources are in `sdk/src`, so you can also build the library yourself,
which is useful if you need a different toolset, CRT or compiler configuration.

## Sources

The library is small. It compiles from six files in `sdk/src`:

| File | Role |
| ---- | ---- |
| `igdext_api.cpp` | Library implementation |
| `igdext_api.h` | Extension context definition |
| `igdext_api_dll.h` | Entry-point typedefs |
| `igdext_helper.h` | Locates and loads the driver's extensions DLL |
| `stdafx.h` | Precompiled header |
| `stdafx.cpp` | Precompiled header source |

plus the two public headers in `sdk/include`, `igdext.h` and `igdext_tools.h`. Those are kept
in one place only, so the copy your application compiles against is the same one the library
is built from.

`igdext_api.cpp`, `igdext_api.h`, `igdext_api_dll.h` and the two public headers are generated
from an API description; the header comments say so. Edit them in the generator, not here.

## Build

A plain clone is enough:

```
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

To build against a different snapshot of the sources, name the directory holding them:

```
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DD3DEXT_SDK_SOURCE_DIR=<dir>
```

Use `-A Win32` for the 32-bit library. The result is `build/Release/igdext64.lib` or
`build/Release/igdext32.lib`.

Configuration fails with the names of any missing files rather than partway through the
compile.

## Notes on the build settings

The target mirrors how the shipped libraries are built:

- `/Zl` — the library does not name a CRT, so the consuming application chooses its own. This
  is why the same `.lib` links into applications built `/MT` or `/MD`.
- `/guard:cf`, `/GS`, `/sdl` — control flow guard and the security checks.
- `stdafx.h` is used as a precompiled header; every translation unit includes it first.
- `D3DEXT_PUBLIC_ONLY` is defined; it drops the includes of the internal API headers, which
  are not part of this SDK.

## Verifying a build

A library built from these sources exports the same symbols as the shipped one:

```
dumpbin -symbols build/Release/igdext64.lib > new.txt
dumpbin -symbols sdk/lib/x64/Release/igdext64.lib > shipped.txt
```

Extract the `INTC_*` names from each and compare. For the 4.21.12 sources both sets contain
the same 62 symbols.

If you are running from Git Bash, use `-symbols` rather than `/symbols` — the shell rewrites
a leading slash into a path and `dumpbin` then fails with `LNK1181`.
