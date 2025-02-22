
/* ******************************* c204.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c204 - Převod infixového výrazu na postfixový (s využitím c202)     */
/*  Referenční implementace: Petr Přikryl, listopad 1994                      */
/*  Přepis do jazyka C: Lukáš Maršík, prosinec 2012                           */
/*  Upravil: Kamil Jeřábek, září 2019                                         */
/* ************************************************************************** */
/*
** Implementujte proceduru pro převod infixového zápisu matematického
** výrazu do postfixového tvaru. Pro převod využijte zásobník (tStack),
** který byl implementován v rámci příkladu c202. Bez správného vyřešení
** příkladu c202 se o řešení tohoto příkladu nepokoušejte.
**
** Implementujte následující funkci:
**
**    infix2postfix .... konverzní funkce pro převod infixového výrazu 
**                       na postfixový
**
** Pro lepší přehlednost kódu implementujte následující pomocné funkce:
**    
**    untilLeftPar .... vyprázdnění zásobníku až po levou závorku
**    doOperation .... zpracování operátoru konvertovaného výrazu
**
** Své řešení účelně komentujte.
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c204.h"
int solved;

/*
** Pomocná funkce untilLeftPar.
** Slouží k vyprázdnění zásobníku až po levou závorku, přičemž levá závorka
** bude také odstraněna. Pokud je zásobník prázdný, provádění funkce se ukončí.
**
** Operátory odstraňované ze zásobníku postupně vkládejte do výstupního pole
** znaků postExpr. Délka převedeného výrazu a též ukazatel na první volné
** místo, na které se má zapisovat, představuje parametr postLen.
**
** Aby se minimalizoval počet přístupů ke struktuře zásobníku, můžete zde
** nadeklarovat a používat pomocnou proměnnou typu char.
*/
void untilLeftPar ( tStack* s, char* postExpr, unsigned* postLen ) {
    char sChar;

    // cita znaky kym nevyprazdni zasobnik
    while (! stackEmpty(s)) {
        // precita a odstrani znak z vrchu zasobniku
        stackTop(s, &sChar);
        stackPop(s);

        // ked narazi na lavu zatvorku tak konci
        if (sChar == '(') {
          break;
        }
      
        postExpr[*postLen] = sChar;
        *postLen += 1;
    }
}

/*
** Pomocná funkce doOperation.
** Zpracuje operátor, který je předán parametrem c po načtení znaku ze
** vstupního pole znaků.
**
** Dle priority předaného operátoru a případně priority operátoru na
** vrcholu zásobníku rozhodneme o dalším postupu. Délka převedeného 
** výrazu a taktéž ukazatel na první volné místo, do kterého se má zapisovat, 
** představuje parametr postLen, výstupním polem znaků je opět postExpr.
*/
void doOperation ( tStack* s, char c, char* postExpr, unsigned* postLen ) {
    char sTop;

    // do prázdneho zásobníku rovno volži znak
    if (stackEmpty(s)) {
        stackPush(s, c);
        return;
    }

    stackTop(s, &sTop);

    // pokiaľ nie je na vrchole ľavá zátvorka alebo
    // vkládame násobenie alebo delenie a súǎsne je na vrchole plus alebo mínus
    // vyberáme znak z vrcholu zásobíku
    while (sTop != '(' && ( (c != '*' && c != '/') || (sTop != '+' && sTop != '-') )) {
        // vložíme znak z vrcholu zásobníku do výsledného reťazca
        postExpr[*postLen] = sTop;
        *postLen += 1;
        // odstránime znak zo zásobníku 
        stackPop(s);

        // ak nie je zásobník prázdny, tak pokračujeme
        if (stackEmpty(s)) {
            break;
        } else {
            stackTop(s, &sTop);
        }
    }

    // vložime nový znak na vrchol zásobníku
    stackPush(s, c);
}

