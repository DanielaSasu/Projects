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
    /// Interaction logic for Search.xaml
    /// </summary>
    public partial class Search : Page
    {
        public Search()
        {
            InitializeComponent();
        }

        private void myTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            myListBox.Visibility = System.Windows.Visibility.Visible;
            myListBox.Items.Clear();
            if (string.IsNullOrEmpty(myTextBox.Text) == false)
            {
                foreach (Word word in (DataContext as WordVM).Words)
                {
                    if (word.MyWord.StartsWith(myTextBox.Text))
                    {
                        if (word.MyCategory == myNewTextBox.Text || string.IsNullOrEmpty(myNewTextBox.Text))
                        {
                            myListBox.Items.Add(word);
                        }
                    }
                }
            }
            else
            {
                myListBox.Visibility = System.Windows.Visibility.Hidden;
            }
        }
    }
}
