#ifndef CLIST_H
#define CLIST_H



template<class T>
class CList
{

    friend class iteratore;

    class nodo {
    friend class CList<T>;

    T info;

    nodo* next;


    nodo(const T& i ,nodo* s =0) :
    info(i),
    next(s) {}

    };

    nodo *primo, *ultimo; // membri dati


    static nodo* _copy(nodo*);
    static nodo* getUltimoNodo(nodo*);
    static void _destroy(nodo*);


public:


    class iteratore {
        friend class CList<T>;
        CList<T>::nodo* punt;
    public:
        iteratore() : punt(0) {}
        iteratore(const iteratore& p): punt(p.punt) {}

        iteratore& operator=(const iteratore&);

        bool operator==(iteratore) const;
        bool operator!=(iteratore) const;

        bool isNotNull() const;
        iteratore& operator++();
        iteratore operator++(int);
        bool operator () () const;
    };


    CList(): primo(0), ultimo(0) {}
    CList(const CList&);
    CList& operator=(const CList&);

    ~CList();

    iteratore begin() const;
    iteratore end() const;
    void rimuoviElemento(const iteratore& it);
    bool is_empty() const;
    unsigned int size() const;


    T operator[](iteratore it) const;

    T pop_front();

    void push_back(const T&);
    void push_front(const T&);

}; // fine della definzione di class CList



template<class T>
bool CList<T>::iteratore::operator () () const
{
    return punt != 0;
}


template<class T>
typename CList<T>::iteratore& // tipo di ritorno
CList<T>::iteratore::operator= // nome metodo
(const typename CList<T>::iteratore& i)
{
    if(this != &i)
    {
        punt = i.punt;
        return *this;
    }
}

template<class T>
bool CList<T>::iteratore::isNotNull() const
{
    return punt != 0;
}

template<class T>
bool CList<T>::iteratore::operator==(iteratore i) const
{
    return punt == i.punt;
}


template<class T>
bool CList<T>::iteratore::operator!=(iteratore i) const
{
    return punt != i.punt;
}


template<class T>
typename CList<T>::iteratore& CList<T>::iteratore::operator++()
{
    if(punt) punt = punt->next;
    return *this;
}


template<class T>
typename CList<T>::iteratore CList<T>::iteratore::operator++(int)
{
    iteratore aux = *this;
    if(punt) punt = punt -> next;
    return aux;
}




template<class T>
typename CList<T>::nodo* CList<T>::_copy(CList<T>::nodo* a)
{
return (a)? new nodo(a->info, _copy (a->next)): 0;
}


template<class T>
void CList<T>::_destroy(CList<T>::nodo* a)
{
        nodo* p;
        while(a)
        {
            p = a;
            a=a->next;
            delete p;
        }
}



template<class T>
typename CList<T>::nodo* CList<T>::getUltimoNodo(nodo* L)
{
    while(L->next)
    L = L ->next;

    return (L)? L : 0;
}






template<class T>
bool CList<T>::is_empty() const {
    return !primo && !ultimo;
}


template<class T>
T CList<T>::operator[](iteratore it) const
{
    return  it.punt->info;
}


template<class T>
void CList<T>::rimuoviElemento(const iteratore& it) {


   nodo* prec =0, * p =primo;
   while(p && !(p == it.punt))
   {
        prec = p;
         p = p->next;
   }
    if(p) {
        if(!prec)
         primo = p->next;
        else
         prec->next = p->next;

      delete p;
    }
 }


template<class T>
CList<T>::CList(const CList& c)
{
    if(this != &c)
    {
        if (primo)
        _destroy (primo);

        primo = _copy (c.primo);
        ultimo = getUltimoNodo (primo);
    }
}

template<class T>
CList<T>& CList<T>::operator=(const CList<T>& c)
{
    if(this != &c)
    {
        if(primo)
            _destroy (primo);

        primo = _copy (c.primo);
        ultimo = getUltimoNodo (primo);
    }
    return *this;
}

template<class T>
CList<T>::~CList()
{
    if(primo)
    {
    _destroy (primo);
    ultimo = 0;
    }
}



template<class T>
typename CList<T>::iteratore CList<T>::begin() const
{
    iteratore aux;
    aux.punt = primo;
    return aux;
}

template<class T>
typename CList<T>::iteratore CList<T>::end() const
{
    iteratore aux;
    aux.punt = 0;
    return aux;
}


template<class T>
unsigned int CList<T>::size() const
{
  if (is_empty ())
      return static_cast<unsigned int>(0);

  int cont = 0;
    for (iteratore i = begin(); i != end(); ++i, ++cont);

    return static_cast<unsigned int>(cont);
}




template<class T>
T CList<T>::pop_front()
{
    if(primo)
    {
        T aux = primo->info;
        nodo* t = primo;
        primo = primo->next;
        t->next = 0;
        delete t;
        return aux;
    }

}


template<class T>
void CList<T>::push_back(const T& c) {

     if(!primo && !ultimo)
     {
        primo = new nodo(c);
        ultimo = primo;
     }
     else
     {
         ultimo -> next = new nodo(c, 0);
         ultimo = ultimo->next;
     }
}


template<class T>
void CList<T>::push_front(const T& c)
{
    if(!primo && !ultimo)
    {
        primo = new nodo(c);
        ultimo = primo;
    }
    else
        primo = new nodo(c, primo);

}

#endif // CLIST_H
