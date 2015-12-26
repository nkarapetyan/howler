#include "login.h"

void *helper_run(void*);

LoginWindow::LoginWindow(QWidget *parent)
: QWidget(parent)
{
    this->setWindowTitle(QString("Login"));

    setFixedSize(200, 180);
    QPushButton *login = new QPushButton(tr("Login"));
    login->setFont(QFont("Times", 14, QFont::Bold));

    m_my_port = new QLineEdit();
    m_user_name = new QLineEdit();	

    connect(login, SIGNAL(clicked()), this, SLOT(server_run_slot()));
    connect(login, SIGNAL(clicked()), this, SLOT(hide()));

    QLabel *un = new QLabel(QString("Username"),0,0);	
    QLabel *pn = new QLabel(QString("Your port number:"),0,0);

    QFormLayout *lay1 = new QFormLayout();
    lay1->addWidget(un);
    lay1->addWidget(m_user_name);
    lay1->addWidget(pn);
    lay1->addWidget(m_my_port);
    lay1->addWidget(login);
    setLayout(lay1);
}

void LoginWindow::server_run_slot()
{
    if(m_my_port->text() == ""){
            exit(1);
    }
    int portno = atoi(m_my_port->text().toAscii().data());
    if(portno == 0){
        exit(1);
    }

    int sock_serv = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_serv < 0){
            exit(1);
    }

    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if( bind(sock_serv, (sockaddr*)&serv_addr, sizeof(serv_addr) ) < 0 ){
            exit(1);
    }
    listen(sock_serv, 12);

    m_add_cont = new AddContactWindow(sock_serv, m_user_name->text());
    m_add_cont->show();

    pthread_t serv;
    pthread_create(&serv, NULL, &helper_run, m_add_cont);

}


void * helper_run(void * obj)
{
    AddContactWindow * ob = reinterpret_cast<AddContactWindow *>(obj);
    ob->ConnectAcception();
    return (void*)1;
}

