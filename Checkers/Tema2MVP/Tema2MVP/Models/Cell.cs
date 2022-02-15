using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tema2MVP.Models
{
    class Cell : INotifyPropertyChanged
    {
        public Cell()
        {
            this.X = -1;
            this.Y = -1;
            this.PieceType = "";
            this.cellImage = "";
        }
        public Cell(int x, int y, string myPieceType, string myCellImage)
        {
            this.X = x;
            this.Y = y;
            this.PieceType = myPieceType;
            this.cellImage = myCellImage;
        }

        private int x;
        public int X
        {
            get { return x; }
            set
            {
                x = value;
                NotifyPropertyChanged("X");
            }
        }

        private int y;
        public int Y
        {
            get { return y; }
            set
            {
                y = value;
                NotifyPropertyChanged("Y");
            }
        }

        private string pieceType;
        public string PieceType
        {
            get { return pieceType; }
            set
            {
                pieceType = value;
                NotifyPropertyChanged("PieceType");
            }
        }

        private string cellImage;
        public string CellImage
        {
            get { return cellImage; }
            set
            {
                cellImage = value;
                NotifyPropertyChanged("CellImage");
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        protected void NotifyPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}