#include "addcontact.h"

AddContactWindow::AddContactWindow(int p, QString n, QWidget *parent)
: QWidget(parent), m_username(n),m_sock_serv(p)
{
	QLabel *ha = new QLabel(QString("Host Address:"),0,0);
	QLabel *dummy = new QLabel(QString("<p></p>"));
	QLabel *un = new QLabel(QString("Port number:"),0,0);
   	QPushButton *add_button =new QPushButton("Add");


	setFixedSize(300, 200);
	this->setWindowTitle(QString("Add contact"));

	m_host_address = new QLineEdit();
	m_port_number = new QLineEdit();

	connect(add_button, SIGNAL(pressed()), this, SLOT(run_client_slot()));
	connect(this, SIGNAL(serv_rw_signal()), this, SLOT(serv_rw_slot()));

	QVBoxLayout *lay = new QVBoxLayout;
	lay->addWidget(ha);
	lay->addWidget(m_host_address);
	lay->addWidget(dummy);
	lay->addWidget(un);
	lay->addWidget(m_port_number);
	lay->addWidget(add_button);
	setLayout(lay);
}

void AddContactWindow::ConnectAcception()
{
	char buf[80];
	memset(buf, 0, 80);
	while(true){
		sockaddr_in cli_addr;
		socklen_t clilen = sizeof(cli_addr);

		//create new socket for current client
		m_newsock_cli = accept( m_sock_serv, (sockaddr*)&cli_addr, &clilen);
		memset(buf, 0, 80);
 		int n = write(m_newsock_cli, m_username.toAscii().data(), m_username.length());
		n = read(m_newsock_cli,buf, 80);
	        m_title = QString(buf);
		emit this->serv_rw_signal();
	}
}
void AddContactWindow::serv_rw_slot()
{
	m_chat = new ChatWindow(m_title, m_username, m_newsock_cli);
	m_chat->show();
}

void AddContactWindow::run_client_slot()
{
	if (m_host_address->text() == "" || m_port_number->text() == ""){
		exit(1);
	}

	// Creates new socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		exit(1);
	}

	hostent* server = gethostbyname(m_host_address->text().toAscii().data());

	if (server == NULL){
		exit(1);
	}


	sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;

	bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr, server->h_length);

	int portno = atoi(m_port_number->text().toAscii().data());
	serv_addr.sin_port = htons(portno);
	if(::connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
		exit(1);
	}

	char buf[80];
        memset(buf, 0, 80);
        int n = write(sockfd, m_username.toAscii().data(), m_username.length());
        n = read(sockfd,buf,80);
	m_title = QString(buf);

	m_chat = new ChatWindow(m_title, m_username, sockfd);
	m_chat->show();
}
