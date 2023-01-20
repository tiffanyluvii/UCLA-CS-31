// rabbits.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the utterly trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;


///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;               // max number of rows in the arena
const int MAXCOLS = 25;               // max number of columns in the arena
const int MAXRABBITS = 100;           // max number of rabbits allowed

const int NORTH = 0;
const int EAST = 1;
const int SOUTH = 2;
const int WEST = 3;
const int NUMDIRS = 4;

const int EMPTY = 0;
const int HAS_POISON = 1;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Rabbit declaration.

class Rabbit
{
public:
    // Constructor
    Rabbit(Arena* ap, int r, int c);

    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

    // Mutators
    void move();

private:
    Arena* m_arena;
    int m_row;
    int m_col;
    // TODO: You'll probably find that a rabbit object needs additional
    // data members to support your implementation of the behavior affected
    // by poisoned carrots.
    // DONE
    int m_poisoned;
    bool m_turn; //determines if it's the rabbit's turn to move
};

class Player
{
public:
    // Constructor
    Player(Arena* ap, int r, int c);

    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

    // Mutators
    string dropPoisonedCarrot();
    string move(int dir);
    void   setDead();

private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     rabbitCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfRabbitsAt(int r, int c) const;
    void    display(string msg) const;

    // Mutators
    void setCellStatus(int r, int c, int status);
    bool addRabbit(int r, int c);
    bool addPlayer(int r, int c);
    void moveRabbits();

private:
    int     m_grid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Rabbit* m_rabbits[MAXRABBITS];
    int     m_nRabbits;
    int     m_turns;

    // Helper functions
    void checkPos(int r, int c, string functionName) const;
    bool isPosInBounds(int r, int c) const;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

    // Mutators
    void play();

private:
    Arena* m_arena;

    // Helper functions
    string takePlayerTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int lowest, int highest);
bool decodeDirection(char ch, int& dir);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Rabbit implementation
///////////////////////////////////////////////////////////////////////////

Rabbit::Rabbit(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A rabbit must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "***** Rabbit created with invalid coordinates (" << r << ","
            << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_poisoned = 2;
    m_turn = true;
}

int Rabbit::row() const
{
    return m_row;
}

int Rabbit::col() const
{
    // TODO: TRIVIAL:  Return what column the Rabbit is at
    // DONE
    return m_col;
}

bool Rabbit::isDead() const
{
    // TODO: Return whether the Rabbit is dead
    //cerr << "entering Rabbit::isDead()" << endl;

    if (m_poisoned == 0) {
        return true;
    }
    else if (m_poisoned == 1) { //returns false if the rabbit has only been poisoned once
        return false;
    }
    return false; //returns false if the rabbit hasn't been poisoned
   
}

