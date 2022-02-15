using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tema1MVP
{
    class QuizElements
    {
        public ObservableCollection<Word> randomWords { get; set; }
        public QuizElements()
        {
            randomWords = new ObservableCollection<Word>();
            WordVM myWords = new WordVM();
            Random random = new Random();
            for(int index = 0;index<5;index++)
            {
                int position = random.Next(0, myWords.Words.Count);
                randomWords.Add(myWords.Words[position]);
                myWords.Words.RemoveAt(position);
            }
        }
    }
}
