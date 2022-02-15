using Microsoft.Owin.Security.Notifications;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tema2MVP.Models;
using Tema2MVP;
using System.Windows.Input;
using Tema2MVP.Services;
using Tema2MVP.Commands;

namespace Tema2MVP.ViewModels
{
    class CellVM : BaseNotification
    {
        GameBusinessLogic bl;
        public CellVM(ref Cell cell, ref GameBusinessLogic bl)
        {
            simpleCell = cell;
            this.bl = bl;
        }
        public CellVM(int x, int y, string myTypeCell, string myCellImage, GameBusinessLogic bl)
        {
            SimpleCell = new Cell(x, y, myTypeCell, myCellImage);
            this.bl = bl;
        }

        private Cell simpleCell;
        public Cell SimpleCell
        {
            get { return simpleCell; }
            set
            {
                simpleCell = value;
                NotifyPropertyChanged("SimpleCell");
            }
        }

        private string turnImage;
        public string TurnImage
        {
            get { return turnImage; }
            set
            {
                turnImage = value;
                NotifyPropertyChanged("TurnImage");
            }
        }

        private ICommand clickCommand;
        public ICommand ClickCommand
        {
            get
            {
                if (clickCommand == null)
                {
                    clickCommand = new RelayCommand<Cell>(bl.ClickAction);
                }
                return clickCommand;
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
