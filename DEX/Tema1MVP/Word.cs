using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tema1MVP
{
    class Word : INotifyPropertyChanged
    {
        private string myWord;
        public string MyWord
        {
            get
            {
                return myWord;
            }
            set
            {
                myWord = value;
                NotifyPropertyChanged("Word");
            }
        }

        private string myCategory;
        public string MyCategory
        {
            get
            {
                return myCategory;
            }
            set
            {
                myCategory = value;
                NotifyPropertyChanged("Category");
            }
        }

        private string myDescription;
        public string MyDescription
        {
            get
            {
                return myDescription;
            }
            set
            {
                myDescription = value;
                NotifyPropertyChanged("Description");
            }
        }

        private string myWordImage;
        public string MyWordImage
        {
            get
            {
                return myWordImage;
            }
            set
            {
                myWordImage = value;
                NotifyPropertyChanged("Image");
            }
        }

        public Word()
        {

        }
        public Word(string word, string category, string description, string image)
        {
            MyWord = word;
            MyCategory = category;
            MyDescription = description;
            MyWordImage = image;
        }

        public event PropertyChangedEventHandler PropertyChanged;
        public void NotifyPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
