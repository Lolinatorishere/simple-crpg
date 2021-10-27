#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>

int Data[16][16];
 
int endstate (int enemyQ){
	int Gameend,temp;
	temp = (enemyQ/10)*2;
	Gameend = (Data[1][12]+Data[1][13]+Data[1][14]+Data[1][15]);
	if(((Gameend%temp)==0)&&(Data[15][4]>2)||(Data[0][0]<1)){
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
	I = (Data[15][4]%2);
	switch(I){
		case 0://playerside text with necessary info
			for(int e = 8 ;e<=(i+7); e++){
				x = Data[1][e];
     			Enamesshort(x);
				if (Data[1][e-8]<1){
            		printf(" (deceaced)\n");
      		  	}
				else if ((Data[15][4]%2)==0){
       				 printf(" HP %d Pos %d\n",Data[1][-8+e],e-7);
   				}
			}
		break;
	
		default://enemyside text with said info
			Enamesshort(Data[1][i+7]);
			if (Data[1][GS-1]<1){
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
		if (Data[1][I] == a){//data in Goblin
			if (Data[1][I+4]==0){
				Data[1][-8+I]=Data[2][0];
				Data[1][4+I] = 1;
			}
			else if ((Data[1][4+I]!=2)&&Data[1][I-8]<1){
				Data[1][4+I] = 2;
			}		
		}
		else if (Data[1][I] == b){//data in skeleton
			if (Data[1][4+I]==0){
				Data[1][-8+I]=Data[2][1];
				Data[1][4+I]=1;
			}
			else if ((Data[1][4+I]!=2)&&Data[1][I-8]<1){
				Data[1][4+I] = 2;
			}
		}
		else if (Data[1][I] == c){//data in Ork
		 	if (Data[1][4+I]==0){
				Data[1][-8+I]=Data[2][3];
				Data[1][4+I]=1;
			}
			else if ((Data[1][4+I]!=2)&&Data[1][I-8]<1){
				Data[1][4+I] = 2;
			}
		}
		else if (Data[1][I] == d){//data in Witch
			if (Data[1][4+I]==0){
				Data[1][-8+I]=Data[2][2];
				Data[1][4+I] = 1;
			}
			else if ((Data[1][4+I]!=2)&&Data[1][I-8]<1){
				Data[1][4+I] = 2;
			}	
		}
		else {
			Data[1][4+I] = 0;	
		}
}

int rng(){
	srand(time(NULL));
		int dice = rand()%10+1;
		return dice;	
}

int PlayerLevel(){//Responsible for Calculating the Players Current Level
	int CurLVL;
	if (Data[0][2]<46690){//the if statement caps the Level off at 30
	 CurLVL = Data [0][3];
		if(Data[0][3]<((CurLVL*50+100)*(CurLVL+1))){
			Data[0][3] = CurLVL;
		}
		else{
			Data[0][3] = CurLVL+1;
		}
	}
	else {
		Data[0][3] = CurLVL;
	}
}

int EnemyQuant(int dice){//RNG behind how many enemys can appear during a battle
	int a,GameDif,EnemyQ;	
	a = dice/2;
	GameDif = dice*Data[0][3];
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
	GameDif = dice*Data[0][3];// allows for more random enemy spawning
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
	 Data[2][0]= 600;//HP
	 Data[2][4] = 150;//Attack
	//second Enemy BONES
	 Data[2][1]= 300;
	 Data[2][5]= 100;
	//thirs enm witch
	 Data[2][2]= 200;
	 Data[2][6]= 100;
	//Fourt Enem ORC
	 Data[2][3] = 500;
	 Data[2][7]= 200;

}

int Enemssmall(int c){
    int Dice,a,b,GS;
    Dice = rng();
    a = Dice%2;//50% chance
	b = Dice%3;//30% chance
	//gs 102 is enemy heal; 103 is attack.
    switch(a){
    case 1:
	    GS = 100;//enemy miss
	break;

	case 9:
		GS = 101;//enemy critical hit
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
	Enemy = Data[1][I-1];
	a = (Data[2][I-1]/2);//metade da vida base de um inimigo
	b = (Data[2][I-1]/4);//um quarto da vida base de um inimigo
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
			printf("The Player has won the game yay!");
			gamestate = 0;
			return gamestate;
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
			printf("\nPlayer HP:%d         Player Mana%d\n",Data[0][0],Data[0][4]);
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
		Enemynames(Data[15][2]);
		printf("\n");
		scanf("%d",&GS);
		if((GS>=1&&GS<=Data[15][2])){
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
			sleep (2);
			system("clear");
			printf ("nice; you entered a wrong value in console");	
			printf("\n%d\n",GS);
			gamestate = 1;
			return gamestate;
	}

	else if( GS>15&&GS<20){//game seeing what the player attacked 
		gamestate = 68;
		printf("player hit: %d damage\n",Data[0][1]);
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

	else{// error that should never apear unless something went horibly wrong with the gamestate or i havent completed that part yet
		system("clear");
		printf("GS not found GUI text not loaded");
		printf("\n GS code = %d",GS);
		sleep(2);
	}
}

int CE(int GS){
	int dice,Result,EQ,Turn=0,Temp;
	Data[15][4] = 0;
	while (GS >= 1){
	dice = rng();
	Turn = Data[15][4]%2;
	
	if (Data[15][3] == 0){//enemy ids loading into memory
		
		EQ = EnemyQuant(dice);
		Data[15][2] = EQ;
			for(int e = 12; e<=15; e++){//resets the id's
				Data[1][e] = 0;
			}
			for(int i = 0;i <= EQ; i++){//loads new id's in the code
			dice = rng();
			sleep(1);
			Data[1][i+7] = EnemyClass(dice);	
		}
		EnemyDefault();
		Data[15][3] += 1;	
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
                    Data[15][4] +=1;
                    printf("\nhahalol turnchanger player");
                    sleep (1);
                break;
            }

		    if (GS>15&&GS<20){
				Temp = GS-16; 
				if(Data[1][Temp]>=1){
				system("clear");
				Data[15][1] = GS-15;
				Data[1][Temp]-=Data[0][1];
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
                if(Data[1][I-1]>=1){ 
                    Enemynames(I);
    		        GS = enemystance(I);
		     	    GS = menu(GS);
    	        	switch(GS){
		    	    	case 1: 
        		    		GS=1;//the enemy missed hard lol
        		    	break;

	    	        	case 2:
	    			    	printf(" %d Damage OOF",(Data[2][I+3]*3));
	    		        	Data[0][0] -= (Data[2][I+3]*3);
	    		    	break;

	    	    	    case 3:
	    	    		    printf(" %d HP",(Data[2][I+3]/2));
	        			    Data[1][I-1]+=(Data[2][I+3]/2);
          			    break;

	        		    default:
    	    			    printf(" %d Damage",Data[2][I+3]);
         				    Data[0][0] -= Data[2][I+3];
    	    		    break;
        		    }
			        printf("\n\n");
			        sleep (3);
                }
                else{
                    GS = 1;
                    Enemynames(I);
      		        printf("hes pretty dead ngl\n");
        		    sleep (2);
                }
    		}
            GS = 1;
            Data[15][4]+=1;
        }
        else{
        printf("the Player has died");
        GS = 0;
        }
    }
    }
}
 

int default_Data(){
	Data[0][0] = 500;
	Data[0][1] = 100;
	Data[0][2] = 0; 
	Data[0][3] = 1;
	Data[0][4] = 100;
}

int main() {
	int Turn,GS = 0;
	default_Data();
	GS = menu(GS);
	CE(GS);	
	}

/* data id
Data [0]:
    Data 0 Player HP
    Data 1 Player Attack
    Data 2 Player XP
    Data 3 Player LVL
    Data 4 Player Mana 

Data[1]: enemy values
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

Data[2]: base game values
    Data 0 Goblin base Hp
    Data 1 Skeliton base Hp
    Data 2 Witch base Hp
    Data 3 Orc base Hp 
    Data 4 Goblin base Atk
    Data 5 Skeleton base Atk
    Data 6 Witch Base Atk
    Data 7 Orc Base Atk

Data[3]: player inventory    
    Data 0 to 7 Player inventory

Data[15]: Game state data
    Data 0 intermediate memory
    Data 1 Enemy selected
    Data 2 Enemy quant
    Data 3 Bool enemy gen 
    Data 4 Current Turn

*/