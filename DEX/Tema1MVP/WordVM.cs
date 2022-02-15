using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tema1MVP
{
    class WordVM
    {
        public ObservableCollection<Word> Words { get; set; }
        public ObservableCollection<string> Categorys { get; set; }
        public WordVM()
        {
            Words = new ObservableCollection<Word>();
            Categorys = new ObservableCollection<string>();
            string[] lines = System.IO.File.ReadAllLines(@"C:\Users\Dani\Desktop\Personal projects\DEX\Tema1MVP\Text.txt");
            for (int index = 0; index <lines.Length; index += 5)
            {
                Words.Add(new Word { MyWord = lines[index], MyCategory = lines[index + 1], MyDescription = lines[index + 2], MyWordImage = lines[index + 3]});
                if(Categorys.Contains(lines[index + 1])== false)
                {
                    Categorys.Add(lines[index + 1]);
                }
            }
        }
    }
}
