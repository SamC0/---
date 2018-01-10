using System;
using System.Collections.Generic;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Net;  // IP，IPAddress, IPEndPoint，端口等；  
using System.Threading;
using System.Drawing.Imaging;
using MySql.Data.MySqlClient;
/*程序介绍：
******************************************************************************************
       
*******************************2016，10，11***********************************************
*/
namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        #region//全局变量
        DotNetBarcode bc = new DotNetBarcode();
        string s,a2;
        string strMsg, strKey;
        byte[] arrSendMsg;
        Thread threadWatch = null; // 负责监听客户端连接请求的 线程；  
        Socket socketWatch = null;

        Dictionary<string, Socket> dict = new Dictionary<string, Socket>();  //哈希key-value
        Dictionary<string, Thread> dictThread = new Dictionary<string, Thread>();
        #endregion
        #region//窗口的初始化
        public Form1()
        {
            InitializeComponent();
            Control.CheckForIllegalCrossThreadCalls = false;//跨线程
           
        }
        private void Form1_Load(object sender, EventArgs e)
        {   bc.Type = DotNetBarcode.Types.QRCode;
            bc.PrintCheckDigitChar = true;
            IPAddress ipaddress=null;
            string HostName = Dns.GetHostName(); //得到主机名
            IPHostEntry IpEntry = Dns.GetHostEntry(HostName);
            for (int i = 0; i < IpEntry.AddressList.Length; i++)
            {
                //从IP地址列表中筛选出IPv4类型的IP地址/AddressFamily.InterNetwork表示此IP为IPv4,
                if (IpEntry.AddressList[i].AddressFamily == AddressFamily.InterNetwork)
                {
                    ipaddress = IpEntry.AddressList[i];
                }
            }
            txtIp.Text = ipaddress.ToString();
        }
        #endregion
        #region//实现方法
        void WatchConnecting()
        {
            while (true)  // 持续不断的监听客户端的连接请求；  
            {
                // 开始监听客户端连接请求，Accept方法会阻断当前的线程；  
                Socket sokConnection = socketWatch.Accept(); // 一旦监听到一个客户端的请求，就返回一个与该客户端通信的 套接字；  
                // 想列表控件中添加客户端的IP信息；  
                lbOnline.Items.Add(sokConnection.RemoteEndPoint.ToString());
                // 将与客户端连接的 套接字 对象添加到集合中；  
                dict.Add(sokConnection.RemoteEndPoint.ToString(), sokConnection);
                ShowMsg("客户端连接成功！");
                Thread thr = new Thread(RecMsg);
                thr.IsBackground = true;
                thr.Start(sokConnection);
                dictThread.Add(sokConnection.RemoteEndPoint.ToString(), thr);  //  将新建的线程 添加 到线程的集合中去。  
            }
        }
        void RecMsg(object sokConnectionparn)
        {
            Socket sokClient = sokConnectionparn as Socket;
            while (true)
            {
                // 定义一个2M的缓存区；  
                byte[] arrMsgRec = new byte[1024 * 1024 * 2];
                // 将接受到的数据存入到输入  arrMsgRec中；  
                int length = -1;
                try
                {
                    length = sokClient.Receive(arrMsgRec); // 接收数据，并返回数据的长度；  
                }
                catch (SocketException se)
                {
                    ShowMsg("异常：" + se.Message);
                    // 从 通信套接字 集合中删除被中断连接的通信套接字；  
                    dict.Remove(sokClient.RemoteEndPoint.ToString());
                    // 从通信线程集合中删除被中断连接的通信线程对象；  
                    dictThread.Remove(sokClient.RemoteEndPoint.ToString());
                    // 从列表中移除被中断的连接IP  
                    lbOnline.Items.Remove(sokClient.RemoteEndPoint.ToString());
                    break;
                }
                catch (Exception e)
                {
                    ShowMsg("异常：" + e.Message);
                    // 从 通信套接字 集合中删除被中断连接的通信套接字；  
                    dict.Remove(sokClient.RemoteEndPoint.ToString());
                    // 从通信线程集合中删除被中断连接的通信线程对象；  
                    dictThread.Remove(sokClient.RemoteEndPoint.ToString());
                    // 从列表中移除被中断的连接IP  
                    lbOnline.Items.Remove(sokClient.RemoteEndPoint.ToString());
                    break;
                }
                if (arrMsgRec[0] != 0)  // 表示接收到的是数据；  
                {
                    if (arrMsgRec[0] == 49 )
                    { dict[strKey].Send(arrSendMsg); }
                }


            }
        }
        void ShowMsg(string str)
        {
            txtMsg.AppendText(str + "\r\n");
        }
        public static Bitmap GetImageBW(Bitmap original)
        {
            Bitmap bmp = new Bitmap(original.Width, original.Height);
            using (Graphics g = Graphics.FromImage(bmp))
            {
                ImageAttributes ias = new ImageAttributes();
                ColorMatrix m = new ColorMatrix();
                m[0, 0] = m[0, 1] = m[0, 2] = 0.30f;
                m[1, 0] = m[1, 1] = m[1, 2] = 0.59f;
                m[2, 0] = m[2, 1] = m[2, 2] = 0.11f;
                ias.SetColorMatrix(m);  // 转化为灰度
                ias.SetThreshold(0.5f); // 单色门槛值 = 0.5
                g.DrawImage(original, new Rectangle(Point.Empty, original.Size), 0, 0, bmp.Width, bmp.Width, GraphicsUnit.Pixel, ias);
            }
            return bmp.Clone(new Rectangle(Point.Empty, bmp.Size), PixelFormat.Format1bppIndexed);  // 输出单色图
        }
        #endregion
        #region//click事件
        private void btnBeginListen_Click(object sender, EventArgs e)

        {
            // 创建负责监听的套接字，注意其中的参数； ip地址类型是ipv4,socket流形式，网络协议tcp类型 
            socketWatch = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IPAddress address = IPAddress.Parse(txtIp.Text.Trim());// 将 IP 地址字符串转换为 IPAddress 实例。
                                                                   //获得文本框中的IP对象；trim去掉前后空格

            // 创建包含ip和端口号的网络节点对象；  
            IPEndPoint endPoint = new IPEndPoint(address, int.Parse(txtPort.Text.Trim()));
            try
            {
                // 将负责监听的套接字绑定到唯一的ip和端口上；  
                socketWatch.Bind(endPoint);
            }
            catch (SocketException se)
            {
                MessageBox.Show("异常：" + se.Message);
                return;
            }
            // 设置监听队列的长度；  最多可容纳的等待接受的传入连接数
            socketWatch.Listen(10);
            // 创建负责监听的线程；  
            threadWatch = new Thread(WatchConnecting);
            threadWatch.IsBackground = true;
            threadWatch.Start();
            ShowMsg("服务器启动监听成功！");
            //}  
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            strMsg =  txtMsgSend.Text.Trim() ;
            if (a2!=null)
            { 
            byte[] arrMsg = strToToHexByte(a2); // 将要发送的字符串转换成16进制字节数组；  
            arrSendMsg = new byte[arrMsg.Length + 1];
            arrSendMsg[0] = 0; // 表示发送的是消息数据 
            byte[] key = new byte[2];
            key[1] = 0xcd;
            Buffer.BlockCopy(arrMsg, 0, arrSendMsg, 1, arrMsg.Length);
            strKey = "";
            strKey = lbOnline.Text.Trim();
            if (string.IsNullOrEmpty(strKey))   // 判断是不是选择了发送的对象；  
            {
                MessageBox.Show("请选择你要发送的客户端！！！");
            }
            else
            {
                dict[strKey].Send(key);// 解决了 sokConnection是局部变量，不能再本函数中引用的问题；  
                ShowMsg(strMsg);
                txtMsgSend.Clear();
            }
            }
        }

        private void btnSendToAll_Click(object sender, EventArgs e)
        {
            string strMsg =  txtMsgSend.Text.Trim();
            byte[] arrMsg = System.Text.Encoding.UTF8.GetBytes(strMsg); // 将要发送的字符串转换成Utf-8字节数组；  
           //< span style = "font-size:14px;" >
           byte[] arrSendMsg = new byte[arrMsg.Length + 1]; // 上次写的时候把这一段给弄掉了，实在是抱歉哈~ 用来标识发送是数据而不是文件，如果没有这一段的客户端就接收不到消息了~~~  
            arrSendMsg[0] = 0; // 表示发送的是消息数据  
            Buffer.BlockCopy(arrMsg, 0, arrSendMsg, 1, arrMsg.Length);//</ span >


            foreach (Socket s in dict.Values)
            {
                s.Send(arrMsg);
            }
            ShowMsg(strMsg);
            txtMsgSend.Clear();
            ShowMsg(" 群发完毕～～～");
        }

        private static byte[] strToToHexByte(string hexString)
        {
            hexString = hexString.Replace(" ", "");
            if ((hexString.Length % 2) != 0)
                hexString += " ";
            byte[] returnBytes = new byte[hexString.Length / 2];
            for (int i = 0; i < returnBytes.Length; i++)
                returnBytes[i] = Convert.ToByte(hexString.Substring(i * 2, 2), 16);
            return returnBytes;
        }
        private void button4_Click(object sender, EventArgs e)
        {
            this.ptQRCode.Refresh();
            Bitmap b = new Bitmap(251, 128);
            ptQRCode.DrawToBitmap(b, new Rectangle(0, 0, 251, 128));
           // Bitmap bmp2 = GetImageBW(b);
            s = string.Join("", Enumerable.Range(0,32128).Select(a => new { x = a /128, y = a %128 })
               .Select(x => b.GetPixel(x.x, x.y).GetBrightness() > 0.5f ? "1" : "0"));
            string[] a1 = new string[4016];
            for (int i = 0; i < 4016; i++)
            {
                a1[i] = string.Format("{0:X000}", Convert.ToInt32(s.Substring(i * 8, 8), 2));
                if (a1[i].Length==1) a1[i] = a1[i].Insert(0,"0");
            }
            a2 = string.Join("", a1);
            a2 = a2.Insert(0, "cd");
            a2 = a2.Insert(8034, "cc");
            txtMsgSend.Text = a2;
            b.Save("D:\\Picture1.bmp");
        }

        private void over_Click(object sender, EventArgs e)
        {
            Application.Exit();

        }
        private MySqlConnection connection()
        {
            string str = "Server=localhost;User ID=root;Password=cqcl1212;Database=dianzibiaoqian;CharSet=gbk";
            MySqlConnection con = new MySqlConnection(str);//实例化链接
            return con;
        }

        private void btnCreate_Click(object sender, EventArgs e)
        {
            MySqlConnection con = connection();
            con.Open();//开启连接
            string strcmd = "select * from test";
            MySqlCommand cmd = new MySqlCommand(strcmd, con);
            MySqlDataAdapter ada = new MySqlDataAdapter(cmd);
            DataSet ds = new DataSet();
            ada.Fill(ds);//查询结果填充数据集
            dataGridView1.DataSource = ds.Tables[0];
            con.Close();//关闭连接
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void txtIp_TextChanged(object sender, EventArgs e)
        {

        }

        private void lbOnline_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void delete_Click(object sender, EventArgs e)//删除数据库内的一条信息
        {
            MySqlConnection con = connection();
            string query = "DELETE FROM test WHERE ID="+textBox10.Text;
            con.Open();
            MySqlCommand cmd = new MySqlCommand(query, con);
            cmd.ExecuteNonQuery();
            con.Close();

        }

        private void insert_Click(object sender, EventArgs e)
        {
            bool i=true;
            MySqlConnection con = connection();
            string data = "'"+textBox10.Text + "'" + "," + "'" + textBox9.Text + "'" + "," + "'" + textBox7.Text + "'" + "," + "'" + textBox2.Text + "'" + "," + "'" + textBox1.Text + "'" + "," + "'" + textBox11.Text +"'" ; 
            string query = "INSERT INTO test (ID,Name,Production,Manufacturer,Shelf,stock) VALUES("+data+")";
            string query1 = "SELECT * FROM test where ID like '%" + textBox10.Text + "%'";
            if ((!(textBox10.Text == "")) && (!(textBox9.Text == "")) && (!(textBox7.Text == "")) && (!(textBox2.Text == "")) && (!(textBox1.Text == "")) && (!(textBox11.Text == "")))
            {
                con.Open();
                MySqlCommand cmd1 = new MySqlCommand(query1, con);
                MySqlDataReader dataReader = cmd1.ExecuteReader();
                while (dataReader.Read())
                {
                    if ((string)dataReader["ID"] == textBox10.Text)
                    {
                        i = false;
                        MessageBox.Show("编号已存在，请重新输入！！！");
                    }
                    else i = false;
                }
                dataReader.Close();
                if (i)
                {
                    MySqlCommand cmd = new MySqlCommand(query, con);
                    cmd.ExecuteNonQuery();
                    
                }
                con.Close();
            }
            else MessageBox.Show("请填写完整数据！！！");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            bool i;
            MySqlConnection con = connection();
            string query = "SELECT * FROM test where ID like '%"+textBox10.Text+"%'";

            con.Open();
            MySqlCommand cmd = new MySqlCommand(query, con);
            MySqlDataReader dataReader = cmd.ExecuteReader(); 
            if (dataReader.Read())
            {
                if((string)dataReader["ID"]== textBox10.Text)
                { 
                textBox3.Text=dataReader["Name"]+"";
                textBox5.Text=dataReader["Production"]+"";
                textBox6.Text=dataReader["Manufacturer"]+"";
                textBox8.Text=dataReader["Shelf"]+"";
                }
                else MessageBox.Show("没有该编号！！！");
            }
            dataReader.Close();
            con.Close();
            textBox10.Clear();
        }


        #endregion

        #region//其他事件
        private void ptQRCode_Paint(object sender, PaintEventArgs e)
        {
          
            e.Graphics.FillRectangle(Brushes.White, new Rectangle() { X = 0, Y = 0, Width = 251, Height = 126 });
            bc.WriteBar(textBox4.Text.Trim(), 200, 50, 80, 80, e.Graphics);
            SolidBrush b1 = new SolidBrush(Color.Black);//定义单色画刷   
            e.Graphics.DrawString("商品名："+textBox3.Text, new Font("宋体", 11), b1, new PointF(0, 0));
            e.Graphics.DrawString("生产日期："+textBox5.Text, new Font("宋体", 11), b1, new PointF(0, 20));
            e.Graphics.DrawString("生产厂家："+textBox6.Text, new Font("宋体", 11), b1, new PointF(0, 40));
            e.Graphics.DrawString("保质期："+textBox8.Text, new Font("宋体", 11), b1, new PointF(0, 60));
            e.Graphics.DrawString("库存：" +textBox11.Text, new Font("宋体", 9), b1, new PointF(190, 0));

        }


        #endregion
    }
}
