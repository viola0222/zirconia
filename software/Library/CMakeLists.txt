cmake_minimum_required(VERSION 3.10)

add_library(Library STATIC
    ntshell-v0.3.1/lib/core/ntlibc.c
    ntshell-v0.3.1/lib/core/ntshell.c
    ntshell-v0.3.1/lib/core/text_editor.c
    ntshell-v0.3.1/lib/core/text_history.c
    ntshell-v0.3.1/lib/core/vtrecv.c
    ntshell-v0.3.1/lib/core/vtsend.c
    ntshell-v0.3.1/lib/util/ntopt.c
    ntshell-v0.3.1/lib/util/ntstdio.c
)
