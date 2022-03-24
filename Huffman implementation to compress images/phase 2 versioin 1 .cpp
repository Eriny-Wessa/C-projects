#include <iostream>
using namespace std;
class cNtree
{
public:
	char name[300];
	cNtree * pleft;
	cNtree * pright;
};
class cNlist
{
public:
	int info;
	char name[300];
	cNlist *pNext;
	cNtree *pDown;
	char code[200];

};
class clist
{
public:
	cNlist * pHead;
	cNlist * pTail;

	clist()
	{
		pHead = NULL;
		pTail = NULL;
	}
	~clist()
	{
		cNlist *pTrav = pHead;
		while (pTrav != NULL)
		{
			pHead = pHead->pNext;
			delete pTrav;
			pTrav = pHead;
		}
	}
	void Attach(cNlist *pnn)
	{
		if (pHead == NULL)
		{
			pHead = pnn;
			pTail = pnn;
		}
		else
		{
			pTail->pNext = pnn;
			pTail = pnn;
		}
	}
	void dis_list_nodes()
	{
		cNlist *pTrav;
		pTrav = pHead;

		while (pTrav != NULL)
		{


			cout << "name " << pTrav->name[0];

			cout << "   freq " << pTrav->info << endl;

			pTrav = pTrav->pNext;
		}
	}
	void insert(cNlist *&pnn)
	{
		cNlist * ptrav = pHead;
		cNlist * pback = NULL;
		if (pHead == NULL)
		{
			Attach(pnn);
			return;
		}
		while (ptrav != NULL)
		{
			if (ptrav->info > pnn->info)
			{
				if (ptrav != pHead)
				{
					pback->pNext = pnn;
					pnn->pNext = ptrav;
				}
				else
				{
					pHead = pnn;
					pnn->pNext = ptrav;
				}

				break;
			}
			else
			{
				if (ptrav == pTail)
				{
					Attach(pnn);
					break;
				}

			}
			pback = ptrav;
			ptrav = ptrav->pNext;
		}
	}
	void combine_Nodes()
	{
		int i, j;
		cNlist * pnn;
		cNlist * p1;
		cNlist * p2;
		cNtree * pt;
		while (pHead != NULL && pHead->pNext != NULL)
		{
			p1 = pHead;
			p2 = pHead->pNext;
			pHead = pHead->pNext->pNext;
			p2->pNext = NULL;

			pnn = new cNlist;
			pnn->info = p1->info + p2->info;
			pnn->pNext = NULL;

			for (i = 0; p1->name[i] != '\0'; i++)
			{
				pnn->name[i] = p1->name[i];
			}

			for (j = 0; p2->name[j] != '\0'; j++)
			{
				pnn->name[i] = p2->name[j];
				i++;
			}
			pnn->name[i] = '\0';

			pnn->pDown = new cNtree;
			for (i = 0; pnn->name[i] != '\0'; i++)
			{
				pnn->pDown->name[i] = pnn->name[i];
			}
			pnn->pDown->name[i] = '\0';
			if (p1->pDown == NULL)
			{
				pt = new cNtree;
				pt->pleft = NULL;
				pt->pright = NULL;
				for (i = 0; p1->name[i] != '\0'; i++)
				{
					pt->name[i] = p1->name[i];
				}
				pt->name[i] = '\0';
				pnn->pDown->pleft = pt;
			}
			else
			{
				pnn->pDown->pleft = p1->pDown;

			}
			if (p2->pDown == NULL)
			{
				pt = new cNtree;
				pt->pleft = NULL;
				pt->pright = NULL;
				for (i = 0; p2->name[i] != '\0'; i++)
				{
					pt->name[i] = p2->name[i];
				}
				pt->name[i] = '\0';
				pnn->pDown->pright = pt;

			}
			else
			{
				pnn->pDown->pright = p2->pDown;
			}
			insert(pnn);


		}
	}

