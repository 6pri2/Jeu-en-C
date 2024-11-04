#include <stdio.h>
#include <stdlib.h>
#include "board.h"

/**
 * \file board.c
 *
 * \brief Source code associated with \ref board.h
 *
 * \author you
 */

/**
 * @brief The board of the game.
 */
 
typedef struct{
	int l_start;
	int c_start;
	int l_movement;
	int c_movement;
	int l_final_movement;
	int c_final_movement;
}selected_piece;

typedef struct {
	type piece;
	player pl;
}pion;

typedef struct{
	int digit;
	pion  pi;
}square;

struct board_s{
	square tab[DIMENSION][DIMENSION];
	player current_play;
	int current_prescribed_move;
	selected_piece selection;
	int remain_strockes;
};

typedef struct board_s * board;

board new_game(){
	board new_board = malloc(sizeof(struct board_s));
	pion p;
	p.piece=NONE;
	p.pl=NO_PLAYER;

	for(int line = 0; line < DIMENSION; line++){
    	int digi = (2 * NB_DIGITS - line) % NB_DIGITS;
    	for(int column = 0; column < DIMENSION; column++){
			square s;
      		s.digit = digi + 1;
      		digi = (digi + 1 + (line % 2)) % NB_DIGITS;
			s.pi=p;
			new_board->tab[line][column]=s;
    	}
	}
	new_board->current_play=NORTH;
	new_board->current_prescribed_move=-1;
	new_board->remain_strockes=0;
	selected_piece sp;
	sp.l_start=-1;
	sp.c_start=-1;
	sp.l_movement=-1;
	sp.c_movement=-1;
	sp.l_final_movement=-1;
	sp.c_final_movement=-1;
	new_board->selection=sp;
	return new_board;
}

board copy_game(board original_game){
	board new_board = malloc(sizeof(struct board_s));
	for (int line=0;line<DIMENSION;line++){
		for (int column=0;column<DIMENSION;column++){
			new_board->tab[line][column]=original_game->tab[line][column];	
		}
	}
	new_board->current_play=original_game->current_play;
	new_board->current_prescribed_move=original_game->current_prescribed_move;
	new_board->selection.l_start=original_game->selection.l_start;
	new_board->selection.c_start=original_game->selection.c_start;
	new_board->selection.l_movement=original_game->selection.l_movement;
	new_board->selection.c_movement=original_game->selection.c_movement;
	new_board->selection.l_final_movement=original_game->selection.l_final_movement;
	new_board->selection.c_final_movement=original_game->selection.c_final_movement;
	return new_board;
}

void destroy_game(board game){
	free(game);
};

board new_random_game(){
	//Defines a new random empty board for starting a game.
	board new_board = malloc(sizeof(struct board_s));
	pion p;
	p.piece=NONE;
	p.pl=NO_PLAYER;
	int un=4;
	int deux=4;
	int trois=4;
	for (int line=0;line<DIMENSION;line++){
		square s;
		for (int column=0;column<DIMENSION;column++){
			if((line<=2)||(line>(DIMENSION-3))){
				if(un>0 && deux>0 && trois>0){
					s.digit=(rand()%3)+1;
				}
				else if (un==0 && deux==0){
					s.digit=3;
				}
				else if(un==0 && trois==0){
					s.digit=2;
				}
				else if(deux==0 && trois==0){
					s.digit=1;
				}
				else if(un==0){
					s.digit=(rand()%2)+2;
				}
				else if(deux==0){
					s.digit=(rand()%2)+1;
					if(s.digit==2){
						s.digit++;
					}
				}
				else{
					s.digit=(rand()%2)+1;
				}
				switch (s.digit){
						case 1:
							un--;
							break;
						case 2:
							deux--;
							break;
						case 3:
							trois--;
							break;
					}
			}
			else{
				s.digit=(rand()%3)+1;
			}
			s.pi=p;			
			new_board->tab[line][column]=s;
		}
	if (line==2){
		un=4;
		deux=4;
		trois=4;
		}
	}
	new_board->current_play=NORTH;
	new_board->current_prescribed_move=-1;
	new_board->remain_strockes=0;
	selected_piece sp;
	sp.l_start=-1;
	sp.c_start=-1;
	sp.l_movement=-1;
	sp.c_movement=-1;
	sp.l_final_movement=-1;
	sp.c_final_movement=-1;
	new_board->selection=sp;
	return new_board;
}

