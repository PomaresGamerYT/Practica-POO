#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <list>
using namespace std;

#define ARRIBA 72 
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80

int const ancho_i = 2;
int const ancho_f = 78;
int const alto_i = 4;
int const alto_f = 33;

void gotoxy(int x, int y) {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);
}

void ocultarCursor () {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 50;
	cci.bVisible = TRUE;
	
	SetConsoleCursorInfo (hCon, &cci);
}

class Nave {
	private:
		int x, y;
		int corazones;
		int vidas;
	
	public:
		Nave(int x, int y, int corazones, int vidas);
		//~Nave();
		int getX() { return x; };
		int getY() { return y; };
		int getVidas() { return vidas; };
		void reducirCorazones() { corazones--; };
			
		void pintar();
		void borrar();
		void mover();
		void pintarCorazones();
		void morir();
		
};

Nave::Nave(int x, int y, int corazones, int vidas) {
	this->x = x;
	this->y = y;
	this->corazones = corazones;
	this->vidas = vidas;
}

void Nave::pintar() {
	gotoxy(x, y);
	printf("   %c", 203);
	
	gotoxy(x, y + 1);
	printf("  %c%c%c", 40, 207, 41);
	
	gotoxy(x, y + 2);
	printf(" %c%c %c%c", 174, 190, 190, 175);
}

void Nave::borrar() {
	gotoxy(x, y);
	printf("      ");
	
	gotoxy(x, y + 1);
	printf("      ");
	
	gotoxy(x, y + 2);
	printf("      ");	
	 
}

void Nave::mover() {
	if (kbhit()) { // Verifica si se presionó una tecla
        char tecla = getch(); // Captura la tecla presionada
        
		borrar();
		
		if (tecla == IZQUIERDA && x > ancho_i + 1) x--; // Movimiento hacia la izquierda
        if (tecla == DERECHA && x + 6 < ancho_f - 1) x++; // Movimiento hacia la derecha
        if (tecla == ARRIBA && y > alto_i + 2) y--; // Movimiento hacia arriba
        if (tecla == ABAJO && y + 3 < alto_f - 1) y++; // Movimiento hacia abajo
        
		pintar();
		pintarCorazones();
	}
}

void Nave::pintarCorazones() {
	gotoxy(50, alto_i -1);
	printf("VIDAS: %d", vidas);
	
	gotoxy(64, alto_i -1);
	printf("Salud:");
	
	gotoxy(71, alto_i -1);
	printf("    ");
	
	for(int i = 0; i < corazones; i++) {
		gotoxy(71 + i, alto_i - 1);
		printf("%c", 157);
	}
		
}

void Nave::morir() {
	if(corazones == 0) {
		borrar();		
		gotoxy(x, y);
		printf(" * *  ");
		gotoxy(x, y + 1);
		printf(" *** ");
		gotoxy(x, y + 2);
		printf(" **  ");
		
		Sleep(400);	
		
		borrar();
		gotoxy(x, y);
		printf(" * * *");
		gotoxy(x, y + 1);
		printf(" *****");
		gotoxy(x, y + 2);
		printf(" * * *");
		
		
		Sleep(300);
		borrar();
		
		vidas--;
		corazones = 3;
		pintarCorazones();
	}
}

class Asteroide {
		int x, y;
		
	public:
		Asteroide(int x, int y);
		
		int getX() { return x; };
		int getY() { return y; };
		
		void pintar();
		void mover();
		void choque(class Nave &nave);
	
};

Asteroide::Asteroide(int x, int y) {
	this->x = x;
	this->y = y;
}

void Asteroide::pintar() {
	gotoxy(x, y);
	printf("%c", 184);
	
	
}

void Asteroide::mover() {
	gotoxy(x, y);
	printf(" ");
	
	y++;
	
	if(y > 32) {
		x = rand()%71 + 4;
		y = alto_i + 2;
	}
	
	pintar();
}

