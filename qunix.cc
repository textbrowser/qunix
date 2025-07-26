#include <QtDebug>

#include "qunix-user.h"

int main(void)
{
  qDebug() << qunix_user::getgroups();
  qDebug() << qunix_user::getgroups_names();
  qDebug() << qunix_user::getlogin_r();
  return EXIT_SUCCESS;
}
