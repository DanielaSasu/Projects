using System;
using System.Collections.Generic;
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
    /// Interaction logic for Entertainment.xaml
    /// </summary>
    public partial class Entertainment : Page
    {
        private int currentWordIndex;
        private int score;
        public Entertainment()
        {
            InitializeComponent();
            Random random = new Random();
            int choice;
            choice = random.Next(2);
            if (choice == 0 && (DataContext as QuizElements).randomWords[0].MyWordImage != @"C:\Users\Dani\Desktop\Personal projects\DEX\Images\defaultImage.png")
            {
                image.Source = new BitmapImage(new Uri((DataContext as QuizElements).randomWords[0].MyWordImage));
                image.Visibility = System.Windows.Visibility.Visible;
                clueBox.Visibility = System.Windows.Visibility.Hidden;
            }
            else
            {
                clueBox.Text = (DataContext as QuizElements).randomWords[0].MyDescription;
                clueBox.Visibility = System.Windows.Visibility.Visible;
                image.Visibility = System.Windows.Visibility.Hidden;
            }
            currentWordIndex = 0;
            score = 0;
        }

        private void showButton_Click(object sender, RoutedEventArgs e)
        {
            if (currentWordIndex < 5)
            {
                if (writeBox.Text == (DataContext as QuizElements).randomWords[currentWordIndex].MyWord)
                {
                    MessageBox.Show("CORRECT!");
                    score++;
                }
                else
                {
                    MessageBox.Show("WRONG! THE CORRECT ANSWER IS  " + (DataContext as QuizElements).randomWords[currentWordIndex].MyWord);
                }
                writeBox.Text = "";
                currentWordIndex++;
                if (currentWordIndex < 5)
                {
                    Random random = new Random();
                    int choice;
                    choice = random.Next(2);
                    if (choice == 0 && (DataContext as QuizElements).randomWords[currentWordIndex].MyWordImage != @"D:\FACULTATE\SEM2\MVP\Tema1MVP\Images\defaultImage.png")
                    {
                        image.Source = new BitmapImage(new Uri((DataContext as QuizElements).randomWords[currentWordIndex].MyWordImage));
                        image.Visibility = System.Windows.Visibility.Visible;
                        clueBox.Visibility = System.Windows.Visibility.Hidden;
                    }
                    else
                    {
                        clueBox.Text = (DataContext as QuizElements).randomWords[currentWordIndex].MyDescription;
                        clueBox.Visibility = System.Windows.Visibility.Visible;
                        image.Visibility = System.Windows.Visibility.Hidden;
                    }
                }
            }
            if (currentWordIndex == 5)
            {
                showButton.Visibility = System.Windows.Visibility.Hidden;
                finishButton.Visibility = System.Windows.Visibility.Visible;
            }
        }

        private void finishButton_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show(score.ToString());
            Random random = new Random();
            int choice;
            choice = random.Next(2);
            if (choice == 0 && (DataContext as QuizElements).randomWords[0].MyWordImage != @"D:\FACULTATE\SEM2\MVP\Tema1MVP\Images\defaultImage.png")
            {
                image.Source = new BitmapImage(new Uri((DataContext as QuizElements).randomWords[0].MyWordImage));
                image.Visibility = System.Windows.Visibility.Visible;
                clueBox.Visibility = System.Windows.Visibility.Hidden;
            }
            else
            {
                clueBox.Text = (DataContext as QuizElements).randomWords[0].MyDescription;
                clueBox.Visibility = System.Windows.Visibility.Visible;
                image.Visibility = System.Windows.Visibility.Hidden;
            }
            currentWordIndex = 0;
            score = 0;
            showButton.Visibility = System.Windows.Visibility.Visible;
            finishButton.Visibility = System.Windows.Visibility.Hidden;
        }
    }
}
