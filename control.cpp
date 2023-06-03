#include "control.h"
#include <QDebug>


#define COUNTELEMENTS 15
#define COUNTLISTREPOSITORIES 15
#define delimiter '`'//розделитель

QString parsingNumDelimiter(QString, int);//парсим данные до разделителя(не включая код действия) по счету от 1 и тд

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

    obj_tcpip = new tcpipastm;
    QObject::connect(obj_tcpip, &tcpipastm::signalReceivedRepositories, this, &Control::slotGetRepositories);
    QObject::connect(obj_tcpip, &tcpipastm::signalReceivedRepositoriesUP, this, &Control::slotGetRepositoriesUP);
    QObject::connect(obj_tcpip, &tcpipastm::signalReceivedRepositoriesDOWN, this, &Control::slotGetRepositoriesDOWN);


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
        QString str_frame("0303");
        str_frame.append(QString::number(current_element_repositories));
        str_frame.append("`");
        str_frame.append(QString::number(COUNTLISTREPOSITORIES));
        str_frame.append("`");
        requestGetRepositories(str_frame);//то сделать запрос на прием 100 репозиториив
        qDebug() << "отправляем запрос на получение репозиториив идя ВВЕРХ";
        return;
    }

    qDebug() << "setControlUp()" << enter_element;
    for(int i = 0; i < vector_elements.count(); i++) qDebug() << vector_elements[i];
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
        QString str_frame("0305");
        str_frame.append(QString::number(current_element_repositories));
        str_frame.append("`");
        str_frame.append(QString::number(COUNTLISTREPOSITORIES));
        str_frame.append("`");
        requestGetRepositories(str_frame);//то сделать запрос на прием 100 репозиториив
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
    QString str_frame;

    if(current_element_repositories == 0 && enter_element < 3){
        str_frame.append("0307");
        str_frame.append(QString::number(current_element_repositories));
        str_frame.append("`");
        str_frame.append(QString::number(COUNTLISTREPOSITORIES));
    }
    else if(current_element_repositories == 0 && enter_element >= 3){
        str_frame.append("0301");
        str_frame.append(QString::number(current_element_repositories));
        str_frame.append("`");
        str_frame.append(QString::number(COUNTLISTREPOSITORIES));


    }
    else if(current_element_repositories >= COUNTLISTREPOSITORIES){
        str_frame.append("0301");
        str_frame.append(QString::number(current_element_repositories));
        str_frame.append("`");
        str_frame.append(QString::number(COUNTLISTREPOSITORIES + COUNTLISTREPOSITORIES));
    }

    str_frame.append("`");    
    requestGetRepositories(str_frame);//отправляем запрос на прием репозиториив

    //добавляем в буфер вывода команды, что бы для начала было хоть чтото
    if(current_element_repositories < COUNTLISTREPOSITORIES){// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if(vector_elements.isEmpty() == false) return;//
        setBufferElements(list_commands, 0);//записываем в конец буфера команды
    }


    setPositionElements();//выводим элементы в меню
}

//
void Control::slotGetRepositories()
{
    list_repositories.clear();
    QString dat_received = obj_tcpip->getDataReceived();
    dat_received = dat_received.mid(4);
    QString str_count_repositories = parsingNumDelimiter(dat_received, 1);
    int count_repositories = str_count_repositories.toInt();

    if(enter_element >= 3){
        current_element_repositories += count_repositories;
    }

    for(int i = 0; i < count_repositories; i++){
        QString rep = parsingNumDelimiter(dat_received, i + 2);
        list_repositories << rep;
    }

    //если в буфер не успели загрузится команды до ответа сервера то загрузить их
    if(vector_elements.isEmpty()){
        setBufferElements(list_commands, 0);
    }

    if(enter_element < 3 && current_element_repositories < COUNTLISTREPOSITORIES){
        setBufferElements(list_repositories, COUNTLISTREPOSITORIES);
        enter_element += count_repositories;
    }
    else if(enter_element >= 3 && current_element_repositories < COUNTLISTREPOSITORIES){// !!!!!!!!!!!!!!
        setBufferElements(list_repositories, 0);
    }
    else if(current_element_repositories >= COUNTLISTREPOSITORIES){
        vector_elements.clear();//очищяем команды
        setBufferElements(list_repositories, 0);
    }

    setPositionElements();
}