	void display_AfterCombine()
	{
		if (pHead == NULL)
		{
			cout << endl << "error 1" << endl;
		}
		cNlist *ptrav = pHead;
		int i = 0;
		while (ptrav != NULL)
		{
			cout << endl << "Node number " << i << endl;
			for (int k = 0; ptrav->name[k] != '\0'; k++)
			{
				cout << ptrav->name[k] << " , ";
			}
			cout << endl;
			cout << " total freq= " << ptrav->info;
			ptrav = ptrav->pNext;
			i++;
		}
	}
};
void search(char text, clist &l)
{
	if (text != '\0')
	{
		int found = 0;
		if (l.pHead != NULL)
		{
			cNlist * ptrav = l.pHead;
			while (ptrav != NULL)
			{
				if (ptrav->name[0] == text)
				{
					ptrav->info++;
					found = 1;
					break;
				}
				ptrav = ptrav->pNext;
			}

		}
		else
		{
			found = 0;
		}

		if (!found)
		{
			cNlist * pnn = new cNlist;
			pnn->info = 1;
			for (int i = 0; i < 300; i++)
			{
				pnn->name[i] = '\0';
			}
			pnn->name[0] = text;
			pnn->pDown = NULL;
			pnn->pNext = NULL;
			l.Attach(pnn);
		}

	}
}
void sorting_list(clist &l, clist &s)
{
	int min = 1001;
	cNlist* ptrav;
	cNlist* pback;
	cNlist* pmin = NULL;
	cNlist* pbackmin = NULL;

	while (l.pHead != NULL)
	{
		ptrav = l.pHead;
		pback = NULL;
		min = 1001;
		while (ptrav != NULL)
		{
			if (ptrav->info < min)
			{
				min = ptrav->info;
				pmin = ptrav;
				pbackmin = pback;
			}
			pback = ptrav;
			ptrav = ptrav->pNext;
		}
		if (pbackmin == NULL && pmin == l.pHead)
		{
			l.pHead = l.pHead->pNext;

		}
		else
		{
			pbackmin->pNext = pmin->pNext;

		}
		s.Attach(pmin);

	}
}
void DispTree(cNtree * pr)
{
	if (pr == NULL)
	{
		return;
	}
	DispTree(pr->pleft);

	cout << endl;
	for (int i = 0; pr->name[i] != NULL; i++)
	{
		cout << pr->name[i] << " , ";
	}
	cout << endl;



	DispTree(pr->pright);
}
void copy_list(clist &l, clist &p)
{
	int i, k;
	cNlist * ptrav = l.pHead;
	cNlist * pnn;
	while (ptrav != NULL)
	{
		pnn = new cNlist;
		pnn->pDown = NULL;
		pnn->pNext = NULL;
		pnn->info = ptrav->info;
		for (i = 0; i < 200; i++)
		{
			pnn->code[i]=NULL;
		}
		for (i = 0; i < 300; i++)
		{
			if (i > 0 && ptrav->name[i] != NULL)
			{
				cout << endl << endl << endl << "error wtf"<<endl;
			}
			pnn->name[i] = ptrav->name[i];
		}
		ptrav = ptrav->pNext;
		p.Attach(pnn);

	}
}
char is_found(cNtree* & ptrav,char target)
{
	char f = '0';
	for (int i = 0; ptrav->pleft->name[i] != NULL; i++)
	{
		if (ptrav->pleft->name[i] == target)
		{
			f = '1';
			break;
		}
	}

	if (f=='1')
	{
		ptrav = ptrav->pleft;
	}
	else
	{
		ptrav = ptrav->pright;
	}
	return f;
}
void generate_code(cNtree * &ptrav , clist &Hcode,int ct)
{
	int i;
	cNtree * proot = ptrav;
	cNlist * letter=Hcode.pHead ;
	char target = NULL;
	int res;
	while (letter != NULL)
	{
		target = letter->name[0];
		ptrav = proot;
		for (i=0; ptrav->pright!=NULL && ptrav->pleft!=NULL ;i++)
		{
			res = is_found(ptrav, target);
			letter->code[i] = res;

		}
		letter->code[i] = NULL;

		letter = letter->pNext;
	}
}
void display_code(clist &h)
{
	cNlist * ptrav = h.pHead;
	cout << endl;
	while (ptrav != NULL)
	{
		cout << ptrav->name[0]<< "    " <<ptrav->info<<"    ";
		for (int i = 0; ptrav->code[i] != NULL; i++)
		{
			cout << ptrav->code[i];
		}
		ptrav = ptrav->pNext;
		cout << endl;
	}
}


