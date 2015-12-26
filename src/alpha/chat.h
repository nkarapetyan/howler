#ifndef CHAT_H
#define CHAT_H

#include "include.hpp"

class ChatWindow : public QWidget
{
    Q_OBJECT
public:
    ChatWindow(QString, QString, int);
    void readMess();
    pthread_t read_th;

public slots:
    void sendMess();

private:
    QTextEdit *m_message_box;
    QLineEdit *m_write_area;

    //helper
    int m_sockfd;
    QString m_username;
    QString m_title;
};

#endif // CHAT_H
