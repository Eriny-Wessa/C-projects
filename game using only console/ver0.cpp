#include <iostream>
#include <conio.h> 
using namespace std;
#define h 37
#define w 160
#define H 37*10
#define W 160*10

struct map
{
	int a = 0, b = 0;
	int scroll = 0;
	////////////////////////////////////////////////////////////////////////////////////////scroll
	int rp = 1, cp = 60;
	int wayp = 2;
	int delay = 0;
	int stp=50;
	int fip=200;
	///////////////////////////////////////////////////////////////////////////////////////plane position
	int dead_hero=0;
	int shape = 2;
	int firstRow = 8;
	int firstCoulmn =3;
	int lastRow;
	int lastCoulmn;
	int steps;
	////////////////////////////////////////////////////////////////////////////////////////hero status
	signed  leftgun[8][22] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','(','/','T','\\',')',' ',' ',' ',
	' ','_','_','_','_','_','_',',','_',' ',' ',' ',' ',' ','(','0',',',' 0',')',' ',' ',' ',
	'"','-','-','=','=','.',' ',' ',' ','\\',' ',' ',' ',' ','\\','(','_',')','/',' ',' ',' '
	,' ',' ',' ',' ',' ',' ','`','-',')','#','\\',' ','=','=','=','`','"','`','=','\\',' ',' ',
	' ',' ',' ',' ',' ',' ',' ',' ','`','-','`',' ',' ',' ','|',' ',' ',' ','|','\\','\\',' ',
	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','L','L','L','L','L',' ','\\','\\',
	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', '|','|',' ','|','|',' ',' ','W',
	' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','C','_',')',' ','(','_','D',' ',' ' };
	signed rigtGun[8][22] = {
	' ',' ',' ','(','/','T','\\',')',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
	' ',' ',' ','(','0',',','0',')',' ',' ',' ',' ',' ','_','_',',','_','_','_','_','_',' ',
	' ',' ',' ','\\','(','_',')','/',' ',' ',' ',' ','/',' ',' ','_','.','=','=','-','-','"',
	' ',' ','/','=','`','"','`','=','=','=',' ','/','#','(','-','`',' ',' ',' ',' ',' ',' ',
	' ','/','/','|',' ',' ',' ','|',' ',' ',' ','`','-','`',' ',' ',' ',' ',' ',' ',' ',' ',
	'/','/',' ','L','L','L','L','L',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
	'W',' ',' ','|','|',' ','|','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
	' ',' ','D','_',')',' ','(','_' ,'C',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', };
	char mainshape[h][w];
	char BIG_GAME[h][W];
	char planeR[6][14] = { ' ',' ',' ',' ',' ',' ',' ','_','_',' ',' ',' ',' ',' ',
		' ','_',' ','_',' ',' ',' ','\\',' ',' ','\\',' ',' ',' ',
		'\\',' ','/','\\','_','_','_',' ','\\','*','*','\\',' ',' ','\\',
		'_','\\','^','^','+','*','#','#','#','#','#','X','*',' ',
		' ',' ',' ',' ',' ',' ',' ','\\',' ',' ','\\','/','o',' ',
		' ',' ',' ',' ',' ',' ',' ',' ','\\','_','_','\\',' ' };
	char planeL[6][14] = { ' ','_','_',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
		' ','\\',' ',' ','\\',' ',' ',' ',' ',' ','_',' ','_',' ',
		' ',' ','\\','*','*','\\',' ','_','_','_','\\','/',' ','\\',
		'X','*','#','#','#','#','#','*','+','^','^','\\','_','\\',
		' ',' ','o','/','\\',' ',' ','\\',' ',' ',' ',' ',' ',' ',
		' ',' ',' ',' ',' ','\\','_','_','\\',' ',' ',' ',' ',' ' };

	char cloud1[6][29] =
	{ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.','-','~','~','~','-','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
' ',' ','.','-',' ','~',' ','~','-','(',' ',' ',' ',' ',' ',' ',' ',')','_',' ','_',' ',' ',' ',' ',' ',' ',' ',' ',
' ','/',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','~',' ','-','.',' ',' ',
'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\\',
' ','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.','"',
' ',' ',' ','~','-',' ','.',' ','_','_','_','_','_','_','_','_','_','_','_','_','_',' ','.',' ','-','~',' ',' ',' ',
	};
	char cloud2[6][29] =
	{
		' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.','-','~','~','~','-','.',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
' ',' ','.','-',' ','~',' ','~','-','(',' ',' ',' ',' ',' ',' ',' ',')','_',' ','_',' ',' ',' ',' ',' ',' ',' ',' ',
' ','/',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','~',' ','-','.',' ',' ',' ',
'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','"',',',
' ','\\',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','.','"',
' ',' ',' ','~','-',' ','.','_',' ',',','.',' ',',','.',',','.',',','.',',',' ',',','.','.',' ','-','~',' ',' ',' ',

	};

	map()
	{
		int r, c;
		for (r = 0; r < h; r++)
		{
			for (c = 0; c < W; c++)
			{
				BIG_GAME[r][c] = ' ';
			}
		}


	}
	void draw_wall()
	{
		int r, c,i,k,l,j;
		for (r = h - 15; r < h - 1; r++)
		{
			for (c = 78; c <= 100; c++)
			{
				BIG_GAME[r][c] = '#';
			}
		}
		for (r = h - 10; r < h - 1; r++)
		{
			for (c = 58; c <= 78; c++)
			{
				BIG_GAME[r][c] = '#';
			}
		}
		for (r = h - 15; r < h - 1; r++)
		{
			for (c = 78 + 200; c <= 100 + 200; c++)
			{
				BIG_GAME[r][c] = '#';
			}
		}
		for (r = h - 10; r < h - 1; r++)
		{
			for (c = 58 + 200; c <= 78 + 200; c++)
			{
				BIG_GAME[r][c] = '#';
			}
		}


	}
	void draw_clouds()
	{
		int r = 1, c = 1, i, k, l, j;
		for (i = 0; i < 40; i++)
		{

			for (k = 0; k < 6; k++)
			{
				l = 0;
				for (j = 0; j < 29; j++)
				{
					if (i % 2 == 0)
					{
						BIG_GAME[r][c + l] = cloud1[k][j];
					}
					else
					{
						BIG_GAME[r][c + l] = cloud2[k][j];
					}
					l++;
				}
				r++;
			}
			r = 1;


			c += 39;

		}
	}
	void SetOurMat()
	{
		for (int r = 0; r < h; r++)
		{
			for (int c = 0; c < w; c++)
			{
				mainshape[r][c] = ' ';
			}
		}

		for (int r = 0; r < h; r++)
		{
			int s = scroll;
			for (int c = 0; c < w; c++)
			{
				mainshape[r][c] = BIG_GAME[r][s];
				s++;
			}
		}

		for (int i = 0; i < w; i++)
		{

			mainshape[0][i] = '*';
			mainshape[h - 1][i] = '*';
		}
		for (int i = 0; i < h; i++)
		{
			mainshape[i][0] = '*';
			mainshape[i][w - 1] = '*';
		}
		cout_mat_to_screen();
	}
	void cout_mat_to_screen()
	{
		system("cls");
		cout << firstRow << "," << firstCoulmn << "    " << scroll<<endl;
		for (int r = 0; r < h; r++)
		{
			for (int c = 0; c < w; c++)
			{
				cout << mainshape[r][c];
			}
		}
		
		
	}
	void move_hero(char kb, int level)
	{

		steps = 0;
		int s;
		if (!stop)
		{
			if (kb == 'A' || kb == 'a')
			{
				s = solid('a');
				if (s)
				{
					if (firstCoulmn == 69 && scroll == 0)
					{
						firstCoulmn -= 3;
						steps = 3;
						if (pick)
						{
							for (int r = rs; r < rs + 7; r++)
							{
								BIG_GAME[r][cs] = ' ';
							}
							cs -= 2;
						}
					}
					else
					{
						if (firstCoulmn < 69)
						{
							if (firstCoulmn - 3 > 0)
							{
								firstCoulmn -= 3;
								steps = 3;
								if (pick)
								{
									for (int r = rs; r < rs + 7; r++)
									{
										BIG_GAME[r][cs] = ' ';
									}
									cs -= 3;
								}
							}
							else
							{
								if (firstCoulmn - 1 > 0)
								{
									steps = 1;
									firstCoulmn--;
									if (pick)
									{
										for (int r = rs; r < rs + 7; r++)
										{
											BIG_GAME[r][cs] = ' ';
										}
										cs -= 1;
									}
								}
							}
						}
						else
						{
							if (scroll - 3 >= 0)
							{
								scroll -= 3;
								steps = 3;
								firstCoulmn -= 3;
								if (pick)
								{
									for (int r = rs; r < rs + 7; r++)
									{
										BIG_GAME[r][cs] = ' ';
									}
									cs -= 3;
								}
							}
							else
							{
								if (scroll - 1 >= 0)
								{
									scroll--;
									steps = 1;
									firstCoulmn--;
									if (pick)
									{
										for (int r = rs; r < rs + 7; r++)
										{
											BIG_GAME[r][cs] = ' ';
										}
										cs--;
									}
								}
							}

						}
					}
					shape = 1;
					if (s == 2)
					{
						dead_hero = 1;
					}
				}
			}
			if (kb == 'D' || kb == 'd')
			{
				s = solid('d');
				if (s)
				{
					if (firstCoulmn < 69)
					{
						if (firstCoulmn + 3 < 70)
						{
							firstCoulmn += 3;
							steps = 3;
							if (pick)
							{
								for (int r = rs; r < rs + 7; r++)
								{
									BIG_GAME[r][cs] = ' ';
								}
								cs += 3;
							}
						}
						else
						{
							firstCoulmn++;
							steps = 1;
							if (pick)
							{
								for (int r = rs; r < rs + 7; r++)
								{
									BIG_GAME[r][cs] = ' ';
								}
								cs++;
							}
						}
					}
					else
					{
						if (scroll + 3 < w * 90)
						{
							scroll += 3;
							firstCoulmn += 3;
							steps = 3;
							if (pick)
							{
								for (int r = rs; r < rs + 7; r++)
								{
									BIG_GAME[r][cs] = ' ';
								}
								cs += 3;
							}
						}
						else
							if (scroll + 1 < w * 90)
							{
								scroll++;
								firstCoulmn++;
								steps = 1;
								if (pick)
								{
									for (int r = rs; r < rs + 7; r++)
									{
										BIG_GAME[r][cs] = ' ';
									}
									cs++;
								}
							}
					}
					shape = 2;

					if (s == 2)
					{
						dead_hero = 1;
					}
				}
			}
			if (kb == 'W' || kb == 'w')
			{
				s = solid('w');
				if (s)
				{
					if (firstRow - 3 > 6)
					{
						firstRow -= 3;
						steps = 3;
						if (pick)
						{
							for (int r = rs; r < rs + 7; r++)
							{
								BIG_GAME[r][cs] = ' ';
							}
							rs -= 3;
						}
					}
					if (s == 2)
					{
						dead_hero = 1;
					}
				}
			}
			if (kb == 'S' || kb == 's')
			{
				s = solid('s');
				if (s)
				{
					if (firstRow + 9 < h)
					{
						firstRow++;
						steps = 1;
						if (pick)
						{
							for (int r = rs; r < rs + 7; r++)
							{
								BIG_GAME[r][cs] = ' ';
							}
							rs++;
						}

					}
					if (s == 2)
					{
						dead_hero = 1;
					}
				}

			}
		}
	
		lastCoulmn = firstCoulmn + 22;
		lastRow = firstRow + 8;
		
		draw_hero(kb);
		if (level != 2)
		{
			if (kb == ' ')
			{
				fire(1);
			}
		}
		if (kb == ' ')
		{
			fire(1);
		}
		if (kb == 'r' || kb == 'R')
		{
			dead_hero = 1;
		}
	}
	void draw_hero(char kb)
	{
		if (kb == 'A' || kb == 'a')
		{
			
			for (int r = firstRow; r < firstRow + 8; r++)
			{
				for (int c = lastCoulmn; c < lastCoulmn + steps; c++)
				{
					BIG_GAME[r][c] = ' ';
				}
			}
		}
		if (kb == 'D' || kb == 'd')
		{
			for (int r = firstRow; r < firstRow + 8; r++)
			{
				for (int c = firstCoulmn - steps; c < firstCoulmn; c++)
				{
					BIG_GAME[r][c] = ' ';
				}
			}
		}
		if (kb == 'W' || kb == 'w')
		{
			for (int r = lastRow; r < lastRow + steps; r++)
			{
				for (int c = firstCoulmn; c < firstCoulmn + scroll + 22; c++)
				{
					BIG_GAME[r][c] = ' ';
				}
			}
		}
		if (kb == 'S' || kb == 's')
		{
			for (int r = firstRow - steps; r < firstRow; r++)
			{
				for (int c = firstCoulmn; c < firstCoulmn + scroll + 22; c++)
				{
					BIG_GAME[r][c] = ' ';
				}
			}
		}


		if (shape == 1)
		{
			a = 0, b = 0;
			for (int r = firstRow; r < firstRow + 8; r++)
			{
				b = 0;
				for (int c = firstCoulmn; c < firstCoulmn+22; c++)
				{
					BIG_GAME[r][c] = leftgun[a][b];
					b++;
				}
				a++;
			}
		}
		if (shape == 2)
		{
			a = 0, b = 0;
			for (int r = firstRow; r < firstRow + 8; r++)
			{
				b = 0;
				for (int c = firstCoulmn; c < firstCoulmn+ 22; c++)
				{
					BIG_GAME[r][c] = rigtGun[a][b];
					b++;
				}
				a++;
			}

		}
	}
	// 1move 2dies 0dont move
	int solid(char kb)
	{


		int flag = 0;

		if (pick)
		{
			return 1;
		}

		// 8*22
		if (kb == 'A' || kb == 'a')
		{
			for (int r = firstRow; r < firstRow + 8; r++)
			{
				for (int c = firstCoulmn - 1; c > firstCoulmn - 4; c--)
				{
					if (BIG_GAME[r][c] != ' '&& BIG_GAME[r][c]!=0)
					{
						flag++;
						// sad face
					}
					if (BIG_GAME[r][c] == '>' || BIG_GAME[r][c] == '<')
					{
						return 2;
					}
				}
			}
			if (flag == 0)
			{
				return 1;
			}

		}
		if (kb == 'D' || kb == 'd')
		{
			for (int r = firstRow; r < firstRow + 8; r++)
			{
				for (int c = firstCoulmn + 22; c < firstCoulmn + 25; c++)
				{
					if (BIG_GAME[r][c] != ' '&& BIG_GAME[r][c] != 0)
					{
						flag++;
						// sad face
					}
					if (BIG_GAME[r][c] == '>' || BIG_GAME[r][c] == '<')
					{
						return 2;
					}
				}
			}
			if (flag == 0)
			{
				return 1;
			}
		}
		if (kb == 'W' || kb == 'w')
		{
			for (int r = firstRow - 3; r < firstRow; r++)
			{
				for (int c = firstCoulmn; c < firstCoulmn + 22; c++)
				{
					if (BIG_GAME[r][c] != ' '&& BIG_GAME[r][c] != 0)
					{
						flag++;
						// sad face
					}

					if (BIG_GAME[r][c] == '>' || BIG_GAME[r][c] == '<')
					{
						return 2;
					}
				}

			}
			if (flag == 0)
			{
				return 1;
			}

		}
		if (kb == 'S' || kb == 's')
		{
			for (int r = firstRow + 8; r < firstRow + 8 + 1; r++)
			{
				for (int c = firstCoulmn; c < firstCoulmn + 22; c++)
				{
					if (BIG_GAME[r][c] != ' '&& BIG_GAME[r][c] != 0)
					{
						flag++;
						// sad face
					}

					if (BIG_GAME[r][c] == '>' || BIG_GAME[r][c] == '<')
					{
						return 2;
					}
				}
			}

			if (flag == 0)
			{
				return 1;
			}

		}
		return 0;


	}
	void fire(int _new_)
	{
		if (_new_)
		{
			if (shape == 1)
			{
				BIG_GAME[firstRow + 3][firstCoulmn - 1] = '<';
			}
			if (shape == 2)
			{
				BIG_GAME[firstRow + 3][firstCoulmn  + 22] = '>';
			}
		}
		else
		{
			for (int r = 0; r < h; r++)
			{
				for (int c = 0; c < 800; c++)
				{
					if (BIG_GAME[r][c] == '>')
					{
						if (BIG_GAME[r][c + 1] == ' ')
						{
							BIG_GAME[r][c] = ' ';
							BIG_GAME[r][c + 1] = '>';
							c++;
						}
						else
						{
						
							if (BIG_GAME[r][c + 1] == '#'|| BIG_GAME[r][c + 1] == '0')
							{
								
								BIG_GAME[r][c] = ' ';

							}
						}

					}

				}
			}

			for (int r = h; r > 0; r--)
			{
				for (int c = scroll + w * 2; c > 0; c--)
				{
					if (BIG_GAME[r][c] == '<')
					{
						if (BIG_GAME[r][c - 1] == ' ')
						{
							BIG_GAME[r][c] = ' ';
							BIG_GAME[r][c - 1] = '<';
							c--;
						}
						else
						{
						
							if (BIG_GAME[r][c - 1] == '#' || BIG_GAME[r][c + 1] == '0')
							{
								BIG_GAME[r][c] = ' ';
								
							}
						}
					}
				}
			}
		}
		for (int r = 0; r < h; r++)
		{
			for (int c = 0; c < 800; c++)
			{
				if (BIG_GAME[r][c] == '>' || BIG_GAME[r][c] == '<')
				{
					dead_hero=hithero(r, c);
				}
			}
		}
	}
	
	void planes()
	{
		delay++;
		int r, c, cc = 0;
		if (cp == stp || cp == stp + 1)
		{
			wayp = 1;

		}
		if (cp == fip || cp == fip + 1)
		{
			wayp = 2;
		}
		if (wayp == 1)
		{
			cp += 2;
			for (r = rp; r < rp + 6; r++)
			{
				for (c = cp - 2; c < cp; c++)
				{
					BIG_GAME[r][c] = ' ';
				}
			}
			int a = 0, b = 0;
			for (r = rp; r < rp + 6; r++)
			{
				b = 0;
				for (c = cp; c < cp + 14; c++)
				{
					BIG_GAME[r][c] = planeR[a][b];
					b++;
				}
				a++;
			}
		}
		if (wayp == 2)
		{
			cp -= 2;
			for (r = rp; r < rp + 6; r++)
			{
				for (c = cp + 14; c < cp + 14 + 2; c++)
				{
					BIG_GAME[r][c] = ' ';
				}
			}
			int a = 0, b = 0;

			for (r = rp; r < rp + 6; r++)
			{
				b = 0;
				for (c = cp; c < cp + 14; c++)
				{
					BIG_GAME[r][c] = planeL[a][b];
					b++;
				}
				a++;
			}
		}
		if (delay > 10)
		{
			if ((cp + 8 > stp + 20) && (cp + 8 < fip - 20))
			{
				BIG_GAME[rp + 8][cp + 8] = '!';
			}
			delay = 0;
			
		}
		int flag;
		for (int r = 0; r < h; r++)
		{
			for (int c = 0; c < fip ; c++)
			{
				if (BIG_GAME[r][c] == '!')
				{
					
					 flag = hithero(r+1 , c);
					if (!flag)
					{
						if (r > h-2-6)
						{
							BIG_GAME[r][c] = ' ';
						}
						else
						{
							BIG_GAME[r][c] = ' ';
							BIG_GAME[r + 1][c] = '!';
							r++;
						}
						
					}
					else
					{
						if (flag)
						{
							dead_hero = 1;
						}

					}

				}
			}
		}

	}
	int hithero(int row, int coulmn)
	{

		for (int r = firstRow; r <= firstRow + 8; r++)
		{
			for (int c = firstCoulmn; c <= firstCoulmn + 22; c++)
			{
				if (row == r)
				{
					if (coulmn == c)
					{
						return 1;
					}
				}
			}
		}
		return 0;
	}
	
	int elrst=35;
	int elrfi=15;

	int elcst=40;
	int elcfi=23+elcst;

	int rnow=elrst;

	int stop=0;
	int endelevator=0;
	void elevator()
	{
		if (!endelevator)
		{
			int r, c;

			if (firstRow == rnow - 8 && firstCoulmn == elcst + 2)
			{
				if (rnow != elrfi)
				{
					stop = 1;

					rnow--;
					firstRow--;
					steps = 1;
					draw_hero('w');
					for (c = elcst; c < elcfi; c++)
					{
						BIG_GAME[rnow+1][c] = ' ';
					}
				}
				else
				{
					stop = 0;
					endelevator = 1;
				}
			}
			for (c = elcst; c < elcfi; c++)
			{
				BIG_GAME[rnow][c] = '=';
			}
		}
	}

	void wall()
	{
		int r, c;
		for (r = 15; r < h - 1; r++)
		{
			for (c = 65; c < 65 + 100; c++)
			{
				BIG_GAME[r][c] = '#';
			}
		}
	}
	
	char shield[7] = { '#','#', '#', '#', '#', '#', '#' };
	int pick = 0;
	int rs, cs;
	
	void cap()
	{
		int r, c;
		//7>14.115
		//7.93
		// 1 A
		//2 d
		if (firstRow == 7 && firstCoulmn == 93)
		{
			pick = 1;
			for (r = 7; r <= 14; r++)
			{
				BIG_GAME[r][115] = ' ';
			}
		}
		if (!pick)
		{
			for (r = 7; r <= 14; r++)
			{
				BIG_GAME[r][115] = '#';
			}
			rs = 7;
			cs = 115;
		}
		//if (pick)
		//{
		//	if (shape == 1) //a
		//	{
		//		for (r = firstRow; r < firstRow + 7; r++)
		//		{
		//			BIG_GAME[r][firstCoulmn - 1] = '0';
		//		}
		//	}
		//	if (shape == 2) //d
		//	{
		//		for (r = firstRow; r < firstRow + 7; r++)
		//		{
		//			BIG_GAME[r][lastCoulmn] = '0';
		//		}
		//	}
		//}
		if (pick)
		{
			for (r = rs; r < rs + 7; r++)
			{
				BIG_GAME[r][cs] = '0';
			}
		}
	}
	
};
struct enemies
{
	int Row, Coulmn;
	int way; //1 left 2right
	int die = 0;
	int delay = 0;
	char temp[5][5];
	char enemy1[5][5] = {
		' ','_','_','_',' ',
		'/','/','_','+','\\',
		'/','[','\\',']','\\',
		' ','|',' ','|',' ',
		' ','/',' ','|',' ' };
	char enemy2[5][5] = {
		' ','_','_','_',' ',
		'%','"','-','"','%',
		'/','[','U',']','\\',
		' ','|',' ','|',' ',
		' ','|',' ','|',' ' };
	void move_enemy(char x[][W], int rhe, int che, int & dead, int scroll)
	{
		if (!die)
		{
			int flag = 0;

			if (way == 1)
			{
				for (int r = Row; r < Row + 5; r++)
				{
					for (int c = Coulmn - 1; c > Coulmn - 3; c--)
					{
						if (x[r][c] != ' ')
						{
							flag++;
							// sad face
						}
						if (x[r][c] == '>' || x[r][c] == '<')
						{
							x[r][c] = ' ';
							die = 1;
							for (int r = 0; r < 5; r++)
							{
								for (int c = 0; c < 5; c++)
								{
									temp[r][c] = ' ';
								}
							}
							for (int r = Row; r < Row + 5; r++)
							{
								for (int c = Coulmn; c < Coulmn + 5; c++)
								{
									x[r][c] = ' ';
								}
							}


						}
					}
				}
				if (flag == 0)
				{
					Coulmn -= 2;
					for (int r = Row; r < Row + 5; r++)
					{
						for (int c = Coulmn; c < Coulmn + 5; c++)
						{
							if (hit(r, c, rhe, che))
							{
								dead = 1;
								
							}
						}
					}
					//there is nothing in the way
				}
				else
				{
					flag = 0;
					way = 2;
					// there is a wall
				}
			}
			if (way == 2)
			{
				for (int r = Row; r < Row + 5; r++)
				{
					for (int c = Coulmn + 5; c < Coulmn + 8; c++)
					{
						if (x[r][c] != ' ')
						{
							flag++;
							// sad face
						}
						if (x[r][c] == '>' || x[r][c] == '<')
						{
							x[r][c] = ' ';
							die = 1;
							for (int r = 0; r < 5; r++)
							{
								for (int c = 0; c < 5; c++)
								{
									temp[r][c] = ' ';
								}
							}
							for (int r = Row; r < Row + 5; r++)
							{
								for (int c = Coulmn; c < Coulmn + 5; c++)
								{
									x[r][c] = ' ';
								}
							}
						}
					}
				}
				if (flag == 0)
				{

					Coulmn += 2;

					for (int r = Row; r < Row + 5; r++)
					{
						for (int c = Coulmn; c < Coulmn + 5; c++)
						{
							if (hit(r, c, rhe, che))
							{
								dead = 1;
								
							}
						}
					}

				}
				else
				{

					flag = 0;
					way = 1;
				}
			}
			draw_enemy(x);
		}
		
	}
	void set_enemy(int shape, int row, int coulmn, int ww)
	{
		Row = row;
		Coulmn = coulmn;
		way = ww;
		if (shape == 1)
		{
			for (int r = 0; r < 5; r++)
			{
				for (int c = 0; c < 5; c++)
				{
					temp[r][c] = enemy1[r][c];
				}
			}
		}
		if (shape == 0)
		{
			for (int r = 0; r < 5; r++)
			{
				for (int c = 0; c < 5; c++)
				{
					temp[r][c] = enemy2[r][c];
				}
			}
		}
	}
	void draw_enemy(char BIG_GAME[][W])
	{
		if (!die)
		{
			if (way == 1)
			{
				for (int r = Row; r < Row + 5; r++)
				{
					for (int c = Coulmn + 5; c < Coulmn + 7; c++)
					{
						BIG_GAME[r][c] = ' ';
					}
				}
			}
			if (way == 2)
			{
				for (int r = Row; r < Row + 5; r++)
				{
					for (int c = Coulmn - 2; c < Coulmn; c++)
					{
						BIG_GAME[r][c] = ' ';
					}
				}
			}
			int e = 0, p = 0;
			for (int r = Row; r < Row + 5; r++)
			{
				p = 0;
				for (int c = Coulmn; c < Coulmn + 5; c++)
				{
					BIG_GAME[r][c] = temp[e][p];
					p++;
				}
				e++;
			}
		}

	}
	void enemyfire(char x[][W], int & dead_hero, int rhe, int che)
	{
		if (delay > 10)
		{
			delay = 0;
			if (way == 1)
			{
				x[Row + 2][Coulmn - 1] = '<';
			}
			
		}
		else
		{
			delay++;
		}
		for (int r = h; r > 0; r--)
		{
			for (int c = 800; c > 0; c--)
			{
				if (x[r][c] == '<')
				{
					if (x[r][c - 1] == ' ')
					{
						x[r][c] = ' ';
						x[r][c - 1] = '<';
						c--;
					}
					else
					{

						if (x[r][c - 1] == '#' || x[r][c + 1] == '0')
						{
							x[r][c] = ' ';

						}
					}
				}
			}
		}
		for (int r = 0; r < h; r++)
		{
			for (int c = 0; c < 800; c++)
			{
				if (x[r][c] == '>' || x[r][c] == '<')
				{
					dead_hero = hit(r, c,rhe,che);
				}
			}
		}

	}
	int hit(int row, int coulmn, int rhe, int che)
	{
		
		for (int r = rhe; r < rhe + 8; r++)
		{
			for (int c = che; c < che + 22; c++)
			{
				if (row == r)
				{
					if (coulmn == c)
					{
						return 1;
					}
				}
			}
		}
		return 0;
	}
};
void main()
{
	
	int level = 2;
	cout << endl << "HEELO! WE HAVE 3 LEVELS TO OFFER WHICH ONE WOULD YOU LIKE TO START WITH?"<<"  ";
	cin >> level;
	system("cls");

	for (; level == 1;)
	{

		map m;
		enemies loki[2];
		char kb;
		loki[0].set_enemy(1, h - 6, 111, 1);
		loki[1].set_enemy(0, h - 6, 111 + 6, 2);
		for (;;)
		{
		
			m.draw_hero('s');
			for (; !_kbhit();)
			{

				m.fire(0);
				m.move_hero('s',1);
				m.draw_wall();
				m.draw_clouds();
				loki[0].move_enemy(m.BIG_GAME, m.firstRow, m.firstCoulmn, m.dead_hero, m.scroll);
				loki[1].move_enemy(m.BIG_GAME, m.firstRow, m.firstCoulmn, m.dead_hero, m.scroll);
				m.SetOurMat();
				if (m.dead_hero)
				{
					break;
					
				}
				if (m.scroll > 220)
				{
					level = 2;
					break;
				}
			}

			if (m.dead_hero)
			{
				break;
				
			}
			if (m.scroll > 220)
			{
				level = 2;
				break;
			}
			kb = _getch();
			m.move_hero(kb,1);
			m.fire(0);
			m.move_hero('s',1);
			m.draw_wall();
			m.draw_clouds();

			loki[0].move_enemy(m.BIG_GAME, m.firstRow, m.firstCoulmn, m.dead_hero, m.scroll);
			loki[1].move_enemy(m.BIG_GAME, m.firstRow, m.firstCoulmn, m.dead_hero, m.scroll);

			m.SetOurMat();

		}
	}
	
	for (; level == 2;)
	{
		map m;
	
		char kb;
		for (;;)
		{
			m.draw_hero('s');
			for (; !_kbhit();)
			{
			
				m.move_hero('s',2);
				m.planes();
				m.SetOurMat();
				if (m.dead_hero)
				{
					break;

				}
				if (m.firstCoulmn > 210)
				{
					level = 3;
					break;
				}
			}
			if (m.dead_hero)
			{
				break;

			}
			if (m.firstCoulmn >210)
			{
				level = 3;
				break;
			}
			kb = _getch();
			m.move_hero(kb,2);
			
			m.move_hero('s',2);
			m.planes();
			m.SetOurMat();
		}
	}
	
	for (; level == 3;)
	{
		int end;
		map m;
		char kb;
		enemies loki[3];
		loki[0].set_enemy(0, h - 6, 300, 1);
		for (;;)
		{
			m.draw_hero('s');
			m.wall();
			for (; !_kbhit();)
			{

				m.fire(0);
				m.move_hero('s', 1);
				m.draw_clouds();
				m.elevator();
				m.cap();
				if (m.scroll>95)
				{
					loki[0].move_enemy(m.BIG_GAME, m.firstRow, m.firstCoulmn, m.dead_hero, m.scroll);

				   loki[0].enemyfire(m.BIG_GAME, m.dead_hero,m.firstRow,m.firstCoulmn);
				   loki[0].enemyfire(m.BIG_GAME, m.dead_hero, m.firstRow, m.firstCoulmn);
				}
				

				m.SetOurMat();
				if (m.dead_hero)
				{
					break;

				}
			
			}
			
			if (m.dead_hero)
			{
				break;
			}
		
			kb = _getch();
			m.move_hero(kb, 1);
			m.fire(0);
			m.move_hero('s', 1);
			m.draw_clouds();
			m.elevator();
			m.cap();
			if (m.scroll > 95)
			{
				loki[0].move_enemy(m.BIG_GAME, m.firstRow, m.firstCoulmn, m.dead_hero, m.scroll);

				loki[0].enemyfire(m.BIG_GAME, m.dead_hero, m.firstRow, m.firstCoulmn);
				loki[0].enemyfire(m.BIG_GAME, m.dead_hero, m.firstRow, m.firstCoulmn);
			}

			m.SetOurMat();

			if (m.scroll > 170)
			{
				level = 4;
				break;
			}

		}
	}
	system("cls");
	cout << endl << "THANKS FOR PLAYING" << endl<<"please give 10 marks :)";
	system("pause");
}
