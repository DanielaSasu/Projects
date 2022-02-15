using Microsoft.Win32;
using System;
using System.Collections.Generic;
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
namespace Tema1MVP
{
    /// <summary>
    /// Interaction logic for AddPage.xaml
    /// </summary>
    public partial class AddPage : Page
    {
        public AddPage()
        {
            InitializeComponent();
        }
        //ADD BUTTON
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (MyList.SelectedIndex == -1)
            {
                if (word.Text == "" || category.Text == "" || description.Text == "")
                {
                    MessageBox.Show("All fields must be completed!");
                }
                else
                {
                    if (ImageSearchBar.Text == "")
                    {
                        ImageSearchBar.Text = @"D:\FACULTATE\SEM2\MVP\Tema1MVP\Images\defaultImage.png";
                    }
                    (DataContext as WordVM).Words.Add(new Word { MyWord = word.Text, MyCategory = category.Text, MyDescription = description.Text, MyWordImage = ImageSearchBar.Text });
                    File.AppendAllText(@"D:\FACULTATE\SEM2\MVP\Tema1MVP\Tema1MVP\Text.txt", Environment.NewLine + word.Text);
                    File.AppendAllText(@"D:\FACULTATE\SEM2\MVP\Tema1MVP\Tema1MVP\Text.txt", Environment.NewLine + category.Text);
                    File.AppendAllText(@"D:\FACULTATE\SEM2\MVP\Tema1MVP\Tema1MVP\Text.txt", Environment.NewLine + description.Text);
                    File.AppendAllText(@"D:\FACULTATE\SEM2\MVP\Tema1MVP\Tema1MVP\Text.txt", Environment.NewLine + ImageSearchBar.Text);
                    File.AppendAllText(@"D:\FACULTATE\SEM2\MVP\Tema1MVP\Tema1MVP\Text.txt", Environment.NewLine);
                }
            }
            else
            {
                MessageBox.Show("Add a different word!");
            }
        }
        //DELETE BUTTON
        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            if (MyList.SelectedIndex == -1)
            {
                MessageBox.Show("You must select a word!!");
            }
            else
            {
                List<string> lines = File.ReadAllLines(@"D:\FACULTATE\SEM2\MVP\Tema1MVP\Tema1MVP\Text.txt").ToList();
                lines.RemoveAt(MyList.SelectedIndex * 5);
                lines.RemoveAt(MyList.SelectedIndex * 5);
                lines.RemoveAt(MyList.SelectedIndex * 5);
                lines.RemoveAt(MyList.SelectedIndex * 5);
                lines.RemoveAt(MyList.SelectedIndex * 5);
                File.WriteAllLines(@"D:\FACULTATE\SEM2\MVP\Tema1MVP\Tema1MVP\Text.txt", lines);
                (DataContext as WordVM).Words.RemoveAt(MyList.SelectedIndex);
            }
        }
        //MODIFY BUTTON
        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            if(MyList.SelectedIndex == -1)
            {
                MessageBox.Show("You must select a word!!");
            }
            else
            {
                List<string> lines = File.ReadAllLines(@"D:\FACULTATE\SEM2\MVP\Tema1MVP\Tema1MVP\Text.txt").ToList();
                lines[MyList.SelectedIndex * 5] = word.Text;
                lines[MyList.SelectedIndex * 5 + 1] = category.Text;
                lines[MyList.SelectedIndex * 5 + 2] = description.Text;
                lines[MyList.SelectedIndex * 5 + 3] = ImageSearchBar.Text;
                if (word.Text == "" || category.Text == "" || description.Text == "")
                {
                    MessageBox.Show("All fields must be completed!");
                }
                else
                {
                    File.WriteAllLines(@"D:\FACULTATE\SEM2\MVP\Tema1MVP\Tema1MVP\Text.txt", lines);
                    (DataContext as WordVM).Words[MyList.SelectedIndex] = new Word { MyWord = word.Text, MyCategory = category.Text, MyDescription = description.Text, MyWordImage = ImageSearchBar.Text };

                }
            }
        }
        //ADD IMAGE BUTTON
        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Image files (*.png;*.jpeg)|*.png;*.jpeg|All files (*.*)|*.*";
            if (openFileDialog.ShowDialog() == true)
            {
                ImageSearchBar.Text = openFileDialog.FileName;
            }
        }
    }
}
