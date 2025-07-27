#include <QtDebug>

#include "qunix-unistd.h"

int main(void)
{
  qDebug() << qunix_unistd::getgroups();
  qDebug() << qunix_unistd::getgroups_names();
  qDebug() << qunix_unistd::gethostname();
  qDebug() << qunix_unistd::getlogin_r();
  return EXIT_SUCCESS;
}