bool on_board (board game, int line, int column){
	if ((line>=DIMENSION || line<0)||(column>=DIMENSION || column<0)){
		return false;
	}
	return true;
}
int get_digit (board game, int line, int column){
	if(on_board(game,line,column)==false){
		return 0;
	}
	//returns the digit displayed by the corresponding square
	return game->tab[line][column].digit;
}

player current_player(board game){
	//return the player whose turn it is to play. 
	return game-> current_play;
}

int get_prescribed_move (board game){
	//return the digit prescribed for the next move
	return game -> current_prescribed_move;
}

player get_place_holder(board game, int line, int column){
	//returns the player holding the indicated place. 
	return game->tab[line][column].pi.pl;
}

bool is_king (board game, int line, int column){
	//returns true if there is a king at the given position, false otherwise 
	return game->tab[line][column].pi.piece==KING;
}

player get_winner (board game){
	//Checks whether the game has a winner already
	int north_king_flag=0;
	int south_king_flag=0;
	for (int line=0;line<DIMENSION;line++){
		for (int column=0;column<DIMENSION;column++){
			if(is_king(game,line,column)&& get_place_holder(game,line,column)==NORTH){
						north_king_flag++;
			}else if(is_king(game,line,column) && get_place_holder(game,line,column)==SOUTH){
						south_king_flag++;
					}
				}
	}
	if(north_king_flag>south_king_flag){
		return NORTH;
	}else if(north_king_flag<south_king_flag){
		return SOUTH;
	}
	return NO_PLAYER;
}

int get_nb_pieces_on_board (board game, player checked_player){
	//Returns the number of pieces of the given player on the board.
	int counter = 0;
	for (int line=0;line<DIMENSION;line++){
		for (int column=0;column<DIMENSION;column++){
			if (get_place_holder(game,line,column)==checked_player){
				counter++;
			}
		}
	}
	return counter;
}

type piece_to_place(board game){
	//indicates which piece the current player should place. 
	if(get_nb_pieces_on_board(game,game->current_play)==0){
		return KING;
	}else if(get_nb_pieces_on_board(game,game->current_play)>0&&get_nb_pieces_on_board(game,game->current_play)<6){
		return PAWN;
	}
	return NONE;
}



enum return_code place_piece (board game, int line, int column){
	//adds a piece on the board on the given position. 
	if(game->current_prescribed_move!=-1){
		return STAGE;
	}
	else if (on_board(game, line, column)==false){
		return OUT;
	}
	else if((game->current_play==NORTH && line >=2)||(game->current_play==SOUTH && line<DIMENSION-2)){
		return RULES;
	}
	else if(game->tab[line][column].pi.piece!=NONE){
		return BUSY;
	}
	else {
		game->tab[line][column].pi.piece=(piece_to_place(game));
		game->tab[line][column].pi.pl=(game->current_play);
		if((game->current_play==NORTH)&&(get_nb_pieces_on_board(game,NORTH)==6)){
			game->current_play=SOUTH;
		}
		else if((game->current_play==SOUTH)&&(get_nb_pieces_on_board(game,SOUTH)==6)){
			game->current_play=NORTH;
			game->current_prescribed_move=0;
		}
		return OK;
	}
	return OK;
}

