#include "qunix-string.h"
#include "qunix-unistd.h"

int main(void)
{
  auto file(qunix_file::dup(0));

  if(file && file->isOpen())
    qDebug() << QObject::tr("File (%1) is open.").arg(file->handle());
  else
    qDebug() << QObject::tr("Cannot open file.");

  qDebug() << qunix_string::strerror_r(ENOMEM);
  qDebug() << qunix_unistd::getgroups();
  qDebug() << qunix_unistd::getgroups_names();
  qDebug() << qunix_unistd::gethostname();
  qDebug() << qunix_unistd::getlogin_r();
  return EXIT_SUCCESS;
}
