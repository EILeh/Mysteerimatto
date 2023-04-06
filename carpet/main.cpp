/* Mysteerimatto
 *
 * Kuvaus:
 * Ohjelma toteuttaa mysteerimaton, jossa sovelletaan mallintunnistusta
 * (pattern matching). Matto ja malli koostuvat erivärisistä ruuduista ja
 * sallitut värit on annettu valmiiksi. Mallin koko on aina 2 x 2, eli se koos-
 * tuu neljästä väriruudusta, joita etsitään matosta. Ohjelma kysyy käyttäjältä
 * maton kokoa, josta leveys ja korkeus erotellaan välilyönnillä. Ohjelma kysyy
 * käyttäjältä halutaanko matto täyttää satunnaisesti arvottavilla väreillä vai
 * luetteleeko käyttäjä maton värit. Jos käyttäjä haluaa, että värit arvotaan
 * mattoon, kysytään häneltä satunnaislukugeneraattorin siemenlukua. Jos käyttä-
 * jä haluaa itse syöttää maton värit, pyydetään häntä syöttämään värejä maton
 * leveyden ja korkeuden kertolaskun verran. Tällöin käyttäjän tulee syöttää
 * värien alkukirjaimet yhtenä merkkijonona. Maton muodostamisen jälkeen käyttä-
 * jältä pyydetään neljä eri väriä, joita lähdetään etsimään matosta tai vaihto-
 * ehtoisesti lopettamaan ohjelman syöttämällä joko 'q' tai 'Q'. Jos käyttäjä
 * syöttää neljä väriä, etsitään värineliö(t) matosta ja tulostetaan niiden
 * koordinaatit sekä kuinka monta niitä löytyi. Ohjelma tarkistaa myös, että
 * käyttäjän syötteet eivät ole virheellisiä ja tulostaa tarvittaessa virheil-
 * moituksen.
 *
 * Ohjelman kirjoittajat
 *
 * Nimi: Elli Lehtimäki
 * Opiskelijanumero: 151309919
 * Käyttäjätunnus: nxelle
 * E-Mail: elli.i.lehtimaki@tuni.fi
 *
 * Nimi: Henri Dyster
 * Opiskelijanumero: H211843
 * Käyttäjätunnus: fghedy
 * E-mail: henri.dyster@tuni.fi
 *
 */

#include <algorithm>
#include <cctype>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

// Luettelotyyppi värien esittämiseen.
enum Color {RED, GREEN, BLUE, YELLOW, WHITE, NUMBER_OF_COLORS};

// Vakiovektori, joka sisältää värien alkukirjaimet.
const vector<char> ENUM_TO_COLOR = {'R', 'G', 'B', 'Y', 'W'};

// Globaalivakio, joka määrää vaaditun pituuden etsittävien värien määrälle.
const int REQUIRED_AMOUNT_OF_COLORS = 4;

// Globaalivakio, jonka syötettäessä ohjelman suoritus lopetetaan.
const string ENDING_LETTER = "Q";

// Globaalivakio, joka määrittelee maton korkeuden tai leveyden vähimmäiskoon.
const int REQUIRED_HEIGTH_OR_WIDTH = 2;

// Globaalivakio, joka määrittelee maton mittojen vaaditun määrän.
const int REQUIRED_AMOUNT_OF_MEASUREMENTS = 2;


bool are_measurements_correct(vector<int> &input_numbers)
{
// Tarkistaa, onko annettu syöte pienempi kuin 2, jos ei palauttaa false,
// muuten true.

// return: Palauttaa totuusarvon tehdyn löydön perusteella.

    // Käy läpi vektorin input_numbers, josta maton leveys ja pituus löytyyvät
    // ja tarkistaa, että sen koko on vähintään 2.
    for (string::size_type vector_member = 0; vector_member <
          input_numbers.size(); ++vector_member)
    {
        if (input_numbers.at(vector_member) < REQUIRED_HEIGTH_OR_WIDTH)
        {
            return false;
        }
    }
    return true;
}

