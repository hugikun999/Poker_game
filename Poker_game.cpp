#include<iostream>
#include<cstdlib>
#include<time.h>
#include<vector>
using namespace std;

class begining    //創造一個已經洗好排的排組，並且分發初始的牌 
{
	public:
	begining();
	void card();
	void check1(int*,int); 
	void distribution();
	void printBegining();
	
	friend class moving;
	
	private:
	int pile[8][52];//第0堆代表洗好的牌，1~7堆代表7個牌堆
	int spreadPile[8][52]; //表示排組有無攤開牌值 
	int outputPile[4]; //輸出的牌堆
	int wastePile[24];
	int stock;//紀錄餘牌發到的位置 
	int money; 
 } ;
 begining::begining()
 {
 	for(int j=1;j<8;j++)//先把七堆內容的初始值設為-1
	 {
	 	for(int q=0;q<52;q++)
	 	{
	 		pile[j][q]=-1;
		 }
	 }
	 for(int l=1;l<8;l++)
	 {
	 	for(int h=0;h<52;h++)
	 	{
	 		spreadPile[l][h]=-1;//先把所有初始值設為-1，表示皆未攤開 	
		 }
		spreadPile[l][l-1]=0;//題目設定一開始攤開的牌 
	 }
	 for(int i=0;i<4;i++)//把輸出牌堆的初始值設為-1 
	 {
	 	outputPile[i]=-1;
	 }
	 for(int k=0;k<24;k++)//把廢棄牌堆的初始值設為-1 
	 {
	 	wastePile[k]=-1;
	 }
	card();
	distribution();
	stock=28;
	money=-52; 
}

void begining::check1(int* s,int b) //檢查k是否已經出現過  如果出現過就重新生成一個新變數重作檢查 
{
	for(int h=0;h<b;h++)
	{
		
		if(*s==pile[0][h])
		{
			*s=rand()%52;
			check1(s,b);
		}
		
	}
}
void begining::card() //洗牌 
{
	srand(time(0)); 
    for(int i=0;i<52;i++)   //將a的每項歸零且0~51分別代表52張牌 ,花色由梅花、菱形、黑桃、愛心為順序排出 
    {
    	int k=rand()%52;
		check1(&k,i);
		pile[0][i]=k;
		
	}
}
void begining::distribution() //發初始的牌 
{
	int count=0;
	for(int Dpoker=0;Dpoker<8;Dpoker++)
	{
	
		for (int Dpile=1+Dpoker;Dpile<8;Dpile++)
		{
			pile[Dpile][Dpoker]=pile[0][count];
			count++;
		}
	}
	
}

void begining::printBegining()//印出初始牌堆狀況，並只顯示最後一張牌的數值 
{
	int suit;
	int number;
	cout<<"初始情況為"<<endl;
	for(int i=1;i<8;i++)
	{
		cout<<"pile"<<i<<":";
		for(int k=0;k<i;k++)
		{
			if(spreadPile[i][k]==-1)
				cout<<"□ ";
			else
			{	suit=pile[i][i-1]/13;//花色 
				number=(pile[i][i-1]%13)+1;//數字
				switch(suit)
				{
					case 0:
						cout<<"C"<<number<<endl;
						break;
		    		case 1:
		    			cout<<"D"<<number<<endl;
		    			break;
		    		case 2:
		    			cout<<"S"<<number<<endl;
		    			break;
		    		case 3:
		    			cout<<"H"<<number<<endl;
		    			break;
				}
			}
	    }
	}
	for(int k=0;k<4;k++)
	{
		cout<<"outputPile"<<k+1<<":"<<endl;
	}
	cout<<"wastePile:"<<endl;
}
 
 
class moving        //一開始和移動牌組的規則 
 {
 	public:
 		moving(begining*);
 		void moveruleA(begining*,int *); 
 		void moveruleB(begining*,int *);
		void moveruleC(begining*,int *);
		void moveruleE(begining*,int *);
 		void getPileTop(begining);
 		void getwastePileTop(begining);
 		int checkWin(begining* ,int *);
 		void printPile(begining);
 		int getmoney(begining);
 	private:
 		int pileTop[8];//紀錄遊戲牌堆最上面的牌 
 		int position[8];
 		int wastePileTop;//紀錄廢棄牌堆最上面的牌 
 		int wasteposition;
 		
 		
 		
 };
