#!/bin/sh

echo "Go to http://web.eecs.utk.edu/~[your-net-id]/pegsol.pdf to view the current board state.\n"
touch ~/webhome/pegsol.pdf
chmod a+r ~/webhome/pegsol.pdf
./bin/pegsol | ./bin/peg2jgraph -I | ./jgraph/jgraph -P | ps2pdf - > ~/webhome/pegsol.pdf