void Rabbit::move()
{
    // TODO:
    //   Return without moving if the rabbit has eaten one poisoned
    //   carrot (so is supposed to move only every other turn) and
    //   this is a turn it does not move.

    //cerr << "entering Rabbit::move()" << endl;

    if (m_poisoned == 1 && m_turn ) {  //could I do a mod thing that alternates turns? create another variable
        m_turn = false;
        return;
    }

    //   Otherwise, attempt to move in a random direction; if can't
    //   move, don't move.  If it lands on a poisoned carrot, eat the
    //   carrot and remove it from the game (so it is no longer on that
    //   grid point).
    int direction = randInt(0, NUMDIRS - 1);

    switch (direction){
    case NORTH:
        if (m_row == 1) {
            m_turn = true;
            return;
        }
        else if ((m_arena->getCellStatus(m_row-1, m_col)) == 1) {
            m_arena->setCellStatus(m_row-1, m_col, EMPTY);
            m_turn = true;
            m_row--;
            m_poisoned--;
            
        }
        else {
            m_turn = true;
            m_row--;
        }
        break;
    case EAST:
        if (m_col == m_arena->cols()) {
            m_turn = true;
            return;
        }
        else if ((m_arena->getCellStatus(m_row, m_col+1)) == 1) {
            m_arena->setCellStatus(m_row, m_col+1, EMPTY);
            m_turn = true;
            m_col++;
            m_poisoned--;
           
        }
        else {
            m_turn = true;
            m_col++;
        }
        break;
    case SOUTH:
        if (m_row == m_arena->rows()) {
            m_turn = true;
            return;
        }
        else if ((m_arena->getCellStatus(m_row+1, m_col)) == 1) {
            m_arena->setCellStatus(m_row+1, m_col, EMPTY);
            m_turn = true;
            m_row++;
            m_poisoned--;
        }
        else {
            m_turn = true;
            m_row++;
        }
        break;
    case WEST:
        if (m_col == 1) {
            m_turn = true;
            return;
        }
        else if ((m_arena->getCellStatus(m_row, m_col-1)) == 1) {
            m_arena->setCellStatus(m_row, m_col-1, EMPTY);
            m_turn = true;
            m_col--;
            m_poisoned--;
        }
        else {
            m_turn = true;
            m_col--;
        }
        break;
    }
    

}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
            << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
    // TODO: TRIVIAL:  Return what row the Player is at
    // DONE
    return m_row; 
}

int Player::col() const
{
    // TODO: TRIVIAL:  Return what column the Player is at
    // DONE
    return m_col;
}

string Player::dropPoisonedCarrot()
{
    if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
        return "There's already a poisoned carrot at this spot.";
    m_arena->setCellStatus(m_row, m_col, HAS_POISON);
    return "A poisoned carrot has been dropped.";
}

string Player::move(int dir)
{
    //cerr << "entering Player::move()" << endl;

    // TODO:  Attempt to move the player one step in the indicated
    //        direction.  If this fails,
    //        return "Player couldn't move; player stands."
    //        A player who moves onto a rabbit, and this
    //        returns "Player walked into a rabbit and died."
    //        Otherwise, return one of "Player moved north.",
    //        "Player moved east.", "Player moved south.", or
    //        "Player moved west."
    // DONE

    switch (dir) {
    case NORTH:
        if (m_row == 1) {
            return "Player couldn't move; player stands.";
        }
        else if (m_arena->numberOfRabbitsAt(m_row - 1, m_col)) {
            setDead();
            return "Player walked into a rabbit and died.";
        }
        else {
            m_row--;
            return "Player moved north.";
        }
        break;
    case EAST:
        if (m_col == m_arena->cols()) {
            return "Player couldn't move; player stands.";
        }
        else if (m_arena->numberOfRabbitsAt(m_row, m_col + 1)) {
            setDead();
            return "Player walked into a rabbit and died.";
        }
        else {
            m_col++;
            return "Player moved east.";
        }
        break;
    case SOUTH:
        if (m_row == m_arena->rows()) {
            return "Player couldn't move; player stands.";
        }
        else if (m_arena->numberOfRabbitsAt(m_row + 1, m_col)) {
            setDead();
            return "Player walked into a rabbit and died.";
         
        }
        else {
            m_row++;
            return "Player moved south";
        }
        break;
    case WEST:
        if (m_col == 1) {
            return "Player couldn't move; player stands.";
        }
        else if (m_arena->numberOfRabbitsAt(m_row, m_col - 1)) {
            setDead();
            return "Player walked into a rabbit and died.";
        }
        else {
            m_col--;
            return "Player moved west.";
        }
        break;
    }

    return "";
}

bool Player::isDead() const
{
    // TODO: Return whether the Player is dead
    // MAYBE
    //cerr << "entering Player::isDead()" << endl;
    return m_dead;
 
    
}

