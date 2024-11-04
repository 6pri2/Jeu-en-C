#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <unistd.h>
#include "board.h"
#include "historical.h"
#define MAX 100

void choose_pseudo(char *pseudo1,char *pseudo2){
	printf("Choose your 2 in game name :\n");
	printf("1 : ");
	scanf("%s",pseudo1);
	printf("2 : ");
	scanf("%s",pseudo2);
	
	
}

void affiche_plateau (board g, char *pseudo1, char *pseudo2){
	//affichage du plateau de jeu
	int num;
	printf("\33[H\33[2J\n           \033[34mNORTH %s\033[37m\n    ",pseudo1);
	for (int k=0; k<6;k++){
		printf("\e[1;90m %d  \033[37m",k+1);
	}
	printf("\n   ");
	for (int k=0; k<6;k++){
		printf("----");
	}
	printf("-\n");
	for (int i=0; i<6;i++){
		//affichage du numéro dans la case
		printf("\e[1;90m%d \033[37m",i+1);
		for (int j=0;j<6;j++){
			printf(" | ");
			num = get_digit(g,i,j);
			printf("%d",num);
		}
		printf(" |\n  ");
		//affichage du pion, roi ou  rien
		for (int j=0;j<6;j++){
			printf(" | ");
		if (get_place_holder(g,i,j)==2){
				printf("\033[31m" );
			}
			else if (get_place_holder(g,i,j)==1){
				printf("\033[34m" );
			}
		if (get_place_holder(g,i,j) != NO_PLAYER){
				if (is_king(g,i,j)==1){
					printf("♚\033[37m");
				}
				else {
					printf("♟\033[37m");
				}
			
		}
		else {
			printf(" \033[37m");
		}
		}

		printf(" |\n   ");
		for (int k=0; k<6;k++){
			printf("----");
		}
		printf("-\n");
	}
	printf("           \033[31mSOUTH %s\033[37m\n\n", pseudo2);
}

void placer_pion( board g, char *pseudo1, char *pseudo2){
	//Place tous les pion d'un joueur
	int column;
	int line;
	while (piece_to_place(g)!=NONE){
		if (current_player(g)==1){
			printf("Joueur North %s, ",pseudo1);
		}
		else if (current_player(g)==2){
			printf("Joueur South %s, ", pseudo2);
		}
		if (piece_to_place(g)==2){
			printf("please enter the King's coordinates : \nLine : ");
		}
		else{
			printf("please enter the pawn's coordinates : \nLine : ");
		}
		while(scanf("%d",&line)==0){
			getchar();
		}
		printf("Column : ");
		while(scanf("%d",&column)==0){
			getchar();
		}
		while (place_piece(g,line-1,column-1)!=OK && place_piece(g,line-1,column-1)!=STAGE ){
			switch (place_piece(g,line-1,column-1)){
				case STAGE :
					printf("End of pawn placement for this player");
					break;
				case OUT :
					printf("The coordinates are incorrect");
					break;
				case RULES :
					printf("You have entered an opponent's square ");
					break;
				case BUSY:
					printf("The square is already occupied");
					break;
				case OK :
					printf("Successful placement ");
					break;
			}				
			printf("\nPlease type again : \nLine : ");
			while(scanf("%d",&line)==0){
				getchar();
			}
			printf("Column : ");
			while(scanf("%d",&column)==0){
				getchar();
			}
		}
		affiche_plateau(g,pseudo1,pseudo2);
	}
}
	
void choice_quick_move (board g,char *pseudo1, char *pseudo2){
    //Fonctionc demandant le quick move
	int line_depart;
	int column_depart;
	int line_arrivee;
	int column_arrivee;
	if (current_player(g)==1){
		printf("Joueur North %s, ", pseudo1);
	}
	else if (current_player(g)==2){
		printf("Joueur South %s, ", pseudo2);
	}
	printf("please select the start sqaure : \nLine : ");
	while(scanf("%d",&line_depart)==0){
		getchar();
	}
	printf("Column : ");
	while(scanf("%d",&column_depart)==0){
		getchar();
	}
	printf("Please select the arrival square : \nLine : ");
	while(scanf("%d",&line_arrivee)==0){
		getchar();
	}
	printf("Column : ");
	while(scanf("%d",&column_arrivee)==0){
		getchar();
	}
	while (quick_move(g,line_depart-1, column_depart-1, line_arrivee-1, column_arrivee-1)!=OK){
		switch (quick_move(g,line_depart-1, column_depart-1, line_arrivee-1, column_arrivee-1)){
			case BUSY:
				printf("This piece is not yours");
				break;
			case RULES :
				printf("Unauthorized movement");
				break;
			case STAGE :
				printf("Unfinished set-up !");
				break;
			case OUT :
				printf("Invalid coordinates");
				break;
			case OK :
				printf("Successful move");
				break;
			}
			printf("\nplease go back to square one : \nLine : ");
			while(scanf("%d",&line_depart)==0){
				getchar();
			}
			printf("Column : ");
			while(scanf("%d",&column_depart)==0){
				getchar();
			}
			printf("\nPlease re-enter the arrival box : \nLine : ");
			while(scanf("%d",&line_arrivee)==0){
				getchar();
			}
			printf("Column : ");
			while(scanf("%d",&column_arrivee)==0){
				getchar();
			}
	}
	affiche_plateau (g,pseudo1,pseudo2);
}

