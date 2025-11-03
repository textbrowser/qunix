/*
** Copyright (c) Alexis Megas.
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to endorse or promote products
**    derived from QUnix without specific prior written permission.
**
** QUNIX IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** QUNIX, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _qunix_unistd_h_
#define _qunix_unistd_h_

#include <QCoreApplication>
#include <QFile>
#include <QtDebug>

extern "C"
{
#include <fcntl.h>
#include <grp.h>
#include <unistd.h>
}

class qunix_file: public QFile
{
  Q_OBJECT

 public:
  qunix_file(const QString &name, QObject *parent):QFile(name, parent)
  {
  }

  qunix_file(void):QFile()
  {
  }

  virtual ~qunix_file()
  {
  }

  static QSharedPointer<qunix_file> dup(const int oldfd)
  {
    auto const newfd = ::dup(oldfd);

    if(newfd == -1)
      return nullptr;

    QSharedPointer<qunix_file> file(new qunix_file());

    if(file->open(newfd, QIODevice::ReadWrite, QFileDevice::AutoCloseHandle))
      return file;

    file.clear();
    return nullptr;
  }

  static QSharedPointer<qunix_file> dup2(const int oldfd, const int newfd)
  {
    auto const fd = ::dup2(oldfd, newfd);

    if(fd == -1)
      return nullptr;

    QSharedPointer<qunix_file> file(new qunix_file());

    if(file->open(fd, QIODevice::ReadWrite, QFileDevice::AutoCloseHandle))
      return file;

    file.clear();
    return nullptr;
  }
};

class qunix_unistd: public QObject
{
  Q_OBJECT

 public:
  enum class FCHOWNAT_FLAGS : int
  {
    AtEmptyPath = AT_EMPTY_PATH,
    AtSymlinkNoFollow = AT_SYMLINK_NOFOLLOW
  };

  qunix_unistd(QObject *parent):QObject(parent)
  {
  }

  qunix_unistd(void):QObject()
  {
  }

  virtual ~qunix_unistd()
  {
  }

  static QByteArray gethostname(void)
  {
    QByteArray buffer(HOST_NAME_MAX, '\0');

    if(::gethostname(buffer.data(), buffer.length()) != 0)
      buffer.clear();

    return buffer.constData();
  }

  static QByteArray getlogin_r(void)
  {
    QByteArray buffer(LOGIN_NAME_MAX, '\0');

    if(::getlogin_r(buffer.data(), buffer.length()) != 0)
      buffer.clear();

    return buffer.constData();
  }

  static QVector<QByteArray> getgroups_names(void)
  {
    auto const size = sysconf(_SC_GETGR_R_SIZE_MAX);

    if(size <= 0)
      return QVector<QByteArray> ();

    QVector<QByteArray> vector;

    foreach(auto const &i, getgroups())
      {
	QByteArray buffer(size, '\0');
	struct group *result;
	struct group group = {};

	if(::getgrgid_r(i,
			&group,
			buffer.data(),
			buffer.length(),
			&result) == 0)
	  vector << group.gr_name;
      }

    return vector;
  }

  static QVector<gid_t> getgroups(void)
  {
    auto size = ::getgroups(0, nullptr);

    if(size == -1)
      return QVector<gid_t> ();

    QScopedArrayPointer<gid_t> buffer(new gid_t[size]);

    size = ::getgroups(size, buffer.data());

    if(size == -1)
      return QVector<gid_t> ();

    QVector<gid_t> vector(size);

    for(auto i = size - 1; i >= 0; i--)
      vector[i] = buffer[i];

    return vector;
  }

  static bool chdir(const char *path)
  {
    if(path)
      return ::chdir(path) != -1;
    else
      return false;
  }

  static bool chown(const char *path, const uid_t owner, const gid_t group)
  {
    if(path)
      return ::chown(path, owner, group) != -1;
    else
      return false;
  }

  static bool close(const int fd)
  {
    return ::close(fd) != -1;
  }

  static bool fchdir(const int fd)
  {
    return ::fchdir(fd) != -1;
  }

  static bool fchown(const int fd, const uid_t owner, const gid_t group)
  {
    return ::fchown(fd, owner, group) != -1;
  }

  static bool fchownat(const int dirfd,
		       const char *path,
		       const uid_t owner,
		       const gid_t group,
		       const FCHOWNAT_FLAGS flags)
  {
    /*
    ** Flags is a bitwise-or of 0 or more of
    ** AT_EMPTY_PATH, AT_SYMLINK_NOFOLLOW.
    */

    if(path)
      return ::fchownat
	(dirfd, path, owner, group, static_cast<int> (flags)) != -1;
    else
      return false;
  }

  static bool fdatasync(const int fd)
  {
    return ::fdatasync(fd) != -1;
  }

  static bool fsync(const int fd)
  {
    return ::fsync(fd) != -1;
  }

  static bool lchown(const char *path, const uid_t owner, const gid_t group)
  {
    if(path)
      return ::lchown(path, owner, group) != -1;
    else
      return false;
  }

  static bool setegid(const gid_t egid)
  {
    return ::setegid(egid) != -1;
  }

  static bool seteuid(const uid_t euid)
  {
    return ::seteuid(euid) != -1;
  }

  static bool setgid(const gid_t gid)
  {
    return ::setgid(gid) != -1;
  }

  static bool sethostid(const long hostid)
  {
    return ::sethostid(hostid) != -1;
  }

  static bool sethostname(const QByteArray &name)
  {
    return ::sethostname(name.constData(), name.length()) != -1;
  }

  static bool setregid(const gid_t rgid, const gid_t egid)
  {
    return ::setregid(rgid, egid) != -1;
  }

  static bool setreuid(const uid_t ruid, const uid_t euid)
  {
    return ::setreuid(ruid, euid) != -1;
  }

  static bool setuid(const uid_t uid)
  {
    return ::setuid(uid) != -1;
  }

  static bool swab(const QByteArray &src, QByteArray &dst, const ssize_t n)
  {
    if(dst.length() < n ||
       n <= 0 ||
       n > src.length())
      return false;

    ::swab(src.data(), dst.data(), n);
    return true;
  }

  static gid_t getegid(void)
  {
    return ::getegid();
  }

  static gid_t getgid(void)
  {
    return ::getgid();
  }

  static int pause(void)
  {
    return ::pause();
  }

  static long gethostid(void)
  {
    return ::gethostid();
  }

  static long sysconf(const int name)
  {
    return ::sysconf(name);
  }

  static uid_t geteuid(void)
  {
    return ::geteuid();
  }

  static uid_t getuid(void)
  {
    return ::getuid();
  }

  static unsigned int alarm(const unsigned int seconds)
  {
    return ::alarm(seconds);
  }
};

inline qunix_unistd::FCHOWNAT_FLAGS operator |
(qunix_unistd::FCHOWNAT_FLAGS a, qunix_unistd::FCHOWNAT_FLAGS b)
{
  return qunix_unistd::FCHOWNAT_FLAGS
    (static_cast<int> (a) | static_cast<int> (b));
}

#endif
