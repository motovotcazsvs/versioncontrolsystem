#include "control.h"
#include <QDebug>

#define COUNTELEMENTS 15
#define COUNTLISTREPOSITORIES 15

Control::Control(QObject *parent) : QObject(parent)
{
    list_commands << "sync";
    list_commands << "path";
    list_commands << "init";
    list_commands << "clone";
    list_commands << "add .";
    list_commands << "commit -m \"\"";
    list_commands << "push";
    list_commands << "push auto";
    list_commands << "pull";
    list_commands << "pull auto";
    list_commands << "branch";
    list_commands << "marge";

    enter_element = 0;
    current_element_repositories = 0;

}

bool Control::commandOrRepository(QString element)
{
    foreach (QString str, list_commands) {
        if(str == element) return false;
    }
    return true;
}

void Control::setControlUp()
{
    int count_elements = vector_elements.count();
    //если крайний элемент меню это последний элемент в буфере
    if(enter_element >= (count_elements - 1 - 3)){
        requestGetRepositories();//то сделать запрос на прием 100 репозиториив
        slotGetRepositoriesUP();
        return;
    }

    //если это последний элемент в буфере и текущий элемент менше 100 и больше количества команд
    getPositionElement(++enter_element, count_elements);//то
    setPositionElements();

}

void Control::setControlDown()
{
    qDebug() << "setControlDown()start enter_element" << enter_element << enter_element + 3 << enter_element - 3;

    int count_elements = vector_elements.count();
    //если крайний элемент меню это первый элемент в буфере
    if(enter_element == 3){//
        requestGetRepositories();//то сделать запрос на прием 100 репозиториив
        slotGetRepositoriesDOWN();
        return;
    }

    getPositionElement(--enter_element, vector_elements.count());
    setPositionElements();

    qDebug() << "setControlDown()finish enter_element" << enter_element << enter_element + 3 << enter_element - 3;
}

void Control::setPositionElements()
{
//выводим элементы в меню
//сначала присваеваем строку выбраном элементу  от выбраной строки которая раньше была,
//потом поочередно трьом элементам вверху меню, от елементов с буфера с теми же позициями
//и потом поочередно трьом элементам ниже выбраного элемента, от елементов с буфера с теми же позициями
    int count_commands = vector_elements.count();
    int position = enter_element;
    QString str4_enter = vector_elements[position];
    QString str3 = vector_elements[getPositionElement(--position, count_commands)];//буфер принимает от функции позицию,...
    QString str2 = vector_elements[getPositionElement(--position, count_commands)];//...а в аргументе по ссылке её редактирует...
    QString str1 = vector_elements[getPositionElement(--position, count_commands)];//...для прохода по всех элементах меню
    position = enter_element;
    QString str5 = vector_elements[getPositionElement(++position, count_commands)];
    QString str6 = vector_elements[getPositionElement(++position, count_commands)];
    QString str7 = vector_elements[getPositionElement(++position, count_commands)];
    emit this->changeShowString(str1, str2, str3, str4_enter, str5, str6, str7);
}

//
void Control::started()
{
    requestGetRepositories();//отправляем запрос на прием репозиториив

    //добавляем в буфер вывода команды если не пролистали 100 элементов
    if(current_element_repositories < COUNTELEMENTS){// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if(vector_elements.isEmpty() == false) return;//
        setBufferElements(list_commands, 0);//записываем в буфер команды
    }

    setPositionElements();//выводим элементы в меню
    slotGetRepositories();
}

//
void Control::slotGetRepositories()
{
    list_repositories.clear();
    //list_repositories << "analyzerGL10";
    //list_repositories << "versioncontrolsystem";
    list_repositories << "GL01";
    list_repositories << "version02";
    list_repositories << "GL03";
    list_repositories << "version04";
    list_repositories << "GL05";
    list_repositories << "version06";
    list_repositories << "GL07";
    list_repositories << "version08";
    list_repositories << "GL09";
    list_repositories << "version010";
    list_repositories << "GL011";
    list_repositories << "version012";
    list_repositories << "version013";
    list_repositories << "GL014";
    list_repositories << "version015";

    //если буфер пуст то сначала загрузить в него команды а потом репозитории
    if(vector_elements.isEmpty()){
        setBufferElements(list_commands, 0);
    }
    setBufferElements(list_repositories, 0);
    setPositionElements();
}

