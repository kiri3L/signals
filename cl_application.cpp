//
// Created by k3l on 17.05.2020.
//

#include "cl_application.h"

#include <string>

cl_application::cl_application() {
    set_object_name("root");

    set_state(1);
}

void cl_application::bild_tree_objects() {

    p_ob_1 = new cl_1();
    p_ob_1->set_object_name("ob_1");
    p_ob_1->set_parent(this);
    test_sig_1 = p_ob_1;

    p_ob_2 = new cl_2();
    p_ob_2->set_object_name("ob_2");
    p_ob_2->set_parent(p_ob_1);

    p_ob_3 = new cl_3();
    p_ob_3->set_object_name("ob_3");
    p_ob_3->set_parent(p_ob_2);
    test_sig_3 = p_ob_3;

    p_ob_3 = new cl_3;
    p_ob_3->set_object_name("ob_4");
    p_ob_3->set_parent(p_ob_2);

    p_ob_4 = new cl_4();
    p_ob_4->set_object_name("ob_5");
    p_ob_4->set_parent(p_ob_1);
    test_sig_4 = p_ob_4;

    p_ob_1 = new cl_1();
    p_ob_1->set_object_name("ob_6");
    p_ob_1->set_parent(this);

    p_ob_3 = new cl_3();
    p_ob_3->set_object_name("ob_7");
    p_ob_3->set_parent(this);

    p_ob_4 = new cl_4();
    p_ob_4->set_object_name("ob_8");
    p_ob_4->set_parent(p_ob_3);

}

int cl_application::exec_app() {
    int a = 0;
    show();
    string ss;

    test_sig_1->set_connect(SIGNAL_D(test_sig_1->signal_1), test_sig_4, HANDLER_D(test_sig_4->handler_1));
    test_sig_1->set_connect(SIGNAL_D(test_sig_1->signal_2), test_sig_4, HANDLER_D(test_sig_4->handler_2));
    test_sig_1->set_connect(SIGNAL_D(test_sig_1->signal_2), test_sig_3, HANDLER_D(test_sig_3->handler_1));
    do {
        cin >> a;
        switch (a) {
            case 1:
                cin >> ss;
                test_sig_1->emit_signal(SIGNAL_D(test_sig_1->signal_1), ss);
                break;
            case 2:
                cin >> ss;
                test_sig_1->emit_signal(SIGNAL_D(test_sig_1->signal_2), ss);
                break;
            case 3:
                cin >> ss;
                test_sig_1->emit_signal(SIGNAL_D(test_sig_1->signal_2), ss);
                break;
            default:
                break;
        }
    } while (a != 0);


    return 0;
}