int autorise_inserer(board g){
    //regarde si l'utilisateur peut inserer
	if (get_nb_pieces_on_board(g,current_player(g))==NB_INITIAL_PIECES){
		return 1;
	}
	for (int i=0;i<DIMENSION;i++){
		for (int j=0;j<DIMENSION;j++){
			if (get_digit(g,i,j)==get_prescribed_move(g) && current_player(g)==get_place_holder(g,i,j) && is_legal_move(g,i,j)){
				return 1;
			}
		}
	}
	return 0;
}

void insertion_pion(board g){
    //fonction insérant pion
	int line=0;
	int column=0;
	printf("Where do you want to place your pawn ?  : \nLine : ");
	while(scanf("%d",&line)==0){
		getchar();
	}
	printf("Column : ");
	while(scanf("%d",&column)==0){
		getchar();
	}
	while (insert_pawn(g,line-1,column-1)!=OK){
		printf("Coordinate error.\nWhere do you want to place your pawn?  : \nLine : ");
		while(scanf("%d",&line)==0){
			getchar();
		}
		printf("Column : ");
		while(scanf("%d",&column)==0){
			getchar();
		}
	}
	insert_pawn(g,line-1,column-1);
}

void party(){
	//fonction générale
	char pseudo1[MAX];
	char pseudo2[MAX];
	choose_pseudo(pseudo1,pseudo2);
	//
	//choix du plateau 
	board g;
	printf("Type 1 if you want standard board or type 2 for random board :");
	int ins=0;
	while (ins!=1 && ins!=2){
			while(scanf("%d", &ins)==0){
		getchar();
		}
	}
	if (ins==1){
		g = new_game();
	}
	else if (ins==2){
		g = new_random_game();
	}
	//affichage et placer pion
	affiche_plateau (g,pseudo1,pseudo2);
	placer_pion(g, pseudo1, pseudo2);
	//debut de partie 
	while (get_winner(g)==NO_PLAYER){
		if (autorise_inserer(g)==0){
			printf("You can't make any moves\n");
			if (get_nb_pieces_on_board(g,current_player(g)) < NB_INITIAL_PIECES){
				printf("Type 1 if you want to reinsert a pawn on the board or 0 if you want to play a pawn.\n");
				while(scanf("%d", &ins)==0){
					getchar();
				}
				if (ins==1){
					insertion_pion(g);
				}
				else if (ins==0){
					printf("bug");
				}
			}
		}
		else {
			choice_quick_move(g,pseudo1,pseudo2);
			//mouv_step(g);
			//choice_move_one_step(g);
		}
		affiche_plateau(g,pseudo1,pseudo2);
	}
	if (get_winner(g)==NORTH){
		printf("\33[H\33[2JThe winner is the player %s \033[34mNORTH\033[37m\n",pseudo1);
        add_score(pseudo1,pseudo2);
	}
	else {
		printf("\33[H\33[2JThe winner is the player %s \033[31mSOUTH\n",pseudo2);
        add_score(pseudo2,pseudo1);
	}
    //everything_to_display_leader();
}

int main(){
	srand(time(NULL));
    //ask if the person wants to play or look at the leaderboard
    printf("do you want to watch the leaderboard (1) or play (2) ?");
    int rep;
    while (rep!=1 && rep!=2){
		while(scanf("%d", &rep)==0){
		    getchar();
		}
	}
    if (rep==1){
        everything_to_display_leader();
    }
    else if(rep==2){
        party();
    }
}