moving::moving(begining *a)        
{
	
	a->wastePile[0]=a->pile[0][a->stock];//一開始先從餘牌拿一張到廢棄牌堆
	cout<<"初始情況是"; 
	a->stock++;
	printPile(*a);
	cout<<"請輸入任意鍵以繼續"<<endl;
	
}
void moving::getPileTop(begining a)//找出所有pile的最上方的牌 
{
	for(int k=1;k<8;k++)
	{
		int h=0;//記住最上面牌的值 
		int count=0;//每個遊戲堆有幾張牌 
		while(h!=-1)
		{
			h=a.pile[k][count];
			count++;
		}
		if(count==1)
		{
			pileTop[k]=-1; 
			position[k]=-1; 
		}
		else 
		{
			pileTop[k]=a.pile[k][count-2];
			position[k]=count-2;
		} 
	}
}

void moving::getwastePileTop(begining a)//找到廢棄牌堆最上方牌的值 
{
	int count=0;
	int k=0;
	while(k!=-1)
	{
		k=a.wastePile[count];
		count++;
	}
	if(count==1)
	{
		wastePileTop=-1;
		wasteposition=-1; 
	}
	else
	{ 
		wastePileTop=a.wastePile[count-2];
		wasteposition=count-2;
	} 
}
void moving::moveruleA(begining *a,int *value)//移動法則A
{
	int k=1;//第幾牌堆 
	int i=0;
	int o=0;
	getPileTop(*a);
	getwastePileTop(*a);
	while(k<8)
	{ 
	 if(pileTop[k]==0||pileTop[k]==13||pileTop[k]==26||pileTop[k]==39)//第一張可放到輸出牌堆的值 
	 {
	 	
		while(i<4)
		{
				if(a->outputPile[i]==-1)
				{
					a->outputPile[i]=pileTop[k];
					a->pile[k][(position[k])]=-1;
					a->spreadPile[k][(position[k])]=-1;
					if((a->spreadPile[k][(position[k])-1]==-1&&(position[k])-1)>=0)//若移動至輸出牌堆的下一張牌為蓋住的，則把他翻開 
					{
						a->spreadPile[k][(position[k])-1]=0; 
					}
					*value+=1;
					a->money+=5;
					cout<<"執行了步驟a"<<endl;
					cout<<"將pile"<<k<<"的牌移動到了輸出牌堆"<<i+1<<endl; 
					break;
				}
		 		else
		 			i++;
		}
		i=0;
	 }
	 else
	{
		
	 	while(o<4)
	 	{
	 		if(pileTop[k]==a->outputPile[o]+1)
	 		{
	 			a->outputPile[o]=pileTop[k];
	 			a->pile[k][(position[k])]=-1;
	 			a->spreadPile[k][(position[k])]=-1;
	 			if((a->spreadPile[k][(position[k])-1]==-1&&(position[k])-1)>=0) ////若移動至輸出牌堆的下一張牌為蓋住的，則把他翻開 
	 			{
	 				a->spreadPile[k][(position[k])-1]=0;
				}
				*value+=1;
				a->money+=5;
				cout<<"執行了步驟a"<<endl;
				cout<<"將pile"<<k<<"的牌移動到了輸出牌堆"<<i+1<<endl; 
	 			break;
			 }
			else
				o++;
		 }
		 o=0;
	}
	if(*value==1)
	break;
	k++;
	}
	if(k==8)
	{
		int d=0;
		while(d<4)
		{
			if(wastePileTop==a->outputPile[d]+1||wastePileTop==0||wastePileTop==13||wastePileTop==26||wastePileTop==39)
			{
				if(a->outputPile[d]==-1)
				{
					a->outputPile[d]=wastePileTop;
					a->wastePile[wasteposition]=-1;
					*value+=1;
					a->money+=5;
					cout<<"執行了步驟a"<<endl;
					cout<<"將廢棄牌堆的牌移動到了輸出牌堆"<<d+1<<endl; 
					break;
				}
				else
				d++;
			}
			else
				d++;
		}
	}
	if(a->wastePile[0]==-1 && a->stock<52)
	{
		a->wastePile[0]=a->pile[0][a->stock];
		a->stock++;
	}
}

		
void moving::moveruleB(begining *a,int *value)//移動法則B 
{
	int x;
	int i=1;
	int j=1;
	int k=1;
	int l=1;
	getPileTop(*a);
	getwastePileTop(*a);
	x=wastePileTop/13;
	switch(x)
	{
		case 0:
			while(i<8)
			{
				if(((wastePileTop+1)%13==((pileTop[i]+1)%13)-1&&(pileTop[i]/13)%2==1)||pileTop[i]==-1)
				{
					a->pile[i][(position[i]+1)]=wastePileTop;
					a->spreadPile[i][(position[i]+1)]=0;
					a->wastePile[wasteposition]=-1;
					*value+=1;
					cout<<"執行了步驟b"<<endl;
					cout<<"將wastePile的牌移動到pile"<<i<<endl; 
					break;
				}
				else
					i++;
			}
			break;
		case 1:
			while(j<8)
			{
				if(((wastePileTop+1)%13==((pileTop[j]+1)%13)-1&&(pileTop[j]/13)%2==0)||pileTop[j]==-1)
				{
					a->pile[j][(position[j]+1)]=wastePileTop;
					a->spreadPile[j][(position[j]+1)]=0;
					a->wastePile[wasteposition]=-1;
					*value+=1;
					cout<<"執行了步驟b"<<endl;
					cout<<"將wastePile的牌移動到pile"<<j<<endl;
					break;
				}
				else
					j++;
			}
			break;
		case 2:
			while(k<8)
			{
				if(((wastePileTop+1)%13==((pileTop[k]+1)%13)-1&&(pileTop[k]/13)%2==1)||pileTop[k]==-1)
				{
					a->pile[k][(position[k]+1)]=wastePileTop;
					a->spreadPile[k][(position[k]+1)]=0;
					a->wastePile[wasteposition]=-1;
					*value+=1;
					cout<<"執行了步驟b"<<endl;
					cout<<"將wastePile的牌移動到pile"<<k<<endl;
					break;
				}
				else
					k++;
			}
			break;
		case 3:
			while(l<8)
			{
				if(((wastePileTop+1)%13==((pileTop[l]+1)%13)-1&&(pileTop[l]/13)%2==0)||pileTop[l]==-1)
				{
					a->pile[l][(position[l]+1)]=wastePileTop;
					a->spreadPile[l][(position[l]+1)]=0;
					a->wastePile[wasteposition]=-1;
					*value+=1;
					cout<<"執行了步驟b"<<endl;
					cout<<"將wastePile的牌移動到pile"<<l<<endl;
					break;
				}
				else
					l++;
			}
			break;	
	}
	if(a->wastePile[0]==-1 && a->stock<52)
	{
		a->wastePile[0]=a->pile[0][a->stock];
		a->stock++;
	}
}


