using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace M2000D
{
    class Tools
    {
        public static double ConvertDegreesToRadians(double angle)
        {
            return (Math.PI / 180) * angle;
        }

        public static double ConvertRadiansToDegrees(double radians)
        {
            double degrees = (180 / Math.PI) * radians;
            return (degrees);
        }

        public static bool checkIfTcpPortAvailable(int port)
        {
            IPAddress ipAddress = Dns.GetHostEntry("localhost").AddressList[0];
            try
            {
                TcpListener tcpListener = new TcpListener(ipAddress, 666);
                tcpListener.Start();
            }
            catch 
            {
                return false;
            }
            return true;
        }


        public static int checkIfTcpPortAvailable2(int port)
        {
            var Ports = new List<Port>();

            try
            {
                using (Process p = new Process())
                {

                    ProcessStartInfo ps = new ProcessStartInfo();
                    ps.Arguments = "-ano -p tcp";
                    ps.FileName = "netstat.exe";
                    ps.UseShellExecute = false;
                    ps.WindowStyle = ProcessWindowStyle.Hidden;
                    ps.RedirectStandardInput = true;
                    ps.RedirectStandardOutput = true;
                    ps.RedirectStandardError = true;

                    p.StartInfo = ps;
                    p.Start();

                    StreamReader stdOutput = p.StandardOutput;
                    StreamReader stdError = p.StandardError;

                    string content = stdOutput.ReadToEnd() + stdError.ReadToEnd();
                    string exitStatus = p.ExitCode.ToString();

                    if (exitStatus != "0")
                    {
                        // Command Errored. Handle Here If Need Be
                    }

                    //Get The Rows
                    string[] rows = Regex.Split(content, "\r\n");
                    foreach (string row in rows)
                    {
                        //Split it baby
                        string[] tokens = Regex.Split(row, "\\s+");
                        if (tokens.Length > 4 && (tokens[1].Equals("UDP") || tokens[1].Equals("TCP")))
                        {
                            string localAddress = Regex.Replace(tokens[2], @"\[(.*?)\]", "1.1.1.1"); 
                            if (Convert.ToInt16(localAddress.Split(':')[1]) == port)
                            {
                                return Convert.ToInt16(tokens[5]);
                            }
                            
                            
                            
                            
                            //Ports.Add(new Port
                            //{
                            //    protocol = localAddress.Contains("1.1.1.1") ? String.Format("{0}v6", tokens[1]) : String.Format("{0}v4", tokens[1]),
                            //    port_number = localAddress.Split(':')[1],
                            //    process_name = (string)(tokens[1] == "UDP" ? LookupProcess(Convert.ToInt16(tokens[4])) : LookupProcess(Convert.ToInt16(tokens[5])))
                            //});
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            return -1;
        }

        private static object LookupProcess(short v)
        {
            throw new NotImplementedException();
        }
    }
    // ===============================================
    // The Port Class We're Going To Create A List Of
    // ===============================================
    public class Port
    {
        public string name
        {
            get
            {
                return string.Format("{0} ({1} port {2})", this.process_name, this.protocol, this.port_number);
            }
            set { }
        }
        public string port_number { get; set; }
        public string process_name { get; set; }
        public string protocol { get; set; }
    }

}

