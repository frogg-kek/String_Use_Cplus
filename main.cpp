#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <regex>
#include <locale>
#include <string>
#include <vector>
#include <algorithm>


std::wstring nuskaityti_wtekstai(const std::string &failo_pavadinimas) {
    std::wifstream failas(failo_pavadinimas);
    failas.imbue(std::locale(""));
    std::wstringstream turinys;
    turinys << failas.rdbuf();
    return turinys.str();
}

std::vector<std::wstring> nuskaityti_eilutes(const std::string &failo_pavadinimas) {
    std::wifstream failas(failo_pavadinimas);
    failas.imbue(std::locale(""));
    std::vector<std::wstring> eilutes;
    std::wstring eil;
    while (std::getline(failas, eil)) {
        eilutes.push_back(eil);
    }
    return eilutes;
}

// sarasiukas musu
std::unordered_set<std::wstring> ikelti_tld(const std::string &failo_pavadinimas) {
    std::wifstream failas(failo_pavadinimas);
    failas.imbue(std::locale(""));
    std::unordered_set<std::wstring> galunes;
    std::wstring eil;
    while (std::getline(failas, eil)) {
        if (!eil.empty() && eil[0] != L'#') {
            std::transform(eil.begin(), eil.end(), eil.begin(), ::towlower);
            galunes.insert(eil);
        }
    }
    return galunes;
}

int main() {
    
    std::locale::global(std::locale("en_US.UTF-8")); 
    
    std::wstring tekstas = nuskaityti_wtekstai("tekstas.txt");
    std::vector<std::wstring> eilutes = nuskaityti_eilutes("tekstas.txt");
    auto galunes = ikelti_tld("galo_saras.txt");

    std::wregex zodis_re(LR"([^\W\d_]{2,})", std::regex::ECMAScript | std::regex::icase);

   
    std::wregex url_re(LR"(([\w\.-]+)\.([a-z]{2,}(?:\.[a-z]{2,})?))", std::regex::icase);


    std::unordered_map<std::wstring, int> zodziu_kiekis;
    std::unordered_map<std::wstring, std::set<int>> paminetos_eilutes;
    std::set<std::wstring> surasti_url;

    // Žodžių skaičiavimas
    for (std::wsregex_iterator it(tekstas.begin(), tekstas.end(), zodis_re), end; it != end; ++it) {
        std::wstring zodis = it->str();
        std::transform(zodis.begin(), zodis.end(), zodis.begin(), ::towlower);
        if (!galunes.count(zodis)) {
        zodziu_kiekis[zodis]++;
        }
    }

    // eilutės suradimas
    for (size_t i = 0; i < eilutes.size(); ++i) {
        for (std::wsregex_iterator it(eilutes[i].begin(), eilutes[i].end(), zodis_re), end; it != end; ++it) {
            std::wstring zodis = it->str();
            std::transform(zodis.begin(), zodis.end(), zodis.begin(), ::towlower);
            if (zodziu_kiekis[zodis] > 1)
                paminetos_eilutes[zodis].insert(i + 1);
        }
    }

    // URL paieška
    for (std::wsregex_iterator it(tekstas.begin(), tekstas.end(), url_re), end; it != end; ++it) {
        std::wstring galas = it->str(2);
        std::transform(galas.begin(), galas.end(), galas.begin(), ::towlower);
        if (galunes.count(galas)) {
            surasti_url.insert(it->str());
        }
    }

    std::wofstream zodziai_failas("pasikartoję_zodziai.txt");
    zodziai_failas.imbue(std::locale(""));
    for (const auto &[zodis, kiekis] : zodziu_kiekis) {
        if (kiekis > 1)
            zodziai_failas << zodis << L": " << kiekis << L" kartus\n";
    }

    std::wofstream eil_failas("paminejimo_eilutes.txt");
    eil_failas.imbue(std::locale(""));
    for (const auto &[zodis, eil] : paminetos_eilutes) {
        eil_failas << zodis << L": ";
        for (int e : eil)
            eil_failas << e << L" ";
        eil_failas << L"\n";
    }

    std::wofstream url_failas("surasti_url.txt");
    url_failas.imbue(std::locale(""));
    for (const auto &url : surasti_url)
        url_failas << url << L"\n";

    return 0;
}
