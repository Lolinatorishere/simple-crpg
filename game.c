#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>

int Data[16][16];
int dice[100];
int gamstat[32]; // gamestate situations 
int player[32]; // player + teammate stats
int enemStat[1][31]; // Enemy statistics
 
int endstate (int enemyQ){
	int Gameend,temp;
	temp = (enemyQ/10)*2;
	Gameend = (enemStat[0][12]+enemStat[0][13]+enemStat[0][14]+enemStat[0][15]);
	if(((Gameend%temp)==0)&&(gamstat[4]>2)||(player[0]<1)){
		return 0;
	}
	else{
		return 10;
	}
}


int Enamesshort(int input){
	switch(input){
            	case 1 :
                	printf("Goblin");
           		break;
            
            	case 2 :
              	 	printf("Skeleton");
            	break;	

   	        	case 3 :
	            	printf("Ork");
	            break;
	
            	case 4 :
            		printf("Witch");
            	break;	

				default:
					printf("\n");
				break;
    	    }
}

int Enemynames(int GS){// reads the id's of the enemys and then prints the respective name
    int i,x,I;
	if(GS>9){
		i = (GS/10);
	}
	else{
		i = GS; 
	}
	I = (gamstat[4]%2);
	switch(I){
		case 0://playerside text with necessary info
			for(int e = 8 ;e<=(i+7); e++){
				x = enemStat[0][e];
     			Enamesshort(x);
				if (enemStat[0][e-8]<1){
            		printf(" (deceaced)\n");
      		  	}
				else if ((gamstat[4]%2)==0){
       				 printf(" HP %d Pos %d\n",enemStat[0][-8+e],e-7);
   				}
			}
		break;
	
		default://enemyside text with said info
			Enamesshort(enemStat[0][i+7]);
			if (enemStat[0][GS-1]<1){
            		printf(" (deceaced) ");
      		  	}
        break;
	}	
    
    
}

int EnemyGS(int GS){//Enemy names Logic withought the printing, usefull
    int a=1,b=2,c=3,d=4,i;
	if(GS>9){
		i = (GS/10);
	}
	else{
		i = GS; 
	}
		for(int I = 8;I<=(i+7); I++)
		if (enemStat[0][I] == a){//data in Goblin
			if (enemStat[0][I+4]==0){
				enemStat[0][-8+I]=enemStat[1][0];
				enemStat[0][4+I] = 1;
			}
			else if ((enemStat[0][4+I]!=2)&&enemStat[0][I-8]<1){
				enemStat[0][4+I] = 2;
			}		
		}
		else if (enemStat[0][I] == b){//data in skeleton
			if (enemStat[0][4+I]==0){
				enemStat[0][-8+I]=enemStat[1][1];
				enemStat[0][4+I]=1;
			}
			else if ((enemStat[0][4+I]!=2)&&enemStat[0][I-8]<1){
				enemStat[0][4+I] = 2;
			}
		}
		else if (enemStat[0][I] == c){//data in Ork
		 	if (enemStat[0][4+I]==0){
				enemStat[0][-8+I]=enemStat[1][3];
				enemStat[0][4+I]=1;
			}
			else if ((enemStat[0][4+I]!=2)&&enemStat[0][I-8]<1){
				enemStat[0][4+I] = 2;
			}
		}
		else if (enemStat[0][I] == d){//data in Witch
			if (enemStat[0][4+I]==0){
				enemStat[0][-8+I]=enemStat[1][2];
				enemStat[0][4+I] = 1;
			}
			else if ((enemStat[0][4+I]!=2)&&enemStat[0][I-8]<1){
				enemStat[0][4+I] = 2;
			}	
		}
		else {
			enemStat[0][4+I] = 0;	
		}
}

int rng(){
	srand(time(NULL));
		for(int i = 0;i<=100;i++){
			dice[i] = rand()%10+1;
		}
}

int PlayerLevel(){//Responsible for Calculating the Players Current Level
	int CurLVL;
	if (player[2]<46690){//the if statement caps the Level off at 30
	 CurLVL = player[3];
		if(player[3]<((CurLVL*50+100)*(CurLVL+1))){
			player[3] = CurLVL;
		}
		else{
			player[3] = CurLVL+1;
		}
	}
	else {
		player[3] = CurLVL;
	}
}