void ask_measurements(vector<int> &input_numbers)
{
// Kysyy käyttäjältä maton leveyden ja korkeuden ja lisää ne vektoriin.

// MUUTTUJIEN ALUSTUKSET TIETOTYYPEITTÄIN AAKKOSJÄRJESTYKSESSÄ.

//  Kokonaisluvut:
    int new_integer = 0;

    for (int i = 0; i < REQUIRED_AMOUNT_OF_MEASUREMENTS; ++i)
    {
        cin >> new_integer;
        input_numbers.push_back(new_integer);
    }
}

void print_carpet(vector<vector<char>> &carpet)
{
// Tulostaa maton halutussa muodossa.

    // Käy läpi vektoreita korkeussuunnassa.
    for (size_t y = 0; y < carpet.size(); y++)
    {
        // Käy läpi yksittäisen vektorin indeksejä leveyssuunnassa ja tulostaa
        // maton halutussa muodossa.
        for (size_t x = 0; x < carpet.at(y).size(); x++)
        {
            cout << " " << carpet.at(y).at(x);
        }

        cout << endl;
    }
}

vector<vector<char>> random_color_generator(unsigned width, unsigned height)
{
// Arpoo värit satunnaisesti käyttäjän syöttämän siemenluvun perusteella.

// MUUTTUJIEN ALUSTUKSET TIETOTYYPEITTÄIN AAKKOSJÄRJESTYKSESSÄ.

//  Kokonaisluvut:
    unsigned seed_value = 0;

//  Vektorit:
    vector<vector<char>> carpet;
    vector<char> row;

//  return: Palauttaa kaksiulotteisen vektorin carpet.

    cout << "Enter a seed value: ";
    cin >> seed_value;

    default_random_engine engine(seed_value);

    uniform_int_distribution<int> distr(0, 4);

    // Käy läpi korkeussuunnassa läpi vektoreita.
    for (unsigned y = 0; y < height; ++y)
    {
        // Käy läpi yksittäisen vektorin indeksejä.
        for (unsigned x = 0; x < width; ++x)
        {
            // Arvotaan satunnainen numero Color enumista muuttujaan random_co-
            // lor, verrataan random_color:n idenksiä switch:ssä määriteltyihin
            // indekseihin ja lisätään värin alkukirjain vektoriin row.
            Color random_color = Color(distr(engine) % NUMBER_OF_COLORS);

            switch (random_color) {
            case 0:
                row.push_back('R');
                break;
            case 1:
                row.push_back('G');
                break;
            case 2:
                row.push_back('B');
                break;
            case 3:
                row.push_back('Y');
                break;
            case 4:
                row.push_back('W');
                break;
            case NUMBER_OF_COLORS:
                break;
            }
        }

        // Tallentaa vektorin row arvot kaksiulotteiseen vektoriin carpet.
        carpet.push_back(row);
        row.clear();
    }

    print_carpet(carpet);

    return carpet;
}

string letters_uppercase(string user_input)
{
// Muuttaa pienet kirjaimet isoiksi kirjaimiksi.

//  return: Palauttaa käyttäjän syöttämän merkkijonon muutettuna isoiksi
//  kirjaimiksi.

    // Käy läpi käyttäjän syöttämää merkkijonoa ja muuttaa syötteen isoiksi kir-
    // jaimiksi. Tämän jälkeen palautetaan merkkijono isoina kirjaimina.
    for (unsigned i = 0; i < user_input.length(); i++)
    {
        user_input.at(i) = toupper(user_input.at(i));
    }

    return user_input;
}

bool correct_colors(string &colors)
{
// Tarkistaa, että käyttäjän syöttämät värit lyötyvät vektorista ENUM_TO_COLOR.

//  return: Palauttaa totuusarvon tehdyn löydön perusteella.

    colors = letters_uppercase(colors);

    // Käy läpi käyttäjän syöttämät värit yksitellen
    for (auto& color : colors)
    {
        // Jos käyttäjän syötteestä löytyy väri, jota ei löydy vektorista
        // ENUM_TO_COLOR, tulostetaan virheilmoitus ja palautetaan false.
        if (!(find(ENUM_TO_COLOR.begin(), ENUM_TO_COLOR.end(), color)
               != ENUM_TO_COLOR.end()))
        {
            cout << " Error: Unknown color." << endl;
            return false;
        }
    }

    return true;
}

