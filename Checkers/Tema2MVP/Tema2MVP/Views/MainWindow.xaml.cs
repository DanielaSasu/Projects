using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Tema2MVP.ViewModels;

namespace Tema2MVP.Views
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void NewGameClick(object sender, RoutedEventArgs e)
        {
            GameVM newGame = new GameVM(@"D:\FACULTATE\SEM2\MVP\Tema2MVP\Tema2MVP\Tema2MVP\Resources\TextFile.txt");
            grid.ItemsSource = newGame.GameBoard;
        }

        private void SaveGameClick(object sender, RoutedEventArgs e)
        {
            List<string> lines = new List<string>();
            foreach (ObservableCollection<CellVM> line in grid.Items)
            {
                foreach (CellVM item in line)
                {
                    lines.Add(item.SimpleCell.X.ToString() + " " + item.SimpleCell.Y.ToString() + " " + item.SimpleCell.PieceType + " " + item.SimpleCell.CellImage);

                }
            }
            File.WriteAllLines(@"D:\FACULTATE\SEM2\MVP\Tema2MVP\Tema2MVP\Tema2MVP\Resources\TextFile1.txt", lines);
        }

        private void LoadGameClick(object sender, RoutedEventArgs e)
        {
            GameVM newGame = new GameVM(@"D:\FACULTATE\SEM2\MVP\Tema2MVP\Tema2MVP\Tema2MVP\Resources\TextFile1.txt");
            grid.ItemsSource = newGame.GameBoard;
        }

        private void AboutClick(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Sasu Daniela Claudia" + System.Environment.NewLine + "10LF393" + System.Environment.NewLine + "daniela.sasu@student.unitbv.ro" + System.Environment.NewLine + "This is a checkers game!");
        }

        private void StatisticsClick(object sender, RoutedEventArgs e)
        {
            string[] lines = System.IO.File.ReadAllLines(@"D:\FACULTATE\SEM2\MVP\Tema2MVP\Tema2MVP\Tema2MVP\Resources\TextFile2.txt");
            MessageBox.Show("Pink score : " + lines[0] + System.Environment.NewLine + "Blue score : " + lines[1]);
        }
    }
}