int EnemyQuant(int dice){//RNG behind how many enemys can appear during a battle
	int a,GameDif,EnemyQ;	
	a = dice/2;
	GameDif = dice*player[3];
	if (GameDif<=100){ // enemy braket 1 acheivable to all levels 
		if (a<=2){
			EnemyQ = 1; 
		}
		else if (a == 3){
			EnemyQ = 2;
		}
		else if (a == 4){
			EnemyQ = 2;
		}
		else if (a == 5){
			EnemyQ = 1;
		}
	}
	else if (GameDif>100 && GameDif<=200){ // enemy braket 2 achivable to only above lv 10s
		if (a == 0){
			EnemyQ = 1; 
		}
		else if ((a>=1)&&(a<3)){
			EnemyQ = 2;
		}
		else if (a == 3){
			EnemyQ = 2;
		}
		else if (a >= 4){
			EnemyQ = 2;
		}
	}
	else{ // enemy braket 3 Achivable only above lv20
		if (a == 0){
			EnemyQ = 2; 
		}
		else if (a == 1){
			EnemyQ = 2;
		}
		else if ((a>=2)&&(a<3)){
			EnemyQ = 3;
		}
		else if (a >= 4 ){
			EnemyQ = 4;
		}
	}
	return EnemyQ;	
}

int EnemyClass(int dice){//Rng behind what enemy is going to spawn
	int a,b,c,d,GameDif,EnemyC,I;
	GameDif = dice*player[3];// allows for more random enemy spawning
	if (GameDif<=100){
		I = 1;
	}
	else if (GameDif>100 && GameDif<=200){
		I = 2;
	}
	switch(I){
		case 1://hmmm mafs
			a = dice%2;
			b = dice%3;
			c = dice%5;
			if(a==0){
				EnemyC = 1;
			}
			else if(b == 0){
				EnemyC = 2;
			}
			else if(c==0){
				EnemyC = 3;
			}
			else if (c!=0){
				EnemyC = 4;
			}
		break;

		case 2://hmmm mafs2
			a = dice%2;
			b = dice%3;
			c = dice%5;
			if (a==0){
				EnemyC = 3;
			}
			else if(b==0){
				EnemyC = 2;
			}
			else if(c==0){
				EnemyC = 4;
			}
			else if(c!=0){
				EnemyC = 1;
			}
		break;

		default://hmmmmmmmmmmm mafs 3
			a = dice%4;
			b = dice%3;
			c = dice%5;
			if (a==0){
			EnemyC = 4;
			}
			else if(b==0){
				EnemyC = 2;
			}
			else if(c==0){
				EnemyC = 1;
			}
			else if(c!=0){
				EnemyC = 3;
			}
		break;
	}
	return EnemyC;//returning the enemyclass
}

int EnemyDefault(){//loads the base values of each monster
	//First enemy Gobulin
	 enemStat[1][0]= 600;//HP
	 enemStat[1][4] = 150;//Attack
	//second Enemy BONES
	 enemStat[1][1]= 300;
	 enemStat[1][5]= 100;
	//thirs enm witch
	 enemStat[1][2]= 200;
	 enemStat[1][6]= 100;
	//Fourt Enem ORC
	 enemStat[1][3] = 500;
	 enemStat[1][7]= 200;

}

int Enemssmall(int c){
    int a,b,GS;
	int Dice = 0;
    a = dice[Dice]%2;//50% chance
	Dice +=1;
	b = dice[Dice]%3;//30% chance
	//gs 102 is enemy heal; 103 is attack.
    switch(a){
    case 1:
	    GS = 100;//enemy miss
	break;

    default:
	    if (a==0){
		    switch(c){
                case 1:
                    GS = 103;
                break;

                case 2:
                    GS = 102;
                break;

                default:
                    GS = 102;
                break;
            }
		}
	    else if(b==0){
            switch(c){
                case 3:
                   GS = 102;
                break;

                default:
                    GS = 103;
                break;
            }	
	    }
		else{
			switch(c){	
				case 3:
                   GS = 103;
                break;

				default:
                    GS = 102;
                break;
			}
		}
    	break;
	}	
	return GS;
}

int enemystance(int I){
	int Dice,Enemy,GS,a,b,c;
	Enemy = enemStat[0][I-1];
	a = (enemStat[1][I-1]/2);//metade da vida base de um inimigo
	b = (enemStat[1][I-1]/4);//um quarto da vida base de um inimigo
	if (Enemy > a){//acima de 50%
        c = 1;
        GS = Enemssmall(c);
	}
    else if(Enemy > b){//acima de 25%
		c = 2;
        GS = Enemssmall(c);
	}
	else{//abaixo de 25%
		c = 3;
        GS = Enemssmall(c);
	}
	return GS;
}