void Player::setDead()
{
    //cerr << "entering Player::setDead()" << endl;
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
            << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRabbits = 0;
    m_turns = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Arena::~Arena()
{
    // TODO:  Deallocate the player and all remaining dynamically allocated
    //        rabbits.
    // MAYBE
    //cerr << "entering Arena::~Arena()" << endl;
    delete m_player;
    for (int i = 0; i < m_nRabbits; i++) {
        delete m_rabbits[i];
    }

}

int Arena::rows() const
{
    // TODO: TRIVIAL:  Return the number of rows in the arena
    // DONE
    return m_rows;
}

int Arena::cols() const
{
    // TODO: TRIVIAL:  Return the number of columns in the arena
    // DONE
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::rabbitCount() const
{
    // TODO: TRIVIAL:  Return the number of rabbits in the arena
    // DONE
    //cerr << "entering Arena::rabbitCount()" << endl;
    return m_nRabbits; 
}

int Arena::getCellStatus(int r, int c) const
{
    checkPos(r, c, "Arena::getCellStatus");
    return m_grid[r - 1][c - 1];
}

int Arena::numberOfRabbitsAt(int r, int c) const
{
    // TODO:  Return the number of rabbits at row r, column c
    // DONE
   // cerr << "entering Arena::numberOfRabbitsAt()" << endl;
    int count = 0;
    for (int i = 0; i < m_nRabbits; i++) {
        if (m_rabbits[i]->row() == r && m_rabbits[i]->col() == c) {
            count++;
        }
    }
    return count;  
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;

    // Fill displayGrid with dots (empty) and stars (poisoned carrots)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r - 1][c - 1] = (getCellStatus(r, c) == EMPTY ? '.' : '*');

   // cerr << "entering Arena::display" << endl;
    // Indicate each rabbit's position
    // TODO:  If one rabbit is at some grid point, set the displayGrid char
    //        to 'R'.  If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.
    // DONE

    for (int r = 1; r <= rows(); r++) {
        for (int c = 1; c <= cols(); c++) {
            switch (numberOfRabbitsAt(r, c)) {
            case 0:
                break;
            case 1:
                displayGrid[r - 1][c - 1] = 'R';
                break;
            case 2:
                displayGrid[r - 1][c - 1] = '2';
                break;
            case 3:
                displayGrid[r - 1][c - 1] = '3';
                break;
            case 4:
                displayGrid[r - 1][c - 1] = '4';
                break;
            case 5:
                displayGrid[r - 1][c - 1] = '5';
                break;
            case 6:
                displayGrid[r - 1][c - 1] = '6';
                break;
            case 7:
                displayGrid[r - 1][c - 1] = '7';
                break;
            case 8:
                displayGrid[r - 1][c - 1] = '8';
                break;
            default:
                displayGrid[r - 1][c - 1] = '9';
                break;
            }
        }
    }


    // Indicate the player's position
    if (m_player != nullptr)
        displayGrid[m_player->row() - 1][m_player->col() - 1] = (m_player->isDead() ? 'X' : '@');

    // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r - 1][c - 1];
        cout << endl;
    }
    cout << endl;

    // Write message, rabbit, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << rabbitCount() << " rabbits remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
    cout << m_turns << " turns have been taken." << endl;
}

void Arena::setCellStatus(int r, int c, int status)
{
    checkPos(r, c, "Arena::setCellStatus");
    m_grid[r - 1][c - 1] = status;
}

bool Arena::addRabbit(int r, int c)
{
    if (!isPosInBounds(r, c))
        return false;

    // Don't add a rabbit on a spot with a poisoned carrot
    if (getCellStatus(r, c) != EMPTY)
        return false;

    // Don't add a rabbit on a spot with a player
    if (m_player != nullptr && m_player->row() == r && m_player->col() == c)
        return false;

    // If there are MAXRABBITSS existing rabbits, return false.  Otherwise,
    // dynamically allocate a new rabbit at coordinates (r,c).  Save the
    // pointer to newly allocated rabbit and return true.
    // TODO:  Implement this.
    // DONE
    //cerr << "entering Arena::addRabbit" << endl;
    if (rabbitCount() == MAXRABBITS) {
        return false;
    }
    else {
        m_rabbits[m_nRabbits] = new Rabbit(this, r,c);
        m_nRabbits++;

    }
    return true;

}

bool Arena::addPlayer(int r, int c)
{
    if (!isPosInBounds(r, c))
        return false;

    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

    // Don't add a player on a spot with a rabbit
    if (numberOfRabbitsAt(r, c) > 0)
        return false;

    m_player = new Player(this, r, c);
    return true;
}

void Arena::moveRabbits()
{
    // Move all rabbits
    // TODO:  Move each rabbit.  Mark the player as dead if necessary.s
    //        Deallocate any dead dynamically allocated rabbit.
    // DONE
    //cerr << "entering Arena::moveRabbits()" << endl;
    for (int i = 0; i < m_nRabbits; i++) {
        m_rabbits[i]->move();
        if (m_rabbits[i]->row() == m_player->row() && m_rabbits[i]->col() == m_player->col()) {
            m_player->setDead();
        }
        if (m_rabbits[i]->isDead()) {
            delete m_rabbits[i];
            m_rabbits[i] = nullptr;
            
            for (int j=i; j < m_nRabbits-1; j++) {
                m_rabbits[j] = m_rabbits[j + 1];
            }   
            
            m_nRabbits--;
        }
    }
    // Another turn has been taken
    m_turns++;
}

bool Arena::isPosInBounds(int r, int c) const
{
    return (r >= 1 && r <= m_rows && c >= 1 && c <= m_cols);
}

void Arena::checkPos(int r, int c, string functionName) const
{
    if (!isPosInBounds(r, c))
    {
        cout << "***** " << "Invalid arena position (" << r << ","
            << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nRabbits)
{
    if (nRabbits < 0)
    {
        cout << "***** Cannot create Game with negative number of rabbits!" << endl;
        exit(1);
    }
    if (nRabbits > MAXRABBITS)
    {
        cout << "***** Trying to create Game with " << nRabbits
            << " rabbits; only " << MAXRABBITS << " are allowed!" << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nRabbits - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
            << cols << " arena, which is too small too hold a player and "
            << nRabbits << " rabbits!" << endl;
        exit(1);
    }

    // Create arena
    m_arena = new Arena(rows, cols);

    // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_arena->addPlayer(rPlayer, cPlayer);

    // Populate with rabbits
    while (nRabbits > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer && c == cPlayer)
            continue;
        m_arena->addRabbit(r, c);
        nRabbits--;
    }
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/c or nothing): ";
        string playerMove;
        getline(cin, playerMove);

        Player* player = m_arena->player();
        int dir;

        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->dropPoisonedCarrot();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'c')
                return player->dropPoisonedCarrot();
            else if (decodeDirection(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/c." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    Player* player = m_arena->player();
    if (player == nullptr)
        return;
    while (!player->isDead() && m_arena->rabbitCount() > 0)
    {
        string msg = takePlayerTurn();
        m_arena->display(msg);
        if (player->isDead())
            break;
        m_arena->moveRabbits();
        m_arena->display(msg);
    }
    if (player->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

  // Return a uniformly distributed random int from lowest to highest, inclusive
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(lowest, highest);
    return distro(generator);
}

bool decodeDirection(char ch, int& dir)
{
    switch (tolower(ch))
    {
    default:  return false;
    case 'n': dir = NORTH; break;
    case 'e': dir = EAST;  break;
    case 's': dir = SOUTH; break;
    case 'w': dir = WEST;  break;
    }
    return true;
}

// Return false without changing anything if moving one step from (r,c)
// in the indicated direction would run off the edge of the arena.
// Otherwise, update r and c to the position resulting from the move and
// return true.
bool attemptMove(const Arena& a, int dir, int& r, int& c)
{
   // cerr << "entering attemptMove" << endl;
    switch (dir) {
    case NORTH:
        if (r == 1) {
            return false;
        }
        else {
            r--;
            return true;
        }
        break;
    case EAST:
        if (c == a.cols()) { //why doesn't m_arena work //how to access arena's columns
            return false;
        }
        else {
            c++;
            return true;
        }
        break;
    case SOUTH:
        if (r == a.rows()) { //how to access arena's rows
            return false;
        }
        else {
            r++;
            return true;
        }
        break;
    case WEST:
        if (c == 1) {
            return false;
        }
        else {
            c--;
            return true;
        }
        break;

    }
    return false;
}

//Create a function that finds the least amount of rabbits
int leastRabbits(const Arena& a, int r, int c) {
    int checkNorth;
    int checkSouth;
    int checkEast;
    int checkWest;

    checkNorth = (a.numberOfRabbitsAt(r - 2, c) + a.numberOfRabbitsAt(r - 1, c - 1) + a.numberOfRabbitsAt(r - 1, c + 1));
    checkSouth = (a.numberOfRabbitsAt(r + 2, c) + a.numberOfRabbitsAt(r + 1, c - 1) + a.numberOfRabbitsAt(r + 1, c + 1));
    checkEast = (a.numberOfRabbitsAt(r, c+2) + a.numberOfRabbitsAt(r - 1, c + 1) + a.numberOfRabbitsAt(r + 1, c + 1));
    checkWest= (a.numberOfRabbitsAt(r, c - 2) + a.numberOfRabbitsAt(r - 1, c - 1) + a.numberOfRabbitsAt(r + 1, c - 1));

    if (r!= 1 && checkNorth <= checkSouth && checkNorth <= checkEast && checkNorth <= checkWest) {
        return NORTH; 
    }
    else if (r!=a.rows() && checkSouth <= checkNorth && checkSouth <= checkEast && checkSouth <= checkWest) {
        return SOUTH;
    }
    else if (c!= a.cols() && checkEast <= checkNorth && checkEast <= checkSouth && checkEast <= checkWest) {
        return EAST;
    }
    else if (c!= 1 &&checkWest <= checkNorth && checkWest <= checkSouth && checkWest <= checkEast) {
        return WEST;
    }
    else {
        return -1;
    }
    
}

// Recommend a move for a player at (r,c):  A false return means the
// recommendation is that the player should drop a poisoned carrot and
// not move; otherwise, this function sets bestDir to the recommended
// direction to move and returns true.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    // TODO:  Implement this function
    // Delete the following line and replace it with your code.
    //return false;  // This implementation compiles, but is incorrect.
    //implement limitations

    //Checks if there's no rabbits surrounding it
    if (a.numberOfRabbitsAt(r - 1, c) == 0 && a.numberOfRabbitsAt(r + 1, c) == 0 && a.numberOfRabbitsAt(r, c + 1) == 0 && a.numberOfRabbitsAt(r, c - 1) == 0) {
        return false;
    }
 

    //Checks if there's a rabbit directly above and besides it
    if (a.numberOfRabbitsAt(r - 1, c) >= 1) { //if there is a rabbit north of the player
        if (r != a.rows() && leastRabbits(a, r, c) == SOUTH && a.numberOfRabbitsAt(r + 1, c) == 0) { //checks if there is a rabbit south
            bestDir = SOUTH;
            r++;
            return true;
        }
        else if (c != a.cols() && leastRabbits(a, r, c) == EAST && a.numberOfRabbitsAt(r, c + 1) == 0 ) { //checks if there is a rabbit east
            bestDir = EAST;
            c++;
            return true;
        }
        else if (c != 1 && leastRabbits(a, r, c) == WEST && a.numberOfRabbitsAt(r, c - 1) == 0 ) { //checks if there is a rabbit west
            bestDir = WEST;
            c--;
            return true;
        }
    }
    else if (a.numberOfRabbitsAt(r + 1, c) >= 1) { //if there is a rabbit south of the player
        if (r != 1 && leastRabbits(a, r, c) == NORTH && a.numberOfRabbitsAt(r - 1, c) == 0 ) { //checks if there is a rabbit north
            bestDir = NORTH;
            r--;
            return true;
        }
        else if (c != a.cols() && leastRabbits(a, r, c) == EAST && a.numberOfRabbitsAt(r, c + 1) == 0) { //checks if there is a rabbit east
            bestDir = EAST;
            c++;
            return true;
        }
        else if (c != 1 && leastRabbits(a, r, c) == WEST && a.numberOfRabbitsAt(r, c - 1) == 0 ) { //checks if there is a rabbit west
            bestDir = WEST;
            c--;
            return true;
        }
    }
    else if (a.numberOfRabbitsAt(r, c + 1) >= 1) { //if there is a rabbit east of the player
        if (r != 1 && leastRabbits(a, r, c) == NORTH && a.numberOfRabbitsAt(r - 1, c) == 0 ) { //checks if there is a rabbit north
            bestDir = NORTH;
            r--;
            return true;
        }
        else if (r != a.rows() && leastRabbits(a, r, c) == SOUTH && a.numberOfRabbitsAt(r + 1, c) == 0 ) { //checks if there is a rabbit south
            bestDir = SOUTH;
            r++;
            return true;
        }
        else if (c != 1 && leastRabbits(a, r, c) == WEST && a.numberOfRabbitsAt(r, c - 1) == 0) { //checks if there is a rabbit west
            bestDir = WEST;
            c--;
            return true;
        }
    }
    else if (a.numberOfRabbitsAt(r, c - 1) >= 1) { //if there is a rabbit west of the player
        if (r != 1 && leastRabbits(a, r, c) == NORTH && a.numberOfRabbitsAt(r - 1, c) == 0 ) { //checks if there is a rabbit north
            bestDir = NORTH;
            r--;
            return true;
        }
        else if (r != a.rows() && leastRabbits(a, r, c) == SOUTH && a.numberOfRabbitsAt(r + 1, c) == 0 ) { //checks if there is a rabbit south
            bestDir = SOUTH;
            r++;
            return true;
        }
        else if (r != a.cols() && leastRabbits(a, r, c) == EAST && a.numberOfRabbitsAt(r, c + 1) == 0 ) { //checks if there is a rabbit east
            bestDir = EAST;
            c++;
            return true;
        }
    }


    //Checks if there's a rabbit directly above
    if (a.numberOfRabbitsAt(r - 1, c) >= 1) { //if there is a rabbit north of the player
        if (r!= a.rows() && a.numberOfRabbitsAt(r + 1, c) == 0 ) { //checks if there is a rabbit south
            bestDir = SOUTH;
            r++;
            return true;
        }
        else if (c!= a.cols()  && a.numberOfRabbitsAt(r, c + 1) == 0 ) { //checks if there is a rabbit east
            bestDir = EAST;
            c++;
            return true;
        }
        else if (c!= 1 && a.numberOfRabbitsAt(r, c - 1) == 0 ) { //checks if there is a rabbit west
            bestDir = WEST;
            c--;
            return true;
        }
    }
    else if (a.numberOfRabbitsAt(r + 1, c) >= 1) { //if there is a rabbit south of the player
        if (r!=1 &&a.numberOfRabbitsAt(r - 1, c) == 0) { //checks if there is a rabbit north
            bestDir = NORTH;
            r--;
            return true;
        }
        else if (c!= a.cols() && a.numberOfRabbitsAt(r, c + 1) == 0) { //checks if there is a rabbit east
            bestDir = EAST;
            c++;
            return true;
        }
        else if (c!= 1 && a.numberOfRabbitsAt(r, c - 1) == 0 ) { //checks if there is a rabbit west
            bestDir = WEST;
            c--;
            return true;
        }
    }
    else if (a.numberOfRabbitsAt(r, c + 1) >= 1) { //if there is a rabbit east of the player
        if (r!= 1&&a.numberOfRabbitsAt(r - 1, c) == 0  ) { //checks if there is a rabbit north
            bestDir = NORTH;
            r--;
            return true;
        }
        else if (r!= a.rows() && a.numberOfRabbitsAt(r + 1, c) == 0 ) { //checks if there is a rabbit south
            bestDir = SOUTH;
            r++;
            return true;
        }
        else if (c!=1 &&a.numberOfRabbitsAt(r, c - 1) == 0  ) { //checks if there is a rabbit west
            bestDir = WEST;
            c--;
            return true;
        }
    }
    else if ( a.numberOfRabbitsAt(r, c - 1) >= 1) { //if there is a rabbit west of the player
        if (r!= 1&& a.numberOfRabbitsAt(r - 1, c) == 0 ) { //checks if there is a rabbit north
            bestDir = NORTH;
            r--;
            return true;
        }
        else if (r!= a.rows() && a.numberOfRabbitsAt(r + 1, c) == 0 ) { //checks if there is a rabbit south
            bestDir = SOUTH;
            r++;
            return true;
        }
        else if (r!=a.cols() && a.numberOfRabbitsAt(r, c + 1) == 0 ) { //checks if there is a rabbit east
            bestDir = EAST;
            c++;
            return true;
        }
    }
    

    if (a.numberOfRabbitsAt(r - 1, c) >= 1 && a.numberOfRabbitsAt(r + 1, c) >= 1 && a.numberOfRabbitsAt(r, c + 1) >= 1 && a.numberOfRabbitsAt(r, c - 1) >= 1) {
        return false;
    }
    else if (a.numberOfRabbitsAt(r - 1, c + 1) >= 1 && a.numberOfRabbitsAt(r - 1, c - 1) >= 1 && a.numberOfRabbitsAt(r + 1, c + 1) >= 1 && a.numberOfRabbitsAt(r + 1, c - 1) >= 1) {
        return false;
    }




    //Check which path to go when there are rabbits surrounding it
    if (r!=1 && leastRabbits(a, r, c) == NORTH && a.numberOfRabbitsAt(r - 1, c) == 0) {
        bestDir = NORTH;
        r--;
        return true;
    }
    else if (r!= a.rows() && leastRabbits(a, r, c) == SOUTH && a.numberOfRabbitsAt(r + 1, c) == 0) {
        bestDir = SOUTH;
        r++;
        return true;
    }
    else if (c!= a.cols() && leastRabbits(a, r, c) == EAST && a.numberOfRabbitsAt(r, c + 1) == 0) {
        bestDir = EAST;
        c++;
        return true;
    }
    else if (c!= 1 &&leastRabbits(a, r, c) == WEST && a.numberOfRabbitsAt(r, c-1) == 0) {
        bestDir = WEST;
        c--;
        return true;
    }
    else if (leastRabbits(a, r, c) == -1) {
        return false;
    }


    return false;

/////

        // Your replacement implementation should do something intelligent.
        // You don't have to be any smarter than the following, although
        // you can if you want to be:  If staying put runs the risk of a
        // rabbit possibly moving onto the player's location when the rabbits
        // move, yet moving in a particular direction puts the player in a
        // position that is safe when the rabbits move, then the chosen
        // action is to move to a safer location.  Similarly, if staying put
        // is safe, but moving in certain directions puts the player in
        // danger of dying when the rabbits move, then the chosen action should
        // not be to move in one of the dangerous directions; instead, the player
        // should stay put or move to another safe position.  In general, a
        // position that may be moved to by many rabbits is more dangerous than
        // one that may be moved to by few.
        //
        // Unless you want to, you do not have to take into account that a
        // rabbit might be poisoned and thus sometimes less dangerous than one
        // that is not.  That requires a more sophisticated analysis that
        // we're not asking you to do.
    }


///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////


int main()
{
  
   
    // Create a game
    // Use this instead to create a mini-game:   
   //Game g(3, 5, 2);
   Game g(10, 15, 40);

    // Play the game
    g.play();



}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not _WIN32

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr || strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif