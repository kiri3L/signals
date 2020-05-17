//
// Created by k3l on 17.05.2020.
//


#include "cl_base.h"
#include <string>

cl_base::cl_base(cl_base * p_parent)
{
//-------------------------------------------------------------------------
// Конструктор
//-------------------------------------------------------------------------

    set_object_name("cl_base");

    if (p_parent) {
        this->p_parent = p_parent;
        p_parent->add_child(this);
    } else {
        this->p_parent = 0;
    }
}

void cl_base::set_object_name(string s_object_name)
{
//-------------------------------------------------------------------------
// Присвоить имя объекту
//-------------------------------------------------------------------------

    object_name = s_object_name;
}

string cl_base::get_object_name()
{
//-------------------------------------------------------------------------
// Получить имя объекта
//-------------------------------------------------------------------------

    return object_name;
}

void cl_base::set_parent(cl_base * p_parent)
{
//-------------------------------------------------------------------------
// Определение ссылки на головной объект
//-------------------------------------------------------------------------

    if(p_parent)
    {
        this->p_parent = p_parent;
        p_parent->children.push_back(this);
    }
}

void cl_base::add_child(cl_base * p_child)
{
//-------------------------------------------------------------------------
// Добавление нового объекта в перечне объектов-потомков
//-------------------------------------------------------------------------

    this->children.push_back(p_child);
}

void cl_base::delete_child(string s_object_name)
{
//-------------------------------------------------------------------------
// Удаление объекта из перечня объектов-потомков
//-------------------------------------------------------------------------

    if(children.size() == 0) return;

    it_child = children.begin();

    while(it_child != children.end())
    {

        if((*it_child)->get_object_name() == s_object_name)
        {

            children.erase(it_child);
            return;
        }
        it_child++;
    }
}

cl_base * cl_base::take_child(string s_object_name)
{
//-------------------------------------------------------------------------
// Удалить подчиненый объект и вернуть ссылку
//-------------------------------------------------------------------------
    cl_base * ob_child;
//-------------------------------------------------------------------------

    ob_child = get_child(s_object_name);

    if(ob_child == 0) return 0;

    delete_child(s_object_name);

    return ob_child;
}

cl_base * cl_base::get_child(string s_object_name)
{
//-------------------------------------------------------------------------
// Получить ссылку на объект потомок по имени объекта
//-------------------------------------------------------------------------

    if(children.size() == 0) return 0;

    it_child = children.begin();

    while(it_child != children.end())
    {

        if((*it_child)->get_object_name() == s_object_name)
        {

            return (*it_child);
        }
        it_child++;
    }

    return 0;
}

void cl_base::set_state(int i_state)
{
//-------------------------------------------------------------------------
// Определить состояние объекта
//-------------------------------------------------------------------------

    this->i_state = i_state;
}

int cl_base::get_state()
{
//-------------------------------------------------------------------------
// Получить состояние объекта
//-------------------------------------------------------------------------

    return i_state;
}

void cl_base::show_object_state(string s)
{
    show_state_next((cl_base*)this);

}
void cl_base::show()
{
    int level=0;
    show_three((cl_base*)this, level);
}

// ===== private: =====
cl_base * cl_base::get_object_root()
{
//-------------------------------------------------------------------------
// Ссылка на корневой объект
//-------------------------------------------------------------------------
    cl_base * p_parent_previous; // ссылка на очередной головной объект
//-------------------------------------------------------------------------

    if(object_name == "root") return
                this;

    p_parent_previous = p_parent;

    while(p_parent_previous->p_parent)
    {

        p_parent_previous = p_parent_previous->p_parent;
    }

    return p_parent_previous;
}

void cl_base::show_state_next(cl_base * ob_parent)
{
//-------------------------------------------------------------------------
// Вывод готовности (состояния) очередного объекта в цикле обхода дерева
//-------------------------------------------------------------------------

    if(ob_parent->get_state() == 1)
    {

        cout << "The object " << ob_parent->get_object_name() << " is ready" << endl;
    }
    else
    {

        cout << "The object " << ob_parent->get_object_name() << " is not ready" << endl;
    }


    if(ob_parent->children.size() == 0) return;

    ob_parent->it_child = ob_parent->children.begin();

    while(ob_parent->it_child != ob_parent->children.end())
    {

        show_state_next((*(ob_parent->it_child)));

        ob_parent->it_child++;
    }
}
void cl_base::show_three(cl_base * ob_parent,int level)
{
//-------------------------------------------------------------------------
// Вывод очередного объекта в цикле обхода дерева
//-------------------------------------------------------------------------
    string s;
    if (level > 0) s.append(4 * level, ' ' );
    if ((ob_parent->get_object_name()) != "root")
        cout<< endl ;
    cout << s << ob_parent->get_object_name();
    if(ob_parent->children.size() == 0) return;

    ob_parent->it_child = ob_parent->children.begin();

    while(ob_parent->it_child != ob_parent->children.end())
    {

        show_three( (*(ob_parent->it_child)), (level+1));

        ob_parent->it_child++;
    }
}

string cl_base::get_path_item(string object_path, int i_level)
{
    int i_item_start, i_item_end, i_lc;
    i_lc=i_item_start = 1;
    while(i_item_start)
    {
        i_item_end = object_path.find('/', i_item_start);
        if(i_lc == i_level) return object_path.substr(i_item_start, i_item_end-i_item_start);
        i_lc++;
        i_item_start = i_item_end+1;
    }
    return "";
}

void cl_base :: set_connect (void(*p_signal)(string &), cl_base *p_ob_handler, void (*p_handler)(cl_base* p_pb, string &))
{
    void (* p_key) (string &);
    c_sh * p_value;
    if(connects.size() > 0)
    {
        it_connects = connects.begin ();
        while (it_connects != connects.end())
        {
            p_key = it_connects->first;
            p_value = it_connects-> second;
            if ((p_key) == p_signal && (p_value-> p_cl_base) == p_ob_handler && (p_value -> p_handler) == p_handler) return;
            it_connects ++;
        }
    }
    p_value = new c_sh();
    p_value -> p_cl_base = p_ob_handler;
    p_value -> p_handler = p_handler;
    connects.insert({p_signal,p_value});
}

void cl_base :: emit_signal (void(*s_ignal)(string &), string & s_command)
{
    void (*p_handler)(cl_base* p_ob, string &);
    if(connects.empty()) return;
    if(connects.count(s_ignal)==0) return;
    (s_ignal)(s_command);
    it_connects = connects.begin();
    while (it_connects != connects.end())
    {
        if((it_connects-> first) == s_ignal)
        {
            p_handler = it_connects -> second -> p_handler;
            (p_handler)(it_connects-> second -> p_cl_base, s_command);
        }
        it_connects ++;
    }
}