int menu(int GS){//all the in game menus/most the text ever
	int gamestate,ES;
	if(GS == 0){//Opening menu
		printf("Welcome to the worst game ever");
		printf("\nI really need to learn to code better");
		printf("\nto start the game press 1");
		printf("\nto not bother press 0\n");
		scanf("%d",&gamestate);
		if(gamestate == 0){ //just so there isnt GS glitches furthter on 
			gamestate = 0;
		
		}
		else{
			gamestate = 1;
			return gamestate;
		}
	}
	else if (GS == 10 || GS == 20||GS == 30||GS == 40){//enemy GUI
		EnemyGS(GS);
        ES = endstate(GS);
		if (ES == 0){
			if(player[0]>=1){
				printf("The Player has won against");
				gamestate = 200;
				return gamestate;
			}
			else{
				printf("the Player has died");
				gamestate = 0;
				return gamestate;
			}
		}
		else{
            system("clear");
            if(GS == 10){
			    printf("\nthere is 1 enemy:\n");
             }
            else{
               printf("\nThere are %d enemys:\n",GS/10); 
            } 
            Enemynames(GS);
			printf("\n\nWhat are you going to do:\n");
			printf("\nPlayer HP:%d         Player Mana%d\n",player[0],player[4]);
			printf("1: attack                  2: mana\n3: inventory               4: run \n");
			scanf("%d",&gamestate);
			gamestate += 10;
			return gamestate;
		}
	}
	else if(gamestate==15){//Go back to main EC menu
		gamestate = 692;
		return gamestate;
	}
	else if (GS == 11){//Player selected to attack
		system("clear");
		printf("you can attack the following enemys\npress anything else to go back\n");
		Enemynames(gamstat[2]);
		printf("\n");
		scanf("%d",&GS);
		if((GS>=1&&GS<=gamstat[2])){
			GS += 15;
			return GS;
		}
		else if (GS>=5){//player Wants to go to main menu
			GS = 15;
		}
	}
	else if(GS == 12){//player selecting special moves
		system("clear");
		printf("\nYou are choosing a spell \npress 1 to confirm\npress anything else to go back\n");
		scanf("%d",&GS);
		if(GS == 1){//incomplete
			GS += 25;	
			return GS;
		}
		else{//user wants to go back to CE main menu
			GS = 15;
			return GS;
		}			
	}	
	else if (GS == 13){//player inventory
		system("clear");
		printf("\nYou are in your inventory \npress the item you want to use\npress 9 to return to menu\n");
		scanf("%d",&GS);
		if (GS == 1){
			GS + 30;	
			return GS;
		}
		else{
			GS = 15;
			return GS;
		}
	}

	else if (GS == 14){//player ran LOL!
		system("clear");
		printf("you Pussy");
		sleep(2);
		GS = 0;
	}

	else if (GS==69||GS==692){//opsie daisy player didnt input the correct thing
			sleep (1);
			system("clear");
			printf ("nice; you entered a wrong value in console");	
			printf("\n%d\n",GS);
			gamestate = 1;
			return gamestate;
	}

	else if( GS>15&&GS<20){//game seeing what the player attacked 
		gamestate = 68;
		printf("player hit: %d damage\n",player[1]);
		return gamestate;
	}

	else if(GS==100){
		printf(" hillariously missed and is now standing there idle");
		GS = 1;
		return GS;
	}

	else if(GS==101){
		printf(" hit you with the force of 3 gods and dealt");
		GS = 2;
		return GS;
	}

	else if(GS==102){
		printf(" is healing it's wounds and regenerated");
		GS = 3;
		return GS;
	}

	else if(GS==103){
		printf(" has hit the player for");
		GS = 420;
	}
	else if(GS==200){
		printf("Do you want to continue playing?\nIf yes press anything other than 0");
		scanf("%d",&ES);
		if(ES==0){
			return ES;
		}
		else{
			ES = 1;
			return ES;
		}	
	}

	else{// error that should never apear unless something went horibly wrong with the gamestate or i havent completed that part yet
		system("clear");
		printf("GS not found GUI text not loaded");
		printf("\n GS code = %d",GS);
		sleep(2);
	}
}