void search_patterns(unsigned width, unsigned height,
                     vector<vector<char>> carpet, string four_colors)
{
// Funktio etsii, kuinka monta mallin esiintymää matosta löytyi ja tulostaa sekä
// niiden koordinaatit että esiintymien määrän.

// MUUTTUJIEN ALUSTUKSET TIETOTYYPEITTÄIN AAKKOSJÄRJESTYKSESSÄ.

//  Kokonaisluvut:
    int counter = 0;

//  return: Palaa takaisin kutsufunktioon.

    // Käy korkeussuunnassa vektoreita läpi ja pysähtyy korkeussuunnassa toisek-
    // si viimeiseen vektoriin, jotta ei indeksoi yli tietorakenteen.
    for (unsigned y = 0; y < height - 1; y++)
    {
        // Käy leveyssuunnassa läpi vektorin indeksejä ja pysähtyy leveyssuun-
        // nassa toiseksi viimeiseen alkioon, jotta ei indektoi yli tietoraken-
        // teen.
        for (unsigned x = 0; x < width - 1; x++)
        {
            // Käy läpi käyttäjän syöttämät värit ja tarkistaa löytyykö matosta
            // haluttuja värjeä 2x2 neliön kokoisena alueena. Jos matosta löy-
            // tyy värit, tulostetaan väriruudun koordinaatit ja kasvatetaan
            // counter:n arvoa yhdellä.
            if (carpet.at(y).at(x) == four_colors.at(0) &&
                    carpet.at(y).at(x+1) == four_colors.at(1) &&
                    carpet.at(y+1).at(x) == four_colors.at(2) &&
                    carpet.at(y+1).at(x+1) == four_colors.at(3))
            {

                // Koordinaatit tulostetaan 2x2 neliön vasemmasta yläkulmasta
                // katsottuna yhden suurempana, koska indeksointi alkaa
                // nollasta, jolloin tulostusvaiheessa niiden arvot olisivat
                // yhden liian pieniä.
                cout << " - Found at (" << x + 1 << ", " << y + 1 << ")"
                     << endl;

                counter++;
            }
        }
    }

    cout << " = Matches found: " << counter << endl;

    return;
}

string enter_colors(unsigned width, unsigned height,
                    vector<vector<char>> carpet)
{
// Kysyy käyttäjältä neljä väriä, joita matosta halutaan etsiä tai vaihto-
// ehtoisesti lopetuskommennon Q.

// MUUTTUJIEN ALUSTUKSET TIETOTYYPEITTÄIN AAKKOSJÄRJESTYKSESSÄ.

//  Merkkijonot:
    string colors;

//  return: Palauttaa merkkijonon käyttäjän syöttämistä väreistä.

    while (true)
    {
        cout << "Enter 4 colors, or q to quit: ";
        cin >> colors;

        // Lopettaa ohjelman suorituksen, jos käyttäjä syöttää ENDING_LETTER:n.
        if (letters_uppercase(colors) == ENDING_LETTER)
        {

            return colors;
        }

        // Tarkistaa, että käyttäjä syöttää oikean määrän värejä.
        else if (colors.length() != REQUIRED_AMOUNT_OF_COLORS)
        {

            cout << " Error: Wrong amount of colors." << endl;
            continue;
        }

        // Tarkistaa, että käyttäjän syöttämät värit ovat sallittuja värejä eli,
        // että ne löytyvät vektorista ENUM_TO_COLOR.
        else if (!correct_colors(colors))
        {

            continue;
        }

        colors = letters_uppercase(colors);

        search_patterns(width, height, carpet, colors);
    }
}

