#include "qunix-user.h"

int main(void)
{
  qDebug() << qunix_user::getgroups();
  qDebug() << qunix_user::getlogin();
  return EXIT_SUCCESS;
}
