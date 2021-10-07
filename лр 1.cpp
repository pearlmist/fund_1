#include <iostream>
//двусвязный неуп список, полином
struct el_poly {
    int data;
    int degree;
    el_poly *next;
    el_poly *last;
};

struct poly {
    el_poly* h;
    el_poly* t;
};
//инициализация
void init (poly *p){
   p->h = NULL;
   p->t = NULL;
}

/* переделать поиск
либо попробовать удалить, по списку не нужен*/


//процедура поиска элемента со степенью degree
int search(poly* p, int degree) {
    if (p->h != NULL) {
        el_poly* cur = new el_poly;
        cur = p->h;
        bool find = false;
        int i = 1;
        while (cur != NULL) {
            if ((cur->degree == degree)&&(find == false)) {
                find = true;
                return i;
            }
            cur = cur->next;
            i++;
        }
        if (find == false) {
            return 0; //возвращает 0, если нет такого эл-та
        }
    }
}
//неупорядоченный список, добавление в конец, а - коэфф, b - степень
void add(poly *p, int data, int degree) {
    el_poly *cur = new el_poly;
    bool find = false;
    cur = p->h;         //создаю указатель на голову
    while (cur != NULL) {    //пока он не будет нулл, ищу нужную степень
        if ((cur->degree == degree) && (find == false)) {
            find = true;
            break;
        }
        cur = cur->next;
    }
    if (find == true) {  //если степень найдена, то складываю коэффициенты при x
        cur->data = cur->data + data;
        if (cur->data == 0) {
            if (not((cur->last == NULL)&&(cur->next == NULL))) { //если в списке не один элемент
                if (cur->last != NULL) cur->last->next = cur->next; //если прошлый не нулл, то указатель прошлого на следующий
                    else cur->next->last = NULL;
                if (cur->next != NULL) cur->next->last = cur->last; //если следующий не нулл, то указатель следующего на прошлый
                    else cur->last->next = NULL;
            }
            if (cur = p->h) p->h = cur->next;
            delete(cur);
            
        }
    }
    else {  //иначе создаю новую ячейку с необх данными
        el_poly* temp = new el_poly;
        temp->data = data;
        temp->degree = degree;
        temp->next = NULL;
        if (p->h == NULL) {             //если голова нулл, то делаю головой эту ячейку
            p->h = temp;
            p->h->data = temp->data;
            p->h->degree = temp->degree;
            temp->last = NULL;
            p->t = p->h;
        }
        else {        //иначе новая ячейка объявляется хвостом
            temp->last = p->t;
            p->t->next = temp;
            p->t = temp;
        }
    }
}

poly* calculate(poly* left, poly* right, char sign) {
    el_poly* cur = new el_poly;
    poly* result = new poly;
    init(result);
    cur = left->h;
    while (cur != NULL) {
        add(result, cur->data, cur->degree);
        cur = cur->next;
    }
    cur = right->h;
    while (cur != NULL) {
        switch (sign) {
        case '+': {
            add(result, cur->data, cur->degree); 
            break;
        }
        case '-': {
            add(result, -cur->data, cur->degree); 
            break;
        }
        }
        cur = cur->next;
    }
    return result;
}
//сложение двух полиномов, результат остается в левом     todo оставлять изначальными левый и правый полиномы, результат отдельно
/*poly* add(poly* left, poly* right) {
    el_poly* cur = new el_poly;
    poly* result = new poly;
    init(result);
    cur = left->h;
    while (cur != NULL) {
        add(result, cur->data, cur->degree);
        cur = cur->next;
    }
    cur = right->h;
    while (cur != NULL) {
        add(result, cur->data, cur->degree);
        cur = cur->next;
    }
    return result;
}
//удаление
poly* remove(poly* left, poly* right) {
    el_poly* cur = new el_poly;
    poly* result = new poly;
    init(result);
    cur = left->h;
    while (cur != NULL) {
        add(result, cur->data, cur->degree);
        cur = cur->next;
    }
    cur = right->h;
    while (cur != NULL) {
        add(result, cur->data, cur->degree);
        cur = cur->next;
    }
    return result;
}*/

//печать списка
void print(poly *p) {
    if (p->h != NULL) {
        el_poly* cur = new el_poly;
        cur = p->h;
        while (cur != NULL) {    //пока текущая ячейка не пустая, вывод в зависимости от степени элемента
            switch (cur->degree) {
                case 0: std::cout << cur->data; break;
                case 1: {
                    if (cur->data == 1) std::cout << "x";
                    else std::cout << cur->data << "x"; 
                    break; 
                }
                default: {
                    if (cur->data == 1) std::cout << "x^" << cur->degree;
                    else std::cout << cur->data << "x^" << cur->degree; 
                }
            }
            if (cur->next != NULL) {
                std::cout << " + ";
            }
            cur = cur->next;
        }
        std::cout << "\n";
    }
}

void delete_poly(poly* p) {
    el_poly* cur = new el_poly;
    cur = p->h;
    while (cur != NULL) {
        if (cur != p->t) {
            cur = cur->next;
            delete(cur->last);
        }
        else {
            delete(cur);
            cur = NULL;
            p->h = NULL;
            p->t = NULL;
        }
    }
}

int main()
{
    poly* polynom = new poly;
    poly* polynom_2 = new poly;
    poly* polynom_3 = new poly;
    init(polynom);
    init(polynom_2);
    add(polynom, -5, 3);
    add(polynom, 2, 1);
    add(polynom, 5, 0);
    add(polynom, 5, 4);
    add(polynom, -2, 1);
    print(polynom);
    add(polynom_2, 8, 1);
    add(polynom_2, 6, 0);
    add(polynom_2, 1, 3);
    add(polynom_2, -2, 2);
    print(polynom_2);
    //polynom_3 = calculate(polynom, polynom_2,'+');
    std::cout << "first polynom: ";
    print(polynom);
    std::cout << "second polynom: ";
    print(polynom_2);
    std::cout << "result: ";
    //print(polynom_3);
    //add(polynom, polynom_2);
    //print(polynom_3);
    //delete_poly(polynom);
    //print(polynom);
    polynom_3 = calculate(polynom_2, polynom_2, '-');
    print(polynom_3);
    
    //std::cout << search(polynom, 5) << "\n";
}