vector<vector<char>> manual_color_generator(unsigned width, unsigned height)
{
// Kysyy käyttäjältä väirt, joista matto muodostetaan.

// MUUTTUJIEN ALUSTUKSET TIETOTYYPEITTÄIN AAKKOSJÄRJESTYKSESSÄ.

//  Merkkijonot:
    string carpet_colors = "";
    string colors = "";

//  Vektorit:
    vector<vector<char>> carpet;
    vector<char> temporary;

//  return: Palauttaa kaksiulotteisen vektorin carpet.

    cout << "Input: ";
    cin >> carpet_colors;

    // Tarkistaa, että värejä on vaadittu määrä eli leveyden ja korkeuden tulo.
    if (carpet_colors.length() != (width * height))
    {
        cout << " Error: Wrong amount of colors." << endl;
        return carpet;
    }

    // Tarkistaa, että käyttäjän syöttämät värit ovat sallittuja eli, että ne
    // löytyvät vektorista ENUM_TO_COLOR.
    else if (!correct_colors(carpet_colors))
    {
        return carpet;
    }

    colors = letters_uppercase(carpet_colors);

    // Käy läpi vektoria korkeussuunnassa.
    for (unsigned y = 0; y < height; y++)
    {
        // Tyhjennetään vektori.
        temporary.clear();

        // Käy läpi yksittäisen vektorin indeksejä leveyssuunnassa.
        for (unsigned x = 0; x < width; x++)
        {
            // Tallennetaan värit vektoriin temporary.
            temporary.push_back(carpet_colors.at(x));
        }

        carpet.push_back(temporary);

        // Lyhennetään käyttäjän antamaa syötettä merkkijonon alusta maton
        // leveyden verran, jotta sisemmän for-loopin suoritus aloitetaan
        // oikeasta kohdasta.
        carpet_colors.erase(carpet_colors.begin() + 0,
                            carpet_colors.begin() + width);
    }

    print_carpet(carpet);

    return carpet;
}

bool is_vector_not_empty(vector<vector<char>> carpet)
{
// Tarkistaa, onko vektori tyhjä.

// return: Palauttaa totuusarvon tehdyn löydön perusteella.

    // Jos vektorin pituus on nolla, palautetaan false.
    if (carpet.size() == 0)
    {
        return false;
    }

    return true;
}

vector<vector<char>> input_review(unsigned width, unsigned height,
                                  vector<vector<char>> carpet)
{
// Kysyy käyttäjältä haluaako hän arpoa maton värit satunnaisesti vai haluaako
// hän syöttää värit manuaalisesti.

// MUUTTUJIEN ALUSTUKSET TIETOTYYPEITTÄIN AAKKOSJÄRJESTYKSESSÄ.

//  Merkkijonot:
    string i_or_r = "";

//  return: Palauttaa kaksiulotteisen vektorin carpet.

    while (true)
    {
        cout << "Select start (R for random, I for input): ";
        cin >> i_or_r;

        if (letters_uppercase(i_or_r) == "I")
        {

            carpet = manual_color_generator(width, height);

            // Jos vektori on tyhjä, palataan while-loopin alkuun.
            if (!is_vector_not_empty(carpet))
            {
                continue;
            }
            break;

        }

        else if (letters_uppercase(i_or_r) == "R")
        {
            carpet = random_color_generator(width, height);

            // Jos vektori on tyhjä, palataan while-loopin alkuun.
            if (!is_vector_not_empty(carpet))
            {
                continue;
            }
            break;
        }
    }

    return carpet;
}

int main()
{
    // Alustetaan vektori.
    vector<int> input_numbers;

    cout << "Enter carpet's width and height: ";
    ask_measurements(input_numbers);

    unsigned width = input_numbers.front();
    unsigned height = input_numbers.back();

    // Tarkistaa, onko syötetyt mitat suurempia kuin 2.
    bool check_input = true;
    check_input = are_measurements_correct(input_numbers);

    // Jos jompikumpi mitoista tai molemmat ovat pienempiä kuin 2, tulostaa
    // virheilmoituksen ja poistuu ohjelmasta arvolla EXIT_FAILURE.
    if (!check_input)
    {
        cout << " Error: Carpet cannot be smaller than pattern. ";
        return EXIT_FAILURE;
    }

    // Alustetaan kaksiulotteinen vektori.
    vector<vector<char>> carpet;

    carpet = input_review(width, height, carpet);

    enter_colors(width, height, carpet);

    return EXIT_SUCCESS;
}