/* 
** Konverzní funkce infix2postfix.
** Čte infixový výraz ze vstupního řetězce infExpr a generuje
** odpovídající postfixový výraz do výstupního řetězce (postup převodu
** hledejte v přednáškách nebo ve studijní opoře). Paměť pro výstupní řetězec
** (o velikosti MAX_LEN) je třeba alokovat. Volající funkce, tedy
** příjemce konvertovaného řetězce, zajistí korektní uvolnění zde alokované
** paměti.
**
** Tvar výrazu:
** 1. Výraz obsahuje operátory + - * / ve významu sčítání, odčítání,
**    násobení a dělení. Sčítání má stejnou prioritu jako odčítání,
**    násobení má stejnou prioritu jako dělení. Priorita násobení je
**    větší než priorita sčítání. Všechny operátory jsou binární
**    (neuvažujte unární mínus).
**
** 2. Hodnoty ve výrazu jsou reprezentovány jednoznakovými identifikátory
**    a číslicemi - 0..9, a..z, A..Z (velikost písmen se rozlišuje).
**
** 3. Ve výrazu může být použit předem neurčený počet dvojic kulatých
**    závorek. Uvažujte, že vstupní výraz je zapsán správně (neošetřujte
**    chybné zadání výrazu).
**
** 4. Každý korektně zapsaný výraz (infixový i postfixový) musí být uzavřen 
**    ukončovacím znakem '='.
**
** 5. Při stejné prioritě operátorů se výraz vyhodnocuje zleva doprava.
**
** Poznámky k implementaci
** -----------------------
** Jako zásobník použijte zásobník znaků tStack implementovaný v příkladu c202. 
** Pro práci se zásobníkem pak používejte výhradně operace z jeho rozhraní.
**
** Při implementaci využijte pomocné funkce untilLeftPar a doOperation.
**
** Řetězcem (infixového a postfixového výrazu) je zde myšleno pole znaků typu
** char, jenž je korektně ukončeno nulovým znakem dle zvyklostí jazyka C.
**
** Na vstupu očekávejte pouze korektně zapsané a ukončené výrazy. Jejich délka
** nepřesáhne MAX_LEN-1 (MAX_LEN i s nulovým znakem) a tedy i výsledný výraz
** by se měl vejít do alokovaného pole. Po alokaci dynamické paměti si vždycky
** ověřte, že se alokace skutečně zdrařila. V případě chyby alokace vraťte namísto
** řetězce konstantu NULL.
*/
char* infix2postfix (const char* infExpr) {
    char *postExpr = malloc(MAX_LEN * sizeof(char));
    if (postExpr == NULL) {
        return NULL;
    }

    int i = 0; //index nacitaneho znaku
    char inChar; //citany znak
    tStack s;
    unsigned int postI = 0; //index a delka vysledneho retazca

    stackInit(&s);

    while (infExpr[i] != '\0') {
        inChar = infExpr[i++]; //ulozi precitany znak a incrementuje index

        if (inChar == '*' || inChar == '/' || inChar == '+' || inChar == '-') {
            //ak je precitany znak operace, spracuje ju
            doOperation(&s, inChar, postExpr, &postI);
        } else if ((inChar >= '0' && inChar <= '9')
                  || (inChar >= 'a' && inChar <= 'z')
                  || (inChar >= 'A' && inChar <= 'Z')) {
            //ak je precitany znak znak alebo cislo, ulozi ho do retazca
            postExpr[postI++] = inChar;
        } else if (inChar == '(') {
            //lavu zatvorku rovno ulozi do retazca
            stackPush(&s, inChar);
        } else if (inChar == ')') {
            //pri pravej zatvorke spracuje zasobnik az po lavu zatvorku
            untilLeftPar(&s, postExpr, &postI);
        } else if (inChar == '=') {
            //pri rovnitku spracuje zasobnik az po koniec retazca
            untilLeftPar(&s, postExpr, &postI);
            //ulozi rovnitko a ukoncovaci znak do retazca
            postExpr[postI++] = inChar;
            postExpr[postI] = '\0';
            return postExpr;
        }
    }

    //ak sa z funkcie nevrati v dosledku rovnitka tak vracia NULL
    return NULL;
}

/* Konec c204.c */