bool is_not_surround(board game, int line, int column){
	//return true if the pice can move 
	if (get_digit(game,line,column)==1){
		if(on_board(game, line-1,column)==true||on_board(game, line+1,column)||on_board(game,line,column+1)==true||on_board(game,line,column-1)==true){
			return true;
		}
	}
	else if(get_digit(game,line,column)==2){
		if (on_board(game,line-1,column)==true && game->tab[line-1][column].pi.pl==NO_PLAYER&&(on_board(game,line-2,column)==true||on_board(game,line-1,column-1)==true||on_board(game,line-1,column+1)==true)){
			return true;
		}
		else if(on_board(game,line+1,column)==true && game->tab[line+1][column].pi.pl==NO_PLAYER&&(on_board(game,line+2,column)==true||on_board(game,line+1,column-1)==true||on_board(game,line+1,column+1)==true)){
			return true;
		}
		else if(on_board(game,line,column-1)==true && game->tab[line][column-1].pi.pl==NO_PLAYER&&(on_board(game,line,column-2)==true||on_board(game,line+1,column-1)==true||on_board(game,line-1,column-1)==true)){
			return true;
		}
		else if(on_board(game,line,column+1)==true && game->tab[line][column+1].pi.pl==NO_PLAYER&&(on_board(game,line,column+2)==true||on_board(game,line+1,column+1)==true||on_board(game,line-1,column+1)==true)){
			return true;
		}
	}
	else if(get_digit(game,line,column)==3){
		if (on_board(game,line-1,column)==true && game->tab[line-1][column].pi.pl==NO_PLAYER){
			if (on_board(game,line-2,column)==true && game->tab[line-2][column].pi.pl==NO_PLAYER){
				if (on_board(game,line-3,column)==true || on_board(game,line-2,column-1)==true || on_board(game,line-2,column+1)==true){
					return true;
				}
			}
			else if(on_board(game,line-1,column-1)==true && game->tab[line-1][column-1].pi.pl==NO_PLAYER){
				if (on_board(game,line-2,column-1)==true || on_board(game,line,column-1)==true || on_board(game,line-1,column+2)==true){
					return true;
				}
			}
			else if(on_board(game,line-1,column+1)==true && game->tab[line-1][column+1].pi.pl==NO_PLAYER){
				if (on_board(game,line-2,column+1)==true || on_board(game,line,column+1)==true || on_board(game,line-1,column+2)==true){
					return true;
				}
			}
		}
		else if(on_board(game,line+1,column)==true && game->tab[line+1][column].pi.pl==NO_PLAYER){
			if (on_board(game,line+2,column)==true && game->tab[line-2][column].pi.pl==NO_PLAYER){
				if (on_board(game,line+3,column)==true || on_board(game,line+2,column-1)==true || on_board(game,line+2,column+1)==true){
					return true;
				}
			}
			else if(on_board(game,line+1,column+1)==true && game->tab[line+1][column+1].pi.pl==NO_PLAYER){
				if (on_board(game,line+1,column+2)==true || on_board(game,line+2,column+1)==true || on_board(game,line,column+1)==true){
					return true;
				}
			}
			else if(on_board(game,line+1,column-1)==true && game->tab[line+1][column-1].pi.pl==NO_PLAYER){
				if (on_board(game,line+1,column-2)==true || on_board(game,line,column-1)==true || on_board(game,line+2,column-1)==true){
					return true;
				}
			}
		}
		else if(on_board(game,line,column-1)==true && game->tab[line][column-1].pi.pl==NO_PLAYER){
			if (on_board(game,line,column-2)==true && game->tab[line][column-2].pi.pl==NO_PLAYER){
				if (on_board(game,line,column-3)==true || on_board(game,line+1,column-2)==true || on_board(game,line-1,column-2)==true){
					return true;
				}
			}
			else if(on_board(game,line+1,column-1)==true && game->tab[line+1][column-1].pi.pl==NO_PLAYER){
				if (on_board(game,line+2,column-1)==true || on_board(game,line+1,column)==true || on_board(game,line+1,column-2)==true){
					return true;
				}
			}
			else if(on_board(game,line-1,column-1)==true && game->tab[line-1][column-1].pi.pl==NO_PLAYER){
				if (on_board(game,line-2,column-1)==true || on_board(game,line-1,column-2)==true || on_board(game,line-1,column)==true){
					return true;
				}
			}
		}
		else if (on_board(game,line,column+1)==true && game->tab[line][column+1].pi.pl==NO_PLAYER){
			if (on_board(game,line,column+2)==true && game->tab[line][column+2].pi.pl==NO_PLAYER){
				if (on_board(game,line,column+3)==true || on_board(game,line-1,column+2)==true || on_board(game,line+1,column+2)==true){
					return true;
				}
			}
			else if(on_board(game,line+1,column+1)==true && game->tab[line+1][column+1].pi.pl==NO_PLAYER){
				if (on_board(game,line+2,column+1)==true || on_board(game,line+1,column)==true || on_board(game,line+1,column+2)==true){
					return true;
				}
			}
			else if(on_board(game,line-1,column+1)==true && game->tab[line-1][column+1].pi.pl==NO_PLAYER){
				if (on_board(game,line-2,column+1)==true || on_board(game,line-1,column)==true || on_board(game,line-1,column+2)==true){
					return true;
				}
			}
		}
	}
	return false;
}