void Asteroide::choque(class Nave &nave) {
	if(x >= nave.getX() && x < nave.getX() + 5 && y >= nave.getY() && y <= nave.getY() + 2 ) {
		nave.reducirCorazones();
		nave.borrar();
		nave.pintar();
		nave.pintarCorazones();
		
		x = rand()%71 + 4;
		y = alto_i + 2;
		
	}
}

class Bala {
	private:
		int x, y;
		
	public:
		Bala(int x, int y);
		
		int getX() { return x; };
		int getY() { return y; };
		
		void mover();
		bool fuera();
};

Bala::Bala(int x, int y) {
	this->x = x;
	this->y = y;
}

void Bala::mover() {
	gotoxy(x, y);
	printf(" ");
	
	if(y > 5) y--;
	
	gotoxy(x, y);
	printf("*");
}

bool Bala::fuera() {
	return y == 5;
}


void pintarLimites() {
	for(int i = ancho_i; i < ancho_f; i++) {
		gotoxy(i, alto_i);
		printf("%c", 205);
		
		gotoxy(i, alto_f);
		printf("%c", 205);
	}

	for(int i = alto_i; i < alto_f; i++) {
		gotoxy(ancho_i, i);
		printf("%c", 186);
		
		gotoxy(ancho_f, i);
		printf("%c", 186);
	}

	gotoxy(ancho_i, alto_i);
	printf("%c", 201);
		
	gotoxy(ancho_i, alto_f);
	printf("%c", 200);
	
	gotoxy(ancho_f, alto_i);
	printf("%c", 187);
		
	gotoxy(ancho_f, alto_f);
	printf("%c", 188);
	
}



int main() {
    ocultarCursor();
    pintarLimites();
    
    
	Nave nave(37, 30, 3, 4);
	nave.pintar();
	nave.pintarCorazones();
	
	
	list<Asteroide*> asteroides;
	list<Asteroide*>::iterator itAst;
	
	for(int i = 0; i < 6; i++) {
		asteroides.push_back(new Asteroide(rand()%75 + 3, rand()%5 + 5));
	}
	
	Asteroide ast1(10, 5), ast2(4, 8), ast3(15, 10);
	
	list<Bala*> balas;
	list<Bala*>::iterator it;

    bool game_over = false;
    int puntos = 0;
    
    while (!game_over) {
    	gotoxy(5, 3);
		printf("Puntos: %d", puntos);
    	
    	if (kbhit()) { // Verifica si se presionó una tecla
	        char tecla = getch(); 
	        
	        if(tecla == 'b' || tecla == 'B') {
	        	balas.push_back(new Bala(nave.getX() + 3, nave.getY() - 1));
	    	}
		}
		
		for(it = balas.begin(); it != balas.end(); it++) {
			(*it)->mover();
			if((*it)->fuera()) {
				gotoxy((*it)->getX(), (*it)->getY());
				printf(" ");
				
				delete (*it);
				it = balas.erase(it);
			}
		}
    	
    	for(itAst = asteroides.begin(); itAst != asteroides.end(); itAst++) {
			(*itAst)->mover();
			(*itAst)->choque(nave);
		}

    	for(itAst = asteroides.begin(); itAst != asteroides.end(); itAst++) {
			for(it = balas.begin(); it != balas.end(); it++) {
				if((*it)->getX() == (*itAst)->getX() && ((*it)->getY() == (*itAst)->getY() + 1 || (*it)->getY() == (*itAst)->getY()) ) {
					gotoxy((*it)->getX(), (*it)->getY());
					printf(" ");
					
					delete (*it);
					it = balas.erase(it);
					
					asteroides.push_back(new Asteroide(rand()%75 + 3, 5));
					
					gotoxy((*itAst)->getX(), (*itAst)->getY());
					printf(" ");
					
					delete (*itAst);
					itAst = asteroides.erase(itAst);
					
					puntos += 5;
				}
			}
		}
				
			
			
				
		if(nave.getVidas() == 0) {
			game_over = true;	
		}	
				
    	nave.morir();
        nave.mover();

        Sleep(30); // Espera para evitar un bucle excesivamente rápido
    }

    return 0;
}
