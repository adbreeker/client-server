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
using System.Net.Sockets;
using System.Threading;
using System.IO;
using System.ComponentModel;
using System.Linq;

namespace Klient
{
    /// <summary>
    /// Interaction logic for Chat.xaml
    /// </summary>
    public partial class Chat : Window
    {
        System.Net.IPAddress[] IPs = System.Net.Dns.GetHostAddresses(MyVariables.host);
        Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        

        public Chat()
        {
            InitializeComponent();
            socket.Connect(IPs[0], MyVariables.port);
            RecNewMessage();
        }

        private void ChatMessageSenderButton_Click(object sender, RoutedEventArgs e)
        {
            byte[] msg = Encoding.UTF8.GetBytes(ChatMessageSender.Text);
            int i = socket.Send(msg);
            Thread.Sleep(1000);
            TypeOfFile();
            
            
        }

        public void TypeOfFile()
        {
            
            byte[] type = new byte[4];
            int i = socket.Receive(type);


            if (Encoding.UTF8.GetString(type) == "--sh")
            {
                RecNewMessage();
            }
            if (Encoding.UTF8.GetString(type) == "--ln")
            {
                ChatTextVisualiser.Text = "\nZ uwagi na zbyt wiele wyników pasujących do wymagań zostaną one zapisane w pliku.\n\nTo może chwilę potrwać.\nProsze nie zamykać programu!!!";
                MessageBox.Show("Bardzo wiele pasujących rezultatów!\nKliknij 'Ok' aby kontynouwać pobieranie");
                RecFile();
            }



        }

        public void RecNewMessage()
        {
            byte[] msgr = new byte[1024];
            int i = socket.Receive(msgr);
            ChatTextVisualiser.Text = Encoding.UTF8.GetString(msgr);
            ChatTextVisualiser.Text += "\n";
        }

        public void RecFile()
        { 
            var buffer = new List<byte>();

            while (socket.Available > 0)
            {
                var currByte = new Byte[1];
                var byteCounter = socket.Receive(currByte, currByte.Length, SocketFlags.None);

                if (byteCounter.Equals(1))
                {
                    buffer.Add(currByte[0]);
                }
            }
            File.WriteAllBytes("ReceivedFile.txt", buffer.ToArray());
            if(MessageBox.Show("Plik zapisano\n Czy chcesz go załadować w osobnym oknie?\nUwaga! To może zająć dużo czasu i zawiesić działanie programu.", "File Ready", MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.Yes)
            {
                OpenFile();  
            }
            

        }

        public void OpenFile()
        {
            Printer printerwindow = new Printer();
            printerwindow.Show();
            foreach (string line in File.ReadLines("ReceivedFile.txt").Take(50))
            {
               
                printerwindow.PrinterText.Text += line;
                printerwindow.PrinterText.Text += "\n";
                MyVariables.counter++;
               
            }
            
        }

        private void ChatWindow_Closing(object sender, CancelEventArgs e)
        {
            socket.Disconnect(false);
        }
    }
}