//
void Control::slotGetRepositoriesUP()
{
    qDebug() << "прииняли репозитории по управлению вверх!";
    list_repositories.clear();//очищаем список для добавления новых репозиториив
    QString dat_received = obj_tcpip->getDataReceived();
    dat_received = dat_received.mid(4);
    QString str_count_repositories = parsingNumDelimiter(dat_received, 1);
    int count_repositories = str_count_repositories.toInt();
    if(count_repositories == 0){
        //current_element_repositories = 0;
        qDebug() << "больше нету элементов вверху";
    }
    else current_element_repositories += count_repositories;
    for(int i = 0; i < count_repositories; i++){
        QString rep = parsingNumDelimiter(dat_received, i + 2);
        list_repositories << rep;
    }

    getRepositoriesUPDOWN(0, count_repositories);
    setControlUp();//возвращаемся для перехода на следующи выбраный элемент
}

void Control::slotGetRepositoriesDOWN()
{
    list_repositories.clear();//очищаем список для добавления новых репозиториив
    QString dat_received = obj_tcpip->getDataReceived();
    dat_received = dat_received.mid(4);
    QString str_count_repositories = parsingNumDelimiter(dat_received, 1);
    int count_repositories = str_count_repositories.toInt();
    current_element_repositories -= count_repositories;
    for(int i = 0; i < count_repositories; i++){
        QString rep = parsingNumDelimiter(dat_received, i + 2);
        list_repositories << rep;
    }
    getRepositoriesUPDOWN(COUNTLISTREPOSITORIES, count_repositories);
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

void Control::requestGetRepositories(QString frame)
{
    //просим в сервера 100 элементов
    QByteArray byte;
    byte.append(frame);
    obj_tcpip->writeFrame(byte);
}

//функция для поддержевания размера буфера не больше 200 элементов
void Control::clearBeginningBuffer(int start_remove)
{
    qDebug() << "clearBeginningBuffer()start";
    for(int i = 0; i < vector_elements.count(); i++) qDebug() << vector_elements[i];

    int count_elements = vector_elements.count();
    if(count_elements < COUNTLISTREPOSITORIES + list_commands.count()){
        if(count_elements <= COUNTLISTREPOSITORIES) return;//если мало элементов то не очищать буфер
    }
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

void Control::getRepositoriesUPDOWN(int up_or_down, int count_new_repositories)
{
    //если пришли репозитории то увеличить текущий элемент репозиториив на количество принятых репозиториив
    //иначе возвращаемся в начало списка элементов, а именно к командам
    clearBeginningBuffer(up_or_down);//оставляем в буфере 100 последних элементов

    bool no_new_repositories = false;//есть новые репозитории
    if(count_new_repositories == 0) no_new_repositories = true;//если нету новых репозиториив

    if(no_new_repositories){
        qDebug() << "getRepositoriesUPDOWN() нету новых репозиториив";
        current_element_repositories = 0;
        setBufferElements(list_commands, up_or_down);//добавляем команды если их нету у буфере

        return;// !!!!!!!!
    }

    setBufferElements(list_repositories, up_or_down);//добавляем начальные 100 элементов
}

QString parsingNumDelimiter(QString str, int num)//парсим данные до разделителя(не включая код действия) по счету от 1 и тд
{
    //"2`15.89`7.5`";
    int i = 1;
    QString temp_str;
    foreach (QChar s, str){
        if(s == delimiter && i == num){
            break;
        }
        else if(s == delimiter){
            i++;
            temp_str = "";
        }
        else temp_str += s;
    }
    return temp_str;
}