void compress(clist &Hcode, char text[99999], char compressed[99999])
{
	int ibit = 7;
	char temp = 0;
	int icomp = 0;
	int icode = 0;
	char targchar;
	cNlist * ptrav;
	for (int itext = 0; text[itext] != NULL; itext++)
	{
		targchar = text[itext];
		ptrav = Hcode.pHead;
		while (ptrav != NULL)
		{
			if (ptrav->name[0] == targchar)
			{
				break;
			}
			if (ptrav->pNext == NULL)
			{
				cout << "ERROR 1" << endl;
			}
			ptrav = ptrav->pNext;
		}
		for (icode = 0; ptrav->code[icode] != NULL; icode++)
		{
			if (ptrav->code[icode] == '1')
			{
				temp = temp | (1 << ibit);
			}
			ibit--;

			
			if (ibit == -1 || (ptrav->code[icode+1]==NULL && text[itext+1]==NULL))
			{
			
				ibit = 7;
				compressed[icomp] = temp;
				temp = 0;
				icomp++;
			}
		}
	}
}

void decompress(clist &Hcode, char de[99999], char compressed[99999])
{
	int icomp = 0;
	int ide = 0;
	char temp;
	int ibit;
	char res;
	char target;
	int f = 0;
	clist letter;
	cNlist *ptrav;
	cNlist *pt;
	cNlist *pnn;
	for (icomp = 0; compressed[icomp] != NULL; icomp++)
	{
		temp = compressed[icomp];
		for (ibit = 7; ibit >= 0; ibit--)
		{
			pnn = new cNlist;
			pnn->pNext = NULL;
			
			res = temp & (1 << ibit);
			if (res != 0)
			{
				pnn->name[0] = '1';
			}
			else
			{
				pnn->name[0] = '0';
			}
			letter.Attach(pnn);


			ptrav = Hcode.pHead;
			pt = letter.pHead;
			target = NULL;
			f = 0;
			while (ptrav != NULL)
			{
				pt = letter.pHead;

				for (int i = 0; ptrav->code[i] != NULL&& pt!=NULL; i++)
				{
					if (pt->name[0] != ptrav->code[i])
					{
						break;
					}
					if (ptrav->code[i + 1] == NULL && pt->pNext == NULL)
					{
						target = ptrav->name[0];
						f = 1;
					}
					pt = pt->pNext;
				}

				ptrav = ptrav->pNext;
			}
			if (f)
			{
				de[ide] = target;
				ide++;
				letter.~clist();
				letter.pHead = NULL;
				letter.pTail = NULL;
			}
		}
	}



}


void main()
{
	char text[99999];
	gets_s(text);
	clist l;
	int lenght=0;
	for (int i = 0; text[i] != NULL; i++)
	{
		lenght++;
	}
	for (int i = 0; text[i] != NULL; i++)
	{
		if (text[i] != NULL)
		{
			search(text[i], l);
		}
	}
	clist sort;
	clist Hcode;
	sorting_list(l, sort);
	copy_list(sort, Hcode);
	int ct = 0;
	cNlist * Ptrav = sort.pHead;
	while (Ptrav != NULL)
	{
		ct++;
		Ptrav = Ptrav->pNext;
	}
	sort.combine_Nodes();
	cNtree * Proot = sort.pHead->pDown;
	generate_code(Proot, Hcode,ct);
	display_code(Hcode);
	cout << endl;
	system("pause");
	////////////////////////////////////////////phase 2////////////////////////////////////////////
	
	char compressed[99999];
	for (int i = 0; i < 99999; i++)
	{
		compressed[i] = NULL;
	}
	compress(Hcode, text, compressed);

	cout << endl;
	for (int i = 0; compressed[i] !=NULL; i++)
	{
		cout<< compressed[i] ;
	}
	cout << endl;
	cout << endl;
	system("pause");

	char decompressed[99999];
	for (int i = 0; i < 99999; i++)
	{
		decompressed[i] = NULL;
	}
	decompress(Hcode, decompressed, compressed);

	cout << endl;
	for (int i = 0; i< lenght; i++)
	{
		cout << decompressed[i];
	}
	cout << endl;	
	cout << endl;
	system("pause");


	int f = 1;
	for (int i = 0; text[i] != NULL; i++)
	{
		if (text[i] != decompressed[i])
		{
			f = 0;
		}

	}

	cout << endl;
	if (f)
	{
		cout << "completed"<<endl;
	}
	else
	{
		cout << "try again?" << endl;
	}
	cout << endl;

	system("pause");


}


