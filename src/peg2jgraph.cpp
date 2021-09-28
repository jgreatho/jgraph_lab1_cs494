#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;


int read_board(const int dim, string temp, vector<string> &board) {
  int i, j;
  stringstream ss;

  
  // Read initial line
  ss.str(temp);
  ss >> temp;
  board[0] = temp;
  // For each remaining line of the board
  for(i = 1; i < dim; i++) {
    board[i] = "";
    // Read in line
    if(!getline(cin,temp)) return -1;
    ss.str(temp);
    for(j = 0; j < i+1; j++) {
      ss >> temp;
      board[i] = board[i] + temp;
    }

  }

  return 0;
}


//// Lots of Strings for jgraph ////
char ng[] = "newgraph\n";
char xa[] = "xaxis min 0 max 9 no_draw_axis\nno_grid_lines no_draw_hash_marks no_auto_hash_labels\n";
char ya[] = "yaxis min 0 max 9 no_draw_axis\nno_grid_lines no_draw_hash_marks no_auto_hash_labels\n";
char bd[] = "newline pts 0 0.5  4.5 9  9 0.5  0 0.5\n";
char curves[][50] = {"newcurve marktype circle marksize 1 1 pts 4.5 7.5",

"copycurve pts 3.5 5.5",
"copycurve pts 5.5 5.5",

"copycurve pts 2.5 3.5",
"copycurve pts 4.5 3.5",
"copycurve pts 6.5 3.5",

"copycurve pts 1.5 1.5",
"copycurve pts 3.5 1.5",
"copycurve pts 5.5 1.5",
"copycurve pts 7.5 1.5"};



char cf[] = " cfill 1 1 0";
char ce[] = " cfill 1 1 1";

char nums[] = "newstring hjc vjc x 4.5 y 7.5 fontsize 20 font Times-Roman : 0\n\
newstring hjc vjc x 3.5 y 5.5 fontsize 20 font Times-Roman : 1\n\
newstring hjc vjc x 5.5 y 5.5 fontsize 20 font Times-Roman : 2\n\
newstring hjc vjc x 2.5 y 3.5 fontsize 20 font Times-Roman : 3\n\
newstring hjc vjc x 4.5 y 3.5 fontsize 20 font Times-Roman : 4\n\
newstring hjc vjc x 6.5 y 3.5 fontsize 20 font Times-Roman : 5\n\
newstring hjc vjc x 1.5 y 1.5 fontsize 20 font Times-Roman : 6\n\
newstring hjc vjc x 3.5 y 1.5 fontsize 20 font Times-Roman : 7\n\
newstring hjc vjc x 5.5 y 1.5 fontsize 20 font Times-Roman : 8\n\
newstring hjc vjc x 7.5 y 1.5 fontsize 20 font Times-Roman : 9\n";


//// Print jgraph format ////
int print_board(const int dim, vector<string> &board, fstream &jgr) {
  int i, j, index;

  jgr << ng << xa << ya << bd;
  index = 0;
  for(i = 0; i < dim; i++) {
    for(j = 0; j < i+1; j++) {
      jgr << curves[index];
      index++;
      if(board[i][j] == 'X') jgr << ce;
      else                   jgr << cf;
      jgr << endl;
    }
  }
  jgr << nums;
  return 1;
}

int main(int argc, char **argv) {
  int dim;
  string temp;
  stringstream ss;
  vector<string> board;
  fstream jgr;

  if(argc != 2) {
    cerr << "Program requires input file.\n";
    return 1;
  }

  // Get board dimensions
  getline(cin, temp);
  ss.str(temp);
  ss >> temp;
  ss >> dim;



  board.resize(dim);
  // Loop until game ends
  while(getline(cin, temp) ) {
    // Open file
    jgr.open(argv[1]);
    if(jgr.fail()) {
      cerr << "Could not open file.\n";
      return 1;
    }
    // Read and print board to file
    read_board(dim, temp, board);
    print_board(dim, board, jgr);
    // Close file
    jgr.close();
  }

  return 0;
}
