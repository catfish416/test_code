#!/bin/bash
find linux-4.5.4 -type f ( -iname '.c' -o -iname '.h' -o -iname '*.S' ) -print0 | wc -l --files0-from- | tail -n 1