bool is_possible(board game){
	//Return true if the player can play with the digit currently or false
	for (int i=0;i<DIMENSION;i++){
		for (int j=0;j<DIMENSION;j++){
			if(get_place_holder(game,i,j)==game->current_play && get_digit(game,i,j)==game->current_prescribed_move && is_not_surround(game,i,j)==true){
				return true; 
			}
		}
	}
	return false ;
}


bool is_legal_move(board game, int line, int column){
	//states whether the piece at the indicated place may be moved.
	if(game->current_prescribed_move==-1||game->selection.l_start!=-1){
		//pas le bon moment 
		return false;
	}
	else if(on_board(game, line, column)==false){
		//Pas dans la grille 
		return false;
	}
	else if (game->tab[line][column].pi.pl!=game->current_play){
		//pas le pion du joueur 
		return false;
	}
	else if(get_digit(game,line,column)!=game->current_prescribed_move&&game->current_prescribed_move!=0){
		//Test du digit 
		if (is_possible(game)==true){
			return false;
		}
	}
	return true ;
}



enum return_code select_piece (board game, int line, int column){
	//Allow the current plaer to select which piece to move
	if (on_board(game,line,column)==false){
		return OUT;
	}
	else if ((game->current_prescribed_move==-1) || game->selection.l_start!=-1 || game->selection.c_start!=-1 || game->selection.l_movement != -1 || game->selection.c_movement != -1 ||game->selection.c_final_movement!=-1||game->selection.l_final_movement!=-1){
		return STAGE;
	}
	else if (game->tab[line][column].pi.pl!=game->current_play){
		return BUSY;
	}
	else if (((game->current_prescribed_move!=game->tab[line][column].digit)&&game->current_prescribed_move!=0&&is_possible(game)==true)){//||(is_not_surround(game,line,column)==false)
		return RULES;
	}
	game->selection.l_start=line;
	game->selection.c_start=column;
	game->remain_strockes=game->tab[line][column].digit;
	return OK;
}

enum return_code cancel_move(board game){
	//cancel a started move, and unselect any selected piece, returning to the previous state of the game.
	if(game->current_prescribed_move==-1||game->selection.l_start==-1||game->selection.c_start==-1){ 
		return STAGE;
	}
	game->selection.l_start= -1;
	game->selection.c_start= -1;
	game->selection.l_movement= -1;
	game->selection.c_movement= -1;
	game->selection.l_final_movement= -1;
	game->selection.c_final_movement= -1;
	game->remain_strockes= 0;
	return OK;
}

enum return_code insert_pawn (board game, int line, int column){
	//Inserts a pawn took earlier at the given position. 
	if(on_board(game,line,column)==false){
		return OUT;
	}
	else if(game->current_prescribed_move==-1||game->selection.l_start!=-1||game->selection.c_start!=-1){
		return STAGE;
	}
	else if(game->tab[line][column].pi.pl!=NO_PLAYER){
		return BUSY;
	}
	else if(get_nb_pieces_on_board(game,game->current_play)==6){
		return RULES;
	}
	else if(game->current_prescribed_move!=game->tab[line][column].digit){
		return RULES;
	}
	for (int i =0; i<DIMENSION;i++){
		for(int j=0;j<DIMENSION;j++){
			if (game->current_prescribed_move!=game->tab[i][j].digit && is_legal_move(game,i,j)==true && game->tab[i][j].pi.pl==game->current_play){
				return RULES;
			}
		}
	}
	game->tab[line][column].pi.piece=PAWN;
	game->tab[line][column].pi.pl=game->current_play;
	if (game->current_play==NORTH){
		game->current_play=SOUTH;
	}
	else {
		game->current_play=NORTH;
	}
	return OK;
}

