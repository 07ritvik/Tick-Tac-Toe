#include <bits/stdc++.h>
using namespace std;

enum PieceType
{
    X,
    O,
    EMPTY,
};

class PlayingPiece
{
    PieceType type;

public:
    PlayingPiece() : type(PieceType::EMPTY) {}
    PlayingPiece(PieceType type)
    {
        this->type = type;
    }

    PieceType getType()
    {
        return this->type;
    }
};

class PlayingPieceX : public PlayingPiece
{
public:
    PlayingPieceX() : PlayingPiece(PieceType::X) {}
};

class PlayingPieceO : public PlayingPiece
{
public:
    PlayingPieceO() : PlayingPiece(PieceType::O) {}
};

class Board
{
    int size;
    vector<vector<PlayingPiece>> board;

public:
    Board(int size) : size(size), board(vector<vector<PlayingPiece>>(size, vector<PlayingPiece>(size))) {};
    void printBoard()
    {
        for (int i = 0; i < size; i++)
        {
            if (i > 0 && i < size)
                cout << "___  ___  ___" << endl;
            cout << endl;
            for (int j = 0; j < size; j++)
            {
                if (board[i][j].getType() == PieceType::EMPTY)
                {
                    cout << "   ";
                }
                else if (board[i][j].getType() == PieceType::X)
                {
                    cout << " X ";
                }
                else
                {
                    cout << " O ";
                }
                if (j < size - 1)
                    cout << " |";
            }
            cout << endl;
        }
    }

    bool addPiece(int x, int y, PlayingPiece piece)
    {
        if (board[x][y].getType() != PieceType::EMPTY)
        {
            return false;
        }
        board[x][y] = piece;
        return true;
    }

    int getSize()
    {
        return size;
    }

    vector<vector<PlayingPiece>> getBoard()
    {
        return board;
    }

    bool isFull(){
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                if(board[i][j].getType()==PieceType::EMPTY){
                    return false;
                }
            }
        }
        return true;
    }
};

class Player
{
    string name;
    PlayingPiece piece;

public:
    Player(string name, PlayingPiece piece) : name(name), piece(piece) {}

    string getName()
    {
        return name;
    }

    PlayingPiece getPiece()
    {
        return piece;
    }
};

class TicTacToe
{
    Board gamingBoard;
    vector<Player> players;

public:
    TicTacToe(Board gamingBoard, vector<Player> players) : gamingBoard(gamingBoard), players(players) {};

    void addPlayer(Player player)
    {
        players.push_back(player);
    }

    bool getWinner(int n, int m, PlayingPiece piece)
    {
        bool rowMatch = true;
        bool colMatch = true;
        bool diagMatch = true;
        bool antiDiagMatch = true;
        vector<vector<PlayingPiece>> board = gamingBoard.getBoard();
        int size = gamingBoard.getSize();
        for (int i = 0; i < size; i++)
        {
            if ((board[n][i].getType() == PieceType::EMPTY) || (board[n][i].getType() != piece.getType()))
            {
                rowMatch = false;
            }
        }

        for (int j = 0; j < size; j++)
        {
            if ((board[j][m].getType() == PieceType::EMPTY) || (board[j][m].getType() != piece.getType()))
            {
                colMatch = false;
            }
        }

        for (int k = 0; k < size; k++)
        {
            if ((board[k][k].getType() == PieceType::EMPTY) || (board[k][k].getType() != piece.getType()))
            {
                diagMatch = false;
            }
        }

        for (int l = size - 1; l >= 0; l--)
        {
            if ((board[l][size - l - 1].getType() == PieceType::EMPTY) || (board[l][size - l - 1].getType() != piece.getType()))
            {
                antiDiagMatch = false;
            }
        }
        return rowMatch || colMatch || diagMatch || antiDiagMatch;
    }

    void play()
    {
        bool noWinner = true;
        gamingBoard.printBoard();
        while (noWinner)
        {
            Player currPlayer = players.front();
            players.erase(players.begin());

            int n, m;
            cout << "Player " << currPlayer.getName() << " turn" << endl;
            cout << "Enter x and y coordinates: ";
            cin >> n >> m;
            if (gamingBoard.addPiece(n, m, currPlayer.getPiece()))
            {
                gamingBoard.printBoard();
                players.push_back(currPlayer);
            }
            else
            {
                cout << "Incorrect move, please try again" << endl;
                players.insert(players.begin(), currPlayer);
            }

            if (getWinner(n, m, currPlayer.getPiece()))
            {
                noWinner = false;
                cout << "Player " << currPlayer.getName() << " won" << endl;
            }
            else if(gamingBoard.isFull()){
                noWinner = false;
                cout << "Draw" << endl;
            }
        }
        
    }
};

int main()
{
    Board gamingBoard = Board(3);
    cout << "Welcome to TicTacToe" << endl;
    string player1Name, player2Name;

    cout << "Enter Player 1 name: ";
    cin >> player1Name;

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << endl;
    Player player1 = Player(player1Name, PlayingPieceX());
    Player player2 = Player(player2Name, PlayingPieceO());
    vector<Player> players;
    ;
    players.push_back(player1);
    players.push_back(player2);
    TicTacToe game = TicTacToe(gamingBoard, players);
    game.play();

    return 0;
}