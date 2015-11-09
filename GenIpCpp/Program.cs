using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using  System.Net;
using  System.Net.Sockets;
using System.Threading.Tasks;

namespace GenIpCpp
{
    class Program
    {
        public static UInt32 IpToInt(string ip)
        {
            char[] separator = new char[] { '.' };
            string[] items = ip.Split(separator);
            return UInt32.Parse(items[0]) << 24
                    | UInt32.Parse(items[1]) << 16
                    | UInt32.Parse(items[2]) << 8
                    | UInt32.Parse(items[3]);
        }

        static void Main(string[] args)
        {
            StringBuilder sb=new StringBuilder(64*1024*1024);
            sb.AppendLine("#include \"items.h\"");
            
            sb.AppendLine("IpItem items[]=");
            sb.AppendLine("{");
            int ncount = 0;
            using (var sr = new StreamReader(@"F:\network\ipwry\ipfile.txt",System.Text.Encoding.GetEncoding(936)))
            {
                var curline = sr.ReadLine();
                while (curline.Length>0)
                {
                    
                    if (curline.Length < 33)
                    {
                        System.Console.WriteLine("Error:{0}",curline);
                        continue;
                    }
                    string strfromip = curline.Substring(0, 16).Trim();
                    string strtoip = curline.Substring(16, 16).Trim();
                    string straddr = curline.Substring(32).Replace("\\","\\\\").Replace("\"","");

                    var fromip = IpToInt(strfromip);
                    var toip = IpToInt(strtoip);

                    sb.AppendFormat("	{{{0},{1},\"{2}\"}},\r\n", fromip, toip, straddr);
                    ncount++;
                    //System.Console.WriteLine("{0},{1},{2}", fromip, toip, straddr);
                    curline = sr.ReadLine();
                    if (curline == null)
                        break;
                }
            }
            sb.AppendLine("};");
            sb.AppendFormat("int itemslen={0};\n",ncount);
            System.Console.WriteLine(sb.ToString());
        }
    }
}
