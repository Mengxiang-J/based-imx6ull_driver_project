#include <QThread>
#include <QDebug>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <poll.h>
#include <sys/ioctl.h>

#define CMD_TRIG  100

class DistanceWorker : public QThread
{
    Q_OBJECT

public:
    explicit DistanceWorker(QObject *parent = nullptr) : QThread(parent), m_stop(false) {}

    void stop() {
        m_stop = true;
    }

signals:
    void distanceUpdated(int value);
    void errorOccurred(const QString &message);

protected:
    void run() override {
        int val;
        struct pollfd fds[1];

        int fd = open("/dev/sr04", O_RDWR);
        if (fd < 0) {
            emit errorOccurred("Failed to open device");
            return;
        }

        while (!m_stop) {
            ioctl(fd, CMD_TRIG);
            qDebug() << "I am going to read distance:";

            fds[0].fd = fd;
            fds[0].events = POLLIN;
            int value;
            if (1 == poll(fds, 1, 5000)) {
                if (read(fd, &val, 4) == 4) {
                    value = val * 17 / 1000000;
                    emit distanceUpdated(value);
                } else {
                    emit errorOccurred("Error reading distance");
                }
            } else {
                emit errorOccurred("Poll timeout/error");
            }

            sleep(1);
        }

        close(fd);
    }

private:
    bool m_stop;
};