enum return_code move_one_step (board game, direction direct){
	//moves the currently selected piece one step in the required direction
	
	if(game->selection.l_start==-1 && game->selection.c_start==-1){
		printf("Mauvaise selection");
		return STAGE;
	}
	int l;
	int c;
	if (game->selection.c_final_movement!=-1){
		c=game->selection.c_final_movement;
		l=game->selection.l_final_movement;
	}
	else if(game->selection.c_movement!=-1){
		c=game->selection.c_movement;
		l=game->selection.l_movement;
	}
	else{
		c=game->selection.c_start;
		l=game->selection.l_start;
	}
	switch (direct){
		case N:
			l--;
			break;
		case S:
			l++;
			break;
		case E:
			c++;
			break;
		case W:
			c--;
			break;	
	}
	if ((game->selection.c_start==game->selection.c_movement&&game->selection.l_start==game->selection.l_movement&&game->selection.l_movement!=-1)
||(game->selection.c_start==game->selection.c_final_movement&&game->selection.l_start==game->selection.l_final_movement&&game->selection.l_movement!=-1)
||(game->selection.c_start==c && game->selection.l_start==l)
||(game->selection.c_movement==c && game->selection.l_movement==l)
||(game->selection.c_final_movement==c && game->selection.l_final_movement==l)
||(game->selection.c_movement==game->selection.c_final_movement&&game->selection.l_movement==game->selection.l_final_movement&&game->selection.l_final_movement!=-1)){
		return RULES;
	}
	if(on_board(game,l,c)==false){
		return OUT;
	}
	else if((game->tab[l][c].pi.piece!=NONE&&game->remain_strockes>1)||(game->remain_strockes==1 && game->tab[l][c].pi.pl==game->current_play)){
		return BUSY;
	}
	if(game->remain_strockes==3){
		game->selection.l_movement=l;
		game->selection.c_movement=c;
	}
	else if(game->remain_strockes==2){
		game->selection.l_final_movement=l;
		game->selection.c_final_movement=c;		
	}
	else if(game->remain_strockes==1){		
		game->tab[l][c].pi.piece=game->tab[game->selection.l_start][game->selection.c_start].pi.piece;
		game->tab[game->selection.l_start][game->selection.c_start].pi.piece=NONE;
		game->tab[l][c].pi.pl=game->tab[game->selection.l_start][game->selection.c_start].pi.pl;
		game->tab[game->selection.l_start][game->selection.c_start].pi.pl=0;
		game->selection.l_start=-1;
		game->selection.c_start=-1;
		game->selection.l_movement=-1;
		game->selection.c_movement=-1;
		game->selection.l_final_movement=-1;
		game->selection.c_final_movement=-1;
		if(game->current_play==NORTH){
			game->current_play=SOUTH;
		}
		else {
			game->current_play=NORTH;
		}
		game->current_prescribed_move=game->tab[l][c].digit;
	}
	game->remain_strockes--;
	return OK;
}