void moving::moveruleC(begining *a,int *value)//移動法則C 
{
	int k=1;
	int start;
	int end;
	getPileTop(*a);
	getwastePileTop(*a);
	while(k<8)
	{
		for(int i=0;i<52;i++)
		{
			if(a->spreadPile[k][i]==0)//牌為攤開的 
			{
				start=i;
				i=52;
			}
		}
		for(int j=51;j>=0;j--)
		{
			if(a->spreadPile[k][j]==0)
			{
				end=j;
				j=-1;
			}
		}
		int movenumber=(end-start)+1;//移動個數 
		for(int q=1;q<8;q++)
		{
			if(*value==0)
				{
					if((pileTop[q]+1)%13+12==(a->pile[k][start]+1)%13||((pileTop[q]+1)%13==(a->pile[k][start]+1)%13+1 && (((pileTop[q])+1)/13)%2!=(((a->pile[k][start])+1)/13)%2 && q!=k))//需要符合紅黑相間以及不可以移動到自己堆(等於沒有移動) 
					{
						cout<<"執行了步驟c"<<endl; 
						cout<<"將pile"<<k<<"的"<<movenumber<<"張牌移動到pile"<<q<<endl;  
						for(int c=0;c<movenumber;c++)
						{
							a->pile[q][position[q]+c+1]=a->pile[k][start+c];
							a->spreadPile[q][position[q]+c+1]=0;
							a->pile[k][start+c]=-1;
							a->spreadPile[k][start+c]=-1;
							if(start>=1)
							{a->spreadPile[k][start-1]=0;} 
							*value+=1;
						}
					}
				}
		}
		if(*value==0)
		k++;
		else
		k=8;
	}
}

	
void moving::moveruleE(begining *a,int *end)
{	
	if(a->stock<52)
	{
		cout<<"執行了步驟e"<<endl;
		getwastePileTop(*a);
		a->wastePile[wasteposition+1]=a->pile[0][a->stock];
		a->stock++;
	}
	if(a->stock==52)
	{
		*end=-1;
	}
}
int moving::checkWin(begining *a,int* end) 
{ 
	if((a->outputPile[0]%13==12 && a->outputPile[1]%13==12 && a->outputPile[2]%13==12 && a->outputPile[3]%13==12)||(a->stock>=52&&*end==0)) 
	{
		cout<<"The game is over." <<endl;
		cout<<"請輸入任意數字以繼續"<<endl;
		system("pause");
		return -1;
	}
	else
	return 1;
	 
}

