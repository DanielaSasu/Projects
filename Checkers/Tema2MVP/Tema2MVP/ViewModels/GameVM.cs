using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tema2MVP.Models;
using Tema2MVP.Services;

namespace Tema2MVP.ViewModels
{
    class GameVM : BaseNotification
    {
        private GameBusinessLogic bl;
        public GameVM(ObservableCollection<ObservableCollection<Cell>> board)
        {
            bl = new GameBusinessLogic(board);
            GameBoard = CellBoardToCellVMBoard(board);
        }
        public GameVM()
        {
            ObservableCollection<ObservableCollection<Cell>> board = Helper.InitGameBoard(@"C:\Users\Dani\Desktop\Personal projects\Checkers\Tema2MVP\Tema2MVP\Resources\TextFile.txt");
            bl = new GameBusinessLogic(board);
            GameBoard = CellBoardToCellVMBoard(board);
        }
        public GameVM(string file)
        {
            ObservableCollection<ObservableCollection<Cell>> board = Helper.InitGameBoard(file);
            bl = new GameBusinessLogic(board);
            GameBoard = CellBoardToCellVMBoard(board);
        }

        private ObservableCollection<ObservableCollection<CellVM>> CellBoardToCellVMBoard(ObservableCollection<ObservableCollection<Cell>> board)
        {
            ObservableCollection<ObservableCollection<CellVM>> result = new ObservableCollection<ObservableCollection<CellVM>>();
            for (int i = 0; i < board.Count; i++)
            {
                ObservableCollection<CellVM> line = new ObservableCollection<CellVM>();
                for (int j = 0; j < board[i].Count; j++)
                {
                    Cell c = board[i][j];
                    CellVM cellVM = new CellVM(ref c, ref bl);
                    line.Add(cellVM);
                }
                result.Add(line);
            }
            return result;
        }
        public ObservableCollection<ObservableCollection<CellVM>> GameBoard { get; set; }
        public ObservableCollection<string> TurnCell { get; set; }
    }
}
