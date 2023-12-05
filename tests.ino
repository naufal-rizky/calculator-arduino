#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7); // RS, En, D4, D5, D6, D7
const byte ROWS = 5;
const byte COLS = 4;
char keys[ROWS][COLS] = {

    {'1', '2', '3', '+'},
    {'4', '5', '6', '-'},
    {'7', '8', '9', 'x'},
    {'.', '0', '=', '/'},
    {'C', 'r', '^', '%'}

};

byte ROWPINS[ROWS] = {6, 5, 4, 3, 2};
byte COLPINS[COLS] = {A3, A2, A1, A0};
Keypad myKeypad = Keypad(makeKeymap(keys), ROWPINS, COLPINS, ROWS, COLS);

boolean valOnePresent = false;
boolean final = false;
String Num1, Num2, hasil;

long hasilLong;   // Use long for integer results
float hasilFloat; // Use float for decimal results
char op;

bool decimalEntered = false;

void setup()
{
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Kalkulator");
    delay(1000);
    lcd.clear();
}

void loop()
{
    char key = myKeypad.getKey();

    if (key != NO_KEY && (isdigit(key) || key == '.'))
    {
        if (!valOnePresent)
        {
            if (key == '.' && !decimalEntered)
            {
                decimalEntered = true;
                Num1 += key;
            }
            else if (isdigit(key))
            {
                Num1 += key;
            }

            int numLength = Num1.length();
            lcd.setCursor(0, 0);
            lcd.print(Num1);
        }
        else
        {
            if (key == '.' && !decimalEntered)
            {
                decimalEntered = true;
                Num2 += key;
            }
            else if (isdigit(key))
            {
                Num2 += key;
            }

            int numLength = Num2.length();
            lcd.setCursor(0, 1);
            lcd.print(Num2);
            final = true;
        }
    }
    else if (valOnePresent == false && key != NO_KEY && (key == '/' || key == 'x' || key == '-' || key == '+' || key == 'r' || key == '^' || key == '%'))
    {
        if (!valOnePresent)
        {
            valOnePresent = true;
            lcd.setCursor(15, 0);
            op = key;
            lcd.print(op);
        }
    }
    else if (final == true && key != NO_KEY && key == '=')
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(Num1);
        lcd.print(op);
        lcd.print(Num2);
        lcd.setCursor(0, 1);
        operation();
        display();
    }
    else if (key != NO_KEY && key == 'C')
    {
        lcd.clear();
        valOnePresent = false;
        final = false;
        Num1 = "";
        Num2 = "";
        hasil = "";
        hasilLong = 0;
        hasilFloat = 0.0;
        op = ' ';
        decimalEntered = false;
    }
}

void operation()
{
    if (op == '+')
    {
        hasilLong = atol(Num1.c_str()) + atol(Num2.c_str());
        hasilFloat = Num1.toFloat() + Num2.toFloat();
    }
    else if (op == '-')
    {
        hasilLong = atol(Num1.c_str()) - atol(Num2.c_str());
        hasilFloat = Num1.toFloat() - Num2.toFloat();
    }
    else if (op == 'x')
    {
        hasilLong = atol(Num1.c_str()) * atol(Num2.c_str());
        hasilFloat = Num1.toFloat() * Num2.toFloat();
    }
    else if (op == '/')
    {
        hasilLong = atol(Num1.c_str()) / atol(Num2.c_str());
        hasilFloat = Num1.toFloat() / Num2.toFloat();
    }
    else if (op == 'r') // r for square root
    {
        hasilFloat = sqrt(Num1.toFloat());
        hasilLong = hasilFloat; // Consider only integer part for display
    }
    else if (op == '^')
    {
        hasilLong = pow(atol(Num1.c_str()), atol(Num2.c_str()));
        hasilFloat = pow(Num1.toFloat(), Num2.toFloat());
    }
    else if (op == '%')
    {
        hasilFloat = Num1.toFloat() * (Num2.toFloat() / 100.0);
        hasilLong = hasilFloat;
    }
}

void display()
{
    if (hasilLong == hasilFloat)
    {
        hasil = String(hasilLong); // Convert integer result to string
    }
    else
    {
        hasil = String(hasilFloat, 2); // Convert float result to string with 2 decimal places
    }
    lcd.print(hasil);
    lcd.noAutoscroll();
}