int CE(int GS){ // Combat Engine is the main logic behind the combat and main events in the game.
	int Result,EQ,Turn=0,Temp,e;
	gamstat[4] = 0;
	while (GS >= 1){
	rng();
	Turn = gamstat[4]%2;
	e = rand()%3+1;
	if (gamstat[3] == 0){//enemy ids loading into memory
		
		EQ = EnemyQuant(dice[e]);
		gamstat[2] = EQ;
			for(int e = 12; e<=15; e++){//resets the id's
				enemStat[0][e] = 0;
			}
			for(int i = 0;i <= EQ; i++){//loads new id's in the code
			enemStat[0][i+7] = EnemyClass(dice[i]);	
		}
		EnemyDefault();
		gamstat[3] += 1;	
	}
	if (Turn==0){
		switch(GS){
			case 1 : //player interactions
				GS = (EQ*10);
				GS = menu(GS);
			break;
			case 11:
				GS = menu(GS);
			break;
			
			case 12:
				GS = menu(GS);
			break;

			case 13:
				GS = menu(GS);
			break;

			case 14:
				GS = menu(GS);
			break;
			
			case 69:
				GS = 69;
				GS = menu(GS);
			break;

			case 68:
				gamstat[4] +=1;
				printf("\nhahalol turnchanger player");
			break;
		}

		if (GS>15&&GS<20){
			Temp = GS-16; 
			if(enemStat[0][Temp]>=1){
			system("clear");
			gamstat[1] = GS-15;
			enemStat[0][Temp]-=player[1];
			GS = menu(GS);	
			}
			else{
				GS = 69;
				GS = menu(GS);
			}
		}
	}
	else{
	    system("clear");
    	printf("enemy turn\n");
		GS = endstate(EQ*10);
        if(GS!=0){
		    for(int I = 1; I<=EQ;I++){
                GS = 1;
                if(enemStat[0][I-1]>=1){ 
                    Enemynames(I);
    		        GS = enemystance(I);
		     	    GS = menu(GS);
    	        	switch(GS){
		    	    	case 1: 
        		    		GS=1;//the enemy missed hard lol
        		    	break;

	    	        	case 2:
	    			    	printf(" %d Damage OOF",(enemStat[1][I+3]*3));
	    		        	player[0] -= (enemStat[1][I+3]*3);
	    		    	break;

	    	    	    case 3:
	    	    		    printf(" %d HP",(enemStat[1][I+3]/2));
	        			    enemStat[0][I-1]+=(enemStat[1][I+3]/2);
          			    break;

	        		    default:
    	    			    printf(" %d Damage",enemStat[1][I+3]);
         				    player[0] -= enemStat[1][I+3];
    	    		    break;
        		    }
			        printf("\n");
                }
                else{
                    GS = 1;
                    Enemynames(I);
      		        printf("hes pretty dead ngl\n");
        		   
                }
				 
    		}
			sleep (1);
            GS = 1;
            gamstat[4]+=1;
        }
        else{
        printf("the Player has died");
        GS = 0;
        }
    }
	if(GS==200){
		GS = menu(GS);
		if(GS!=0){
			gamstat[3] = 0;
			player[0] = 500;
		}
	}
    }
}
 

int default_Data(){
    player[0] = 500;//player hp default (for now)
    player[1] = 100;//player attack 
    player[2] = 0; // player level
    player[3] = 1; //player xp
    player[4] = 100; //player mana (has no use curruntly lol)
}

int main() {
	int Turn,GS = 0;
	default_Data();
	GS = menu(GS);
	CE(GS);	
	}

/* data id
bye bye [0][0] i will always love u
enemStat[0]: enemy values (time has passed)
    Data 0  e1HP
    Data 1  e2HP
    Data 2  e3HP
    Data 3  e4HP
    Data 4 e1atk
    Data 5 e2atk
    Data 6 e3atk
    Data 7 e4atk
    Data 8 e1 id
    Data 9 e2 id
    Data 10 e3 id
    Data 11 e4 id
    Data 12 e1 life switch
    Data 13 e2 life switch
    Data 14 e3 life switch
    Data 15 e4 life switch

Data[1][0] I will always love you
    Data 0 Goblin base Hp
    Data 1 Skeliton base Hp
    Data 2 Witch base Hp
    Data 3 Orc base Hp 
    Data 4 Goblin base Atk
    Data 5 Skeleton base Atk
    Data 6 Witch Base Atk
    Data 7 Orc Base Atk

Data[3]: player inventory  (unused right now) 
    Data 0 to 7 Player inventory

gamestat: Game state data ()
    Data 0 intermediate memory
    Data 1 Enemy selected
    Data 2 Enemy quant
    Data 3 Bool enemy gen 
    Data 4 Current Turn

*/	