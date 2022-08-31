using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.IO;
using System.ComponentModel;
using System.Linq;

namespace Klient
{
    /// <summary>
    /// Interaction logic for Printer.xaml
    /// </summary>
    public partial class Printer : Window
    {
        public Printer()
        {
            InitializeComponent();
        }

        private void sv_ScrollChanged(object sender, ScrollChangedEventArgs e)
        {
            if(sv.VerticalOffset==sv.ScrollableHeight && sv.ScrollableHeight>0)
            {
                ContinueFile();
            }
        }

        public void ContinueFile()
        {
            int sum = 0;
            foreach(string line in File.ReadLines("ReceivedFile.txt").Skip(MyVariables.counter).Take(50))
            {
                PrinterText.Text += line;
                PrinterText.Text += "\n";
                sum++;
            }
            MyVariables.counter += sum;
        }
    }
}
