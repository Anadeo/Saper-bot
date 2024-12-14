#include<iostream>
#include<windows.h>
using namespace std;
struct pole {
    short x;
    short y;
};
struct mapa {
    short mapa[24][20];
};
HBITMAP hBitmap;
HDC hdcMemory;
short prawdopodobienstwo[20 * 24], wszystkie_bomby;
void screenshot() {
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, hBitmap);
    CloseClipboard();
}
int get_Bitmap(int x, int y, HDC& hdcMemory, int width, int height) {
    HDC hdcSource = GetDC(NULL);
    hdcMemory = CreateCompatibleDC(hdcSource);
    hBitmap = CreateCompatibleBitmap(hdcSource, width, height);
    HBITMAP hBitmapOld = (HBITMAP)SelectObject(hdcMemory, hBitmap);
    if (!BitBlt(hdcMemory, 0, 0, width, height, hdcSource, x, y, CAPTUREBLT | SRCCOPY)) {
        cout << "BitBlt failed!" << endl;
        return 0;
    }
    //clean up
    DeleteObject(hBitmapOld);
    DeleteObject(hBitmap);
    DeleteDC(hdcSource);
    return 1;
}
mapa mapa_update(short szerokosc, short wysokosc, mapa mapa){
    get_Bitmap(0, 0, hdcMemory, 1920, 1080);
    //screenshot();
    COLORREF kolor;
    short czerwony, zielony, niebieski, x, y, koniec_x=szerokosc+600, koniec_y=wysokosc+500;
    bool pentla_dziala;
    //czyszczenie mapy
    /*for (short i = 0; i < 24; i++) {
        for (short j = 0; j < 20; j++) {
            if (mapa.mapa[i][j] != -2) {
                mapa.mapa[i][j] = 0;
            }
        }
    }*/
    //SetCursorPos(0, 0);
    //Sleep(50);
    x = 0;
    for (short i = szerokosc; i < koniec_x; i += 25) {
        y = 0;
        for (short j = wysokosc; j < koniec_y; j += 25) {
            if (mapa.mapa[x][y] != -2) {
                kolor = GetPixel(hdcMemory, i + 12, j + 12);
                czerwony = GetRValue(kolor);
                zielony = GetGValue(kolor);
                niebieski = GetBValue(kolor);
                //0
                if ((czerwony == 229 && zielony == 194 && niebieski == 159) || (czerwony == 215 && zielony == 184 && niebieski == 153)) {
                    mapa.mapa[x][y] = 0;
                }
                //1
                else if (czerwony == 25 && zielony == 118 && niebieski == 210) {
                    mapa.mapa[x][y] = 1;
                }
                //2
                else if ((czerwony == 187 && zielony == 182 && niebieski == 135) || (czerwony == 177 && zielony == 174 && niebieski == 130) || (czerwony == 193 && zielony == 193 && niebieski == 153) || (czerwony == 184 && zielony == 188 && niebieski == 150)) {
                    mapa.mapa[x][y] = 2;
                }
                //3
                else if (czerwony == 211 && zielony == 47 && niebieski == 47) {
                    mapa.mapa[x][y] = 3;
                }
                //4
                else if ((czerwony == 212 && zielony == 168 && niebieski == 159) || (czerwony == 200 && zielony == 159 && niebieski == 154) || (czerwony == 218 && zielony == 180 && niebieski == 180) || (czerwony == 209 && zielony == 175 && niebieski == 176)) {
                    mapa.mapa[x][y] = 4;
                }
                //5
                else if (czerwony == 255 && zielony == 143 && niebieski == 0) {
                    mapa.mapa[x][y] = 5;
                }
                //6
                else if ((czerwony == 219 && zielony == 192 && niebieski == 159) || (czerwony == 206 && zielony == 182 && niebieski == 153) || (czerwony == 226 && zielony == 206 && niebieski == 182) || (czerwony == 215 && zielony == 199 && niebieski == 178)) {
                    mapa.mapa[x][y] = 6;
                }
                //nie odkryte
                else {
                    mapa.mapa[x][y] = -1;
                }
                //else if(()())
                /*pentla_dziala = true;
                for (short k = i + 7; k < 18 + i && pentla_dziala; k++) {
                    for (short l = j + 6; l < 20 + j && pentla_dziala; l++) {
                        kolor = GetPixel(hdcMemory, k, l);
                        czerwony = GetRValue(kolor);
                        zielony = GetGValue(kolor);
                        niebieski = GetBValue(kolor);
                        //1
                        if (czerwony >= 25 && czerwony <= 80 && zielony >= 118 && zielony <= 137 && niebieski >= 193 && niebieski <= 210) {
                            mapa.mapa[x][y] = 1;
                            pentla_dziala = false;
                        }
                        //2
                        else if (czerwony >= 56 && czerwony <= 79 && zielony >= 142 && zielony <= 146 && niebieski >= 60 && niebieski <= 69) {
                            mapa.mapa[x][y] = 2;
                            pentla_dziala = false;
                        }
                        //3
                        else if (czerwony >= 211 && czerwony <= 213 && zielony >= 47 && zielony <= 112 && niebieski >= 47 && niebieski <= 97) {
                            mapa.mapa[x][y] = 3;
                            pentla_dziala = false;
                        }
                        //4
                        else if (czerwony >= 123 && czerwony <= 166 && zielony >= 31 && zielony <= 102 && niebieski >= 157 && niebieski <= 162) {
                            mapa.mapa[x][y] = 4;
                            pentla_dziala = false;
                        }
                        //5
                        else if (czerwony >= 254 && czerwony <= 255 && zielony >= 143 && zielony >= 144 && niebieski >= 0 && niebieski <= 5) {
                            mapa.mapa[x][y] = 5;
                            pentla_dziala = false;
                        }
                        //6
                        else if (czerwony >= 0 && czerwony <= 75 && zielony >= 151 && zielony <= 162 && niebieski >= 162 && niebieski <= 167) {
                            mapa.mapa[x][y] = 6;
                            pentla_dziala = false;
                        }
                    }
                }
                //nie odkryte
                kolor = GetPixel(hdcMemory, i + 12, j + 12);
                czerwony = GetRValue(kolor);
                zielony = GetGValue(kolor);
                niebieski = GetBValue(kolor);
                if (pentla_dziala) {
                    if ((czerwony >= 161 && czerwony <= 171 && zielony >= 199 && zielony <= 216 && niebieski >= 72 && niebieski <= 82) || (czerwony == 191 && zielony == 225 && niebieski == 125) || (czerwony == 185 && zielony == 221 && niebieski == 119)) {
                        mapa.mapa[x][y] = -1;
                    }
                }*/
            }
            y++;
        }
        x++;
    }
    /*cout << "Uaktualniona mapa: " << endl;
    for (short j = 0; j < 20; j++) {
        for (short i = 0; i < 24; i++) {
            if (mapa.mapa[i][j] >= 0) {
                cout << " " << mapa.mapa[i][j] << " ";
            }
            else {
                cout << mapa.mapa[i][j] << " ";
            }
        }
        cout << endl;
    }*/
    return mapa;
}
bool sprawdzenie_liczba(mapa mapa, short x, short y) {
    short bomby=0;
    if (x > 0 && y > 0) {
        if (mapa.mapa[x - 1][y - 1] == -3) {
            return true;
        }
        else if(mapa.mapa[x - 1][y - 1] == -2 || mapa.mapa[x - 1][y - 1] == -5) {
            bomby++;
        }
    }
    if (y > 0) {
        if (mapa.mapa[x][y - 1] == -3) {
            return true;
        }
        else if (mapa.mapa[x][y - 1] == -2 || mapa.mapa[x][y - 1] == -5) {
            bomby++;
        }
    }
    if (x < 23 && y > 0) {
        if (mapa.mapa[x + 1][y - 1] == -3) {
            return true;
        }
        else if(mapa.mapa[x + 1][y - 1] == -2 || mapa.mapa[x + 1][y - 1] == -5) {
            bomby++;
        }
    }
    if (x < 23) {
        if (mapa.mapa[x + 1][y] == -3) {
            return true;
        }
        else if(mapa.mapa[x + 1][y] == -2 || mapa.mapa[x + 1][y] == -5) {
            bomby++;
        }
    }
    if (x < 23 && y < 19) {
        if (mapa.mapa[x + 1][y + 1] == -3) {
            return true;
        }
        else if (mapa.mapa[x + 1][y + 1] == -2 || mapa.mapa[x + 1][y + 1] == -5) {
            bomby++;
        }
    }
    if (y < 19) {
        if (mapa.mapa[x][y + 1] == -3) {
            return true;
        }
        else if (mapa.mapa[x][y + 1] == -2 || mapa.mapa[x][y + 1] == -5) {
            bomby++;
        }
    }
    if (x > 0 && y < 19) {
        if (mapa.mapa[x - 1][y + 1] == -3) {
            return true;
        }
        else if (mapa.mapa[x - 1][y + 1] == -2 || mapa.mapa[x - 1][y + 1] == -5) {
            bomby++;
        }
    }
    if (x > 0) {
        if (mapa.mapa[x - 1][y] == -3) {
            return true;
        }
        else if (mapa.mapa[x - 1][y] == -2 || mapa.mapa[x - 1][y] == -5) {
            bomby++;
        }
    }
    return (bomby == mapa.mapa[x][y]);
}
bool sprawdzenie(mapa mapa, short x, short y) {
    if (x > 0 && y > 0) {
        if (mapa.mapa[x - 1][y - 1] > 0) {
            if (!sprawdzenie_liczba(mapa, x - 1, y - 1)) {
                return false;
            }
        }
    }
    if (y > 0) {
        if (mapa.mapa[x][y - 1] > 0) {
            if (!sprawdzenie_liczba(mapa, x, y - 1)) {
                return false;
            }
        }
    }
    if (x < 23 && y > 0) {
        if (mapa.mapa[x + 1][y - 1] > 0) {
            if (!sprawdzenie_liczba(mapa, x + 1, y - 1)) {
                return false;
            }
        }
    }
    if (x < 23) {
        if (mapa.mapa[x + 1][y] > 0) {
            if (!sprawdzenie_liczba(mapa, x + 1, y)) {
                return false;
            }
        }
    }
    if (x < 23 && y < 19) {
        if (mapa.mapa[x + 1][y + 1] > 0) {
            if (!sprawdzenie_liczba(mapa, x + 1, y + 1)) {
                return false;
            }
        }
    }
    if (y < 19) {
        if (mapa.mapa[x][y + 1] > 0) {
            if (!sprawdzenie_liczba(mapa, x, y + 1)) {
                return false;
            }
        }
    }
    if (x > 0 && y < 19) {
        if (mapa.mapa[x - 1][y + 1] > 0) {
            if (!sprawdzenie_liczba(mapa, x - 1, y + 1)) {
                return false;
            }
        }
    }
    if (x > 0) {
        if (mapa.mapa[x - 1][y] > 0) {
            if (!sprawdzenie_liczba(mapa, x - 1, y)) {
                return false;
            }
        }
    }
    return true;
}
void podlicz(mapa mapa, pole*koordy_bomby, short ile_bomb_do_zgadniecia) {
    for (short i = 0; i < ile_bomb_do_zgadniecia; i++) {
        if (mapa.mapa[koordy_bomby[i].x][koordy_bomby[i].y] == -5) {
            prawdopodobienstwo[i]++;
        }
    }
    wszystkie_bomby++;
}
void przypuszczenie(mapa mapa, pole*koordy_bomby, short ile_bomb_do_zgadniecia, bool bomba, short iteracje) {
    if (bomba) {
        mapa.mapa[koordy_bomby[iteracje].x][koordy_bomby[iteracje].y] = -5;
    }
    else {
        mapa.mapa[koordy_bomby[iteracje].x][koordy_bomby[iteracje].y] = -4;
    }
    if (iteracje + 1 != ile_bomb_do_zgadniecia) {
        if (sprawdzenie(mapa, koordy_bomby[iteracje].x, koordy_bomby[iteracje].y)) {
            przypuszczenie(mapa, koordy_bomby, ile_bomb_do_zgadniecia, false, iteracje + 1);
            przypuszczenie(mapa, koordy_bomby, ile_bomb_do_zgadniecia, true, iteracje + 1);
        }
    }
    else {
        if (sprawdzenie(mapa, koordy_bomby[iteracje].x, koordy_bomby[iteracje].y)) {
            podlicz(mapa, koordy_bomby, ile_bomb_do_zgadniecia);
        }
    }
}
pole znajc_mape() {
    HDC hdcMemory;
    COLORREF kolor;
    pole mapa;
    short czerwony, zielony, niebieski;
    get_Bitmap(0, 0, hdcMemory, 1920, 1080);
    for (short i = 0; i < 1920; i++) {
        for (short j = 0; j < 1080; j++) {
            kolor = GetPixel(hdcMemory, i, j);
            czerwony = GetRValue(kolor);
            zielony = GetGValue(kolor);
            niebieski = GetBValue(kolor);
            if (czerwony == 170 && zielony == 215 && niebieski == 81) {
                mapa.x = i;
                mapa.y = j;
                return mapa;
            }
        }
    }
    mapa.x = -1;
    return mapa;
}
int main(int argc, char* argv[]) {
    COLORREF kolor;
    pole koordy_bomby[24 * 20], koordy_mapy;
    mapa mapa={0};
    short x, y, nie_odkryte, flagi, /*szybkosc = 1, */ile_bomb_do_zgadniecia, najmniejsze_prawdopodobienstwo, najmniejsze_prawdopodobienstwo_nr, szansa_w_procentach;
    bool kierunek[8], wygrana=false, ruch, bomba_do_zgadniecia, petla;
    //cout << "Program autorstwa: Amadeusz Nowak IVAg" << endl;
    cout << "PRZYGOTUJ GRE I WCISNIJ \"s\"" << endl;
    cout << "Wymagania:" << endl;
    cout << "1. To musi byc googlowski saper na przegladarce" << endl;
    cout << "2. Poziom trudnosci ustawiony na: trudny" << endl;
    cout << "3. Cala mapa musi byc widoczna i odslonieta" << endl;
    cout << "4. Powiekszenie przegladarki: 100%" << endl;
    while (!GetAsyncKeyState(0x53)) {}
    cout << "Szukanie mapy..." << endl;
    koordy_mapy = znajc_mape();
    if (koordy_mapy.x == -1) {
        cout << "Error: Nie znaleziono mapy sapera" << endl;
        system("pause");
        return 1;
    }
    cout << "Mapa znaleziona na koordynatach: " << endl;
    cout << "x: " << koordy_mapy.x << endl;
    cout << "y: " << koordy_mapy.y << endl;
    cout << "Rozwiazywanie sapera!" << endl;
    while(true){
        //cout << "------------------------------------------------" << endl;
        while(!wygrana) {
            mapa = mapa_update(koordy_mapy.x, koordy_mapy.y, mapa);
            ruch = false;
            for (short x = 0; x < 24; x++) {
                for (short y = 0; y < 20; y++) {
                    if (mapa.mapa[x][y] > 0) {
                        nie_odkryte = 0;
                        //czyszczenie informacji o kierunku
                        for (short k = 0; k < 8; k++) {
                            kierunek[k] = false;
                        }
                        //ustalanie nie odkrytych pól
                        if (x > 0 && y > 0) {
                            if (mapa.mapa[x - 1][y - 1] == -1) {
                                nie_odkryte++;
                                kierunek[0] = true;
                            }
                        }
                        if (y > 0) {
                            if (mapa.mapa[x][y - 1] == -1) {
                                nie_odkryte++;
                                kierunek[1] = true;
                            }
                        }
                        if (x < 23 && y > 0) {
                            if (mapa.mapa[x + 1][y - 1] == -1) {
                                nie_odkryte++;
                                kierunek[2] = true;
                            }
                        }
                        if (x < 23) {
                            if (mapa.mapa[x + 1][y] == -1) {
                                nie_odkryte++;
                                kierunek[3] = true;
                            }
                        }
                        if (x < 23 && y < 19) {
                            if (mapa.mapa[x + 1][y + 1] == -1) {
                                nie_odkryte++;
                                kierunek[4] = true;
                            }
                        }
                        if (y < 19) {
                            if (mapa.mapa[x][y + 1] == -1) {
                                nie_odkryte++;
                                kierunek[5] = true;
                            }
                        }
                        if (x > 0 && y < 19) {
                            if (mapa.mapa[x - 1][y + 1] == -1) {
                                nie_odkryte++;
                                kierunek[6] = true;
                            }
                        }
                        if (x > 0) {
                            if (mapa.mapa[x - 1][y] == -1) {
                                nie_odkryte++;
                                kierunek[7] = true;
                            }
                        }
                        //czy przy liczbie jest chocia¿ 1 nie odkryte pole
                        if (nie_odkryte) {
                            //ustalenie iloœci flag przy liczbie
                            flagi = 0;
                            if (x > 0 && y > 0) {
                                if (mapa.mapa[x - 1][y - 1] == -2) {
                                    flagi++;
                                }
                            }
                            if (y > 0) {
                                if (mapa.mapa[x][y - 1] == -2) {
                                    flagi++;
                                }
                            }
                            if (x < 23 && y > 0) {
                                if (mapa.mapa[x + 1][y - 1] == -2) {
                                    flagi++;
                                }
                            }
                            if (x < 23) {
                                if (mapa.mapa[x + 1][y] == -2) {
                                    flagi++;
                                }
                            }
                            if (x < 23 && y < 19) {
                                if (mapa.mapa[x + 1][y + 1] == -2) {
                                    flagi++;
                                }
                            }
                            if (y < 19) {
                                if (mapa.mapa[x][y + 1] == -2) {
                                    flagi++;
                                }
                            }
                            if (x > 0 && y < 19) {
                                if (mapa.mapa[x - 1][y + 1] == -2) {
                                    flagi++;
                                }
                            }
                            if (x > 0) {
                                if (mapa.mapa[x - 1][y] == -2) {
                                    flagi++;
                                }
                            }
                            //znajdywanie bomby
                            if (mapa.mapa[x][y] == nie_odkryte + flagi) {
                                if (kierunek[0]) {
                                    if (mapa.mapa[x - 1][y - 1] != -2){
                                        SetCursorPos((x - 1) * 25 + koordy_mapy.x + 12, (y - 1) * 25 + koordy_mapy.y + 12);
                                        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                                        //Sleep(szybkosc);
                                        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                                        //Sleep(szybkosc);
                                        mapa.mapa[x - 1][y - 1] = -2;
                                        ruch = true;
                                        //cout << "Tu jest bomba (" << x - 1 << " " << y - 1 << ") bo ilosc nie odkrytych pol (" << nie_odkryte << ") zgadza sie z liczba w miejscu: " << x << " " << y << "(lewo gora od liczby)" << endl;
                                    }
                                }
                                if (kierunek[1]) {
                                    if (mapa.mapa[x][y - 1] != -2) {
                                        SetCursorPos(x * 25 + koordy_mapy.x + 12, (y - 1) * 25 + koordy_mapy.y + 12);
                                        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                                        //Sleep(szybkosc);
                                        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                                        //Sleep(szybkosc);
                                        mapa.mapa[x][y - 1] = -2;
                                        ruch = true;
                                        //cout << "Tu jest bomba (" << x << " " << y - 1 << ") bo ilosc pobliskich flag (" << nie_odkryte << ") zgadza sie z liczba w miejscu: " << x << " " << y << "(gora od liczby)" << endl;
                                    }
                                }
                                if (kierunek[2]) {
                                    if (mapa.mapa[x + 1][y - 1] != -2) {
                                        SetCursorPos((x + 1) * 25 + koordy_mapy.x + 12, (y - 1) * 25 + koordy_mapy.y + 12);
                                        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                                        //Sleep(szybkosc);
                                        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                                        //Sleep(szybkosc);
                                        mapa.mapa[x + 1][y - 1] = -2;
                                        ruch = true;
                                        //cout << "Tu jest bomba (" << x + 1 << " " << y - 1 << ") bo ilosc pobliskich flag (" << nie_odkryte << ") zgadza sie z liczba w miejscu: " << x << " " << y << "(prawo gora od liczby)" << endl;
                                    }
                                }
                                if (kierunek[3]) {
                                    if (mapa.mapa[x + 1][y] != -2) {
                                        SetCursorPos((x + 1) * 25 + koordy_mapy.x + 12, y * 25 + koordy_mapy.y + 12);
                                        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                                        //Sleep(szybkosc);
                                        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                                        //Sleep(szybkosc);
                                        mapa.mapa[x + 1][y] = -2;
                                        ruch = true;
                                        //cout << "Tu jest bomba (" << x + 1 << " " << y << ") bo ilosc pobliskich flag (" << nie_odkryte << ") zgadza sie z liczba w miejscu: " << x << " " << y << "(prawo od liczby)" << endl;
                                    }
                                }
                                if (kierunek[4]) {
                                    if (mapa.mapa[x + 1][y + 1] != -2) {
                                        SetCursorPos((x + 1) * 25 + koordy_mapy.x + 12, (y + 1) * 25 + koordy_mapy.y + 12);
                                        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                                        //Sleep(szybkosc);
                                        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                                        //Sleep(szybkosc);
                                        mapa.mapa[x + 1][y + 1] = -2;
                                        ruch = true;
                                        //cout << "Tu jest bomba (" << x + 1 << " " << y + 1 << ") bo ilosc pobliskich flag (" << nie_odkryte << ") zgadza sie z liczba w miejscu: " << x << " " << y << "(prawo dol od liczby)" << endl;
                                    }
                                }
                                if (kierunek[5]) {
                                    if (mapa.mapa[x][y + 1] != -2) {
                                        SetCursorPos(x * 25 + koordy_mapy.x + 12, (y + 1) * 25 + koordy_mapy.y + 12);
                                        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                                        //Sleep(szybkosc);
                                        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                                        //Sleep(szybkosc);
                                        mapa.mapa[x][y + 1] = -2;
                                        ruch = true;
                                        //cout << "Tu jest bomba (" << x << " " << y + 1 << ") bo ilosc pobliskich flag (" << nie_odkryte << ") zgadza sie z liczba w miejscu: " << x << " " << y << "(dol od liczby)" << endl;
                                    }
                                }
                                if (kierunek[6]) {
                                    if (mapa.mapa[x - 1][y + 1] != -2) {
                                        SetCursorPos((x - 1) * 25 + koordy_mapy.x + 12, (y + 1) * 25 + koordy_mapy.y + 12);
                                        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                                        //Sleep(szybkosc);
                                        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                                        //Sleep(szybkosc);
                                        mapa.mapa[x - 1][y + 1] = -2;
                                        ruch = true;
                                        //cout << "Tu jest bomba (" << x - 1 << " " << y + 1 << ") bo ilosc pobliskich flag (" << nie_odkryte << ") zgadza sie z liczba w miejscu: " << x << " " << y << "(lewo dol od liczby)" << endl;
                                    }
                                }
                                if (kierunek[7]) {
                                    if (mapa.mapa[x - 1][y] != -2) {
                                        SetCursorPos((x - 1) * 25 + koordy_mapy.x + 12, y * 25 + koordy_mapy.y + 12);
                                        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                                        //Sleep(szybkosc);
                                        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                                        //Sleep(szybkosc);
                                        mapa.mapa[x - 1][y] = -2;
                                        ruch = true;
                                        //cout << "Tu jest bomba (" << x - 1 << " " << y << ") bo ilosc pobliskich flag (" << nie_odkryte << ") zgadza sie z liczba w miejscu: " << x << " " << y << "(lewo od liczby)" << mapa.mapa[x - 1][y] << endl;
                                    }
                                }
                            }
                            //sprawdzanie czy mo¿na ods³oniæ kolejne pola
                            else if (mapa.mapa[x][y] == flagi) {
                                if (kierunek[0]) {
                                    SetCursorPos((x - 1) * 25 + koordy_mapy.x + 12, (y - 1) * 25 + koordy_mapy.y + 12);
                                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                                    //Sleep(szybkosc);
                                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                                    ruch = true;
                                    //Sleep(szybkosc);
                                    //cout << "Kliknolem tu (" << x - 1 << " " << y - 1 << ") bo ilosc pobliskich flag (" << flagi << ") zgadza sie z liczba w miejscu: " << x << " " << y << "(lewo gora od liczby)" << endl;
                                }
                                if (kierunek[1]) {
                                    SetCursorPos(x * 25 + koordy_mapy.x + 12, (y - 1) * 25 + koordy_mapy.y + 12);
                                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                                    //Sleep(szybkosc);
                                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                                    ruch = true;
                                    //Sleep(szybkosc);
                                    //cout << "Kliknolem tu (" << x << " " << y - 1 << ") bo ilosc pobliskich flag (" << flagi << ") zgadza sie z liczba w miejscu: " << x << " " << y << "(gora od liczby)" << endl;
                                }
                                if (kierunek[2]) {
                                    SetCursorPos((x + 1) * 25 + koordy_mapy.x + 12, (y - 1) * 25 + koordy_mapy.y + 12);
                                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                                    //Sleep(szybkosc);
                                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                                    ruch = true;
                                    //Sleep(szybkosc);
                                    //cout << "Kliknolem tu (" << x + 1 << " " << y - 1 << ") bo ilosc pobliskich flag (" << flagi << ") zgadza sie z liczba w miejscu: " << x << " " << y << "(prawo gora od liczby)" << endl;
                                }
                                if (kierunek[3]) {
                                    SetCursorPos((x + 1) * 25 + koordy_mapy.x + 12, y * 25 + koordy_mapy.y + 12);
                                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                                    //Sleep(szybkosc);
                                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                                    ruch = true;
                                    //Sleep(szybkosc);
                                    //cout << "Kliknolem tu (" << x + 1 << " " << y << ") bo ilosc pobliskich flag (" << flagi << ") zgadza sie z liczba w miejscu: " << x << " " << y << "(prawo od liczby)" << endl;
                                }
                                if (kierunek[4]) {
                                    SetCursorPos((x + 1) * 25 + koordy_mapy.x + 12, (y + 1) * 25 + koordy_mapy.y + 12);
                                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                                    //Sleep(szybkosc);
                                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                                    ruch = true;
                                    //Sleep(szybkosc);
                                    //cout << "Kliknolem tu (" << x + 1 << " " << y + 1 << ") bo ilosc pobliskich flag (" << flagi << ") zgadza sie z liczba w miejscu: " << x << " " << y << "(prawo dol od liczby)" << endl;
                                }
                                if (kierunek[5]) {
                                    SetCursorPos(x * 25 + koordy_mapy.x + 12, (y + 1) * 25 + koordy_mapy.y + 12);
                                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                                    //Sleep(szybkosc);
                                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                                    ruch = true;
                                    //Sleep(szybkosc);
                                    //cout << "Kliknolem tu (" << x << " " << y + 1 << ") bo ilosc pobliskich flag (" << flagi << ") zgadza sie z liczba w miejscu: " << x << " " << y << "(dol od liczby)" << endl;
                                }
                                if (kierunek[6]) {
                                    SetCursorPos((x - 1) * 25 + koordy_mapy.x + 12, (y + 1) * 25 + koordy_mapy.y + 12);
                                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                                    //Sleep(szybkosc);
                                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                                    ruch = true;
                                    //Sleep(szybkosc);
                                    //cout << "Kliknolem tu (" << x - 1 << " " << y + 1 << ") bo ilosc pobliskich flag (" << flagi << ") zgadza sie z liczba w miejscu: " << x << " " << y << "(lewo dol od liczby)" << endl;
                                }
                                if (kierunek[7]) {
                                    SetCursorPos((x - 1) * 25 + koordy_mapy.x + 12, y * 25 + koordy_mapy.y + 12);
                                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                                    //Sleep(szybkosc);
                                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                                    ruch = true;
                                    //Sleep(szybkosc);
                                    //cout << "Kliknolem tu (" << x - 1 << " " << y << ") bo ilosc pobliskich flag (" << flagi << ") zgadza sie z liczba w miejscu: " << x << " " << y << "(lewo od liczby)" << endl;
                                }
                            }
                        }
                    }
                }
            }
            if (!ruch) {
                cout << "Brak mozliwosci ruchu, szukanie najlepszego miejsca do strzalu" << endl;
                //screenshot();
                //wybranie miejsc na zgadywanie bomby
                ile_bomb_do_zgadniecia = 0;
                for (short i = 0; i < 24; i++) {
                    for (short j = 0; j < 20; j++) {
                        if (mapa.mapa[i][j] == -1) {
                            bomba_do_zgadniecia = false;
                            if (i > 0 && j > 0) {
                                if (mapa.mapa[i - 1][j - 1] > 0) {
                                    bomba_do_zgadniecia = true;
                                }
                            }
                            if (j > 0) {
                                if (mapa.mapa[i][j - 1] > 0) {
                                    bomba_do_zgadniecia = true;
                                }
                            }
                            if (i < 23 && j > 0) {
                                if (mapa.mapa[i + 1][j - 1] > 0) {
                                    bomba_do_zgadniecia = true;
                                }
                            }
                            if (i < 23) {
                                if (mapa.mapa[i + 1][j] > 0) {
                                    bomba_do_zgadniecia = true;
                                }
                            }
                            if (i < 23 && j < 19) {
                                if (mapa.mapa[i + 1][j + 1] > 0) {
                                    bomba_do_zgadniecia = true;
                                }
                            }
                            if (j < 19) {
                                if (mapa.mapa[i][j + 1] > 0) {
                                    bomba_do_zgadniecia = true;
                                }
                            }
                            if (i > 0 && j < 19) {
                                if (mapa.mapa[i - 1][j + 1] > 0) {
                                    bomba_do_zgadniecia = true;
                                }
                            }
                            if (i > 0) {
                                if (mapa.mapa[i - 1][j] > 0) {
                                    bomba_do_zgadniecia = true;
                                }
                            }
                            if (bomba_do_zgadniecia) {
                                mapa.mapa[i][j] = -3;
                                koordy_bomby[ile_bomb_do_zgadniecia].x = i;
                                koordy_bomby[ile_bomb_do_zgadniecia].y = j;
                                ile_bomb_do_zgadniecia++;
                            }
                        }
                    }
                }
                if (ile_bomb_do_zgadniecia) {
                    cout << "Ilosc miejsc do zgadywania: " << ile_bomb_do_zgadniecia << endl;
                    cout << "Prawdopodobienstwo na kazdym polu na wystapienie bomby: " << endl;
                    //wygenerowanie i podliczenie wszystkich mozliwosci wystapienia bomb
                    for (short i = 0; i < ile_bomb_do_zgadniecia; i++) {
                        prawdopodobienstwo[i] = 0;
                    }
                    wszystkie_bomby = 0;
                    przypuszczenie(mapa, koordy_bomby, ile_bomb_do_zgadniecia, false, 0);
                    przypuszczenie(mapa, koordy_bomby, ile_bomb_do_zgadniecia, true, 0);
                    for (short i = 0; i < 20; i++) {
                        for (short j = 0; j < 24; j++) {
                            petla = true;
                            for (short k = 0; k < ile_bomb_do_zgadniecia && petla; k++) {
                                if (koordy_bomby[k].x == j && koordy_bomby[k].y == i) {
                                    szansa_w_procentach = prawdopodobienstwo[k] * 100 / wszystkie_bomby;
                                    cout << szansa_w_procentach << "%";
                                    petla = false;
                                    if (szansa_w_procentach < 10) {
                                        cout << "  ";
                                    }
                                    else if (szansa_w_procentach != 100) {
                                        cout << " ";
                                    }
                                }
                            }
                            if (petla) {
                                cout << mapa.mapa[j][i];
                                if (mapa.mapa[j][i] < 0) {
                                    cout << "  ";
                                }
                                else {
                                    cout << "   ";
                                }
                            }
                        }
                        cout << endl;
                    }
                    //znalezienie miejsca z najmnejszym prawdopodobienstwem
                    najmniejsze_prawdopodobienstwo_nr = 0;
                    najmniejsze_prawdopodobienstwo = prawdopodobienstwo[0];
                    while (ile_bomb_do_zgadniecia != 1) {
                        if (najmniejsze_prawdopodobienstwo > prawdopodobienstwo[ile_bomb_do_zgadniecia - 1]) {
                            najmniejsze_prawdopodobienstwo = prawdopodobienstwo[ile_bomb_do_zgadniecia - 1];
                            najmniejsze_prawdopodobienstwo_nr = ile_bomb_do_zgadniecia - 1;
                        }
                        ile_bomb_do_zgadniecia--;
                    }
                    //klikniecie na to miejsce
                    SetCursorPos(koordy_bomby[najmniejsze_prawdopodobienstwo_nr].x * 25 + koordy_mapy.x + 12, koordy_bomby[najmniejsze_prawdopodobienstwo_nr].y * 25 + koordy_mapy.y + 12);
                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                    //Sleep(szybkosc);
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                    //Sleep(szybkosc);
                    cout << "----------------------------------------------------------------------------" << endl;
                    //system("pause");
                }
                else {
                    petla = true;
                    for (short i = 0; i < 24 && petla; i++) {
                        for (short j = 0; j < 20 && petla; j++) {
                            if (mapa.mapa[i][j] == -1) {
                                SetCursorPos(i * 25 + koordy_mapy.x + 12, j * 25 + koordy_mapy.y + 12);
                                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                                //Sleep(szybkosc);
                                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                                //Sleep(szybkosc);
                                petla = false;
                            }
                        }
                    }
                }
            }
            kolor = GetPixel(hdcMemory, koordy_mapy.x + 155, koordy_mapy.y + 70);
            if (GetRValue(kolor) == 77 && GetGValue(kolor) == 193 && GetBValue(kolor) == 249) {
                wygrana = true;
            }
            if (GetAsyncKeyState(0x51)) {
                wygrana = true;
            }
        }
        for (short i = 0; i < 24; i++) {
            for (short j = 0; j < 20; j++) {
                mapa.mapa[i][j] = 0;
            }
        }
        cout << "Wygrana!!" << endl;
        cout << "Rozwiazac go jeszcze raz?" << endl;
        cout << "Zresetuj mape nie przesuwajac jej i wcisnij \"s\" aby uruchomic bota ponownie" << endl;
        while (!GetAsyncKeyState(0x53)) { wygrana = false; }
        cout << "Ponowne rozwiazywanie sapera..." << endl;
        //screenshot();
    }
    system("pause");
    return 0;
}