void moving::printPile(begining a)
{
	int suit;
	int number;
	int suit1;
	int number1;
	int suit2;
	int number2;
	getPileTop(a);
	getwastePileTop(a);
	for(int i=1;i<8;i++)
	{
		cout<<endl;
		cout<<"pile"<<i<<":";
		if(position[i]==-1); 
		else 
		{
			for(int k=0;k<position[i]+1;k++)
			{
				if(a.pile[i][0]==-1)
				cout<<endl;
				if(a.spreadPile[i][k]==-1)
					cout<<"□ ";
				else
				{	
					suit=a.pile[i][k]/13;//花色 
					number=(a.pile[i][k]%13)+1;//數字
					switch(suit)
					{
						case 0:
							cout<<"C"<<number<<" ";
							break;
		    			case 1:
		    				cout<<"D"<<number<<" ";
		    				break;
		    			case 2:
		    				cout<<"S"<<number<<" ";
		    				break;
		    			case 3:
		    				cout<<"H"<<number<<" ";
		    				break;
					}
				}
	    	} 
		}
	}
	cout<<endl;
	for(int k=0;k<4;k++)
	{
		if(a.outputPile[k]==-1)
		cout<<"outputPile"<<k+1<<":"<<endl;
	else
			{	
				cout<<"outputPile"<<k+1<<":";
				suit1=a.outputPile[k]/13;//花色 
				number1=(a.outputPile[k]%13)+1;//數字
				switch(suit1)
				{
					case 0:
						cout<<"C"<<number1<<endl;
						break;
		    		case 1:
		    			cout<<"D"<<number1<<endl;
		    			break;
		    		case 2:
		    			cout<<"S"<<number1<<endl;
		    			break;
		    		case 3:
		    			cout<<"H"<<number1<<endl;
		    			break;
				}
		
			}
	}
	
	 
	if(a.wastePile[wasteposition]==-1)
	cout<<"wastePile:"<<endl;
	else
		{
		cout<<"wastePile:";
		for(int y=0;y<wasteposition+1;y++)
		{	
				suit2=a.wastePile[y]/13;//花色 
				number2=(a.wastePile[y]%13)+1;//數字
				switch(suit2)
				{
					case 0:
						cout<<"C"<<number2<<" ";
						break;
		    		case 1:
		    			cout<<"D"<<number2<<" ";
		    			break;
		    		case 2:
		    			cout<<"S"<<number2<<" ";
		    			break;
		    		case 3:
		    			cout<<"H"<<number2<<" ";
		    			break;
		
				}
		}
		cout<<endl;
		}
	cout<<"stock= "<<52-(a.stock)<<endl; 
	cout<<"The money you win is"<<a.money<<endl; 
}
int moving::getmoney(begining a)
{
	return a.money;
}


