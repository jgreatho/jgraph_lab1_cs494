/* UTK CS494 Lab 1: Game Portion
 * John Wally Greathouse
 * Due: 02:00 EST, September 28th, 2021
 * http://web.eecs.utk.edu/~jplank/plank/classes/cs494/Labs/Lab-1-Jgraph/index.html
 */
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
using namespace std;

/* --- Pegboard Solitaire Class --- */
class jwg_pegboard {
public:
  jwg_pegboard();
  jwg_pegboard(const int empty, const int slots, const bool dup);

  bool try_move(const int start, const int end);
  bool print(const int offset);
  bool game_over();

private:
  int numslots;           // Number of peg slots
  int numpegs;            // Number of pegs remaining
  int nummoves;           // Number of moves taken
  bool gameover;          // Status of game

  bool dupout;            // Duplicates output for piping board

  map<int,string> coords; // (x,y) coordinates of pegs
  vector<string>  board;  // Weights of the edges

  // Returns whether curr can reach goal
  bool check_move(const int curr, const int prev, const int goal);

  // Populate board with defined empty slot
  void fill_board(const int empty);

  // Returns whether a slot has a peg in it
  bool check_full(const int i);
  bool check_empty(const int i);

  // Returns x or y coordiante of peg at index i
  int get_x(const int index); 
  int get_y(const int index);

};


/* --- Class Function Definitions --- */
//// Board filling helper function ////
void jwg_pegboard::fill_board(const int empty) {
  int vector_size, i, j, currpeg;
  string index;

  // Resize board
  i = 0;
  vector_size = 0;
  while(i < numpegs) {
    vector_size++; //cout << vector_size << endl;
    i += vector_size;
  }
  board.resize(vector_size);

  // Populate board
  currpeg = 0;
  index = "0,0";
  for(i = 0; i < (int)board.size(); i++) { // Iterate rows
    board[i] = "";
    for(j = 0; j < i+1; j++) { // Iterate columns

      // Convert index values to string
      index[0] = '0' + i;
      index[2] = '0' + j;   //cout <<"Peg " << currpeg << " has index: " << index << endl;

      // Assign value to string board
      if(empty == currpeg) board[i] = board[i] + 'X';
      else                 board[i] = board[i] + 'O';

      // Store value coordinates in map
      coords.insert(make_pair(currpeg,index) );
      currpeg++;
    }
  }
  // For file output
  cout << "jwg_pegboard_dimensions: " << vector_size << endl;
  if(dupout) cerr << "jwg_pegboard_dimensions: " << vector_size << endl;
}


//// Default Constructor ////
jwg_pegboard::jwg_pegboard() {
  numslots = 10;
  numpegs  = numslots-1;
  nummoves = 0;
  gameover = 0;
  dupout   = 0;

  fill_board(0);
}


//// Custom Constructor ////
jwg_pegboard::jwg_pegboard(const int empty, const int slots, const bool dup) {
  numslots = slots;
  numpegs  = numslots-1;
  nummoves = 0;
  gameover = 0;
  dupout   = dup;


  fill_board(empty);
}


//// Get x coordinate from slot index////
int jwg_pegboard::get_x(const int i) {
  map<int,string>::iterator it;

  it = coords.find(i);
  if(it == coords.end() || !it->second.empty() ) return (int)(it->second[0] - '0');
  else return -1;
}


//// Get y coordinate from slot index////
int jwg_pegboard::get_y(const int i) {
  map<int,string>::iterator it;

  it = coords.find(i);
  if(it == coords.end() || !it->second.empty() ) return (int)(it->second[2] - '0');
  else return -1;
}


//// Check if a slot is full ////
bool jwg_pegboard::check_full(const int i) {
  int x, y;

  x = get_x(i);
  y = get_x(i);
  if('X' ==  board[x][y] ) return 1;
  return 0;
}


//// Check if a slot is empty ////
bool jwg_pegboard::check_empty(const int i) {
  return !check_full(i);
}


