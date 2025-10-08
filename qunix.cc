#include "qunix-string.h"
#include "qunix-unistd.h"

int main(void)
{
  auto file(qunix_file::dup(0));

  if(file && file->isOpen())
    qDebug() << QObject::tr("File (%1) is now open.").arg(file->handle());
  else
    qDebug() << QObject::tr("Cannot open file.");

  qDebug() << "ENOMEM:" << qunix_string::strerror_r(ENOMEM);
  qDebug() << qunix_unistd::getgroups();
  qDebug() << qunix_unistd::getgroups_names();
  qDebug() << qunix_unistd::gethostname();
  qDebug() << qunix_unistd::getlogin_r();

  QByteArray a(10, '\0');

  a[0] = 0x00;
  a[1] = 0x01;
  a[2] = 0x02;
  a[3] = 0x03;
  a[4] = 0x04;

  QByteArray b(5, '\0');

  qDebug() << "swab:" << qunix_unistd::swab(a, b, 5);
  qDebug() << b;
  return EXIT_SUCCESS;
}
