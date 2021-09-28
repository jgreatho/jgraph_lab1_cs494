#!/bin/sh
if [ $# -ne 1 ]; then
  echo 'usage: initally-empty-slot(0-9)' >&2
  exit 1
fi

echo "Go to http://web.eecs.utk.edu/~[your-net-id]/pegsol.pdf to view the current board state."
echo
touch ~/webhome/pegsol.pdf
touch temp.board
chmod a+r ~/webhome/pegsol.pdf

./bin/pegsol $1 10 1 | ./bin/peg2jgraph temp.board & 

while true; do
  ./jgraph/jgraph -P < temp.board | ps2pdf - > ~/webhome/pegsol.pdf
  sleep 1
done
