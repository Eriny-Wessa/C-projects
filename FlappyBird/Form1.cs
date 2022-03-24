using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Text;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FlappyBird
{
    public class background
    {
        public int x, y, w, h;
        public Bitmap img;
        public background()
        {
            img = new Bitmap("bg.png");
            h = img.Height;
            w = img.Width;
        }
    }
    public class pipe
    {
        public int x, y, w, h ,dh;
        public Bitmap img;
        public bool pass = false;
        public bool up=false;
        public pipe(int i)
        {
            if(i==1) // up
            {
                up = true;
                img = new Bitmap("pu.png");
                h = img.Height;
                w = img.Width;

            }
            if (i==2) // down
            {
                img = new Bitmap("pd.png");
                h = img.Height;
                w = img.Width;

            }
        }
    }
    public class Bird
    {
        public int x, y, w, h ,dh,dw;
        public Bitmap img;
        public List<Bitmap> imgs = new List<Bitmap>();
        public bool dead = false;
        public Bird()
        {
            dh = 100;
            dw = 100;
            for (int i = 1; i < 9; i++)
            {
                Bitmap pnn = new Bitmap("" + i + ".png");
                imgs.Add(pnn);
            }

            img = imgs[0];
            w = img.Width;
            h = img.Height;
        }
        public void next()
        {
            for (int i = 0; i < 8; i++)
            {
                if(img==imgs[i])
                {
                    if(i==7)
                    {
                        img = imgs[0];
                    }
                    else
                    {
                        img = imgs[i + 1];
                        break;
                    }
                }
            }
            w = img.Width;
            h = img.Height;

        }
    }
    public partial class Form1 : Form
    {
        Bitmap off;
        public int scroe = 0, hscroe = 0;
        public int ac = 0;

        public int wbg = 350 , scroll=10,backct;
        public int stat = 1; 
        /// <summary>
        ///  1 = start menue
        ///  2 = game
        ///  3 = death screen
        /// </summary>
     
        public List<background> bg = new List<background>();
        public List<pipe> p = new List<pipe>();
        public Bird bird = new Bird();
        public bool jump = false; 
        Random rr = new Random();
        public int wpipe = 100;
        public bool rest = false;
        public int space = 200;
        Timer tt = new Timer();
        int inter;
        public Form1()
        {
            WindowState = FormWindowState.Maximized;
            this.Load += new EventHandler(Form1_Load);
            this.Paint += new PaintEventHandler(Form1_Paint);
            KeyDown += Form1_KeyDown;
            tt.Tick += Tt_Tick;
            tt.Interval = 200;
            tt.Start();
           inter =tt.Interval;
            backct = 0;
        }
    
        private void Tt_Tick(object sender, EventArgs e)
        {
            if (backct %3==0)
            {
                movebg();

            }
            if(stat==2)
            {
                if (backct % 40 == 0)
                {
                    Creat_Pipe();
                }
                move_pipe();
                for (int i = 0; i < p.Count; i++)
                {
                    if(bird.x> p[i].x+wpipe+5)
                    {
                        if(p[i].up && !p[i].pass)
                        {
                            scroe++;
                            p[i].pass = true;
                        }
                    }
                }
                move_bird(10);
                Hit();
            }
            if(stat==2 || stat ==1)
            {
                bird.next();
            }
            if(stat==3)
            {
                if(!rest)
                {
                    grav_bird();
                }
               
            }
            
            // check if (pip ! passed and pip is up and the bird y > pip y +pip w) then ( score++ pip paseed)
       
           
            DrawDubb(this.CreateGraphics());

            backct++;
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.KeyCode==Keys.M)
            {
                if (stat == 3)
                {
                    set_stat(1);
                }
            }
            if (e.KeyCode == Keys.R)
            {
                set_stat(1);
                hscroe = 0;
            }
            if (e.KeyCode == Keys.Space)
            {
                if(stat==1)
                {
                    set_stat(2);
                   
                }
                else
                {
                    if (stat==2)
                    {
                        jump = true;
                    }
                    else
                    {
                        //
                    }
                }

            }
        }


        void Form1_Paint(object sender, PaintEventArgs e)
        {
            DrawDubb(e.Graphics);
        }

        void Form1_Load(object sender, EventArgs e)
        {
            off = new Bitmap(ClientSize.Width, ClientSize.Height);
            Creat_BG();
            Creat_bird();
        }

        void DrawScene(Graphics g)
        {
            g.Clear(Color.Black);
            
            for (int i = 0; i < bg.Count; i++)
            {
                g.DrawImage(bg[i].img,
                new Rectangle(bg[i].x, bg[i].y, wbg, ClientSize.Height),  // Dst
                new Rectangle(0,0, bg[i].w, bg[i].h),  // sor
                GraphicsUnit.Pixel);

            }
            if(stat==1)
            {
              
                FontFamily fontFamily = new FontFamily("Comic Sans MS");
                Font font = new Font(
                   fontFamily,
                   50,
                   FontStyle.Bold,
                   GraphicsUnit.Pixel);

                SolidBrush b = new SolidBrush(Color.Black);
                g.DrawString("Flappy Bird", font, b, ClientSize.Width/2 -150 , 100);
                g.DrawString("Press Space", font, b, ClientSize.Width / 2 - 150, 400);
                g.DrawString("To Jump", font, b, ClientSize.Width / 2 - 150+30, 500);

            }
            if(stat==2|| stat==3)
            {
               

                /// draw scoore
                for (int i = 0; i < p.Count; i++)
                {
                    g.DrawImage(p[i].img,
                    new Rectangle(p[i].x, p[i].y, wpipe, p[i].dh),  // Dst
                    new Rectangle(0, 0, p[i].w, p[i].h),  // sor
                    GraphicsUnit.Pixel);
                }

              
            }
            if (stat == 3)
            {

                FontFamily fontFamily = new FontFamily("Comic Sans MS");
                Font font = new Font(
                   fontFamily,
                   50,
                   FontStyle.Bold,
                   GraphicsUnit.Pixel);

                SolidBrush b = new SolidBrush(Color.Black);
                g.DrawString("High Score: " + hscroe, font, b, ClientSize.Width / 2 - 150, 100);
                g.DrawString("Your Score: " + scroe, font, b, ClientSize.Width / 2 - 150, 200);
                g.DrawString("Press Space", font, b, ClientSize.Width / 2 - 150, 400);
                g.DrawString("To Try Again", font, b, ClientSize.Width / 2 - 180 + 30, 500);

            }

            if (stat==2)
            {
                FontFamily fontFamily = new FontFamily("Comic Sans MS");
                Font font = new Font(
                   fontFamily,
                   50,
                   FontStyle.Bold,
                   GraphicsUnit.Pixel);

                SolidBrush b = new SolidBrush(Color.WhiteSmoke);
                g.DrawString("Your Score: " + scroe, font, b, 20, 20);
            }
            g.DrawImage(bird.img,
                   new Rectangle(bird.x, bird.y, bird.dw,bird.dh),  // Dst
                   new Rectangle(0, 0, bird.w, bird.h),  // sor
                   GraphicsUnit.Pixel);
        }

        void DrawDubb(Graphics g)
        {
            Graphics g2 = Graphics.FromImage(off);
            DrawScene(g2);
            g.DrawImage(off, 0, 0);
        }

        public void set_stat(int s)
        {
            stat = s;
            if( s==1)
            {
               
                p.Clear();
                Creat_bird();
                bird.dead = false;
                rest = false;
                scroe = 0;
            }
            if(s==2)
            {
                p = new List<pipe>();
            }
            if(s==3)
            {
                if(scroe> hscroe)
                {
                    hscroe = scroe;
                }
            }
        }

        public void Creat_BG()
        {
            double sx = -1 * ClientSize.Width * 0.5;
            double ex = this.ClientSize.Width * 1.5;
            int x = Convert.ToInt32(sx);

            while (x<ex)
            {
                background pnn = new background();
                pnn.x = x;
                pnn.y = 0;

                x += wbg;
                bg.Add(pnn);

            }
        }
        public void movebg()
        {
            double sx = -1 * ClientSize.Width * 0.5;
            double ex = this.ClientSize.Width * 1.5;
            int x=0;
            for (int i = 0; i < bg.Count; i++)
            {
                bg[i].x -= scroll;
                if(bg[i].x<sx && bg[i].x+bg[i].w < -10)
                {
                    bg.RemoveAt(i);
                }
            }
            x = bg[bg.Count - 1].x;
            x += wbg;
            if(x<ex)
            {
                background pnn = new background();
                pnn.x = x;
                pnn.y = 0;

                bg.Add(pnn);

            }
         
        }
        public void Creat_Pipe()
        {
            pipe pnn = new pipe(1);
            int rs = rr.Next(wpipe/2, ClientSize.Height - wpipe*2);
            int re = rs + space;
            pnn.x = ClientSize.Width + 10;
            pnn.y = rs-pnn.h/2;
            
             pnn.dh = rs-pnn.y;
            int dh = pnn.dh;
            p.Add(pnn);
            pnn = new pipe(2);
            pnn.x = ClientSize.Width + 10;
            pnn.y = re;
           pnn.dh = dh;
            p.Add(pnn);
            /// rs is randomw=e space start 
            /// re = random space end;


        }
        public void move_pipe()
        {
            for (int i = 0; i < p.Count; i++)
            {
                p[i].x -= 10;
                if(p[i].x+p[i].w<-10)
                {
                    p.RemoveAt(i);
                }
            }
        }
        public void Creat_bird()
        {
            
            bird.x = 150;
            bird.y = ClientSize.Height / 2 - bird.dh/2;
        }
        public void grav_bird()
        {
            if (bird.y + bird.dw > ClientSize.Height - 20)
            {
               rest=true;
            }
            bird.y += 40;
        }
        public void move_bird(int k)
        {
            if(jump==true)
            {
                bird.y -= k*2;
                jump = false;
                ac = 1;
            }
            else
            {
                
                bird.y += k+ac;
                ac++;
            }
        }
        public void Hit()
        {
            for (int i = 0; i < p.Count; i++)
            {
                // face into the pipe
                if(bird.x+bird.dw >= p[i].x && bird.x + bird.dw < p[i].x+ wpipe 
                    && bird.y >=p[i].y && bird.y< p[i].y+p[i].dh)
                {
                    bird.dead = true;
                    break;
                }
                
                if(bird.x+bird.dw >=p[i].x && bird.x <p[i].x+wpipe) // x check
                {
                    if(bird.y >= p[i].y && bird.y <= p[i].y + p[i].dh && p[i].up) // upper into pipe
                    {
                        bird.dead = true;
                        break;
                    } 
                    if(bird.y+bird.dw >= p[i].y && bird.y+bird.dw <= p[i].y + p[i].dh && !p[i].up) //lower to pipe
                    {
                        bird.dead = true;
                        break;
                    }
                }


            }

            if (bird.y <= 0)
            {
                bird.dead = true;
            }
            if(bird.y+bird.dw >ClientSize.Height-10)
            {
                bird.dead = true;
            }

            if (bird.dead == true)
            {
                set_stat(3);
            }



        }

    }
}
