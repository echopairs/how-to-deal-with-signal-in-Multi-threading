#!/usr/bin/env bash

set -e
script=$(readlink -f "$0")
route=$(dirname "$script")

sh "$route"/build_without_lib_update.sh
cd "$route"/../build
./signal_example &

kill -60 `pgrep signal_example`
sleep 10
kill -61 `pgrep signal_example`
kill -9  `pgrep signal_example`

pprof --pdf signal_example /tmp/signal.profile >> signal.pdf
