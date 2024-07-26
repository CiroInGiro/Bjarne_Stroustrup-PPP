/* Capitolo 25 Esercizio 4
* Aggiungi gli operatori bitwise &, |, ^ e ~ a Calculator del capitolo 7
*/

/* Nel C++ Reference gli operatori bitwise vengono elaborati dopo gli operatori '+' e '-' secondo questo ordine:
* '!' e '~', '<<' e '>>', '&', '^', '|'
* aggiungeremo una funziona che elabora questi operatori e modifichiamo la classe token per riconoscerli
*/

// Calculatore dal capitolo 7:
//
// This is example code from Chapter 6.7 "Trying the second version" of
// "Software - Principles and Practice using C++" by Bjarne Stroustrup
//

/*
    This file is known as calculator02buggy.cpp

    I have inserted 5 errors that should cause this not to compile
    I have inserted 3 logic errors that should cause the program to give wrong results

    First try to find an remove the bugs without looking in the book.
    If that gets tedious, compare the code to that in the book (or posted source code)

    Happy hunting!

*/

// Capitolo 6
/*
Esercizio 2: aggiungere l'uso delle parentesi graffe {}
*/

/*
Esercizio 3: aggiungere la possibilità di calcolare il fattoriale utilizzando il carattere '!' e che abbia la priorità su '*' e '/'
*/

#include "std_lib_facilities.h"

//------------------------------------------------------------------------------

//lass Token { // 1 errore di compilazione. si intende definire un proprio tipo con la parola chiave class
class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
    :full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

// Token get() 2. Errore di compilazione. get() definita nella classe Token_Stream e definita al suo esterno
Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case '=':    // for "print" // Capitolo 6 Drill 3
    case 'x':    // for "quit" // Capitolo 6 Drill 2
    case '{': case '}': case '(': case ')': case '+': case '-': case '*': case '/': case '!':
    case '~': case '&': case '^': case '|':
        return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '9':
    {
        cin.putback(ch);         // put digit back into the input stream
        double val;
        cin >> val;              // read a floating-point number
        return Token('8', val);   // let '8' represent "a number"
    }
    default:
        error("Bad token");
    }
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback() 

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '{': // gestione delle parentesi graffe
    {
        double d = expression();
        t = ts.get();
        if (t.kind != '}') error("aspetto ancora la '}' di chiusura.");
        return d;
    }
    case '(':    // handle '(' expression ')'
    {
        double d = expression();
        t = ts.get();
        //if (t.kind != ')') error("')' expected); // 3. Errore di compilazione. Mancano gli apici che chiudono la stringa passata ad error()
        if (t.kind != ')') error("')' expected");
        return d;
    }
    /* Soluzione alternativa alla funzione tilde()
    case '~': {
        double right = expression();
        //t = ts.get();
        //if (t.kind != '8') error("primary expected after the '~'");
        //right = ~(int)(expression());
        //t = ts.get(); // gestiamo anche le negazioni multiple!
        return ~(int)right;
        //break;
    }
    */
    case '8':            // we use '8' to represent a number
        return t.value;  // return the number's value
    default:
        error("primary expected");
    }
}

//------------------------------------------------------------------------------

// operazioni sui bit, l'operatore di inversione bit ha la precedenza su * e /
double tilde() {
    double right = 0;
    Token t = ts.get();

    while (true) {
        switch (t.kind) {
        case '~':
            right = ~(int)(expression());
            return right;
        default:
            ts.putback(t);
            return primary();
        }
    }

    return right;
}


//------------------------------------------------------------------------------

// lavoriamo col fattoriale
double factorial()
{
    double left = tilde();
    Token t = ts.get();

    while (true)
    {
        switch (t.kind)
        {
        case '!':
            for (int ciclo = (left - 1); ciclo >= 1; --ciclo)
            {
                left *= ciclo;
            }
            t = ts.get(); // con questo permetto di chiedere il fattoriale di un fattoriale 5!!
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

// ------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    //double left = primary();  // prima di avere il numero primario dobbiamo controllare che non bisogna calcolare il fattoriale
    double left = factorial();
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            // 3. errore logico: manca il break, altrimenti dopo il caso '*' va avanti col caso '/' senza motivo.
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    // double left = term(;      // read and evaluate a Term // 4. errore di compilazione. manca la parentesi che chiude gli argomenti di term()
    double left = term();
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            //left += term();    // evaluate Term and subtract  // 1. Errore logico, qui si somma solo
            left += (term() * -1); // così sommo il valore negativo quando è positivo e inverto il segno per sottrarre un negativo
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

//-------------------------------------------------------------------------------------
//
// operazioni sui bit, gli operatori &, ^ e | sono gli ultimi ad avere la priorità
double bitoper() {
    double left = expression();
    Token t = ts.get();

    while (true) {
        switch (t.kind) {
        case '&':
            left = (int)left & (int)(expression());
            t = ts.get();
            break;
        case '^':
            left = (int)left ^ (int)(expression());
            t = ts.get();
            break;
        case '|':
            left = (int)left | (int)(expression());
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

//------------------------------------------------------------------------------

int main() // il blocco try è visto come un unica istruzione quindi le parentesi del blocco main possono mancare.
try
{
    double val = 0; // 5. errore di compilazione. mancava la dichiarazione di val

    // Capitolo 6 Drill 4
    cout << "\n" << "Benvenuto in Calculator, scrivi una espressione con numeri double, " << "\n";

    // Capitolo 6 Drill 5
    cout << "\n"
        << "puoi calcolare in successione somme, sottrazioni, moltiplicazioni, divisioni  e fattoriale con i rispettivi carattei: " << "\n"
        << "'+', '-', '*', '/' e '!', puoi utilizzare anche le parentesi '(', ')', '{' e '}'" << "\n"
        << "al capitolo 25 sono stati aggiunti gli operatori bitwise coi caratteri '&', '|', '^' e '~'\n"
        << "usa il carattere '=' per avere il risultato e il carattere 'x' per uscire." << "\n";

    while (cin) {
        Token t = ts.get();

        if (t.kind == 'x') break; // 'q' for quit // Capitolo 6 Drill 2
        if (t.kind == '=')        // ';' for "print now" // Capitolo 6 Drill 3
            cout << "=" << val << '\n';
        else // 2. errore logico: qui ci vuole un blocco perché entranbe le istruzioni vengono eseguite se kind è diverso da 'q' e ';'
        {
            ts.putback(t);
            // metto val quiin modo che dopo aver dato il primo risultato evito di richiamare expression() senza un nuovo input
            //val = expression();
            val = bitoper(); // aggiunti gli operatori bitwise eseguiti per ultimi
        }
    }
    keep_window_open();
}
catch (exception& e) {
    cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;
}

//------------------------------------------------------------------------------