//// Tests all possible ways to get from curr to goal recursively ////
bool jwg_pegboard::check_move(const int curr, const int prev, const int goal) {
  (void) curr;
  (void) prev;
  (void) goal;
  return 0;
}

//// Wrapper for class usage ////
bool jwg_pegboard::try_move(const int start, const int end) {
  return check_move(start,-1,end);
}


bool jwg_pegboard::game_over() {
  return (bool)gameover;
}


bool jwg_pegboard::print(const int offset) {
  int i, j, k;
  int padsize, lastrowsize;
  
  lastrowsize = board[board.size()-1].size();
  
  // Iterate rows for cout
  for(i = 0; i < (int)board.size(); i++) {
    padsize = lastrowsize - board[i].size();

    // Print padded row
    if(!dupout) for(k = 0; k < offset; k++)    cout << " "; 
    for(k = 0; k < padsize; k++)   cout << " ";
    for(j = 0; j < i+1; j++)       cout << board[i][j] << " ";
    for(k = 0; k < padsize-1; k++) cout << " ";

    cout << endl; 

  }
  if(!dupout) return 1;

  // Iterate rows for cerr
  for(i = 0; i < (int)board.size(); i++) {
    padsize = lastrowsize - board[i].size();

    // Print padded row
    for(k = 0; k < offset; k++)    cerr << " "; 
    for(k = 0; k < padsize; k++)   cerr << " ";
    for(j = 0; j < i+1; j++)       cerr << board[i][j] << " ";
    for(k = 0; k < padsize-1; k++) cerr << " ";

    cerr << endl; 

  }
  return 1;
}


/* --- Main Game --- */
char usag[] =  "   usage:  pegsol  [starting empty slot index]  [total slots]  [dup board to error]\n";
char usag2[] = "defaults:  ------  ----- 0 (zero-indexed) ----  ----- 10 ----  ------ 0 (bool) ----\n";


int main(int argc, char **argv) {
  stringstream ss;
  string temp;
  bool dup;
  int empty, total;

  jwg_pegboard *game;
  int start, end;
  int board_offset, totalbadmoves;

  // Usage
  if(  argc > 4 || argc < 1 || 
  (argc==2 && strcmp("--help",argv[1])==0)  ) {
    cerr << usag << usag2;
    return 1;
  }

  // Populate class
  if(argc >= 2) {
    ss << argv[1];
    ss >> empty;
    
    if(ss.fail()) empty = 0;
    ss.clear();
    total = 10;
    dup   =  0;
  } 
  if(argc >= 3) {
    ss << argv[2];
    ss >> total;
    if(ss.fail()) total = 10;
    ss.clear();
  }
  if(argc == 4) {
    ss << argv[3];
    ss >> dup;
    if(ss.fail()) dup = 0;
    ss.clear();
  }
  if(argc == 1) game = new jwg_pegboard();
  else          game = new jwg_pegboard(empty, total, dup);

  // Print board and request first move
  board_offset = 7;
  game->print(board_offset);
  cerr << "Select a move: (type two numbers)\n";
  cerr << "             [start slot] [end slot]\n";

  // Iterate until game ends or EOF reached
  //cin.clear();
  totalbadmoves = 1;
  while(getline(cin,temp) && !(game->game_over()) && totalbadmoves <= 35) {
    // Read and check user input
    ss.clear(); //cout << temp << endl;
    ss.str(temp);
    ss >> start; //cout << start << endl;
    if(ss.fail() || (start<0 || start>total-1)) {
      cerr << "Bad move: \"" << temp << "\"\n";
      totalbadmoves++;
      continue;
    }
    ss >> end; //cout << end << endl;
    if(ss.fail() || (end<0 || end>total-1)) {
      cerr << "Bad move: \"" << temp << "\"\n";
      totalbadmoves++;
      continue;
    }

    // Try given move
    game->try_move(start, end);

    // Request next move
    if(game->game_over()) continue;
    game->print(board_offset);
    cerr << "\nSelect a move: (type two numbers)\n";
    cerr << "             [start slot] [end slot]\n";
    temp.clear();
  }

  delete game;
  return 0;
}
