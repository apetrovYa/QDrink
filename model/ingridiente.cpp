#include "ingridiente.h"

double Ingridiente::tassoAlcolico(int q, int pa) {
    double densita_etanolo = 0.79;
    return (q*pa*densita_etanolo)/1000;
}

int Ingridiente::volume() const {
    return quantita;
}


double Ingridiente::gradazioneAlcolica() const {
   return tassoAlcolico (quantita, percentualeAlcolica);
}

int Ingridiente::getPercentualeAlcolica() const {
    return percentualeAlcolica;
}
const std::string& Ingridiente::getNome() const {
    return nome;
}
void Ingridiente::setQuantita(int q) {
      quantita = q;
}
void Ingridiente::setPercentualeAlcolica(int pa) {
    percentualeAlcolica = pa;
}
void Ingridiente::setNome(const std::string& n) {
   if(nome != n)
      nome = n;
}

