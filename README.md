## Aprašymas

Ši programa analizuoja tekstinį failą, skaičiuoja žodžių pasikartojimus, ieško žodžių paminėjimo eilučių ir suranda visus URL adresus pagal galimų galūnių sąrašą (`galo_saras.txt`). Rezultatai išsaugomi atskiruose failuose:

- **pasikartoję_zodziai.txt** – žodžiai, kurie tekste pasikartoja daugiau nei vieną kartą, su jų kiekiu.
- **paminejimo_eilutes.txt** – žodžiai ir eilučių numeriai, kuriose jie paminėti daugiau nei vieną kartą.
- **surasti_url.txt** – visi tekste rasti URL adresai su galiojančiomis galūnėmis.

## Naudojimas

1. Įdėkite tekstą į `tekstas.txt`.
2. Įdėkite galimų domenų galūnių sąrašą į `galo_saras.txt`.
3. Kompiliuokite programą:
   ```sh
   make
   ```
4. Paleiskite programą:
   ```sh
   ./find
   ```
5. Rezultatus rasite aukščiau nurodytuose failuose.

## Priklausomybės

- C++20 palaikymas
- UTF-8 locale aplinkoje