#include "chat.h"

void* helper_read(void *);
void smile(QString *);

ChatWindow::ChatWindow(QString t,QString qs,int s):m_sockfd(s), m_username(qs), m_title(t)
{
    this->setWindowTitle(t);
    QPushButton *send_message = new QPushButton(QString("Send Message"));
    QPushButton *send_file = new QPushButton(QString("Send File"));

    setFixedSize(250, 400);
    m_write_area = new QLineEdit();
    m_message_box = new QTextEdit();
    m_message_box->setReadOnly(true);
   // m_write_area->setStyleSheet(QString("height:50px"));
    m_message_box->setStyleSheet(QString("height:400px"));


    connect(send_message, SIGNAL(pressed()), this, SLOT(sendMess()));
    connect(m_write_area, SIGNAL(returnPressed()), this, SLOT(sendMess()));

    QVBoxLayout *lay = new QVBoxLayout();
    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addWidget(send_message);
    buttons->addWidget(send_file);
    lay->addWidget(m_message_box);
    lay->addLayout(buttons);
    lay->addWidget(m_write_area);

    setLayout(lay);

    pthread_create(&read_th, NULL, &helper_read, this);
}


void ChatWindow::sendMess()
{
    if(m_write_area->text() != "")
    {
         int n = write(m_sockfd, ("<b>"+m_username+QString(":</b> ")+m_write_area->text()).toAscii().data(), ("<b>"+m_username+QString(":</b> ")+m_write_area->text()).length());

         if(n < 0){
             exit(1);
         }
       
         QString msg = m_write_area->text();
	 smile(&msg);
         m_message_box->append(QString("<b>me:</b> ") + msg);
         m_write_area->clear();
    }

}

void ChatWindow::readMess()
{
    int n = 1; 
    char buffer[255];
    while(n > 0 && m_sockfd > 0){
        memset(buffer,0, 255);
        n = read(m_sockfd, buffer, 255);
 	QString msg = QString(buffer);
       	smile(&msg);
        m_message_box->append(msg);
    }
}

void* helper_read(void * obj)
{
    ChatWindow * ob = reinterpret_cast<ChatWindow *>(obj);
    ob->readMess();
    return (void *)1;
}

void smile(QString* msg)
{
        msg->replace(QString(":)"), QString("<img src='./smiley/s1.gif' />"));
        msg->replace(QString(":("), QString("<img src='./smiley/s2.gif' />"));
        msg->replace(QString(":P"), QString("<img src='./smiley/s3.gif' />"));
        msg->replace(QString(":D"), QString("<img src='./smiley/s4.png' />"));
        msg->replace(QString(":*"), QString("<img src='./smiley/s5.png' />"));
}
