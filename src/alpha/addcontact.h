#ifndef ADDCONTACT_H
#define ADDCONTACT_H

#include "include.hpp"
#include "chat.h"

class AddContactWindow : public QWidget
{
        Q_OBJECT

   public:
        AddContactWindow(int ,QString, QWidget *parent = 0);
        void ConnectAcception();

   public slots:
        void run_client_slot();
	void serv_rw_slot();
	
   signals:
	void serv_rw_signal();

   private:
        QLineEdit *m_host_address;
        QLineEdit *m_port_number;
        ChatWindow *m_chat;

        //helper
        QString m_username;
        QString m_title;
        int m_sock_serv;
        int m_newsock_cli;
};

#endif // ADDCONTACT_H
