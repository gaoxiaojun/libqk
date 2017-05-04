![libqk][libqk_banner]

## Overview

libqk is a multi-platform support library with a focus on automated trading system. 

## Feature highlights

## Versioning

Starting with version 1.0.0 libqk follows the [semantic versioning](http://semver.org/)
scheme. The API change and backwards compatibility rules are those indicated by
SemVer. libqk will keep a stable ABI across major releases.

The ABI/API changes can be tracked [here](http://abi-laboratory.pro/tracker/timeline/libqk/).

## Licensing

libqk is licensed under the BSD license. Check the [LICENSE file](LICENSE).

## Community

 * [Support](https://github.com/libqk/help)
 * [Mailing list](http://groups.google.com/group/libqk)
 * [IRC chatroom (#libqk@irc.freenode.org)](http://webchat.freenode.net?channels=libqk&uio=d4)

## Documentation

### Official API documentation

Located in the docs/ subdirectory. It uses the [Sphinx](http://sphinx-doc.org/)
framework, which makes it possible to build the documentation in multiple
formats.

Show different supported building options:

    $ make help

Build documentation as HTML:

    $ make html

Build documentation as HTML and live reload it when it changes (this requires
sphinx-autobuild to be installed and is only supported on Unix):

    $ make livehtml

Build documentation as man pages:

    $ make man

Build documentation as ePub:

    $ make epub

NOTE: Windows users need to use make.bat instead of plain 'make'.

Documentation can be browsed online [here](http://docs.libqk.org).

The [tests and benchmarks](https://github.com/libqk/libqk/tree/master/test)
also serve as API specification and usage examples.

## Downloading

libqk can be downloaded either from the
[GitHub repository](https://github.com/libqk/libqk)
or from the [downloads site](http://dist.libqk.org/dist/).

Starting with libqk 1.7.0, binaries for Windows are also provided. This is to
be considered EXPERIMENTAL.

Before verifying the git tags or signature files, importing the relevant keys
is necessary. Key IDs are listed in the
[MAINTAINERS](https://github.com/libqk/libqk/blob/master/MAINTAINERS.md)
file, but are also available as git blob objects for easier use.

Importing a key the usual way:

    $ gpg --keyserver pool.sks-keyservers.net \
      --recv-keys AE9BC059

Importing a key from a git blob object:

    $ git show pubkey-saghul | gpg --import

### Verifying releases

Git tags are signed with the developer's key, they can be verified as follows:

    $ git verify-tag v1.0.0

Starting with libqk 1.0.0, the tarballs stored in the
[downloads site](http://dist.libqk.org/dist/) are signed and an accompanying
signature file sit alongside each. Once both the release tarball and the
signature file are downloaded, the file can be verified as follows:

    $ gpg --verify libqk-1.0.0.tar.gz.sign

## Build Instructions

For GCC there are two build methods: via autotools or via [GYP][].
GYP is a meta-build system which can generate MSVS, Makefile, and XCode
backends. It is best used for integration into other projects.

To build with autotools:

    $ sh autogen.sh
    $ ./configure
    $ make
    $ make check
    $ make install

### Windows

First, [Python][] 2.6 or 2.7 must be installed as it is required by [GYP][].
If python is not in your path, set the environment variable `PYTHON` to its
location. For example: `set PYTHON=C:\Python27\python.exe`

To build with Visual Studio, launch a git shell (e.g. Cmd or PowerShell)
and run vcbuild.bat which will checkout the GYP code into build/gyp and
generate qk.sln as well as related project files.

To have GYP generate build script for another system, checkout GYP into the
project tree manually:

    $ git clone https://chromium.googlesource.com/external/gyp.git build/gyp

### Unix

For Debug builds (recommended) run:

    $ ./gyp_qk.py -f make
    $ make -C out

For Release builds run:

    $ ./gyp_qk.py -f make
    $ BUILDTYPE=Release make -C out

Run `./gyp_qk.py -f make -Dtarget_arch=x32` to build [x32][] binaries.

### OS X

Run:

    $ ./gyp_qk.py -f xcode
    $ xcodebuild -ARCHS="x86_64" -project qk.xcodeproj \
         -configuration Release -target All

Using Homebrew:

    $ brew install --HEAD libqk

Note to OS X users:

Make sure that you specify the architecture you wish to build for in the
"ARCHS" flag. You can specify more than one by delimiting with a space
(e.g. "x86_64 i386").

### Using Ninja

To use ninja for build on ninja supported platforms, run:

    $ ./gyp_qk.py -f ninja
    $ ninja -C out/Debug     #for debug build OR
    $ ninja -C out/Release


### Running tests

Run:

    $ ./gyp_qk.py -f make
    $ make -C out
    $ ./out/Debug/run-tests

## Supported Platforms

check the [SUPPORTED_PLATFORMS file](SUPPORTED_PLATFORMS.md).