int main()
{
	int x;
	int endvalue1=0;
	begining game1;
	moving movegame1(&game1);
	cin>>x;
	int a=0;
	
	while(&a>0)
	{
		
		do
		{
			endvalue1=0;
			if(endvalue1==0)
			{
				movegame1.moveruleA(&game1,&endvalue1);
				if(endvalue1!=0)
				{
					movegame1.printPile(game1);
					 
					if(movegame1.checkWin(&game1,&endvalue1)==-1)
					{
						break;
					}
					else
					{
					cout<<"請輸入任意數字以繼續"<<endl;
					cin>>x;
					}
				}
		    }
			if(endvalue1==0)
			{
				movegame1.moveruleB(&game1,&endvalue1);
				if(endvalue1!=0)
				{
					movegame1.printPile(game1);
					if(movegame1.checkWin(&game1,&endvalue1)==-1) 
					{
						break;
					}
					else
					{
					cout<<"請輸入任意數字以繼續"<<endl;
					cin>>x;
					}
		    	}
			}
			if(endvalue1==0)
			{
				movegame1.moveruleC(&game1,&endvalue1);
				if(endvalue1!=0)
				{
					movegame1.printPile(game1);
					if(movegame1.checkWin(&game1,&endvalue1)==-1)
					{
						break;
						
					}
					else
					{
					cout<<"請輸入任意數字以繼續"<<endl;
					cin>>x;
					}
				}
			}
		}while(endvalue1!=0);
		
		if(movegame1.checkWin(&game1,&endvalue1)==-1)
		{
			break;
		}
		else
		{
		movegame1.moveruleE(&game1,&a);
		movegame1.printPile(game1);
		}
		cout<<"請輸入任意鍵以繼續"<<endl;
		cin>>x;
	}
	cout<<"請按任意鍵開啟下一局"<<endl;
	begining game2;
	moving movegame2(&game2);
	cin>>x;
	int b=0;
	int endvalue2=0;
	while(&b>0)
	{
		
		do
		{
			endvalue2=0;
			if(endvalue2==0)
			{
				movegame2.moveruleA(&game2,&endvalue2);
				if(endvalue2!=0)
				{
					movegame2.printPile(game2);
					 
					if(movegame2.checkWin(&game2,&endvalue2)==-1)
					{
						break;
					 } 
					 else
					{
					cout<<"請輸入任意數字以繼續"<<endl;
					cin>>x;
					}
				}
		    }
			if(endvalue2==0)
			{
				movegame2.moveruleB(&game2,&endvalue2);
				if(endvalue2!=0)
				{
					movegame2.printPile(game2);
					if(movegame2.checkWin(&game2,&endvalue2)==-1)
					{
						break;
					 } 
					else
					{
					cout<<"請輸入任意數字以繼續"<<endl;
					cin>>x;
					}
		    	}
			}
			if(endvalue2==0)
			{
				movegame2.moveruleC(&game2,&endvalue2);
				if(endvalue2!=0)
				{
					movegame2.printPile(game2);
					if(movegame2.checkWin(&game2,&endvalue2)==-1)
					{
						break;
					 } 
					else
					{
					cout<<"請輸入任意數字以繼續"<<endl;
					cin>>x;
					}
				}
			}
		}while(endvalue2!=0);
		if(movegame2.checkWin(&game2,&endvalue2)==-1)
		{
			break;
		}
		else 
		{
		movegame2.moveruleE(&game2,&b);
		movegame2.printPile(game2);
		cout<<"請輸入任意數字以繼續"<<endl;
		cin>>x;
		}
		
	}
	cout<<"第一局:"<<endl;
	cout<<"       淨輸贏金額"<<movegame1.getmoney(game1)<<endl;
	cout<<"第二局:"<<endl;
	cout<<"       淨輸贏金額"<<movegame2.getmoney(game2)<<endl;
	system("pause");
	return 0;
	 

	
}
	
	
