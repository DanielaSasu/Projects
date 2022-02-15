using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Tema2MVP.Models;

namespace Tema2MVP.Services
{
    class GameBusinessLogic
    {
        private int numberOfClicks = 0;
        private Cell previousCell;
        private string turn;

        private ObservableCollection<ObservableCollection<Cell>> cells;
        public GameBusinessLogic(ObservableCollection<ObservableCollection<Cell>> cells)
        {
            this.cells = cells;
            this.turn = "firstPlayer";
            turnChange();
        }

        public void simpleMoveSwap(Cell currentCell, Cell previousCell)
        {
            Cell temp = new Cell();
            temp.CellImage = currentCell.CellImage;
            temp.PieceType = currentCell.PieceType;
            cells[currentCell.X][currentCell.Y].CellImage = previousCell.CellImage;
            cells[currentCell.X][currentCell.Y].PieceType = previousCell.PieceType;
            cells[previousCell.X][previousCell.Y].CellImage = temp.CellImage;
            cells[previousCell.X][previousCell.Y].PieceType = temp.PieceType;
        }

        public bool simpleMove(Cell currentCell, Cell previousCell)
        {
            if (currentCell.PieceType != "emptyBlack")
                return false;

            if (previousCell.PieceType == "playerPink")
            {
                if (currentCell.X + 1 != previousCell.X)
                {
                    return false;
                }
                if (currentCell.Y - 1 != previousCell.Y && currentCell.Y + 1 != previousCell.Y)
                {
                    return false;
                }
            }

            if (previousCell.PieceType == "playerWhite")
            {
                if (currentCell.X - 1 != previousCell.X)
                {
                    return false;
                }
                if (currentCell.Y - 1 != previousCell.Y && currentCell.Y + 1 != previousCell.Y)
                {
                    return false;
                }
            }

            if (previousCell.PieceType == "player1King" || previousCell.PieceType == "player2King")
            {
                if (currentCell.X + 1 != previousCell.X && currentCell.X - 1 != previousCell.X)
                {
                    return false;
                }
                if (currentCell.Y - 1 != previousCell.Y && currentCell.Y + 1 != previousCell.Y)
                {
                    return false;
                }
            }

            return true;
        }

