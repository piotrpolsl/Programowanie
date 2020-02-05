#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>


using namespace std;

bool KoniecGry;
bool Wylacz;
const int szerokosc = 20;
const int wysokosc = 20;

int x, y, owocX, owocY, wynik;

int ogonX[500], ogonY[500];
int n_ogon;

enum Kierunek { STOP, GORA, DOL, PRAWO, LEWO};

Kierunek dir;

void Menu()
{
	system("cls"); cout << endl;
	cout << "   GRA W SNAKE'A\n\n";
	cout << "   [s]   Nacisnij 's' aby rozpoczac gre w Snake'a"; cout << endl;
	cout << "   [z]   Nacisnij 'i' aby wyswietlic zasady gry"; cout << endl;
	cout << "   [q]   Nacisnij 'q' aby opuscic gre"; cout << endl;
    cout << "\n\n   Twoj poprzedni wynik wynosil: " << wynik << endl << endl;
}
void Instrukcje()
{
	system("cls"); cout << endl;
	cout << "Do poruszania sie uzywaj klawiszy: 'w','s','a','d'"; cout << endl;
    cout << "Aby zakonczyc gre nacisnij 'k'"; cout << endl;
	cout << "\nNie dotykaj granic planszy"<<"\nNie zjedz swojego ogona"; cout << endl;
	cout << "\nAby wrocic do menu nacisnij dowolny klawisz"; cout << endl;
	string input;
	cin >> input;
	if (input == "m")
    Menu();

}

void Poczatek_gry()
{
    KoniecGry = false;
	Wylacz = false;
    dir = STOP;
    x = szerokosc / 2;
    y = wysokosc / 2;
    owocX = rand() % szerokosc;
    owocY = rand() % wysokosc;
    wynik = 0;
	  n_ogon = 0;
}

void Wyswietlanie()
{
    system("cls");
	for (int i = 0; i < szerokosc + 2; i++)
        cout << "~";
        cout << endl;

    for (int i = 0; i < wysokosc; i++)
    {
        for (int j = 0; j < szerokosc; j++)
        {
            if (j == 0)
                cout << "|";
            if (i == y && j == x)
                cout << "#";
            else if (i == owocY && j == owocX)
                cout << "$";
            else
            {
                bool drukuj = false;
                for (int k = 0; k < n_ogon; k++)
                {
                    if (ogonX[k] == j && ogonY[k] == i)
                    {
                        cout << "o";
                        drukuj = true;
                    }
                }
                if (!drukuj)
                    cout << " ";
            }
            if (j == szerokosc - 1)
                cout << "|";
        }
        cout << endl;
    }
    
    for (int i = 0; i < szerokosc + 2; i++)
        cout << "~";
        cout << endl;
    cout << "Twoj wynik:" << wynik << endl;

}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'W': case 'w': dir = GORA; break;
        case 'S': case 's': dir = DOL; break;
        case 'D': case 'd': dir = PRAWO; break;
        case 'A': case 'a': dir = LEWO; break;

        case 'k': KoniecGry = true; break;
        }
    }
}

void Mechanika_gry()
{
    	int ostatniX = ogonX[0];
    	int ostatniY = ogonY[0];
    	int ostatni2X, ostatni2Y;
    	ogonX[0] = x;
    	ogonY[0] = y;
    
    	for (int i = 1; i < n_ogon; i++) {
            ostatni2X = ogonX[i];
            ostatni2Y = ogonY[i];
    		ogonX[i] = ostatniX;
    		ogonY[i] = ostatniY;
            ostatniX = ostatni2X;
            ostatniY = ostatni2Y;
    
    	}


        switch (dir)
        {
        case GORA: y--; break;
        case DOL: y++; break;
        case PRAWO: x++; break;
        case LEWO: x--; break;

        }


        if (x > szerokosc || x < 0 || y > wysokosc || y < 0)
        {
            KoniecGry = true;
            Menu();
        }


        for (int i = 0; i < n_ogon; i++)
        {
            if (ogonX[i] == x && ogonY[i] == y)
                KoniecGry = true;
        }
        
        if (x == owocX && y == owocY)
        {
            wynik ++;
            n_ogon++;
            owocX = rand() % szerokosc;
            owocY = rand() % wysokosc;
        }

    }



int main()
{
	do
	{
		Menu();
		string input;
		cin >> input;
		if (input == "s")
		{
			Poczatek_gry();

			while (!KoniecGry)
			{
				Wyswietlanie();
				Input();
				Mechanika_gry();
				Sleep(10);
			}
		}
		else if (input == "z")
			Instrukcje();
		else if (input == "q")
			Wylacz = true;
	}
	while (Wylacz == false);

    system("pause");
}