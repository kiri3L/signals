//
// Created by k3l on 17.05.2020.
//

#ifndef DAY17_05_CL_BASE_H
#define DAY17_05_CL_BASE_H

#include <iostream>

#include <string>

#include <vector>

#include <map>

using namespace std;
#define SIGNAL_D(signal_f) ((void(*)(string &))((&signal_f)))
#define HANDLER_D(handler_f) ((void(*)(cl_base*,string & ))(&(handler_f)))

class cl_base
{
public:
    cl_base(cl_base * p_parent = 0);
    void show();
    void set_object_name(string s_object_name);
    string get_object_name();
    void set_connect (void(*s_ignal)(string &), cl_base *p_ob_handler, void (*h_handler)(cl_base* p_pb, string &));
    void emit_signal (void(*s_ignal)(string &), string & s_command);
    void dalete_connect (void(*s_ignal)(string &),cl_base *p_ob_handler, void (*h_handler)(cl_base* p_pb, string&));
//-------------------------------------------------------------— Иерахия объектов
    void set_parent(cl_base * p_parent);
    void add_child(cl_base * p_child);
    void delete_child(string s_object_name);
    cl_base * take_child(string s_object_name);
    cl_base * get_child(string s_object_name);
//-------------------------------------------------------------— Состояние объекта
    void set_state(int i_state);
    int get_state();
    cl_base * get_object(string);
//-------------------------------------------------------------— Сервис
    void show_object_state(string);
private:
    vector<cl_base*> children; // ссылки на подчиненных объектов
    vector<cl_base*>::iterator it_child;

    string object_name; // наименование объекта
    cl_base * p_parent; // ссылка на головной объект
    int i_state; // состояние объекта

    cl_base * get_object_root();

    void show_state_next(cl_base * ob_parent);
    void show_three(cl_base * ob_parent,int level);
    struct c_sh{cl_base * p_cl_base; void (*p_handler) (cl_base* p_ob, string &);};
    multimap < void (*)(string &), c_sh*> connects;
    multimap < void(*)(string &), c_sh*> :: iterator it_connects;
    string get_path_item(string , int );

};

#endif //DAY17_05_CL_BASE_H
