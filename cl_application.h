//
// Created by k3l on 17.05.2020.
//

#ifndef DAY17_05_CL_APPLICATION_H
#define DAY17_05_CL_APPLICATION_H

#include "cl_3.h"

#include "cl_2.h"

#include "cl_4.h"

#include "cl_1.h"

//using namespace std;

class cl_application: public cl_base
{
public: cl_application();
// ~cl_application ( );

    void bild_tree_objects();
    int exec_app();
    void signal_1(string & ss){};
    void signal_2(string & ss){};
private: cl_base * p_ob;
    cl_3 * p_ob_3;
    cl_4 * p_ob_4;
    cl_2 * p_ob_2;
    cl_1 * p_ob_1;
    cl_1 * test_sig_1;
    cl_3 * test_sig_3;
    cl_4 * test_sig_4;
};


#endif //DAY17_05_CL_APPLICATION_H
