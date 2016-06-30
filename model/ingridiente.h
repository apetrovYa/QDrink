#ifndef INGRIDIENTE_H
#define INGRIDIENTE_H
#include <string>


class Ingridiente
{

private:
    int quantita/*espressa in cl*/,
        percentualeAlcolica;
    std::string nome;



    static double tassoAlcolico(int, int);

public:

    // getters
    int volume() const;
    double gradazioneAlcolica() const;
    int getPercentualeAlcolica() const;
    const std::string& getNome() const;

    // setters
    void setQuantita(int);
    void setPercentualeAlcolica(int);
    void setNome(const std::string&);

    virtual Ingridiente* copia() const  =0;
    virtual std::string getTipo() const =0;
    virtual ~Ingridiente() {}
};
#endif // INGRIDIENTE_H
