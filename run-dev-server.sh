#!/bin/bash

watchexec --no-vcs-ignore -w server/src/.running/built_at.txt -r -c -- "_build/default/server/src/server.exe"
