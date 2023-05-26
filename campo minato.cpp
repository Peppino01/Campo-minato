#include<iostream>
#include<cstdlib>
#include<ctime>
#include<time.h>

using namespace std;
char coperto=254, bomba=207, bandiera=244, pint=63, libero=95;
int bombe;
int altc=5, larc=5;
int game=0; // 0-->partita in corso  1-->win  2-->lose
int mossa[3];  // 0-->colonna  1-->riga  2-->azione

int campo[5][5][2]={  0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1  };	
 // campo[][][0] è quello reale(scoperto)             campo[][][1] è quello che vede all'inizio il giocatore(coperto)
          // 0-->libero								    	// 1-->coperto
	      // 1-8-->numero									// 2-->pint
	      // 9-->bomba								    	// 3-->bandiera
												    		// 0-->scoperto
void plotcampo(){
	cout<<"  ";
	for(int a=1;a<larc+1;a++) cout<<a<<" ";
	cout<<endl;
	for(int i=0;i<altc;i++){
		cout<<(i+1)<<" ";
		for(int j=0;j<5;j++){
			if(campo[i][j][1]==1) cout<<coperto<<" ";
			else if(campo[i][j][1]==2) cout<<pint<<" ";
			else if(campo[i][j][1]==3) cout<<bandiera<<" ";
			else if(!campo[i][j][1]) if(!campo[i][j][0]) cout<<libero<<" ";
									 else if(campo[i][j][0]<9) cout<<campo[i][j][0]<<" ";
									 else cout<<bomba<<" ";
		}
		cout<<endl;
	}
}

void plotprova(){
	cout<<endl;
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			/*if(campo[i][j][1]==1) cout<<coperto<<" ";
			else if(campo[i][j][1]==2) cout<<pint<<" ";
			else if(campo[i][j][1]==3) cout<<bandiera<<" ";
			else if(!campo[i][j][1]) */if(!campo[i][j][0]) cout<<libero<<" ";
									 else if(campo[i][j][0]<9) cout<<campo[i][j][0]<<" ";
									 else cout<<bomba<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void spown(){
	int xrand, yrand;
	for(int i=bombe;i>0;i--){
		xrand=rand()%5;
		yrand=rand()%5;
		if(campo[xrand][yrand][0]==0)
			campo[xrand][yrand][0]=9;
		else i++;
	}
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			for(int a=-1;a<2;a++)
				for(int b=-1;b<2;b++)
					if(campo[i+a][j+b][0]==9 && campo[i][j][0]!=9 && (i+a)>=0&&(i+a)<5 && (j+b)>=0&&(j+b)<5 ) campo[i][j][0]++;
			
}

void inseriscimossa(){
	do{
		cout<<"colonna: ";
		cin>>mossa[0];
		mossa[0]-=1;
		while(mossa[0]<0||mossa[0]>4){
			cout<<"colonna non valida, riprova: ";
			cin>>mossa[0];
		}
		cout<<"riga: ";
		cin>>mossa[1];
		mossa[1]-=1;
		while(mossa[1]<0||mossa[1]>4){
			cout<<"riga non valida, riprova: ";
			cin>>mossa[1];
		}
		if(campo[mossa[1]][mossa[0]][1]==0) cout<<"mossa non valida, riprova"<<endl;
	}while(campo[mossa[1]][mossa[0]][1]==0);
	cout<<"1:scava 2:bandiera 3:?"<<endl;
	cin>>mossa[2];
	while(mossa[2]<1||mossa[2]>3){
		cout<<"azione non valida, riprova: ";
		cin>>mossa[2];
	}
}

void scava(int col, int rig){
	campo[col][rig][1]=0;
	for(int a=-1;a<2;a++)
		for(int b=-1;b<2;b++){
			if(campo[col+a][rig+b][1]!=0&&(col+a)>-1&&(col+a)<5&&(rig+b)>-1&&(rig+b)<5)
				if(campo[col+a][rig+b][0]>0&&campo[col+a][rig+b][0]<9) campo[col+a][rig+b][1]=0;
				else if(campo[col+a][rig+b][0]==0) scava((col+a), (rig+b));
		}
}

int azione(int mossa[3]){
	int bombeok=0;
	if(mossa[2]==3) campo[mossa[1]][mossa[0]][1]=2;
	else if(mossa[2]==2) campo[mossa[1]][mossa[0]][1]=3;
	else if(mossa[2]==1){
		if(campo[mossa[1]][mossa[0]][0]==9) return 2;
		else if(campo[mossa[1]][mossa[0]][0]>0) campo[mossa[1]][mossa[0]][1]=0;
		else scava(mossa[1], mossa[0]);
	}
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			if(campo[i][j][0]==9&&campo[i][j][1]==3) bombeok++;
	if(bombeok==bombe) return 1;
	else bombeok=0;
	
	return 0;
}

void menu(){
	cout<<"istruzioni: inserisci la colonna e la riga della casella su cui vuoi agire e decidi che cosa fare";
	cout<<endl<<"quante bombe vuoi? ";
	cin>>bombe;
	if(bombe<1)
	do{
		cout<<endl<<"valore non valido,"<<endl<<"riprova ";
		cin>>bombe;
	}while(bombe<1);
}

int main(){
	int twin=0;
	srand(time(0));
	menu();
	spown();
	
	while(!game){
		system("cls");
		plotcampo();
		//plotprova();
		inseriscimossa();
		game=azione(mossa);
		
	}
	if(game==1){
		system("cls");
		plotcampo();
		twin=clock()/1000;
		cout<<"hai vinto in: "<<twin<<"s";
	}
	else if(game==2){
		for(int i=0;i<5;i++)
			for(int j=0;j<5;j++)
				if(campo[i][j][0]==9) campo[i][j][1]=0;
		system("cls");
		plotcampo();
		cout<<"hai perso";
	}
	cin>>game;
}