bool is_good_move(board game, int line, int column,int finish_line, int finish_column){
	//Renvoie true si le deplacement finish marche et false sinon
	if (game->tab[line][column].digit==1){
		if(on_board(game, line-1,column)==true||on_board(game, line+1,column)||on_board(game,line,column+1)==true||on_board(game,line,column-1)==true){
			if((line-1==finish_line &&column==finish_column)||(line+1==finish_line && column==finish_column)||(line==finish_line && column+1==finish_column)|(line==finish_line&&column-1==finish_column)){
			return true;
			}
		}
	}
	else if(game->tab[line][column].digit==2){
		if (on_board(game,line-1,column)==true && game->tab[line-1][column].pi.pl==NO_PLAYER&&(on_board(game,line-2,column)==true||on_board(game,line-1,column-1)==true||on_board(game,line-1,column+1)==true)){
			if ((line-2==finish_line&&column==finish_column)||(line-1==finish_line&&column-1==finish_column)||(line-1==finish_line&&column+1==finish_column)){
				return true;
			}
		}
		if(on_board(game,line+1,column)==true && game->tab[line+1][column].pi.pl==NO_PLAYER&&(on_board(game,line+2,column)==true||on_board(game,line+1,column-1)==true||on_board(game,line+1,column+1)==true)){
			if((line+2==finish_line&&column==finish_column)||(line+1==finish_line&&column-1==finish_column)||(line+1==finish_line&&column==finish_column)){
				return true;
			}
		}
		if(on_board(game,line,column-1)==true && game->tab[line][column-1].pi.pl==NO_PLAYER&&(on_board(game,line,column-2)==true||on_board(game,line+1,column-1)==true||on_board(game,line-1,column-1)==true)){
			if((line==finish_line&&column-2==finish_column)||(line+1==finish_line&&column-1==finish_column)||(line-1==finish_line&&column-1==finish_column)){
				return true;
			}
		}
		if(on_board(game,line,column+1)==true && game->tab[line][column+1].pi.pl==NO_PLAYER&&(on_board(game,line,column+2)==true||on_board(game,line+1,column+1)==true||on_board(game,line-1,column+1)==true)){
			if((line==finish_line&&finish_column==column+2)||(line+1==finish_line&&column+1==finish_column)||(line-1==finish_line&&column+1==finish_column)){
				return true;
			}
		}
	}
	else if(game->tab[line][column].digit==3){
		if (on_board(game,line-1,column)==true && game->tab[line-1][column].pi.pl==NO_PLAYER){
			if (on_board(game,line-2,column)==true && game->tab[line-2][column].pi.pl==NO_PLAYER){
				if (on_board(game,line-3,column)==true || on_board(game,line-2,column-1)==true || on_board(game,line-2,column+1)==true){
					if ((line-3==finish_line&&column==finish_column)||(line-2==finish_line&&column-1==finish_column)||(line-2==finish_line&&column+1==finish_column)){
						return true;
					}
				}
			}
			if(on_board(game,line-1,column-1)==true && game->tab[line-1][column-1].pi.pl==NO_PLAYER){
				if (on_board(game,line-2,column-1)==true || on_board(game,line,column-1)==true || on_board(game,line-1,column+2)==true){
					if ((line-2==finish_line&&column-1==finish_column)||(line==finish_line&&column-1==finish_column)||(line-1==finish_line&&column+2==finish_column)){
						return true;
					}
				}
			}
			if(on_board(game,line-1,column+1)==true && game->tab[line-1][column+1].pi.pl==NO_PLAYER){
				if (on_board(game,line-2,column+1)==true || on_board(game,line,column+1)==true || on_board(game,line-1,column+2)==true){
					if ((line-2==finish_line&&column+1==finish_column)||(line==finish_line&&column+1==finish_column)||(line-1==finish_line&&column+2==finish_column)){
						return true;
					}
				}
			}
		}
		if(on_board(game,line+1,column)==true && game->tab[line+1][column].pi.pl==NO_PLAYER){
			if (on_board(game,line+2,column)==true && game->tab[line-2][column].pi.pl==NO_PLAYER){
				if (on_board(game,line+3,column)==true || on_board(game,line+2,column-1)==true || on_board(game,line+2,column+1)==true){
					if ((line+3==finish_line&&column==finish_column)||(line+2==finish_line&&column-1==finish_column)||(line+2==finish_line&&column+1==finish_column)){
						return true;
					}
				}
			}
			if(on_board(game,line+1,column+1)==true && game->tab[line+1][column+1].pi.pl==NO_PLAYER){
				if (on_board(game,line+1,column+2)==true || on_board(game,line+2,column+1)==true || on_board(game,line,column+1)==true){
					if ((line+1==finish_line&&column+2==finish_column)||(line+2==finish_line&&column+1==finish_column)||(line=finish_line&&column+1==finish_column)){
						return true;
					}
				}
			}
			if(on_board(game,line+1,column-1)==true && game->tab[line+1][column-1].pi.pl==NO_PLAYER){
				if (on_board(game,line+1,column-2)==true || on_board(game,line,column-1)==true || on_board(game,line+2,column-1)==true){
					if ((line+1==finish_line&&column-2==finish_column)||(line==finish_line&&column-1==finish_column)||(line+2==finish_line&&column-1==finish_column)){
						return true;
					}
				}
			}
		}
		if(on_board(game,line,column-1)==true && game->tab[line][column-1].pi.pl==NO_PLAYER){
			if (on_board(game,line,column-2)==true && game->tab[line][column-2].pi.pl==NO_PLAYER){
				if (on_board(game,line,column-3)==true || on_board(game,line+1,column-2)==true || on_board(game,line-1,column-2)==true){
					if ((line==finish_line&&column-3==finish_column)||(line+1==finish_line&&column-2==finish_column)||(line-1==finish_line&&column-2==finish_column)){
						return true;
					}
				}
			}
			if(on_board(game,line+1,column-1)==true && game->tab[line+1][column-1].pi.pl==NO_PLAYER){
				if (on_board(game,line+2,column-1)==true || on_board(game,line+1,column)==true || on_board(game,line+1,column-2)==true){
					if ((line+2==finish_line&&column-1==finish_column)||(line+1==finish_line&&column==finish_column)||(line+1==finish_line&&column-2==finish_column)){
						return true;
					}
				}
			}
			if(on_board(game,line-1,column-1)==true && game->tab[line-1][column-1].pi.pl==NO_PLAYER){
				if (on_board(game,line-2,column-1)==true || on_board(game,line-1,column-2)==true || on_board(game,line-1,column)==true){
					if ((line-2==finish_line&&column-1==finish_column)||(line-1==finish_line&&column-2==finish_column)||(line-1==finish_line&&column==finish_column)){
						return true;
					}
				}
			}
		}
		if (on_board(game,line,column+1)==true && game->tab[line][column+1].pi.pl==NO_PLAYER){
			if (on_board(game,line,column+2)==true && game->tab[line][column+2].pi.pl==NO_PLAYER){
				if (on_board(game,line,column+3)==true || on_board(game,line-1,column+2)==true || on_board(game,line+1,column+2)==true){
					if ((line==finish_line&&column+3==finish_column)||(line-1==finish_line&&column+2==finish_column)||(line+1==finish_line&&column+2==finish_column)){
						return true;
					}
				}
			}
			if(on_board(game,line+1,column+1)==true && game->tab[line+1][column+1].pi.pl==NO_PLAYER){
				if (on_board(game,line+2,column+1)==true || on_board(game,line+1,column)==true || on_board(game,line+1,column+2)==true){
					if ((line+2==finish_line&&column+1==finish_column)||(line+1==finish_line&&column==finish_column)||(line+1==finish_line&&column+2==finish_column)){
						return true;
					}
				}
			}
			if(on_board(game,line-1,column+1)==true && game->tab[line-1][column+1].pi.pl==NO_PLAYER){
				if (on_board(game,line-2,column+1)==true || on_board(game,line-1,column)==true || on_board(game,line-1,column+2)==true){
					if ((line-2==finish_line&&column+1==finish_column)||(line-1==finish_line&&column==finish_column)||(line-1==finish_line&&column+2==finish_column)){
						return true;
					}
				}
			}
		}
	}
	return false;
}

enum return_code quick_move (board game, int start_line, int start_column, int target_line, int target_column){
	//Allow the current player to directly move a piece from a starting position to an ending position. 
	if(on_board(game,start_line,start_column)==false||on_board(game,target_line,target_column)==false){
		return OUT;
	}
	else if(game->current_prescribed_move==-1||game->selection.l_start!=-1){
		return STAGE;
	}
	else if(get_place_holder(game,start_line,start_column)!=game->current_play){
		return BUSY;
	}
	else if((is_good_move(game,start_line,start_column,target_line,target_column)==false)||(game->current_prescribed_move!=get_digit(game,start_line,start_column)&&is_possible(game)==true)){

		return RULES;
	}
	game->tab[target_line][target_column].pi.piece=game->tab[start_line][start_column].pi.piece;
	game->tab[start_line][start_column].pi.piece=NONE;
	game->tab[target_line][target_column].pi.pl=game->tab[start_line][start_column].pi.pl;
	game->tab[start_line][start_column].pi.pl=0;
	if(game->current_play==NORTH){
		game->current_play=SOUTH;
	}
	else {
		game->current_play=NORTH;
	}
	game->current_prescribed_move=game->tab[target_line][target_column].digit;
	return OK;
} 
