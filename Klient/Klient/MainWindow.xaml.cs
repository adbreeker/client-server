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
using System.Net.Sockets;

namespace Klient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    /// 

    static class MyVariables
    {
        public static int port;
        public static string host;
        public static int counter = 0;

    }

    public partial class MainWindow : Window
    {
        
        
        public MainWindow()
        {
            InitializeComponent();
        }

        public void MakeConection_Click(object sender, RoutedEventArgs e)
        {
            
            MyVariables.host = HostTextBox.Text;
            MyVariables.port = Convert.ToInt32(PortTextBox.Text);
            // wartosci dla testow
            //MyVariables.host = "192.168.1.10";
            //MyVariables.port = 4040;



            // byte[] msg = Encoding.UTF8.GetBytes("This is a test");
            // int i = socket.Send(msg);
            // MessageBox.Show("Wysłano wiadomość: " +  Encoding.UTF8.GetString(msg) + "\nDo użytkownika: " + host);

            Chat chatwindow = new Chat();
            chatwindow.Show();
        }

        private void PortTextBox_GotFocus(object sender, RoutedEventArgs e)
        {
            PortTextBox.Text = "";
        }

        private void PortTextBox_LostFocus(object sender, RoutedEventArgs e)
        {
            if (PortTextBox.Text == "")
            {
                PortTextBox.Text = "Podaj port";
            }
        }

        private void HostTextBox_LostFocus(object sender, RoutedEventArgs e)
        {
            if (HostTextBox.Text == "")
            {
                HostTextBox.Text = "Podaj hosta";
            }
        }

        private void HostTextBox_GotFocus(object sender, RoutedEventArgs e)
        {
            HostTextBox.Text="";
        }
    }

}
