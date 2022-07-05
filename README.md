# C-WIN-SHW

A shell interpreter wrapper for windows' OpenSSHD.

## Issue

The OpenSSHD implementation shipped with MS Windows has the following issues.

1.- It isn't posible to specify arguments for the shell. The interpreter can
    be set by changing "HKLM:\SOFTWARE\OpenSSH DefaultShell" but it doesn't
    allow arguments (such as -l).
    
2.- A wrapper can't be done in "cmd.exe" language, because it doesn't allow
    newlines in it's arguments. So the following command would fail:
    
    ssh USER@MACHINE '
    echo Hello
    echo World
    '

## Solution.

The [x64/shw.exe](x64/shw.exe) and [x32/shw.exe](x32/shw.exe) binaries execute the
"busybox.exe" shell with -l.

This way you can setup the shell environment by writting %USERPROFILE%\.profile.

## Prerequisites

- MS Windows (Runtime).
- Mingw32 gcc and GNU/Make (Build time).

## Installing

1.- Copy [x32/busybox.exe](x32/busybox.exe) and [x32/shw.exe](x32/shw.exe) to some
    directory. (32bits)

1.- Copy [x64/busybox.exe](x64/busybox.exe) and [x64/shw.exe](x64/shw.exe) to
    some directory. (64bits).

2.- Configure OpenSSHD to run shw with PowerShell.

    New-ItemProperty -Path "HKLM:\SOFTWARE\OpenSSH" -Name DefaultShell -Value "<SHW-PATH>" -PropertyType String -Force
    or
    Set-ItemProperty -Path "HKLM:\SOFTWARE\OpenSSH" -Name DefaultShell -Value "<SHW-PATH>"

## Building

The Makefile builds both versions, 32 and 64. You can disable one or change the
compiler by setting CC32 and CC64.

    make                # On a linux machine with a cross compiler.
    make CC64=gcc C32=  # In a Windows machine with GCC

## Collaborating

For making bug reports, feature requests and donations visit
one of the following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

