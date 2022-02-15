using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tema2MVP.Models;

namespace Tema2MVP.Services
{
    class Helper
    {
        public static Cell CurrentCell { get; set; }

        public static ObservableCollection<ObservableCollection<Cell>> InitGameBoard(string file)
        {
            string[] lines = System.IO.File.ReadAllLines(file);
            ObservableCollection<ObservableCollection<Cell>> result = new ObservableCollection<ObservableCollection<Cell>>();
            for (int i = 0; i < 8; i++)
            {
                ObservableCollection<Cell> line = new ObservableCollection<Cell>();
                for (int j = 0; j < 8; j++)
                {
                    string[] words = lines[i * 8 + j].Split(' ');
                    Cell c = new Cell(int.Parse(words[0]), int.Parse(words[1]), words[2], words[3]);
                    line.Add(c);
                }
                result.Add(line);
            }
            return result;
        }
    }
}