//
void Control::slotGetRepositoriesUP()
{
    list_repositories.clear();//очищаем список для добавления новых репозиториив
    list_repositories << "GL1";
    list_repositories << "version2";
    list_repositories << "GL3";
    list_repositories << "version4";
    list_repositories << "GL5";
    list_repositories << "version6";
    list_repositories << "GL7";
    list_repositories << "version8";
    list_repositories << "GL9";
    list_repositories << "version10";
    list_repositories << "GL11";
    list_repositories << "version12";
    list_repositories << "version13";
    list_repositories << "GL14";
    list_repositories << "version15";

    getRepositoriesUPDOWN(0);

    setControlUp();//возвращаемся для перехода на следующи выбраный элемент
}

void Control::slotGetRepositoriesDOWN()
{
    list_repositories.clear();//очищаем список для добавления новых репозиториив
    list_repositories << "version15";
    list_repositories << "GL14";
    list_repositories << "version13";
    list_repositories << "version12";
    list_repositories << "GL11";
    list_repositories << "version10";
    list_repositories << "GL9";
    list_repositories << "version8";
    list_repositories << "GL7";
    list_repositories << "version6";
    list_repositories << "GL5";
    list_repositories << "version4";
    list_repositories << "GL3";
    list_repositories << "version2";
    list_repositories << "GL1";

    getRepositoriesUPDOWN(COUNTLISTREPOSITORIES);

    setControlDown();//возвращаемся для перехода на следующи выбраный элемент
}

//функция проверяет если позиция менше 0 то переходим на останний элемент, а если больше останнего то переходим на первый элемент
//возвращает позицию(позиция возвращается двумя способами: через возврат функции и по ссылку в аргументе)
//уже провереную и отредактированую
int Control::getPositionElement(int &current_position, int count_position)
{
    if(current_position < 0) current_position = count_position - 1;
    else if(current_position >= count_position) current_position = 0;
    return current_position;
}

void Control::setBufferElements(QStringList &listElements, int position_add_element)
{
//добавляем в буфер элементы
    if(position_add_element == 0){
        foreach(QString element, listElements) {
            vector_elements << element;
        }
    }
    else if(position_add_element == COUNTLISTREPOSITORIES){
        foreach(QString element, listElements) {
            vector_elements.prepend(element);
        }
    }
}

void Control::requestGetRepositories()
{
    //просим в сервера 100 элементов
}

//функция для поддержевания размера буфера не больше 200 элементов
void Control::clearBeginningBuffer(int start_remove)
{
    qDebug() << "clearBeginningBuffer()start";
    for(int i = 0; i < vector_elements.count(); i++) qDebug() << vector_elements[i];

    int count_elements = vector_elements.count();
    if(count_elements < COUNTLISTREPOSITORIES + list_commands.count()) return;//если мало элементов то не очищать буфер
    vector_elements.remove(start_remove, count_elements - COUNTLISTREPOSITORIES);//оставляем 100 элементов

    //выбраный элемент меняет номер позиции в буфере, изза очистки
    if(start_remove == 0){//если вперед листаем
        enter_element -= (count_elements - COUNTLISTREPOSITORIES);
    }
    else if(start_remove == COUNTLISTREPOSITORIES){//если назад листаем
        enter_element += (count_elements - COUNTLISTREPOSITORIES);// !!!!!!!!!!!!!!!!!!!
    }

    qDebug() << "clearBeginningBuffer()finish";
    for(int i = 0; i < vector_elements.count(); i++) qDebug() << vector_elements[i];

}

void Control::getRepositoriesUPDOWN(int up_or_down)
{
    //если пришли репозитории то увеличить текущий элемент репозиториив на количество принятых репозиториив
    //иначе возвращаемся в начало списка элементов, а именно к командам
    clearBeginningBuffer(up_or_down);//оставляем в буфере 100 последних элементов
    bool no_new_repositories = false;//нету новых репозиториив
    if(no_new_repositories){
        current_element_repositories = 0;
        if(list_repositories.isEmpty() == false) setBufferElements(list_commands, up_or_down);//добавляем команды если их нету у буфере
    }

    setBufferElements(list_repositories, up_or_down);//добавляем начальные 100 элементов
}




