# Seminar_OOP

Battleship igra - Gabriel Milunovic
Dobrodošli u igru Potapanje brodova. Ovo je konzolna implementacija igre Battleship, gdje možete igrati protiv drugog(vi ste oba) igrača ili protiv računala.

## Pravila igre

1. **Postavljanje**: Svaki igrač postavlja svoje brodove na ploču. Brodovi se ne smiju preklapati, biti susjedi i moraju biti unutar granica ploče.
2. **Potezi**: Igrači naizmjence napadaju koordinate na protivničkoj ploči.
3. **Pogodak/Promašaj**: Ako je brod pogođen, koordinata se označava s 'X' (zeleno). Ako je promašaj, označava se s 'O' (crveno).
4. **Potapanje brodova**: Kada su svi dijelovi broda pogođeni, brod je potopljen.
5. **Pobjeda**: Igra se nastavlja dok svi brodovi jednog igrača nisu potopljeni. Drugi igrač se proglašava pobjednikom.

## Korištenje
Da biste pokrenuli igru morate kompajlirati i pokrenuti main.cpp:

  g++ -std=c++14 -o battleship main.cpp
  ./battleship

## Poboljšanja
- pametniji AI
- bolja vizualizacija igre
