using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace Real_Windows_Form_Calculation
{
    public partial class Form1 : Form
    {
        Button[,] btn = new Button[3, 3];
        Button[] finallybtn = new Button[3];
        Button[] operabtn = new Button[4];
        Button[] operabtn2 = new Button[4];
        Button[] operabtn3 = new Button[5];
        TextBox Edit1 = new TextBox();
        TextBox Edit2 = new TextBox();
        TextBox Edit3 = new TextBox();
        Font btnFont = new Font("行楷", 18, FontStyle.Bold);
        int equFlag = 1;
        int dotflag;
        int COpenParen = 0;
        int parenFlag = 0;
        string str = "";
        string showstr = "";
        string prior = "";


        [DllImport("sub.dll")]
        public static extern double solve(string str);

        //放上去会有阴影效果
        public Form1()
        {
            InitializeComponent();
            //设置主窗口属性
            this.StartPosition = FormStartPosition.CenterScreen;
            //设置控件尺寸
            Size s = new Size(317, 410);
            Size bs = new Size(60, 60);
            Size ts = new Size(290, 80);
            this.Size = s;
            dotflag = 0;
            //1~9 btn[i,j]
            #region
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    btn[i, j] = new Button();
                    btn[i, j].Size = bs;
                    btn[i, j].Visible = true;
                    btn[i, j].Location = new Point(60 * j, 130 + 60 * i);
                    btn[i, j].Font = btnFont;
                    btn[i, j].Text = "";
                    this.BackColor = ColorTranslator.FromHtml("#d2d8b7");
                    this.Controls.Add(btn[i, j]);
                    btn[i, j].Click += button_Click;
                    btn[i, j].MouseMove += color_Move;
                    btn[i, j].MouseLeave += color_Leave;
                }
            }
            btn[0, 0].Text = "7".ToString();
            btn[0, 1].Text = "8".ToString();
            btn[0, 2].Text = "9".ToString();
            btn[1, 0].Text = "4".ToString();
            btn[1, 1].Text = "5".ToString();
            btn[1, 2].Text = "6".ToString();
            btn[2, 0].Text = "1".ToString();
            btn[2, 1].Text = "2".ToString();
            btn[2, 2].Text = "3".ToString();
            #endregion
            // . 0 =  finallybtn[i]
            #region
            for (int i = 0; i < 3; i++)
            {
                finallybtn[i] = new Button();
                finallybtn[i].Size = bs;
                finallybtn[i].Visible = true;
                this.Controls.Add(finallybtn[i]);
                finallybtn[i].Font = btnFont;
                finallybtn[i].MouseMove += color_Move;
                finallybtn[i].MouseLeave += color_Leave;
            }
            finallybtn[0].Location = new Point(0, 310);
            finallybtn[1].Location = new Point(60, 310);
            finallybtn[2].Location = new Point(120, 310);
            finallybtn[0].Text = ".";
            finallybtn[1].Text = "0";
            finallybtn[2].Text = "=";
            finallybtn[0].Click += button_Click;
            finallybtn[1].Click += button_Click;
            finallybtn[2].Click += equbutton_Click;
            #endregion
            //+ - * \ operabtn[i]
            #region
            for (int i = 0; i < 4; i++)
            {
                operabtn[i] = new Button();
                operabtn[i].Size = bs;
                operabtn[i].Location = new Point(180, 130 + 60 * i);
                this.Controls.Add(operabtn[i]);
                operabtn[i].Click += obutton_Click;
                operabtn[i].Font = btnFont;
                operabtn[i].MouseMove += color_Move;
                operabtn[i].MouseLeave += color_Leave;
            }
            operabtn[0].Text = "+";
            operabtn[1].Text = "-";
            operabtn[2].Text = "*";
            operabtn[3].Text = "/";
            #endregion
            //%  √ (  )  operabtn2[i]
            #region
            for (int i = 0; i < 4; i++)
            {
                operabtn2[i] = new Button();
                operabtn2[i].Size = bs;
                operabtn2[i].Location = new Point(60 * i, 70);
                this.Controls.Add(operabtn2[i]);
                operabtn2[i].Click += obutton_Click;
                operabtn2[i].Font = btnFont;
                operabtn2[i].MouseMove += color_Move;
                operabtn2[i].MouseLeave += color_Leave;
            }
            operabtn2[0].Text = "%";
            operabtn2[1].Text = "√";
            operabtn2[2].Text = "(";
            operabtn2[3].Text = ")";
            #endregion
            //Clear ^  Sin   Cos   back operabtn3[i]
            #region
            for (int i = 0; i < 5; i++)
            {
                operabtn3[i] = new Button();
                operabtn3[i].Size = bs;
                operabtn3[i].Location = new Point(240, 70 + 60 * i);
                this.Controls.Add(operabtn3[i]);
                operabtn3[i].MouseMove += color_Move;
                operabtn3[i].MouseLeave += color_Leave;
            }
            operabtn3[0].Font = new Font("行楷", 10, FontStyle.Bold);
            operabtn3[0].Text = "Clear";
            operabtn3[1].Font = btnFont;
            operabtn3[1].Text = "^";
            operabtn3[2].Font = new Font("行楷", 11, FontStyle.Bold);
            operabtn3[2].Text = "Sin";
            operabtn3[3].Font = new Font("行楷", 11, FontStyle.Bold);
            operabtn3[3].Text = "Cos";
            operabtn3[4].Font = new Font("行楷", 10, FontStyle.Bold);
            operabtn3[4].Text = "Back";
            operabtn3[1].Click += obutton_Click;
            operabtn3[0].Click += clear_Click;
            operabtn3[2].Click += sin_Click;
            operabtn3[3].Click += cos_Click;
            operabtn3[4].Click += back_Click;
            #endregion
            //初始化第一个编辑框 点击"="号后 用来显示公式
            #region
            Edit1.Font = new Font("行楷", 20, FontStyle.Bold);
            Edit1.Size = ts;
            Edit1.BackColor = ColorTranslator.FromHtml("#d2d8b7");
            Edit1.Visible = true;
            Edit1.Enabled = true;
            Edit1.ReadOnly = true;
            Edit1.TextAlign = HorizontalAlignment.Right;
            Edit1.Location = new Point(5, 5);
            Edit1.CausesValidation = false;
            Edit1.BorderStyle = BorderStyle.None;
            this.Controls.Add(Edit1);
            #endregion
            //初始化第二个编辑框 用来显示公式，点击"="号后 用来显示结果。
            #region
            Edit2.Font = new Font("行楷", 20, FontStyle.Bold);
            Edit2.BackColor = ColorTranslator.FromHtml("#d2d8b7");
            Edit2.Size = ts;
            Edit2.Visible = true;
            Edit2.TextAlign = HorizontalAlignment.Right;
            Edit2.Location = new Point(5, 35);
            Edit2.ReadOnly = true;
            Edit2.BorderStyle = BorderStyle.None;
            this.Controls.Add(Edit2);
            #endregion

            #region
            Edit3.Font = new Font("行楷", 42, FontStyle.Bold);
            Edit3.BackColor = ColorTranslator.FromHtml("#C8C8C8");
            Edit3.Size = new Size(300,200);
            Edit3.Visible = true;
            Edit3.Location = new Point(0, 0);
            Edit3.ReadOnly = true;
            Edit3.BorderStyle = BorderStyle.Fixed3D;
            this.Controls.Add(Edit3);
            #endregion
            /*
            //开始时 屏蔽按钮
            finallybtn[0].Enabled = false;      //屏蔽.
            finallybtn[2].Enabled = false;      //屏蔽=
            for (int i = 0; i < 3; i++)         //屏蔽 + - * /
                operabtn[i].Enabled = false;
            operabtn2[0].Enabled = false;       //屏蔽%
            operabtn2[3].Enabled = false;       //屏蔽)
            operabtn3[1].Enabled = false;       //屏蔽 
            */
        }
        //数字0~9以及'.'的处理事件
        private void button_Click(object sender, EventArgs e)
        {
            Button tempBtn = (Button)sender;
            if (tempBtn.Text.ToString() != "." || dotflag != 0)
            {
                prior = tempBtn.Text.ToString();
                str = str + tempBtn.Text.ToString();                //用于处理的字符串
                showstr = showstr + tempBtn.Text.ToString();        //用于显示的字符串
                dotflag = 1;
                if (tempBtn.Text.ToString() == ".")
                    dotflag = 0;
                Edit2.Text = showstr;                               //显示
                equFlag = 1;                                        //可以使用"="
                parenFlag = 1;                                      //可以使用")"
            }
            /*
            //开放某些按钮
            finallybtn[0].Enabled = true;      //开放 0
            finallybtn[2].Enabled = true;      //开放 = 
            for (int i = 0; i < 3; i++)         //开放 + - * /
                operabtn[i].Enabled = true;
            operabtn2[0].Enabled = true;       //开放%
            operabtn3[1].Enabled = true;       //开放 ^
            */
        }
        //操作符号的处理事件
        private void obutton_Click(object sender, EventArgs e)
        {
            Button tempBtn = (Button)sender;

            if (prior != "+" && prior != "-" && prior != "*" && prior != "/" && prior != "%" && prior != "√"
                && tempBtn.Text != "("&&tempBtn.Text!=")")//如果前边不是一个操作符
            {
                if (tempBtn.Text.ToString() != "√" && tempBtn.Text.ToString()!=")"&&tempBtn.Text.ToString()!="(")
                {
                    if (prior == ")")
                        equFlag = 1;
                    else
                        equFlag = 2;                                    //不可使用"="
                    showstr = showstr + tempBtn.Text.ToString();        //用于显示的字符串
                    str = str + tempBtn.Text.ToString();                //用于处理的字符串
                    Edit2.Text = showstr;                               //显示
                    prior = tempBtn.Text.ToString();
                }
                else
                {
                    str = str + "~";                                    //用于处理的字符串
                    showstr = showstr + tempBtn.Text.ToString();        //用于显示的字符串
                    Edit2.Text = showstr;                               //显示
                    prior = tempBtn.Text.ToString();
                    equFlag = 2;
                }
                /*
                //屏蔽某些按钮
                finallybtn[0].Enabled = false;      //屏蔽 0     
                finallybtn[2].Enabled = false;      //屏蔽 =
                for (int i = 0; i < 3; i++)         //屏蔽 + - * /
                    operabtn[i].Enabled = false;
                operabtn2[0].Enabled = false;       //屏蔽%
                operabtn2[3].Enabled = false;       //屏蔽)
                operabtn3[1].Enabled = false;       //屏蔽 ^
                */
            }
            else if (tempBtn.Text.ToString() == "√")
            {
                str = str + "~";                                    //用于处理的字符串
                showstr = showstr + tempBtn.Text.ToString();        //用于显示的字符串
                Edit2.Text = showstr;                               //显示
                prior = tempBtn.Text.ToString();
                equFlag = 2;
            }
            else if (tempBtn.Text.ToString() == "(")
            {
                COpenParen++;
                str = str + tempBtn.Text.ToString();                    //用于处理的字符串
                showstr = showstr + tempBtn.Text.ToString();            //用于显示的字符串
                Edit2.Text = showstr;                                   //显示                                      
                prior = tempBtn.Text.ToString();
                equFlag = 2;                                            //不可使用"="
                parenFlag = 0;
            }
            else if (tempBtn.Text.ToString() == ")" && COpenParen != 0 && parenFlag!=0)
            {
                COpenParen--;
                str = str + tempBtn.Text.ToString();                    //用于处理的字符串
                showstr = showstr + tempBtn.Text.ToString();            //用于显示的字符串
                Edit2.Text = showstr;                                   //显示
                prior = tempBtn.Text.ToString();
                equFlag = 1;                                            //可以使用"="
            }
        }

        //等于号的处理事件
        private void equbutton_Click(object sender, EventArgs e)
        {
            //先进行清理屏幕
            double solution;
            if (equFlag != 2)
            {
                Edit1.Text = Edit2.Text;
                Edit2.Text = "";
                solution = solve(str);
                Edit2.Text = solution.ToString();
                str = "";
                showstr = "";
                equFlag = 1;   //避免使用"="
                COpenParen = 0;
            }
        }

        //sin符号的处理事件
        private void sin_Click(object sender, EventArgs e)
        {
            Button tempBtn = (Button)sender;
            if (prior != ".")
            {
                str = str + "s";
                showstr = showstr + tempBtn.Text.ToString();
                Edit2.Text = showstr;
                equFlag = 2;
            }

        }

        //cos符号的处理事件
        private void cos_Click(object sender, EventArgs e)
        {
            Button tempBtn = (Button)sender;
            if (prior != ".")
            {
                str = str + "c";
                showstr = showstr + tempBtn.Text.ToString();
                Edit2.Text = showstr;
                equFlag = 2;
            }
        }

        //清屏操作
        private void clear_Click(object sender, EventArgs e)
        {
            Edit1.Text = "";
            Edit2.Text = "";
            dotflag = 0;
            str = "";
            showstr = "";
        }

        //back按钮
        private void back_Click(object sender, EventArgs s)
        {
            if (Edit2.Text != "")
            {
                str = str.Substring(0, str.Length - 1);
                showstr = showstr.Substring(0, showstr.Length - 1);
                Edit2.Text = showstr;
            }
        }

        //当鼠标移动到当前按钮
        private void color_Move(object sender, EventArgs s)
        {
            Button tempBtn = (Button)sender;
            tempBtn.BackColor = ColorTranslator.FromHtml("#4B4B4B");
        }
        //当鼠标离开按钮
        private void color_Leave(object sender, EventArgs s)
        {
            Button tempBtn = (Button)sender;
            tempBtn.BackColor = ColorTranslator.FromHtml("#d2d8b7");
        }
    }
}

//加声音事件
//屏蔽无需按钮
//减少Bug
//加个框
//换个色
//0变长
