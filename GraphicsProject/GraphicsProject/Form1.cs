using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GraphicsProject
{

    public partial class Form1 : Form
    {
        Timer tt = new Timer();
        Bitmap off;
        Bitmap zumaFrog, rotfrog;
        Bitmap bg;
        PointF zumaPos, mousePoin;
        double angel, faceAngel;
        RectangleF destRectZumaFrog, srcRectZumaFrog, destRectFace, srcRectFace;
        BezCurve mycurve = new BezCurve();
        List<ball> balls = new List<ball>();
        PointF startcurve, endcurve;
        int dragindex;
        bool isDrag = false;
        int click = 0;
        bool editcurve = true;
        bool editzuma = false;
        public bool gamestart = false;
        bool makingnewballs = false;
        int counttick = 0;
        Bitmap skullopen, skullclosed, skull;
        PointF skullPos, myZumaClickPos;
        ball swapBall, tongueBall;
        List<ball> lineBall = new List<ball>();
        PointF toung, swap;

        public Form1()
        {
            this.WindowState = FormWindowState.Maximized;
            this.Load += Form1_Load;
            this.Paint += Form1_Paint;
            this.MouseMove += Form1_MouseMove;
            this.MouseDown += Form1_MouseDown;
            this.MouseUp += Form1_MouseUp;
            this.KeyDown += Form1_KeyDown;
            tt.Tick += Tt_Tick;
            tt.Start();
        }
        /////////////////////////////////////////////////////////////////////////// events
        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter && editcurve)
            {
                editcurve = false;
                editzuma = true;
                startcurve = mycurve.CalcCurvePointAtTime(0);
                endcurve = mycurve.CalcCurvePointAtTime(1);
            }
            if (e.KeyCode == Keys.B)
            {

            }
        }

        private void Form1_MouseUp(object sender, MouseEventArgs e)
        {
            isDrag = false;
            dragindex = -1;
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            if (!editcurve && !editzuma && gamestart && e.Button == MouseButtons.Left)
            {
                addBalltoBallLine(new PointF(e.X, e.Y));
            }
            else if (!editcurve && !editzuma && gamestart && e.Button == MouseButtons.Right)
            {
                switchBall();
            }
            if (editcurve)
            {
                if (e.Button == MouseButtons.Left)
                {
                    mycurve.LCtrPts.Add(new PointF(e.X, e.Y));
                }
                else
                {
                    for (int i = 0; i < mycurve.LCtrPts.Count; i++)
                    {
                        if (e.X > mycurve.LCtrPts[i].X - 5 && e.X < mycurve.LCtrPts[i].X + 5)
                        {
                            if (e.Y > mycurve.LCtrPts[i].Y - 5 && e.Y < mycurve.LCtrPts[i].Y + 5)
                            {

                                mycurve.LCtrPts[i] = new PointF(e.X, e.Y);
                                isDrag = true;
                                dragindex = i;
                            }
                        }
                    }
                }
            }
            if (editzuma)
            {
                putZuma(e.X, e.Y);
                editzuma = false;
                createskull(true);
                makingnewballs = true;
                gamestart = true;
                addTAndSBall(e.X, e.Y);
            }
            DrawDubb(this.CreateGraphics());
        }
        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            mousePoin = new PointF(e.X, e.Y);
            transformZuma();
            if (gamestart)
            {
                updateTAndSBall();
            }
            if (isDrag == true)
            {
                mycurve.LCtrPts[dragindex] = new PointF(e.X, e.Y);
            }


        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            DrawDubb(this.CreateGraphics());
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            off = new Bitmap(this.ClientSize.Width, this.ClientSize.Height);
            bg = new Bitmap("bg.jpg");
            skullclosed = new Bitmap("closed.jpg");
            skullopen = new Bitmap("open.jpg");
            zumaFrog = new Bitmap("zuma.png");
        }

        /////////////////////////////////////////////////////////////////////////// tick
        private void Tt_Tick(object sender, EventArgs e)
        {
            if (gamestart)
            {
                if (makingnewballs == true)
                {
                    if (balls.Count > 0)
                    {
                        float dis = getdistance(startcurve, balls.Last().pos);
                        if (dis >= 40)
                        {
                            createnewball();
                        }
                    }
                    else
                    {
                        createnewball();
                        counttick = 0;
                    }
                    if (balls.Count > 0)
                    {
                        if (balls.Count >= 15 || balls[0].time >= 0.5)
                        {
                            makingnewballs = false;
                        }
                    }
                }
                if (counttick % 10 == 0)
                {
                    moveballs(0, balls.Count, false);

                }
               /// if(counttick>11)
                //catchhabal();
            }
            updatelevel();
            moveBallInLine();
            counttick++;
         
            DrawDubb(this.CreateGraphics());
        }

        //////////////////////////////////////////////////////////////////////draw
        void DrawDubb(Graphics g)
        {
            Graphics g2 = Graphics.FromImage(off);
            DrawScene(g2);
            g.DrawImage(off, 0, 0);
        }
        void DrawScene(Graphics g)
        {
            g.Clear(Color.Black);
            mycurve.DrawYourSelf(g, !gamestart);
            if (!editcurve && !editzuma && gamestart)
            {
                /////////////////////////////////
                g.DrawLine(Pens.Red, zumaPos.X, zumaPos.Y, mousePoin.X, mousePoin.Y);
                g.DrawImage(skull, destRectFace, srcRectFace, GraphicsUnit.Pixel);
                /////////////////////////////////
                /// ///// draw balls
                for (int i = 0; i < balls.Count; i++)
                {
                    if (balls[i].draw)
                    {
                        g.DrawImage(balls[i].img,
                        new Rectangle((int)balls[i].pos.X - 20, (int)balls[i].pos.Y - 20, 40, 40),   //dest
                        new Rectangle(0, 0, balls[i].img.Width, balls[i].img.Height),   // source
                        GraphicsUnit.Pixel);
                        Font drawFont = new Font("Arial", 16);
                        g.DrawString("" + i, drawFont, Brushes.White, balls[i].pos);


                    }
                }
                g.DrawImage(rotfrog, destRectZumaFrog, srcRectZumaFrog, GraphicsUnit.Pixel);
                ///////////////////////////////////////////////////////////////////////////////////////////////
                g.DrawImage(tongueBall.img,
               new Rectangle((int)tongueBall.pos.X - 17, (int)tongueBall.pos.Y - 17, 35, 35),  // Dst
               new Rectangle(0, 0, tongueBall.img.Width, tongueBall.img.Height),  // sor
               GraphicsUnit.Pixel);
                g.DrawImage(swapBall.img,
               new Rectangle((int)swapBall.pos.X - 12, (int)swapBall.pos.Y - 12, 25, 25),  // Dst
               new Rectangle(0, 0, swapBall.img.Width, swapBall.img.Height),  // sor
               GraphicsUnit.Pixel);
                foreach (ball b in lineBall)
                {
                    g.DrawImage(b.img,
                    new Rectangle((int)b.pos.X - 35 / 2, (int)b.pos.Y - 35 / 2, 35, 35),  // Dst
                    new Rectangle(0, 0, b.img.Width, b.img.Height),  // sor
                    GraphicsUnit.Pixel);
                }

            }


        }
        ///////////////////////////////////////////////////////////////// our functions
        //void catchhabal()
        //{
        //    int k;
        //    for (k= 0; k < balls.Count-1; k++)
        //    {
        //        if( Math.Abs( balls[k+1].time- balls[k].time) < balls[k].speed)
        //        {
        //            break;
        //        }
        //    }

        //    if(k<balls.Count)
        //    {
        //        int end = findminindexinlevel(balls[k].level+1);
        //        for (int i = k; i < end; i++)
        //        {
                    
                  
        //                float nata = 1;
        //                while (true)
        //                {
        //                    if (getdistance(balls[i].pos, mycurve.CalcCurvePointAtTime(balls[i].time + balls[i].speed * nata)) < 40)
        //                    {
        //                        nata += 1;
        //                    }
        //                    else
        //                    {
        //                        break;
        //                    }
        //                }
        //                balls[i].time += balls[i].speed * nata;
        //                balls[i].pos = mycurve.CalcCurvePointAtTime(balls[i].time);

                    

        //        }
        //    }
        //}
        void addTAndSBall(int x, int y)
        {
            //toung
            float hi = zumaFrog.Width / 2;
            hi *= 200;
            hi /= zumaFrog.Width;
            hi += zumaPos.X - 100;
            float hi2 = zumaFrog.Height - (zumaFrog.Height / 5);
            hi2 *= 200;
            hi2 /= zumaFrog.Height;
            hi2 += zumaPos.Y - 100;
            //swap
            float hi3 = zumaFrog.Width / 2;
            hi3 *= 200;
            hi3 /= zumaFrog.Width;
            hi3 += zumaPos.X - 100;
            float hi4 = (zumaFrog.Height / 10);
            hi4 *= 200;
            hi4 /= zumaFrog.Height;
            hi4 += zumaPos.Y - 100;
            //add
            toung = new PointF(hi, hi2);
            swap = new PointF(hi3, hi4);
            Random r = new Random();
            int num = r.Next(5);
            tongueBall = new ball(num, toung);
            num = r.Next(5);
            swapBall = new ball(num, swap);

        }
        void updateTAndSBall()
        {
            tongueBall.pos = DoRotate(toung, new PointF(zumaPos.X, zumaPos.Y), (float)angel);
            swapBall.pos = DoRotate(swap, new PointF(zumaPos.X, zumaPos.Y), (float)angel);
        }
        void addBalltoBallLine(PointF endPoint)
        {
            tongueBall.Line = new DDALine((int)zumaPos.X, (int)zumaPos.Y, (int)endPoint.X, (int)endPoint.Y);
            lineBall.Add(tongueBall);
            tongueBall = new ball(swapBall.colorid, swapBall.pos);
            Random r = new Random();
            int num = r.Next(5);
            bool f = true;
            while (balls.Count>0 && f)
            {
                foreach (ball b in balls)
                {
                    if (b.colorid == num)
                    {
                        f = false;
                        break;
                    }
                }
                if (f)
                {
                    num = r.Next(5);
                }
            }
            swapBall = new ball(num, new PointF(zumaPos.X, zumaPos.Y));
        }
        void moveBallInLine()
        {
            for (int i = 0; i < lineBall.Count; i++)
            {
                int hitindex = -1;
                lineBall[i].pos = lineBall[i].Line.getnextpoint(lineBall[i].pos.X, lineBall[i].pos.Y);

                for (int j = 0; j < balls.Count; j++)
                {
                    if (balls[j].isHit(lineBall[i].pos))
                    {
                        hitindex = j;
                        this.Text += "," + j;
                        break;
                    }
                }
                if (hitindex != -1 && hitindex > 1 && hitindex != balls.Count - 1)
                {
                    if (balls[hitindex].colorid == lineBall[i].colorid)
                    {
                        if (balls[hitindex + 1].colorid == balls[hitindex].colorid)
                        {

                            changeLevel(hitindex);
                            lineBall.RemoveAt(i);
                            balls.RemoveAt(hitindex);
                            balls.RemoveAt(hitindex);

                        }
                        else if (balls[hitindex - 1].colorid == balls[hitindex].colorid)
                        {
                            changeLevel(hitindex - 1);
                            lineBall.RemoveAt(i);
                            balls.RemoveAt(hitindex - 1);
                            balls.RemoveAt(hitindex - 1);
                        }

                        else
                        {
                            updateBallsList(lineBall[i], hitindex);
                            lineBall.RemoveAt(i);
                        }
                    }
                    else if (balls[hitindex - 1].colorid == balls[hitindex - 2].colorid && balls[hitindex - 2].colorid == lineBall[i].colorid)
                    {
                        changeLevel(hitindex - 2);
                        lineBall.RemoveAt(i);
                        balls.RemoveAt(hitindex - 2);
                        balls.RemoveAt(hitindex - 2);
                    }
                    else
                    {
                        updateBallsList(lineBall[i], hitindex);
                        lineBall.RemoveAt(i);
                    }

                }
                else if (hitindex == 0&& balls.Count>1)
                {
                    if (balls[hitindex].colorid == lineBall[i].colorid)
                    {
                        if (balls[hitindex].colorid == balls[hitindex + 1].colorid)
                        {

                            lineBall.RemoveAt(i);
                            balls.RemoveAt(hitindex);
                            balls.RemoveAt(hitindex);

                        }

                        else
                        {
                            updateBallsList(lineBall[i], hitindex);
                            lineBall.RemoveAt(i);
                        }
                    }
                    else
                    {
                        updateBallsList(lineBall[i], hitindex);
                        lineBall.RemoveAt(i);
                    }
                }
                else if (hitindex == 1&& balls.Count >2)
                {
                    if (balls[hitindex].colorid == lineBall[i].colorid)
                    {
                        if (balls[hitindex].colorid == balls[hitindex - 1].colorid)
                        {

                            lineBall.RemoveAt(i);
                            balls.RemoveAt(hitindex);
                            balls.RemoveAt(hitindex);

                        }
                        else if (balls[hitindex].colorid == balls[hitindex + 1].colorid)
                        {
                            changeLevel(hitindex);
                            lineBall.RemoveAt(i);
                            balls.RemoveAt(hitindex);
                            balls.RemoveAt(hitindex);

                        }

                        else
                        {
                            updateBallsList(lineBall[i], hitindex);
                            lineBall.RemoveAt(i);
                        }
                    }
                    else
                    {
                        updateBallsList(lineBall[i], hitindex);
                        lineBall.RemoveAt(i);
                    }
                }
                else if (hitindex == balls.Count - 1&& balls.Count>1)
                {
                    if (balls[hitindex].colorid == lineBall[i].colorid)
                    {

                        if (balls[hitindex - 1].colorid == balls[hitindex].colorid)
                        {

                            lineBall.RemoveAt(i);
                            balls.RemoveAt(hitindex - 1);
                            balls.RemoveAt(hitindex - 1);
                        }

                        else
                        {
                            updateBallsList(lineBall[i], hitindex);
                            lineBall.RemoveAt(i);
                        }
                    }

                    else
                    {
                        updateBallsList(lineBall[i], hitindex);
                        lineBall.RemoveAt(i);
                    }
                }
                else if(balls.Count==1&& hitindex!=-1)
                {
                    updateBallsList(lineBall[i], hitindex);
                    lineBall.RemoveAt(i);    
                }
            }
        }
        void changeLevel(int index)
        {
            for (int i = 0; i <= index; i++)
            {
                balls[i].level++;
            }

        }
        void updatelevel()
        {
           /// one ball lebel 0
           /// one ball level 1 
           /// 0 --> 1
           /// 0 level 1
           /// 1 level 0
           if(balls.Count>0)
           {
                int i;
                /// min level must be level
                /// 2 3 4
                /// 0 1 2

                for (i = 0; i < balls.Count - 1; i++)
                {
                    if (balls[i].level != balls[i + 1].level &&
                        balls[i].level != balls[i + 1].level - 1)
                    {
                        if (getdistance(balls[i].pos, balls[i + 1].pos) < 40)
                        {
                            balls[i].level = balls[i + 1].level;

                        }
                        else
                        {
                            balls[i].level = balls[i + 1].level - 1;
                        }
                    }
                }
                if (balls.Last().level > 0)
                {
                    int oldlevl = balls.Last().level;
                    for (i = 0; i < balls.Count; i++)
                    {
                        balls[i].level -= oldlevl;
                    }
                }
                // minlvl0=find min index with level 1 
                // first lvl1 = find the minlvl0-1
                //if they hit
                // anything not level 0 --> lvl --

                /// 0 level 1
                /// 1 level 0
                int minlvl0 = findminindexinlevel(0);
                int miinlvl1 = findminindexinlevel(1);
       
               // i; //-1
             
                if(minlvl0 >0 && miinlvl1>=0)
                {
                    // 15 14 13   12 11 10 9   8 6 5 
                    if (getdistance(balls[minlvl0].pos, balls[minlvl0 - 1].pos) < 40)
                    {
                        for (int j = 0; j < balls.Count; j++)
                        {
                            if (balls[j].level != 0)
                            {
                                balls[j].level--;
                                this.Text += "," + j;

                            }
                        }

                        moveballs(miinlvl1 , minlvl0 , false);
                    }
                }
          


            }






            //////int i;
            //////for (i = balls.Count - 2; i >= 0; i--)
            //////{
            //////    /// 15 14 13 12 11 10 9 8  -- 0
            //////    if (balls[i].level > 0)
            //////    {
            //////        if (getdistance(balls[i].pos, balls[i + 1].pos) < 40)
            //////        {
            //////            balls[i].level = 0;
            //////            moveballs(i, i + 1, false);
            //////        }
            //////    }
            //////}

        }
        int findminindexinlevel(int level)
        {
            int minlvl = -1;
            for (int i = 0; i < balls.Count; i++)
            {
                if (balls[i].level == level)
                {
                    minlvl = i;
                    break;

                }
            }
            return minlvl;
        }
        void switchBall()
        {
            ball temp1 = new ball(tongueBall.colorid, tongueBall.pos);
            ball temp2 = new ball(swapBall.colorid, swapBall.pos);
            tongueBall = temp2;
            swapBall = temp1;
        }
        void createskull(bool open)
        {
            //293*319
            skullPos = new PointF(endcurve.X, endcurve.Y);
            if (open)
            {
                skull = skullopen;
            }
            else
            {
                skull = skullclosed;
            }
            PointF refrence = mycurve.CalcCurvePointAtTime(0.8f);
            faceAngel = ConvertToDegrees(Math.Atan2(refrence.Y - endcurve.Y, refrence.X - endcurve.X));
            faceAngel -= 90;
            skull = rotateImage(skull, (float)faceAngel);
            srcRectFace = new RectangleF(0, 0, skull.Width, skull.Height);
            destRectFace = new RectangleF(skullPos.X - 75, skullPos.Y - 75, 150, 150);
        }
        void putZuma(int x, int y)
        {
            myZumaClickPos = new PointF(x, y);
            zumaPos = new Point(x, y);
            destRectZumaFrog = new Rectangle(x - 100, y - 100, 200, 200);
            srcRectZumaFrog = new Rectangle(0, 0, zumaFrog.Width, zumaFrog.Height);
        }
        void transformZuma()
        {
            angel = ConvertToDegrees(Math.Atan2((mousePoin.Y - zumaPos.Y), (mousePoin.X - zumaPos.X)));
            angel -= 90;
            rotfrog = rotateImage(zumaFrog, (float)angel);
        }
        void createnewball()
        {
            Random r = new Random();
            int num = r.Next(5);
            if (balls.Count > 2)
            {
                while (num == balls[balls.Count - 1].colorid && balls[balls.Count - 1].colorid == balls[balls.Count - 2].colorid)
                {
                    num = r.Next(5);
                }
            }
            ball pnn = new ball(num, startcurve);
            balls.Add(pnn);

        }
        void moveballs(int start, int end, bool fmove)
        {   if(end > balls.Count)
            {
                MessageBox.Show("wtf");
            }
            for (int i = start; i < end; i++)
            {
                if (balls[i].level == 0 ||  (fmove && balls[end-1].level == balls[i].level) )
                {
                    if (balls[i].time >= 1)
                    {
                      //  tt.Stop();
                       // MessageBox.Show("you looooose!!!!!");
                    }
                    float nata = 1;
                    while (true)
                    {
                        if (getdistance(balls[i].pos, mycurve.CalcCurvePointAtTime(balls[i].time + balls[i].speed * nata)) < 40)
                        {
                            nata += 1;
                        }
                        else
                        {
                            break;
                        }
                    }
                    balls[i].time += balls[i].speed * nata;
                    balls[i].pos = mycurve.CalcCurvePointAtTime(balls[i].time);

                }

            }
        }
        public void updateBallsList(ball newball, int hitindex)
        {
            float nata = 1;
            while (true)
            {
                if (getdistance(balls[hitindex].pos,
                    mycurve.CalcCurvePointAtTime(balls[hitindex].time + balls[hitindex].speed * nata)) < 40)
                {
                    nata += 1;
                }
                else
                {
                    break;
                }
            }
            newball.time = balls[hitindex].time + (balls[hitindex].speed * nata);
            newball.pos = mycurve.CalcCurvePointAtTime(newball.time);
            if (hitindex != 0)
            {
                moveballs(0, hitindex, true);
            }
            newball.level = balls[hitindex].level;
            balls.Insert(hitindex, newball);
            updatelevel();
        }
        public double ConvertToRadians(double angle)
        {
            return (Math.PI / 180) * angle;
        }
        public double ConvertToDegrees(double angle)
        {
            return (180 * angle) / Math.PI;
        }
        public float getAngle(PointF p1, PointF p2)
        {
            float xDiff = p2.X - p1.X;
            float yDiff = p2.Y - p1.Y;
            return (float)(Math.Atan2(yDiff, xDiff) * (180 / Math.PI));
        }
        public float getdistance(PointF p1, PointF p2)
        {
            float dis;
            double a = Math.Pow(Math.Abs(p2.X - p1.X), 2);
            double b = Math.Pow(Math.Abs(p2.Y - p1.Y), 2);
            dis = (float)Math.Sqrt(a + b);
            return dis;
        }
        public Bitmap rotateImage(Bitmap b, float angle)
        {

            int maxside = (int)(Math.Sqrt(b.Width * b.Width + b.Height * b.Height));

            //create a new empty bitmap to hold rotated image

            Bitmap returnBitmap = new Bitmap(maxside, maxside);

            //make a graphics object from the empty bitmap

            Graphics g = Graphics.FromImage(returnBitmap);

            //move rotation point to center of image

            g.TranslateTransform(b.Width / 2, b.Height / 2);

            //rotate

            g.RotateTransform(angle);

            //move image back

            g.TranslateTransform(-b.Width / 2, -b.Height / 2);

            //draw passed in image onto graphics object

            g.DrawImage(b, new Point(0, 0));



            return returnBitmap;

        }
        PointF DoRotate(PointF pMe, PointF pRef, float th)
        {
            PointF me2 = new PointF();
            me2.X = pMe.X - pRef.X;
            me2.Y = pMe.Y - pRef.Y;
            th = (float)ConvertToRadians(th);
            PointF me3 = new PointF();
            me3.X = (float)(me2.X * Math.Cos(th) - me2.Y * Math.Sin(th));
            me3.Y = (float)(me2.X * Math.Sin(th) + me2.Y * Math.Cos(th));

            pMe.X = me3.X + pRef.X;
            pMe.Y = me3.Y + pRef.Y;
            return pMe;
        }
    }

    public class ball
    {
        public PointF pos;
        public DDALine Line;
        public float speed;
        public int colorid;
        public Bitmap img;
        public int index; // new space // check index ba3do change level
                          // sab2enn 1
                          // rest move level 0 
        public int level; // condition 0 => move
                          // new space (below index) sap2een => level 1 
        public bool draw;
        public float time;
        public ball(int cid, PointF p)
        {
            speed = 0.001f;
            time = 0;
            colorid = cid;
            // index = i;
            level = 0;
            draw = true;
            pos = p;

            if (cid == 0)
            {
                img = new Bitmap("blue.png");

            }
            else
            {
                if (cid == 1)
                {
                    img = new Bitmap("green.png");
                }
                else
                {
                    if (cid == 2)
                    {
                        img = new Bitmap("purple.png");
                    }
                    else
                    {
                        if (cid == 3)
                        {
                            img = new Bitmap("red.png");
                        }
                        else
                        {
                            img = new Bitmap("yellow.png");
                        }
                    }
                }
            }
            img.MakeTransparent(img.GetPixel(0, 0));


        }
        public bool isHit(PointF p)
        {

            if (pos.X - 20 <= p.X &&
                pos.X + 20 >= p.X &&
                pos.Y - 20 <= p.Y &&
                pos.Y + 20 >= p.Y
               )
            {



                return true;

            }

            return false;
        }


    }


}