        public bool simpleAttackMove(Cell currentCell, Cell previousCell)
        {
            if (currentCell.PieceType != "emptyBlack")
                return false;

            if (previousCell.PieceType == "playerPink")
            {
                if (currentCell.X + 2 != previousCell.X)
                {
                    return false;
                }
                if (currentCell.Y - 2 == previousCell.Y && (cells[previousCell.X - 1][previousCell.Y + 1].PieceType == "playerWhite" || cells[previousCell.X - 1][previousCell.Y + 1].PieceType == "player2King"))
                {
                    cells[previousCell.X - 1][previousCell.Y + 1].PieceType = "emptyBlack";
                    cells[previousCell.X - 1][previousCell.Y + 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    return true;
                }

                if (currentCell.Y + 2 == previousCell.Y && (cells[previousCell.X - 1][previousCell.Y - 1].PieceType == "playerWhite" || cells[previousCell.X - 1][previousCell.Y - 1].PieceType == "player2King"))
                {
                    cells[previousCell.X - 1][previousCell.Y - 1].PieceType = "emptyBlack";
                    cells[previousCell.X - 1][previousCell.Y - 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    return true;
                }
            }
            if (previousCell.PieceType == "playerWhite")
            {
                if (currentCell.X - 2 != previousCell.X)
                {
                    return false;
                }
                if (currentCell.Y + 2 == previousCell.Y && (cells[previousCell.X + 1][previousCell.Y - 1].PieceType == "playerPink" || cells[previousCell.X + 1][previousCell.Y - 1].PieceType == "player1King"))
                {
                    cells[previousCell.X + 1][previousCell.Y - 1].PieceType = "emptyBlack";
                    cells[previousCell.X + 1][previousCell.Y - 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    return true;
                }
                if (currentCell.Y - 2 == previousCell.Y && (cells[previousCell.X + 1][previousCell.Y + 1].PieceType == "playerPink" || cells[previousCell.X + 1][previousCell.Y + 1].PieceType == "player1King"))
                {
                    cells[previousCell.X + 1][previousCell.Y + 1].PieceType = "emptyBlack";
                    cells[previousCell.X + 1][previousCell.Y + 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    return true;
                }
            }
            if (previousCell.PieceType == "player1King")
            {
                if (currentCell.X + 2 == previousCell.X && currentCell.Y - 2 == previousCell.Y && (cells[previousCell.X - 1][previousCell.Y + 1].PieceType == "playerWhite" || cells[previousCell.X - 1][previousCell.Y + 1].PieceType == "player2King"))
                {
                    cells[previousCell.X - 1][previousCell.Y + 1].PieceType = "emptyBlack";
                    cells[previousCell.X - 1][previousCell.Y + 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    return true;
                }
                if (currentCell.X + 2 == previousCell.X && currentCell.Y + 2 == previousCell.Y && (cells[previousCell.X - 1][previousCell.Y - 1].PieceType == "playerWhite" || cells[previousCell.X - 1][previousCell.Y - 1].PieceType == "player2King"))
                {
                    cells[previousCell.X - 1][previousCell.Y - 1].PieceType = "emptyBlack";
                    cells[previousCell.X - 1][previousCell.Y - 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    return true;
                }
                if (currentCell.X - 2 == previousCell.X && currentCell.Y + 2 == previousCell.Y && (cells[previousCell.X + 1][previousCell.Y - 1].PieceType == "playerWhite" || cells[previousCell.X + 1][previousCell.Y - 1].PieceType == "player2King"))
                {
                    cells[previousCell.X + 1][previousCell.Y - 1].PieceType = "emptyBlack";
                    cells[previousCell.X + 1][previousCell.Y - 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    return true;
                }
                if (currentCell.X - 2 == previousCell.X && currentCell.Y - 2 == previousCell.Y && (cells[previousCell.X + 1][previousCell.Y + 1].PieceType == "playerWhite" || cells[previousCell.X + 1][previousCell.Y + 1].PieceType == "player2King"))
                {
                    cells[previousCell.X + 1][previousCell.Y + 1].PieceType = "emptyBlack";
                    cells[previousCell.X + 1][previousCell.Y + 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    return true;
                }
            }

            if (previousCell.PieceType == "player2King")
            {
                if (currentCell.X + 2 == previousCell.X && currentCell.Y - 2 == previousCell.Y && (cells[previousCell.X - 1][previousCell.Y + 1].PieceType == "playerPink" || cells[previousCell.X - 1][previousCell.Y + 1].PieceType == "player1King"))
                {
                    cells[previousCell.X - 1][previousCell.Y + 1].PieceType = "emptyBlack";
                    cells[previousCell.X - 1][previousCell.Y + 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    return true;
                }
                if (currentCell.X + 2 == previousCell.X && currentCell.Y + 2 == previousCell.Y && (cells[previousCell.X - 1][previousCell.Y - 1].PieceType == "playerPink" || cells[previousCell.X - 1][previousCell.Y - 1].PieceType == "player1King"))
                {
                    cells[previousCell.X - 1][previousCell.Y - 1].PieceType = "emptyBlack";
                    cells[previousCell.X - 1][previousCell.Y - 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    return true;
                }
                if (currentCell.X - 2 == previousCell.X && currentCell.Y + 2 == previousCell.Y && (cells[previousCell.X + 1][previousCell.Y - 1].PieceType == "playerPink" || cells[previousCell.X + 1][previousCell.Y - 1].PieceType == "player1King"))
                {
                    cells[previousCell.X + 1][previousCell.Y - 1].PieceType = "emptyBlack";
                    cells[previousCell.X + 1][previousCell.Y - 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    return true;
                }
                if (currentCell.X - 2 == previousCell.X && currentCell.Y - 2 == previousCell.Y && (cells[previousCell.X + 1][previousCell.Y + 1].PieceType == "playerPink" || cells[previousCell.X + 1][previousCell.Y + 1].PieceType == "player1King"))
                {
                    cells[previousCell.X + 1][previousCell.Y + 1].PieceType = "emptyBlack";
                    cells[previousCell.X + 1][previousCell.Y + 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    return true;
                }
            }
            return false;
        }
        public void kingPieces(Cell currentCell)
        {
            if (currentCell.PieceType == "playerPink")
            {
                if (currentCell.X == 0)
                {
                    cells[currentCell.X][currentCell.Y].CellImage = "/Tema2MVP;component/Resources/cellPlayer1King.jpg";
                    cells[currentCell.X][currentCell.Y].PieceType = "player1King";
                }
            }

            if (currentCell.PieceType == "playerWhite")
            {
                if (currentCell.X == 7)
                {
                    cells[currentCell.X][currentCell.Y].CellImage = "/Tema2MVP;component/Resources/cellPlayer2King.jpg";
                    cells[currentCell.X][currentCell.Y].PieceType = "player2King";
                }
            }
        }

        public bool complexAttackMove(ref Cell currentCell)
        {
            if (currentCell.PieceType == "playerPink")
            {
                if (currentCell.X == 1 || currentCell.X == 0 || currentCell.Y == 1 || currentCell.Y == 6 || currentCell.Y == 0 || currentCell.Y == 7)
                    return false;
                if ((cells[currentCell.X - 1][currentCell.Y - 1].PieceType == "playerWhite" || cells[currentCell.X - 1][currentCell.Y - 1].PieceType == "player2King") && cells[currentCell.X - 2][currentCell.Y - 2].PieceType == "emptyBlack")
                {
                    cells[currentCell.X - 1][currentCell.Y - 1].PieceType = "emptyBlack";
                    cells[currentCell.X - 1][currentCell.Y - 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    cells[currentCell.X - 2][currentCell.Y - 2].PieceType = "playerPink";
                    cells[currentCell.X - 2][currentCell.Y - 2].CellImage = "/Tema2MVP;component/Resources/cellPlayer2.jpg";
                    cells[currentCell.X][currentCell.Y].PieceType = "emptyBlack";
                    cells[currentCell.X][currentCell.Y].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    currentCell = cells[currentCell.X - 2][currentCell.Y - 2];
                    return true;
                }
                if ((cells[currentCell.X - 1][currentCell.Y + 1].PieceType == "playerWhite" || cells[currentCell.X - 1][currentCell.Y + 1].PieceType == "player2King") && cells[currentCell.X - 2][currentCell.Y + 2].PieceType == "emptyBlack")
                {
                    cells[currentCell.X - 1][currentCell.Y + 1].PieceType = "emptyBlack";
                    cells[currentCell.X - 1][currentCell.Y + 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    cells[currentCell.X - 2][currentCell.Y + 2].PieceType = "playerPink";
                    cells[currentCell.X - 2][currentCell.Y + 2].CellImage = "/Tema2MVP;component/Resources/cellPlayer2.jpg";
                    cells[currentCell.X][currentCell.Y].PieceType = "emptyBlack";
                    cells[currentCell.X][currentCell.Y].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    currentCell = cells[currentCell.X - 2][currentCell.Y + 2];
                    return true;
                }
            }

            if (currentCell.PieceType == "playerWhite")
            {
                if (currentCell.X == 6 || currentCell.X == 7 || currentCell.Y == 1 || currentCell.Y == 6 || currentCell.Y == 0 || currentCell.Y == 7)
                    return false;
                if ((cells[currentCell.X + 1][currentCell.Y - 1].PieceType == "playerPink" || cells[currentCell.X + 1][currentCell.Y - 1].PieceType == "player1King") && cells[currentCell.X + 2][currentCell.Y - 2].PieceType == "emptyBlack")
                {
                    cells[currentCell.X + 1][currentCell.Y - 1].PieceType = "emptyBlack";
                    cells[currentCell.X + 1][currentCell.Y - 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    cells[currentCell.X + 2][currentCell.Y - 2].PieceType = "playerWhite";
                    cells[currentCell.X + 2][currentCell.Y - 2].CellImage = "/Tema2MVP;component/Resources/cellPlayer1.jpg";
                    cells[currentCell.X][currentCell.Y].PieceType = "emptyBlack";
                    cells[currentCell.X][currentCell.Y].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    currentCell = cells[currentCell.X + 2][currentCell.Y - 2];
                    return true;
                }
                if ((cells[currentCell.X + 1][currentCell.Y + 1].PieceType == "playerPink" || cells[currentCell.X + 1][currentCell.Y + 1].PieceType == "player1King") && cells[currentCell.X + 2][currentCell.Y + 2].PieceType == "emptyBlack")
                {
                    cells[currentCell.X + 1][currentCell.Y + 1].PieceType = "emptyBlack";
                    cells[currentCell.X + 1][currentCell.Y + 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    cells[currentCell.X + 2][currentCell.Y + 2].PieceType = "playerWhite";
                    cells[currentCell.X + 2][currentCell.Y + 2].CellImage = "/Tema2MVP;component/Resources/cellPlayer1.jpg";
                    cells[currentCell.X][currentCell.Y].PieceType = "emptyBlack";
                    cells[currentCell.X][currentCell.Y].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    currentCell = cells[currentCell.X + 2][currentCell.Y + 2];
                    return true;
                }
            }
            return false;
        }

        public bool kingComplexAttackMove(ref Cell currentCell)
        {
            if (currentCell.PieceType == "player1King")
            {
                if (currentCell.X == 7 || currentCell.X == 6 || currentCell.X == 1 || currentCell.X == 0 || currentCell.Y == 1 || currentCell.Y == 6 || currentCell.Y == 0 || currentCell.Y == 7)
                    return false;
                if ((cells[currentCell.X - 1][currentCell.Y - 1].PieceType == "playerWhite" || cells[currentCell.X - 1][currentCell.Y - 1].PieceType == "player2King") && cells[currentCell.X - 2][currentCell.Y - 2].PieceType == "emptyBlack")
                {
                    cells[currentCell.X - 1][currentCell.Y - 1].PieceType = "emptyBlack";
                    cells[currentCell.X - 1][currentCell.Y - 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    cells[currentCell.X - 2][currentCell.Y - 2].PieceType = "player1King";
                    cells[currentCell.X - 2][currentCell.Y - 2].CellImage = "/Tema2MVP;component/Resources/cellPlayer1King.jpg";
                    cells[currentCell.X][currentCell.Y].PieceType = "emptyBlack";
                    cells[currentCell.X][currentCell.Y].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    currentCell = cells[currentCell.X - 2][currentCell.Y - 2];
                    return true;
                }
                if ((cells[currentCell.X - 1][currentCell.Y + 1].PieceType == "playerWhite" || cells[currentCell.X - 1][currentCell.Y + 1].PieceType == "player2King") && cells[currentCell.X - 2][currentCell.Y + 2].PieceType == "emptyBlack")
                {
                    cells[currentCell.X - 1][currentCell.Y + 1].PieceType = "emptyBlack";
                    cells[currentCell.X - 1][currentCell.Y + 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    cells[currentCell.X - 2][currentCell.Y + 2].PieceType = "player1King";
                    cells[currentCell.X - 2][currentCell.Y + 2].CellImage = "/Tema2MVP;component/Resources/cellPlayer1King.jpg";
                    cells[currentCell.X][currentCell.Y].PieceType = "emptyBlack";
                    cells[currentCell.X][currentCell.Y].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    currentCell = cells[currentCell.X - 2][currentCell.Y + 2];
                    return true;
                }
                if ((cells[currentCell.X + 1][currentCell.Y - 1].PieceType == "playerWhite" || cells[currentCell.X + 1][currentCell.Y - 1].PieceType == "player2King") && cells[currentCell.X + 2][currentCell.Y - 2].PieceType == "emptyBlack")
                {
                    cells[currentCell.X + 1][currentCell.Y - 1].PieceType = "emptyBlack";
                    cells[currentCell.X + 1][currentCell.Y - 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    cells[currentCell.X + 2][currentCell.Y - 2].PieceType = "player1King";
                    cells[currentCell.X + 2][currentCell.Y - 2].CellImage = "/Tema2MVP;component/Resources/cellPlayer1King.jpg";
                    cells[currentCell.X][currentCell.Y].PieceType = "emptyBlack";
                    cells[currentCell.X][currentCell.Y].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    currentCell = cells[currentCell.X + 2][currentCell.Y - 2];
                    return true;
                }
                if ((cells[currentCell.X + 1][currentCell.Y + 1].PieceType == "playerWhite" || cells[currentCell.X + 1][currentCell.Y + 1].PieceType == "player2King") && cells[currentCell.X + 2][currentCell.Y + 2].PieceType == "emptyBlack")
                {
                    cells[currentCell.X + 1][currentCell.Y + 1].PieceType = "emptyBlack";
                    cells[currentCell.X + 1][currentCell.Y + 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    cells[currentCell.X + 2][currentCell.Y + 2].PieceType = "player1King";
                    cells[currentCell.X + 2][currentCell.Y + 2].CellImage = "/Tema2MVP;component/Resources/cellPlayer1King.jpg";
                    cells[currentCell.X][currentCell.Y].PieceType = "emptyBlack";
                    cells[currentCell.X][currentCell.Y].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    currentCell = cells[currentCell.X + 2][currentCell.Y + 2];
                    return true;
                }
            }
            if (currentCell.PieceType == "player2King")
            {
                if (currentCell.X == 7 || currentCell.X == 6 || currentCell.X == 1 || currentCell.X == 0 || currentCell.Y == 1 || currentCell.Y == 6 || currentCell.Y == 0 || currentCell.Y == 7)
                    return false;
                if ((cells[currentCell.X - 1][currentCell.Y - 1].PieceType == "playerPink" || cells[currentCell.X - 1][currentCell.Y - 1].PieceType == "player1King") && cells[currentCell.X - 2][currentCell.Y - 2].PieceType == "emptyBlack")
                {
                    cells[currentCell.X - 1][currentCell.Y - 1].PieceType = "emptyBlack";
                    cells[currentCell.X - 1][currentCell.Y - 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    cells[currentCell.X - 2][currentCell.Y - 2].PieceType = "player2King";
                    cells[currentCell.X - 2][currentCell.Y - 2].CellImage = "/Tema2MVP;component/Resources/cellPlayer2King.jpg";
                    cells[currentCell.X][currentCell.Y].PieceType = "emptyBlack";
                    cells[currentCell.X][currentCell.Y].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    currentCell = cells[currentCell.X - 2][currentCell.Y - 2];
                    return true;
                }
                if ((cells[currentCell.X - 1][currentCell.Y + 1].PieceType == "playerPink" || cells[currentCell.X - 1][currentCell.Y + 1].PieceType == "player1King") && cells[currentCell.X - 2][currentCell.Y + 2].PieceType == "emptyBlack")
                {
                    cells[currentCell.X - 1][currentCell.Y + 1].PieceType = "emptyBlack";
                    cells[currentCell.X - 1][currentCell.Y + 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    cells[currentCell.X - 2][currentCell.Y + 2].PieceType = "player2King";
                    cells[currentCell.X - 2][currentCell.Y + 2].CellImage = "/Tema2MVP;component/Resources/cellPlayer2King.jpg";
                    cells[currentCell.X][currentCell.Y].PieceType = "emptyBlack";
                    cells[currentCell.X][currentCell.Y].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    currentCell = cells[currentCell.X - 2][currentCell.Y + 2];
                    return true;
                }
                if ((cells[currentCell.X + 1][currentCell.Y - 1].PieceType == "playerPink" || cells[currentCell.X + 1][currentCell.Y - 1].PieceType == "player1King") && cells[currentCell.X + 2][currentCell.Y - 2].PieceType == "emptyBlack")
                {
                    cells[currentCell.X + 1][currentCell.Y - 1].PieceType = "emptyBlack";
                    cells[currentCell.X + 1][currentCell.Y - 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    cells[currentCell.X + 2][currentCell.Y - 2].PieceType = "player2King";
                    cells[currentCell.X + 2][currentCell.Y - 2].CellImage = "/Tema2MVP;component/Resources/cellPlayer2King.jpg";
                    cells[currentCell.X][currentCell.Y].PieceType = "emptyBlack";
                    cells[currentCell.X][currentCell.Y].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    currentCell = cells[currentCell.X + 2][currentCell.Y - 2];
                    return true;
                }
                if ((cells[currentCell.X + 1][currentCell.Y + 1].PieceType == "playerPink" || cells[currentCell.X + 1][currentCell.Y + 1].PieceType == "player1King") && cells[currentCell.X + 2][currentCell.Y + 2].PieceType == "emptyBlack")
                {
                    cells[currentCell.X + 1][currentCell.Y + 1].PieceType = "emptyBlack";
                    cells[currentCell.X + 1][currentCell.Y + 1].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    cells[currentCell.X + 2][currentCell.Y + 2].PieceType = "player2King";
                    cells[currentCell.X + 2][currentCell.Y + 2].CellImage = "/Tema2MVP;component/Resources/cellPlayer2King.jpg";
                    cells[currentCell.X][currentCell.Y].PieceType = "emptyBlack";
                    cells[currentCell.X][currentCell.Y].CellImage = "/Tema2MVP;component/Resources/cellBoard.jpg";
                    currentCell = cells[currentCell.X + 2][currentCell.Y + 2];
                    return true;
                }
            }
            return false;
        }

        public void gameOver()
        {
            string[] lines = System.IO.File.ReadAllLines(@"D:\FACULTATE\SEM2\MVP\Tema2MVP\Tema2MVP\Tema2MVP\Resources\TextFile2.txt");
            int nrPinkWin = int.Parse(lines[0]);
            int nrWhiteWin = int.Parse(lines[1]);
            int pink = 0;
            int white = 0;
            foreach(ObservableCollection<Cell> row in cells)
            {
                foreach (Cell piece in row)
                {
                    if (piece.PieceType == "playerPink" || piece.PieceType == "player1King")
                        pink++;
                    if (piece.PieceType == "playerWhite" || piece.PieceType == "player2King")
                        white++;
                }
            }
            if (pink == 0)
            {
                MessageBox.Show("GAME OVER! THE WINNER IS BLUE!");
                nrWhiteWin++;
                lines[1] = nrWhiteWin.ToString();
            }
            if (white == 0)
            {
                MessageBox.Show("GAME OVER! THE WINNER IS PINK!");
                nrPinkWin++;
                lines[0] = nrPinkWin.ToString();
            }
            File.WriteAllLines(@"D:\FACULTATE\SEM2\MVP\Tema2MVP\Tema2MVP\Tema2MVP\Resources\TextFile2.txt", lines);
        }

        public void turnChange()
        {
            if (turn == "firstPlayer")
            {
                foreach (ObservableCollection<Cell> line in cells)
                {
                    foreach (Cell item in line)
                    {
                        if (item.PieceType == "playerPink")
                            cells[item.X][item.Y].CellImage = "/Tema2MVP;component/Resources/cellPlayer2.jpg";
                        if (item.PieceType == "player1King")
                            cells[item.X][item.Y].CellImage = "/Tema2MVP;component/Resources/cellPlayer1King.jpg";
                        if (item.PieceType == "playerWhite")
                            cells[item.X][item.Y].CellImage = "/Tema2MVP;component/Resources/turnImage.jpg";
                        if (item.PieceType == "player2King")
                            cells[item.X][item.Y].CellImage = "/Tema2MVP;component/Resources/turnImageKing.jpg";
                    }
                }
            }
            if (turn == "secondPlayer")
            {
                foreach (ObservableCollection<Cell> line in cells)
                {
                    foreach (Cell item in line)
                    {
                        if (item.PieceType == "playerPink")
                            cells[item.X][item.Y].CellImage = "/Tema2MVP;component/Resources/turnImage.jpg";
                        if (item.PieceType == "player1King")
                            cells[item.X][item.Y].CellImage = "/Tema2MVP;component/Resources/turnImageKing.jpg";
                        if (item.PieceType == "playerWhite")
                            cells[item.X][item.Y].CellImage = "/Tema2MVP;component/Resources/cellPlayer1.jpg";
                        if (item.PieceType == "player2King")
                            cells[item.X][item.Y].CellImage = "/Tema2MVP;component/Resources/cellPlayer2King.jpg";
                    }
                }
            }
        }
        public void ClickAction(Cell obj)
        {
            if (numberOfClicks == 0)
            {
                if ((obj.PieceType == "playerPink" || obj.PieceType == "player1King") && turn == "firstPlayer")
                {
                    previousCell = obj;
                    numberOfClicks++;
                    turn = "secondPlayer";
                }
                if ((obj.PieceType == "playerWhite" || obj.PieceType == "player2King") && turn == "secondPlayer")
                {
                    previousCell = obj;
                    numberOfClicks++;
                    turn = "firstPlayer";
                }
            }
            else
            {
                if (simpleMove(obj, previousCell) == true)
                {
                    simpleMoveSwap(obj, previousCell);
                    numberOfClicks = 0;
                }
                else
                {
                    if (simpleAttackMove(obj, previousCell) == true)
                    {
                        simpleMoveSwap(obj, previousCell);
                        numberOfClicks = 0;
                        bool ok = true;
                        while (ok == true)
                        {
                            if(obj.PieceType == "playerWhite" || obj.PieceType == "playerPink")
                            {
                                ok = complexAttackMove(ref obj);
                            }
                            else
                            {
                                ok = kingComplexAttackMove(ref obj);
                            }
                            kingPieces(obj);
                        }
                    }
                    else
                    {
                        numberOfClicks = 0;
                        if (turn == "firstPlayer")
                            turn = "secondPlayer";
                        else
                            turn = "firstPlayer";
                    }
                }
                kingPieces(obj);
                turnChange();
                gameOver();
            }
        }
    }
}
