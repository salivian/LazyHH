using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;
using System.IO.Ports;
namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        private SerialPort sp;
        public const int DEFAULT_BAUD_RATE = 9600;
        public Form1()
        {
            InitializeComponent();
            
        }
        public bool Connect()
        {
            return OpenPort("COM3", DEFAULT_BAUD_RATE);
        }

        public bool Disconnect()
        {
            return ClosePort();
        }
        private bool OpenPort(string port, int baudRate)
        {
            try
            {
                sp = new SerialPort(port, baudRate);
                if (!sp.IsOpen)
                    sp.Open();
                //sp.DataReceived += new SerialDataReceivedEventHandler(ArduinoDataReceived);
                sp.WriteLine("abc");
                return true;
            }
            catch
            {
                return false;
            }
        }
        private bool ClosePort()
        {
            try
            {
                Task.Factory.StartNew(() => { sp.Close(); });
                Thread.Sleep(500);
                return true;
            }
            catch
            {
                return false;
            }
        }
        private void ArduinoDataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                string data = sp.ReadLine();
                while (data.Length == 0 || data[0] != '=')
                    data = sp.ReadLine();

                List<double> dists = new List<double>();
                string[] vals = data.Substring(1).Split(',');
                foreach (string val in vals)
                {
                    try
                    {
                        double dist = double.Parse(val);
                        dists.Add(dist);
                    }
                    catch { }
                }
                //OnDistancesChanged(dists.ToArray());
            }
            catch { }
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            
        }
    }
}
