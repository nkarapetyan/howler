#ifndef HEAD_H
#define HEAD_H

#include "include.hpp"
#include "addcontact.h"

class LoginWindow : public QWidget
{
        Q_OBJECT

    public:
        LoginWindow(QWidget *parent = 0);


    public slots:
        void server_run_slot();

    private:
        AddContactWindow * m_add_cont;
        QLineEdit *m_my_port;
	QLineEdit *m_user_name;
};

#endif // HEAD_H
