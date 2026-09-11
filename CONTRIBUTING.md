# Contributing

Contributing to the **Intel(R) Graphics Extensions SDK** is subject to our
[code of conduct](CODE_OF_CONDUCT.md).

## Submitting issues

### Security issues

Do not submit security issues here on GitHub or in any other public channel!
Instead, see the [SECURITY.md](SECURITY.md) file for instructions.

### Other issues

Submit regular issues here on GitHub. Include relevant data like the SDK version
(see [sdk/docs/CHANGELOG.md](sdk/docs/CHANGELOG.md)), the extension API version
you requested, your GPU and installed Intel Graphics Driver version, and your
OS build.

Our main bugtracker is an internal one, so don't be surprised if a known bug is
not filed on GitHub.

## What can be contributed here

This repository is a published snapshot of an SDK developed inside Intel. What
you can change depends on whether a file is written by hand or generated.

| Area | Contributions |
| ---- | ------------- |
| `samples/` | Yes — bug fixes and improvements |
| `docs/`, `README.md`, `sdk/BUILDING.md` | Yes — corrections and clarifications |
| `sdk/src/stdafx.h`, `stdafx.cpp`, `igdext_helper.h` | Yes — these are hand-written parts of the loader |
| `sdk/src/igdext_api.cpp`, `igdext_api.h`, `igdext_api_dll.h` | **Generated** from an API description. A patch here is lost on the next release — open an issue describing the change instead |
| `sdk/include/igdext.h`, `igdext_tools.h` | **Generated.** Open an issue |
| `sdk/docs/*.md` | **Generated.** Open an issue |
| `sdk/lib/*.lib` | Prebuilt from the sources in `sdk/src`; see [sdk/BUILDING.md](sdk/BUILDING.md). Open an issue |

Every generated file says "auto-generated" near the top, so you can also tell
from the file itself.

Note that the extension entry points themselves are implemented in the Intel
Graphics Driver, not here. `sdk/src` is the loader and wrapper: it finds the
driver's extensions DLL, resolves the entry points and forwards calls. A change
to what an extension *does* is a driver change, and belongs in an issue.

## Contributing code

We accept pull requests here on GitHub. Before starting work on a PR, please let
us know what you want to work on. This will avoid duplicating efforts and will
ensure that your work aligns with our vision and direction.

Please write proper commit messages. (A popular howto:
[cbea.ms/git-commit](https://cbea.ms/git-commit/).) Please create commits that
are _logical_, _discrete_, _easy_ to review steps toward your end goal.

### License

The **Intel(R) Graphics Extensions SDK** is licensed under the terms in
[LICENSE](LICENSE). By contributing to the project, you agree to the license and
copyright terms therein and release your contribution under these terms.

Some files carry a third party's copyright and are listed in
[THIRD-PARTY-NOTICES.md](THIRD-PARTY-NOTICES.md). Do not remove or alter those
notices.

### Sign your work

Please use the sign-off line at the end of the patch. Your signature certifies
that you wrote the patch or otherwise have the right to pass it on as an
open-source patch. The rules are pretty simple: if you can certify the below
(from [developercertificate.org](http://developercertificate.org/)):

```
Developer Certificate of Origin
Version 1.1

Copyright (C) 2004, 2006 The Linux Foundation and its contributors.
660 York Street, Suite 102,
San Francisco, CA 94110 USA

Everyone is permitted to copy and distribute verbatim copies of this
license document, but changing it is not allowed.

Developer's Certificate of Origin 1.1

By making a contribution to this project, I certify that:

(a) The contribution was created in whole or in part by me and I
    have the right to submit it under the open source license
    indicated in the file; or

(b) The contribution is based upon previous work that, to the best
    of my knowledge, is covered under an appropriate open source
    license and I have the right under that license to submit that
    work with modifications, whether created in whole or in part
    by me, under the same open source license (unless I am
    permitted to submit under a different license), as indicated
    in the file; or

(c) The contribution was provided directly to me by some other
    person who certified (a), (b) or (c) and I have not modified
    it.

(d) I understand and agree that this project and the contribution
    are public and that a record of the contribution (including all
    personal information I submit with it, including my sign-off) is
    maintained indefinitely and may be redistributed consistent with
    this project or the open source license(s) involved.
```

Then you just add a line to every git commit message:

    Signed-off-by: Your Name <your.name@email.com>

Use your real name (sorry, no pseudonyms or anonymous contributions.)

If you set your `user.name` and `user.email` git configs, you can sign your
commit automatically with `git commit -s`.
